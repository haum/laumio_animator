#include "laumioanimation.h"
#include <QFile>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

LaumioAnimation::LaumioAnimation(QObject * parent) : QAbstractListModel(parent)
{

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
        return qVariantFromValue(m_laumios.at(index.row()).get());
    default:
        return QVariant();
    }
}

QHash <int, QByteArray> LaumioAnimation::roleNames() const {
    QHash <int, QByteArray> ret;
    ret[LaumioRole] = "laumio";
    return ret;
}

void LaumioAnimation::newLaumio() {
    beginInsertRows(QModelIndex(), m_laumios.size(), m_laumios.size());
    m_laumios.push_back(std::move(std::unique_ptr<Laumio>(new Laumio)));
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
        auto aptr = std::unique_ptr<Laumio>(new Laumio);
        auto * ptr = aptr.get();
        m_laumios.push_back(std::move(aptr));
        auto obj = elem.toObject();
        ptr->loadFromJSON(obj);
    }
    endInsertRows();
}

void LaumioAnimation::saveToFile(QString filename) {
    QJsonDocument doc;
    QJsonArray array;
    for (auto & apLaumio : m_laumios) {
        QJsonObject obj;
        apLaumio.get()->saveToJSON(obj);
        array.append(obj);
    }
    doc.setArray(array);

    QFile f(QUrl(filename).toLocalFile());
    if (!f.open(QFile::ReadWrite))
        return;
    f.write(doc.toJson());
}
