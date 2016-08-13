#ifndef LAUMIOANIMATION_H
#define LAUMIOANIMATION_H

#include <QAbstractListModel>
#include <QObject>
#include <memory>
#include <vector>
#include <map>
#include "animation.h"
#include "laumio.h"

/** Class to manage animations **/
class LaumioAnimation : public QAbstractListModel {
    Q_OBJECT

public:
    /** Enumation of model roles **/
    enum {
        LaumioRole = Qt::UserRole + 1,
        AnimationsRole,
    };

    /** Constructor
      * @param parent QObject's parent if memory ownership is managed by Qt,
      *               nullptr otherwise
      */
    explicit LaumioAnimation(QObject * parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    QHash <int, QByteArray> roleNames() const override;

public slots:
    /** Add a new (empty) laumio **/
    void newLaumio();

    /** Delete laumio (and its animations) at given index
      * @param index Index to delete
      */
    void deleteLaumio(int index);

    /** Get list of factories' names
      * @return Factories' names
      */
    static QStringList factoriesNames();

    /** Add new (default constructed) animation
      * @param factoryName Factory's code name
      */
    void newAnimation(QString factoryName);

    /** Load config from file
      * @param filename Filename to parse
      */
    void loadFromFile(QString filename);

    /** Save config into file
      * @param filename Filename to save in
      */
    void saveToFile(QString filename);

private:
    /** Factories **/
    static std::map <QString, std::unique_ptr <Animation> (*)()> sFactories;

    /** Channel informations **/
    struct LaumioInfo {
        std::unique_ptr<Laumio> laumio; //<< Laumio linked to this channel
        std::vector <Animation*> animations; //< Animations linked to this channel
    };

    /** All channels **/
    std::vector <LaumioInfo> m_laumios;

    /** Storage for created animations **/
    std::vector <std::unique_ptr<Animation>> m_animationsStorage;
};

#endif // LAUMIOANIMATION_H
