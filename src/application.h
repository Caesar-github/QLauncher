#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>

class Application : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString pkgName READ pkgName NOTIFY pkgNameChanged)
     Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)

public:
    explicit Application(QObject *parent = 0);
    Application(const QString &name, const QString &pkgName, QObject *parent = 0);
    Application(const QString &name, const QString &pkgName,const QString &icon, QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QString pkgName() const;
    void setApplicationName(const QString &pkgName);

    QString icon() const;
    void setIcon(const QString &icon);

signals:
    void nameChanged();
    void pkgNameChanged();
    void iconChanged();

private:
    QString mName;
    QString mApplicationName;
    QString mIcon;
public:
    QString app_file;
    QString dir;
};

#endif // APPLICATION_H
