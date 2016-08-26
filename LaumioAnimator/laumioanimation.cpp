#include "laumioanimation.h"
#include <QFile>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QQmlEngine>

#include "animations/constantcoloranimation.h"
#include "animations/pulsingcoloranimation.h"
#include "animations/progressivecoloranimation.h"
#include "animations/boundedpulsingcoloranimation.h"
#include "animations/mix2colorsanimation.h"

std::map <QString, std::unique_ptr <Animation> (*)()> LaumioAnimation::sFactories {
    {"ConstantColor", &ConstantColorAnimation::factory},
    {"PulsingColor", &PulsingColorAnimation::factory},
    {"ProgressiveColor", &ProgressiveColorAnimation::factory},
    {"BoundedPulsingColor", &BoundedPulsingColorAnimation::factory},
    {"Mix2Colors", &Mix2ColorsAnimation::factory},
};

LaumioAnimation::LaumioAnimation(QObject * parent) : QAbstractListModel(parent) {
    m_play_timer.setSingleShot(false);
    m_play_timer.setInterval(100);
    QObject::connect(&m_play_timer, &QTimer::timeout, this, &LaumioAnimation::playContinue);
}

int LaumioAnimation::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_laumios.size();
}

QVariant LaumioAnimation::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= (long) m_laumios.size())
        return QVariant();
    switch (role) {
    case LaumioRole:
        return qVariantFromValue(m_laumios.at(index.row()).laumio.get());
    case AnimationsRole:{
        QList <QObject*> ret;
        auto & anims = m_laumios.at(index.row()).animations;
        int size = anims.size();
        for(auto i = 0; i < size; i++)
            ret.append(anims[i]);
        return qVariantFromValue(ret);
    }
    default:
        return QVariant();
    }
}

QHash <int, QByteArray> LaumioAnimation::roleNames() const {
    QHash <int, QByteArray> ret;
    ret[LaumioRole] = "laumio";
    ret[AnimationsRole] = "animations";
    return ret;
}

void LaumioAnimation::newLaumio() {
    beginInsertRows(QModelIndex(), m_laumios.size(), m_laumios.size());
    m_laumios.push_back({std::move(std::unique_ptr<Laumio>(new Laumio)), {}});
    endInsertRows();
}

void LaumioAnimation::deleteLaumio(int index) {
    if (index < 0 || index > (long) m_laumios.size())
        return;
    beginRemoveRows(QModelIndex(), index, index);
    auto it = m_laumios.begin();
    std::advance(it, index);
    m_laumios.erase(it);
    endRemoveRows();
}

QStringList LaumioAnimation::factoriesNames() {
    QStringList ret;
    for (auto imap: sFactories)
        ret.append(imap.first);
    return ret;
}

Animation* LaumioAnimation::newAnimation(int idx, QString factoryName) {
    auto itFactory = sFactories.find(factoryName);
    if (itFactory != std::end(sFactories)) {
        auto anim = (*itFactory->second)();
        auto * animptr = anim.get();
        m_animationsStorage.push_back(std::move(anim));
        m_laumios[idx].animations.push_back(animptr);
        dataChanged(index(idx), index(idx), {AnimationsRole});
        QQmlEngine::setObjectOwnership(animptr, QQmlEngine::CppOwnership);
        return animptr;
    }
    return nullptr;
}

void LaumioAnimation::deleteAnimation(int laumioNb, int idx) {
    if (LaumioAnimation::playing())
        return;
    if (laumioNb < 0 || laumioNb > (long) m_laumios.size())
        return;
    auto itAnim = std::find_if(m_animationsStorage.begin(), m_animationsStorage.end(), [&](std::unique_ptr<Animation>& ptr){
        return ptr.get() == m_laumios[laumioNb].animations[idx];
    });
    auto it = m_laumios[laumioNb].animations.begin();
    if(itAnim == m_animationsStorage.end() || it == m_laumios[laumioNb].animations.end())
        return;
    std::advance(it, idx);
    m_laumios[laumioNb].animations.erase(it);
    m_animationsStorage.erase(itAnim);
    dataChanged(index(laumioNb), index(laumioNb), {AnimationsRole});
}

void LaumioAnimation::loadFromFile(QString filename) {
    beginResetModel();
    m_laumios.clear();
    endResetModel();

    QFile f(QUrl(filename).toLocalFile());
    if (!f.open(QFile::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    QJsonObject rootobj = doc.object();
    if (rootobj.contains("audioSource"))
            set_audioSource(rootobj["audioSource"].toString());

    QJsonArray array = rootobj["animations"].toArray();
    beginInsertRows(QModelIndex(), 0, array.size()-1);
    for (auto elem : array) {
        auto channel = elem.toObject();

        auto aptr = std::unique_ptr<Laumio>(new Laumio);
        auto * ptr = aptr.get();
        m_laumios.push_back({std::move(aptr), {}});
        auto obj = channel["laumio"].toObject();
        ptr->loadFromJSON(obj);

        QJsonArray anims = channel["anims"].toArray();
        for (auto anidesc : anims) {
            auto ani = anidesc.toObject();
            if (ani.contains("type")) {
                auto itFactory = sFactories.find(ani["type"].toString());
                if (itFactory != std::end(sFactories)) {
                    auto anim = (*itFactory->second)();
                    auto * animptr = anim.get();
                    m_animationsStorage.push_back(std::move(anim));
                    animptr->loadFromJSON(ani);
                    m_laumios.back().animations.push_back(animptr);
                }
            }
        }
    }
    endInsertRows();
}

void LaumioAnimation::saveToFile(QString filename) {
    QJsonDocument doc;
    QJsonArray array;
    for (auto & apLaumio : m_laumios) {
        QJsonObject channel;
        QJsonObject obj;
        apLaumio.laumio.get()->saveToJSON(obj);
        channel["laumio"] = obj;
        QJsonArray animarray;
        for (auto anipair : apLaumio.animations) {
            QJsonObject obj;
            anipair->saveToJSON(obj);
            obj["type"] = anipair->name();
            animarray.append(obj);
        }
        channel["anims"] = animarray;
        array.append(channel);
    }
    QJsonObject rootobj;
    rootobj["audioSource"] = audioSource();
    rootobj["animations"] = array;
    doc.setObject(rootobj);

    QFile f(QUrl(filename).toLocalFile());
    if (!f.open(QFile::ReadWrite))
        return;
    f.write(doc.toJson());
}

int LaumioAnimation::priorityTest(PlayAnim p1, PlayAnim p2){
    int ret = 0;
    if(p1.laumio == p2.laumio){
        ret = 1;
        if(p1.anim->priority() > p2.anim->priority())
            ret = 2;
    }
    return ret;
}

void LaumioAnimation::play(int ms) {
    std::chrono::milliseconds delay(ms);
    set_playing(true);
    m_play_playing.clear();
    m_play_toBePlayed.clear();
    m_play_toBeDeleted.clear();
    if(ms >= 0) {
        m_play_start = std::chrono::system_clock::now() - delay;
    } else {
        m_play_start += std::chrono::system_clock::now() - m_pause_start;
        paused = false;
    }

    // Create a list of animations to be played sorted by start time
    for (auto & laumioinfo : m_laumios) {
        for (auto & ani : laumioinfo.animations) {
            PlayAnim item{ani, laumioinfo.laumio.get()};
            m_play_toBePlayed.insert(
                        std::upper_bound(
                            m_play_toBePlayed.begin(),
                            m_play_toBePlayed.end(),
                            item,
                            [](const PlayAnim &a, const PlayAnim &b) {
                                return a.anim->fromStart() < b.anim->fromStart();
                            }),
                        item
                    );
        }
    }

    m_play_timer.start();
    playContinue();
}

void LaumioAnimation::pause(){
    m_pause_start = std::chrono::system_clock::now();
    paused = true;
    m_play_timer.stop();
    set_playing(false);
}

void LaumioAnimation::stop() {
    m_play_timer.stop();
    set_playing(false);
}

void LaumioAnimation::playContinue() {
    double now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_play_start).count() / 1000.0;
    std::list <PlayAnim> m_play_reallyPlaying;
    // Start animations that need to
    auto itBegin = std::begin(m_play_toBePlayed);
    auto itEnd = std::end(m_play_toBePlayed);
    auto it = itBegin;
    while (it != itEnd && it->anim->fromStart() <= now) {
        bool update = it->anim->animationStart(*(it->laumio));
        if (update)
            m_play_playing.push_back(*it);
        else
            m_play_toBeDeleted.push_back(*it);
        ++it;
    }
    if (it != itBegin)
        m_play_toBePlayed.erase(itBegin, it);

    // Update animations
    auto itReally = std::begin(m_play_reallyPlaying);
    itBegin = std::begin(m_play_playing);
    itEnd = std::end(m_play_playing);
    it = itBegin;
    while (it != itEnd) {
        if (it->anim->fromStart() + it->anim->duration() <= now) {
            m_play_toBeDeleted.push_back(*it);
            auto itRm = it;
            ++it;
            m_play_playing.erase(itRm);
        } else {
            if(m_play_reallyPlaying.empty()){
                m_play_reallyPlaying.push_back(*it);
            }
            itReally = std::begin(m_play_reallyPlaying);
            while (itReally != std::end(m_play_reallyPlaying)) {
                int test = priorityTest(*it, *itReally);
                switch(test){
                    case 1: {
                        ++itReally;
                        break;
                    }
                    case 2: {
                        auto itRm = itReally;
                        ++itReally;
                        m_play_reallyPlaying.erase(itRm);
                        break;
                    }
                    case 0: {
                        ++itReally;
                        m_play_reallyPlaying.push_back(*it);
                        break;
                    }
                }
            }
            ++it;
        }
    }
    itReally = std::begin(m_play_reallyPlaying);
    while (itReally != std::end(m_play_reallyPlaying)){
        bool update = itReally->anim->animationUpdate(*(itReally->laumio), now - itReally->anim->fromStart());
        auto itRm = itReally;
        itReally++;
        if (!update){
            m_play_toBeDeleted.push_back(*itRm);
            m_play_playing.erase(itRm);
        }
    }

    // Delete animations
    itBegin = std::begin(m_play_toBeDeleted);
    itEnd = std::end(m_play_toBeDeleted);
    it = itBegin;
    while (it != itEnd) {
        if (it->anim->fromStart() + it->anim->duration() <= now) {
            it->anim->animationStop(*(it->laumio));
           auto itRm = it;
            ++it;
            m_play_toBeDeleted.erase(itRm);
        } else {
            ++it;
        }
    }

    // Stop animations
    if (m_play_toBePlayed.empty() && m_play_playing.empty() && m_play_toBeDeleted.empty()) {
        m_play_timer.stop();
        set_playing(false);
    }
}
