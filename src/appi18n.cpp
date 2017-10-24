#include "appi18n.h"
#include <QDir>
#include <QSettings>
#include <QDebug>
#include "applicationManager.h"

AppI18n* AppI18n::s_instance =  0;

AppI18n::AppI18n(QObject *parent) : QObject(parent)
{
}

QSettings* AppI18n::getSettings(){
    QDir settingsDir("/data/");

    if(settingsDir.exists()){
        return new QSettings("/data/i18n.ini", QSettings::IniFormat);

    }else{
        return new QSettings("/etc/i18n.ini", QSettings::IniFormat);
    }
}

QString AppI18n::getName(Application* app){
    QSettings* setting= m_map.value(app,NULL);
    if(setting!=NULL){
        QSettings* tmp= getSettings();
        QString lang= tmp->value("LANG").toString()+"/appName";
        return setting->value(lang).toString();
    }
}

void AppI18n::reflush(){

    QMapIterator<Application*,QSettings*> iter(m_map);
    while(iter.hasNext())
    {
        iter.next();
        QSettings* tmp= getSettings();
        QString lang= tmp->value("LANG").toString()+"/appName";
        QString name= iter.value()->value(lang).toString();
        iter.key()->setUiName(name);
    }

    emit reflushUI();

}

void AppI18n::addApplication(Application *app,QSettings *setting){
    if(!m_map.contains(app)){
        m_map.insert(app,setting);
        QString name= getName(app);
        if(name!=""){
            app->setUiName(name);
        }

    }
}

void AppI18n::removeApplication(Application *app){
    if(m_map.contains(app)){
        m_map.remove(app);
    }
}
