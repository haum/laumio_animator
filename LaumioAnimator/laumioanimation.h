#ifndef LAUMIOANIMATION_H
#define LAUMIOANIMATION_H

#include <QAbstractListModel>
#include <QObject>
#include <memory>
#include <vector>
#include "laumio.h"

class LaumioAnimation : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        LaumioRole = Qt::UserRole + 1,
    };

    explicit LaumioAnimation(QObject * parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    QHash <int, QByteArray> roleNames() const override;

public slots:
    void newLaumio();
    void deleteLaumio(int index);

    void loadFromFile(QString filename);
    void saveToFile(QString filename);

private:
    std::vector <std::unique_ptr<Laumio>> m_laumios;
};

#endif // LAUMIOANIMATION_H
