#ifndef OSUIRCCLIENT_H
#define OSUIRCCLIENT_H

#include <QObject>
#include <QTcpSocket>

class OsuIrcClient : public QObject
{
    Q_OBJECT
public:
    explicit OsuIrcClient(
        const QString &nickname,
        const QString &password,
        const QString &server,
        const int &port,
        QObject *parent = nullptr
    );
    void init();
    void setNick(const QString &nickname);
    void setPass(const QString &password);
    void setServer(const QString &server);
    void setPort(const int &port);

private:
    QString nickname;
    QString password;
    QString server;
    int port;
    QTcpSocket *socket;

signals:
    void connected();
    void disconnected();

public slots:
    void onConnected();
    void onDisconnected();
};

#endif // OSUIRCCLIENT_H
