// mytcpserver.cpp

#include "mytcpserver.h"
#include <qdatastream.h>

MyTcpServer::MyTcpServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }
}

void MyTcpServer::newConnection()
{
    // need to grab the socket
    socket = server->nextPendingConnection();

	qDebug() << " connect";

	// �ؒf�������̏������`
	connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

	// ��M�������̏������`
	connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
	// �G���[�����̒�`
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
	// �ؒf�����Ƃ��̏����Ƃ���SLOT�֐���ݒ肷��B
	connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));

	// �N���C�A���g��IP�A�h���X���擾
	QString ippaddr = socket->localAddress().toString();

	// ���M�f�[�^��stream�Ƃ��Ē�`
	QDataStream out(socket);
	out.setVersion(QDataStream::Qt_5_0);

	out << "Hello client\r\n";
	
    //socket->write("Hello client\r\n");
    //socket->flush();

    //socket->waitForBytesWritten(3000);

    //socket->close();
}

void MyTcpServer::readData()
{
	QString s;

	// ��M�f�[�^���vstream�Ƃ��Ē�`
	//QDataStream in(socket);
	//in.setVersion(QDataStream::Qt_5_11);

	//in >> s;

	s = socket->readAll();

	qDebug() << "receive : " << s << "( " << s.size() << " ) ";

	if ("bye\r\n" == s)
	{
		qDebug() << "close process";

		//deleteLater();
		emit socket->disconnected();
	}

}

void MyTcpServer::socketError(QAbstractSocket::SocketError )
{
	qDebug() << " socket error!";

	socket->close();
}

void MyTcpServer::deleteLater()
{
	qDebug() << " socket disconnected";

	socket->close();
}