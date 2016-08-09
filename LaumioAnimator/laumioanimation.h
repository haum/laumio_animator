#ifndef LAUMIOANIMATION_H
#define LAUMIOANIMATION_H

#include <QAbstractListModel>
#include <QObject>
#include <memory>
#include <vector>
#include <map>
#include "animation.h"
#include "laumio.h"

class LaumioAnimation : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        LaumioRole = Qt::UserRole + 1,
        AnimationsRole,
    };

    explicit LaumioAnimation(QObject * parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    QHash <int, QByteArray> roleNames() const override;

public slots:
    void newLaumio();
    void deleteLaumio(int index);

    void newAnimation();
    void deleteAnimation(int index);

    void loadFromFile(QString filename);
    void saveToFile(QString filename);

private:
    struct LaumioInfo {
        std::unique_ptr<Laumio> laumio;
        std::vector <Animation*> animations;
    };
    std::vector <LaumioInfo> m_laumios;
    std::map <QString, std::unique_ptr <Animation> (*)()> m_factories;

    std::vector <std::unique_ptr<Animation>> m_animationsStorage;

    void registerFactory(QString name, std::unique_ptr <Animation> (*factory)());
};

#endif // LAUMIOANIMATION_H
