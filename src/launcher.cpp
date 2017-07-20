#include "launcher.h"

Launcher::Launcher(QObject *parent) : QObject(parent)
{
}

void Launcher::pickWallpaper()
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
