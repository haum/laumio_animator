#include "laumioanimation.h"
#include <QFile>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "constantcoloranimation.h"

std::map <QString, std::unique_ptr <Animation> (*)()> LaumioAnimation::sFactories {
    {"ConstantColor", &ConstantColorAnimation::factory}
};

LaumioAnimation::LaumioAnimation(QObject * parent) : QAbstractListModel(parent) {
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

void LaumioAnimation::newAnimation(QString factoryName) {
    auto itFactory = sFactories.find(factoryName);
    if (itFactory != std::end(sFactories)) {
        auto anim = (*itFactory->second)();
        auto * animptr = anim.get();
        m_animationsStorage.push_back(std::move(anim));
        m_laumios.back().animations.push_back(animptr);
    }
}

void LaumioAnimation::deleteAnimation(int index) {

}

void LaumioAnimation::loadFromFile(QString filename) {
    beginResetModel();
    m_laumios.clear();
    endResetModel();

    QFile f(QUrl(filename).toLocalFile());
    if (!f.open(QFile::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    QJsonArray array = doc.array();
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
    doc.setArray(array);

    QFile f(QUrl(filename).toLocalFile());
    if (!f.open(QFile::ReadWrite))
        return;
    f.write(doc.toJson());
}
