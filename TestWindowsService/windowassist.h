#ifndef WINDOWASSIST_H
#define WINDOWASSIST_H

#include <QObject>

class WindowAssist: public QObject
{
    Q_OBJECT

public:
    /*! \brief Creates the instance of WindowAssist. */
    explicit WindowAssist(QObject* parent = nullptr);

    /*! \brief Destroys the instance of WindowAssist. */
    virtual ~WindowAssist();

Q_SIGNALS:

    /*! \brief Signal emited whenever the user logon system.
     *  \details Signal emited whenever the user logon system.
     */
    void logon();

    /*! \brief Signal emited whenever the user logoff system.
     *  \details Signal emited whenever the user logoff system.
     */
    void logoff();

    /*! \brief Signal emited whenever the user lock system.
     *  \details Signal emited whenever the user lock system.
     */
    void locked();

    /*! \brief Signal emited whenever the user unlock system.
     *  \details Signal emited whenever the user unlock system.
     */
    void unlocked();

    /*! \brief Signal emited whenever the computer goes to sleep.
     *  \details Signal emited whenever the computer goes to sleep.
     */
    void sleep();

    /*! \brief Signal emited whenever the computer wakes up after sleep.
     *  \details Signal emited whenever the computer wakes up after sleep.
     */
    void awake();
};

#endif // WINDOWASSIST_H
