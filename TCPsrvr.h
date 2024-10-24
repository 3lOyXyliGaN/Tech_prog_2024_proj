/**
 * @file TCPsrvr.h
 * @brief Заголовочный файл класса TCP сервера
 */
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QCoreApplication> // для базовых функций QT
#include <QObject> // для работы сигналов и слотов
#include <QString> // для работы со строками
#include <QTcpServer> // для реализации сервера по протоколу TCP
#include <QTcpSocket> // для работы с сокетами (ip + порт)
#include <QtNetwork> // для работы с сетью
#include <QByteArray> // для работы с пригодными к передаче данными
#include <QDebug> // для вывода сообщений в консоль
#include <QMap> // для векторов

/**
 * @brief Класс TCP сервера
 * @details Обеспечивает функционал сервера для TCP соединений
 */
class TcpServer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор класса
     * @param parent Родительский объект
     */
    explicit TcpServer(QObject* parent = nullptr);

    /**
     * @brief Деструктор класса
     */
    ~TcpServer();

public slots:
    /**
     * @brief Слот обработки нового подключения
     */
    void slotNewConnection();

    /**
     * @brief Слот обработки отключения клиента
     */
    void slotClientDisconnected();

    /**
     * @brief Слот чтения данных с сервера
     */
    void slotServerRead();

private:
    QTcpServer* mTcpServer; ///< Указатель на TCP сервер
    QMap<int, QTcpSocket*> sockets; ///< Карта активных сокетов
};

#endif // TCPSERVER_H
