#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);

signals:

public slots:
    void newConnection();
	void readData();
	void socketError(QAbstractSocket::SocketError);
	void deleteLater();

private:
    QTcpServer *server;
	QTcpSocket *socket;
};

#endif // MYTCPSERVER_H
