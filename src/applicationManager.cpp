#include "applicationManager.h"
#include "application.h"

#include <QDebug>
#include <QSettings>
#include <QApplication>
#include "appscanner.h"


ApplicationManager::ApplicationManager(QObject *parent) :
    QAbstractListModel(parent)
{
    connect(this, SIGNAL(newApplicationDetected(QString, QString,QString,QString,QString)), this, SLOT(addApplication(QString, QString,QString,QString,QString)));
    connect(this, SIGNAL(removedApplication(QString)), this, SLOT(removeApplication(QString)));

    pro=new  QProcess(this);
    connect(pro, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));
    connect(pro, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));
}

int ApplicationManager::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mApplications.count();
}

QVariant ApplicationManager::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mApplications.count())
        return QVariant();

    switch (role) {
    case NameRole:
        return qobject_cast<Application*>(mApplications.at(index.row()))->name();
        break;
    case PackageNameRole:
        return qobject_cast<Application*>(mApplications.at(index.row()))->pkgName();
        break;
    }
    return QVariant();
}

void ApplicationManager::launchApplication(const QString &application,const QString &pkgName,const QString &argv,const QString &exitCallback)
{
    QStringList arguments;
#ifdef PLATFORM_WAYLAND
    qDebug() << "launchApplication(PLATFORM_WAYLAND):application=" << application<<",argv="<<argv;

    arguments <<"-platform"<<"wayland";
    pro->start("/usr/local/"+application+"/"+pkgName,arguments);
#else
    qDebug() << "launchApplication:application=" << application<<",argv="<<argv;

    //QStringList arguments;
    //arguments <<"-platform"<<"EGLFS";

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if(application.compare("video")==0 || application.compare("camera")==0)
    {
        env.insert("LC_ALL", "zh_CN.utf8");
        env.insert("QT_EGLFSPLATFORM_USE_GST_VIDEOSINK", "1");
        env.insert("QT_GSTREAMER_WINDOW_VIDEOSINK", "kmssink"); // Add  environment variable
        //env.insert("GST_DEBUG", "kmssink:5");//show video fps

    }
    else
    {
        //env.insert("QT_EGLFSPLATFORM_USE_GST_VIDEOSINK", "");
        env.insert("QT_GSTREAMER_WINDOW_VIDEOSINK", " "); // remove  environment variable
    }
    if(!exitCallback.isEmpty())
    {
        env.insert("EXIT_CALLBACK", exitCallback);
        env.insert("APP_DIR", application);
    }
    pro->setProcessEnvironment(env);
    if(false)
    {
        foreach(QString str,env.toStringList())
            qDebug() <<str;

        //pro->setStandardOutputFile("/tmp/"+application+"_out.log",QIODevice::Truncate);
        //pro->setStandardErrorFile("/tmp/"+application+"_error.log",QIODevice::Truncate);
    }
    if(!argv.isEmpty())
    {
        arguments=argv.split(" ");
        //foreach(QString str,arguments)
        //    qDebug() <<str;
         pro->start("/usr/local/"+application+"/"+pkgName,arguments);
    }
    else
    {
         pro->start("/usr/local/"+application+"/"+pkgName);
    }
    emit  launcherApplicationState(true);
#endif

}

QHash<int, QByteArray> ApplicationManager::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[PackageNameRole] = "pkgName";
    return roles;
}

void ApplicationManager::retrievePackages()
{
    beginResetModel();

    AppScanner *appScanner=new AppScanner();

    QList<Application*> *apps= appScanner->scan("/usr/local");

   //qDebug() << "apps->size():" << apps->size();
    for(int i=0; i< apps->size();i++){
        Application* app= apps->at(i);
       // qDebug() << "apps(" << i<<") app->mName="<<app->name()<<",pkgName="<<app->pkgName()<<"app->app_icon="<<app->icon();
        mApplications.append(new Application(app->name(), app->pkgName(),app->argv(),app->icon(),app->exitCallback()));
        emit addedApplicationToGrid(app->name(), app->pkgName(),app->argv(),app->icon(),app->exitCallback());
    }
    delete appScanner;
    endResetModel();
    emit sectionsChanged();
}

void ApplicationManager::registerBroadcast()
{
    retrievePackages();


}

int ApplicationManager::indexOfSection(const QString &section)
{
    return mSectionsPositions.at(mSections.indexOf(section));
}

void ApplicationManager::openApplicationInfo(const QString &pkgName)
{

    Q_UNUSED(pkgName)
}

void ApplicationManager::addApplicationToGrid(const QString &name, const QString &pkgName,const QString &argv,const QString &icon,const QString &exitCallback)
{
    emit addedApplicationToGrid(name, pkgName,argv,icon,exitCallback);
}

QStringList ApplicationManager::sections() const
{
    return mSections;
}

void ApplicationManager::addApplication(const QString &name, const QString &pkgName,const QString &argv,const QString &icon,const QString &exitCallback)
{
    int i;
    for (i = 0; i < mApplications.length(); ++i) {
        Application *application = qobject_cast<Application*>(mApplications.at(i));
        if (name.compare(application->name()) < 0)
            break;
    }

    qDebug() << Q_FUNC_INFO << "NAME:" << name << " PACKAGE:" << pkgName;
    beginInsertRows(QModelIndex(), i, i);
    Application *application = new Application(name, pkgName,argv,icon,exitCallback);
    mApplications.insert(i, application);
    endInsertRows();
}

void ApplicationManager::removeApplication(const QString &pkgName)
{
    qDebug() << Q_FUNC_INFO << pkgName;
    int i = 0;
    foreach (QObject *object, mApplications) {
        Application *app = qobject_cast<Application*>(object);
        if (app->pkgName() == pkgName) {
            beginRemoveRows(QModelIndex(), i, i);
            delete mApplications.takeAt(i);
            endRemoveRows();
            i--;
        }
        i++;
    }

    mSections.clear();
    mSectionsPositions.clear();

    sectionsChanged();
}

void ApplicationManager::emitAddApplication(const QString &name, const QString &pkgName,const QString &argv,const QString &icon,const QString &exitCallback)
{
    emit newApplicationDetected(name, pkgName,argv,icon,exitCallback);
}

void ApplicationManager::emitRemoveApplication(const QString &pkgName)
{
    emit removedApplication(pkgName);
}

void ApplicationManager::processFinished(int, QProcess::ExitStatus){
      qDebug() << "processFinished" << endl;
      emit  launcherApplicationState(false);
      processExitCallback();
}

void ApplicationManager::processError(QProcess::ProcessError){
    qDebug() << "processError" << endl;
     emit  launcherApplicationState(false);
    processExitCallback();
}
void ApplicationManager::processExitCallback()
{
    qDebug() << "processExitCallback" << endl;
    if(pro->processEnvironment().contains("EXIT_CALLBACK"))
    {
        QString exit_work=pro->processEnvironment().value("EXIT_CALLBACK");
        QString pro_path=pro->processEnvironment().value("APP_DIR");
        qDebug() <<"exit_work="<<exit_work<<"pro_path="<<pro_path<<":"<<"/usr/local/"+pro_path+"/"+exit_work;
        QProcess::execute("/usr/local/"+pro_path+"/"+exit_work);
    }
}

