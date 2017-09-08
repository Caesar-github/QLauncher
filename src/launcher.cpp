#include "launcher.h"
#include "powerManager/PowerManager.h"
#include <QDebug>
#include<QTimer>
Launcher::Launcher(QObject *parent) : QObject(parent)
{
}


void Launcher::slot_standby()
{
}

void Launcher::pickWallpaper()
{
}

void Launcher::powerControl()
{
}

void Launcher::emitNewIntent()
{
    emit newIntentReceived();
}

void Launcher::registerMethods()
{
    registerNativeMethods();
}

void Launcher::minimize()
{
    emit minimized();
}

void Launcher::registerNativeMethods()
{

}
