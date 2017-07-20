#ifndef APPLICATIONMANAGER
#define APPLICATIONMANAGER
#include <QProcess>
#include <QAbstractListModel>

class ApplicationManager : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QStringList sections READ sections NOTIFY sectionsChanged)

public:
    explicit ApplicationManager(QObject *parent = 0);

    enum Roles {
        NameRole = Qt::UserRole +1,
        PackageNameRole,
        CategoryRole
    };

    int rowCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE void launchApplication(const QString &application,const QString &pkgName);
    Q_INVOKABLE void registerBroadcast();
    Q_INVOKABLE int indexOfSection(const QString &section);
    Q_INVOKABLE void openApplicationInfo(const QString &pkgName);
    Q_INVOKABLE void addApplicationToGrid(const QString &name, const QString &pkgName, const QString &icon);
    Q_INVOKABLE void emitAddApplication(const QString &name, const QString &pkgName,const QString &icon);
    Q_INVOKABLE void emitRemoveApplication(const QString &pkgName);

    QStringList sections() const;

public slots:
    void retrievePackages();
    void addApplication(const QString &name, const QString &pkgName,const QString &icon);
    void removeApplication(const QString &pkgName);

protected:
    QHash<int, QByteArray> roleNames() const;

signals:
    void newApplicationDetected(const QString &name, const QString &pkgName, const QString &icon);
    void addedApplicationToGrid(const QString &name, const QString &pkgName, const QString &icon);
    void removedApplication(const QString &pkgName);
    void sectionsChanged();
    void launcherApplicationState(bool state);

private:
    QObjectList mApplications;
    QMap<QString, QObject> mApps;
    QStringList mSections;
    QList<int> mSectionsPositions;

private:
    QProcess* pro;
private slots:
    void processFinished(int, QProcess::ExitStatus);
    void processError(QProcess::ProcessError);
};

#endif
