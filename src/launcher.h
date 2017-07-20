#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>

class Launcher : public QObject
{
    Q_OBJECT
public:
    explicit Launcher(QObject *parent = 0);

    Q_INVOKABLE void pickWallpaper();
    Q_INVOKABLE void emitNewIntent();
    Q_INVOKABLE void registerMethods();
    Q_INVOKABLE void minimize();

signals:
    void newIntentReceived();
    void minimized();

private:
    void registerNativeMethods();

};

#endif // LAUNCHER_H
