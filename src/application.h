#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>

class Application : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString pkgName READ pkgName NOTIFY pkgNameChanged)
    Q_PROPERTY(QString argv READ argv NOTIFY argvChanged)
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(QString exitCallback READ exitCallback NOTIFY exitCallbackChanged)

public:
    explicit Application(QObject *parent = 0);
    Application(const QString &name, const QString &pkgName, QObject *parent = 0);
   // Application(const QString &name, const QString &pkgName,const QString &icon, QObject *parent = 0);
     Application(const QString &name, const QString &pkgName, const QString & argv,const QString &icon,const QString exitCallback, QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QString pkgName() const;
    void setApplicationName(const QString &pkgName);

    QString argv() const;
    void setArgv(const QString &argv);

    QString icon() const;
    void setIcon(const QString &icon);

    QString exitCallback() const;
    void setExitCallback(const QString &exitCallback);

signals:
    void nameChanged();
    void pkgNameChanged();
    void argvChanged();
    void iconChanged();
    void exitCallbackChanged();

private:
    QString mName;
    QString mApplicationName;
    QString mArgv;
    QString mIcon;
    QString mExitCallback;
public:
    QString app_file;
    QString dir;
};

#endif // APPLICATION_H
