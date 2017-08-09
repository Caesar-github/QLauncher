#include "launcher.h"
#include "powerManager/PowerManager.h"
#include <QDebug>
#include<QTimer>
Launcher::Launcher(QObject *parent) : QObject(parent)
{
}


void Launcher::slot_standby()
{
    system("echo mem > /sys/power/state");
}

void Launcher::pickWallpaper()
{
}

void Launcher::powerControl()
{
    if(rk_get_screen_status())
    {
        qDebug()<<"key value is PowerKey, screen off ";
        rk_screen_off();
        QTimer::singleShot(100, this, SLOT(slot_standby()));
    }
    else
    {
        qDebug()<<"key value is PowerKey, screen ON ";
        rk_screen_on();
    }
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
