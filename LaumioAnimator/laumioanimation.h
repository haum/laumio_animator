#ifndef LAUMIOANIMATION_H
#define LAUMIOANIMATION_H

#include <QAbstractListModel>
#include <QTimer>
#include <QObject>
#include <memory>
#include <vector>
#include <map>
#include <chrono>
#include "macrodegeu.h"
#include "animations/animation.h"
#include "laumio.h"

/*

JSON format :

{
    "animations" : [
        {
            "anims": [
                {
                    "type": "<TYPE>",
                    ...
                }
                ...
            ],
            "laumio": ...
        }
        ...
    ],
    "audioSource" : "<AUDIO_URL>"
}

*/

/** Class to manage animations **/
class LaumioAnimation : public QAbstractListModel {
    Q_OBJECT

    PROP(QString, audioSource, "")
    PROP(bool, playing, false)

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
      * @param index       Index of laumio
      * @param factoryName Factory's code name
      */
    Animation* newAnimation(int index, QString factoryName);

    /** Remove animation
      * @param laumioNb    Index of laumio
      * @param index       Index of animation
      */
    void deleteAnimation(int laumioNb, int index);

    /** Load config from file
      * @param filename Filename to parse
      */
    void loadFromFile(QString filename);

    /** Save config into file
      * @param filename Filename to save in
      */
    void saveToFile(QString filename);

    /** Play animation **/
    void play(int timeInMilliseconds);

    /** Stop animation **/
    void stop();

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

    /** Callback to continue playing **/
    void playContinue();

    /** Timer to play animations */
    QTimer m_play_timer;

    /** Current playing time **/
    std::chrono::system_clock::time_point m_play_start;

    struct PlayAnim {
        Animation* anim;
        Laumio * laumio;
    };

    /** List of aimations to be played **/
    std::list <PlayAnim> m_play_toBePlayed;

    /** List of aimations playing **/
    std::list <PlayAnim> m_play_playing;

    /** List of aimations to be deleted **/
    std::list <PlayAnim> m_play_toBeDeleted;
};

#endif // LAUMIOANIMATION_H
