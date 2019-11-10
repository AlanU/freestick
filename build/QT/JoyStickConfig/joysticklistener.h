#ifndef JOYSTICKLISTENER_H
#define JOYSTICKLISTENER_H

#include <QObject>

class JoystickListener : public QObject
{
    Q_OBJECT
public:
    explicit JoystickListener(QObject *parent = nullptr);

signals:

public slots:
};

#endif // JOYSTICKLISTENER_H