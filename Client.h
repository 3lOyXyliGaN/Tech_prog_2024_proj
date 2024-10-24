// Client.h
/**
 * @file Client.h
 * @brief Заголовочный файл класса клиента
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class Client;

/**
 * @brief Класс деструктора клиента
 *
 * Класс реализует механизм уничтожения экземпляра класса Client
 */
class ClientDestroyer
{
private:
    Client* p_instance; ///< Указатель на экземпляр класса Client

public:
    /**
     * @brief Деструктор класса
     */
    ~ClientDestroyer() { delete p_instance; }

    /**
     * @brief Инициализация указателя на экземпляр класса Client
     * @param p Указатель на экземпляр класса Client
     */
    void initialize(Client* p) { p_instance = p; }
};

/**
 * @brief Класс клиента
 *
 * Класс реализует логику работы клиента с сервером
 * @warning Перед использованием убедитесь, что сервер запущен на адресе 127.0.0.1:33333
 * @warning Класс реализован как синглтон, не пытайтесь создать экземпляр напрямую
 */
class Client : public QObject
{
    Q_OBJECT

private:
    static Client* p_instance; ///< Указатель на экземпляр класса Client
    static ClientDestroyer destroyer; ///< Экземпляр класса деструктора
    QTcpSocket* mTcpSocket; ///< Указатель на сокет для связи с сервером

private slots:
    /**
     * @brief Слот для чтения данных от сервера
     */
    void SlotServerRead();

protected:
    /**
     * @brief Конструктор класса
     * @param parent Родительский объект
     */
    explicit Client(QObject* parent = nullptr);

    /**
     * @brief Копирование запрещено
     */
    Client(Client&) = delete;

    /**
     * @brief Присваивание запрещено
     */
    Client& operator=(Client&) = delete;

    friend class ClientDestroyer; ///< Дружественный класс деструктора

public:
    /**
     * @brief Получение экземпляра класса Client
     * @return Указатель на экземпляр класса Client
     */
    static Client* getInstance();

    /**
     * @brief Отправка сообщения на сервер
     * @param msg Сообщение для отправки
     * @warning Метод не проверяет состояние соединения перед отправкой
     */
    void SendMsgToServer(QString msg);

signals:
    /**
     * @brief Сигнал для отправки сообщения от сервера
     * @param msg Сообщение от сервера
     */
    void MsgFromServer(QString msg);
};

#endif // CLIENT_H
