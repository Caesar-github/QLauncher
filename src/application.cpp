#include "application.h"

Application::Application(QObject *parent) :
    QObject(parent)
{
}

/*Application::Application(const QString &name, const QString &pkgName,const QString &icon, QObject *parent) :
    QObject(parent),
    mName(name),
    mApplicationName(pkgName),
    mIcon(icon)
{
}*/

Application::Application(const QString &name, const QString &pkgName,const QString &icon, const QString exitCallback,QObject *parent) :
    QObject(parent),
    mName(name),
    mApplicationName(pkgName),
    mIcon(icon),
    mExitCallback(exitCallback)
{
}

QString Application::name() const
{
    return mName;
}

void Application::setName(const QString &name)
{
    if (mName == name)
        return;

    mName = name;
    emit nameChanged();
}

QString Application::icon() const
{
    return mIcon;
}

void Application::setIcon(const QString &icon)
{
    if (mIcon == icon)
        return;

    mIcon = icon;
    emit iconChanged();
}

QString Application::pkgName() const
{
    return mApplicationName;
}

void Application::setApplicationName(const QString &pkgName)
{
    if (mApplicationName == pkgName)
        return;

    mApplicationName = pkgName;
    emit pkgNameChanged();
}

QString Application::exitCallback() const
{
    return mExitCallback;
}

void Application::setExitCallback(const QString &exitCallback)
{
    if (mExitCallback == exitCallback)
        return;
    mExitCallback = exitCallback;
    emit exitCallbackChanged();
}
