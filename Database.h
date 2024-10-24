// Database.h
/**
 * @file Database.h
 * @brief Заголовочный файл класса базы данных
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QStringList>

/**
 * @brief Класс базы данных (синглтон)
 * @warning Этот класс реализует паттерн Синглтон. Создание экземпляров напрямую невозможно,
 * используйте метод getInstance()
 */
class Database;

/**
 * @brief Класс для корректного удаления синглтона базы данных
 */
class DatabaseDestroyer
{
private:
    Database* p_instance; ///< Указатель на экземпляр базы данных

public:
    /**
     * @brief Деструктор
     */
    ~DatabaseDestroyer();

    /**
     * @brief Инициализация указателя на базу данных
     * @param p Указатель на экземпляр базы данных
     */
    void initialize(Database* p);
};

/**
 * @brief Класс базы данных (синглтон)
 */
class Database
{
private:
    static Database* p_instance; ///< Статический указатель на экземпляр
    static DatabaseDestroyer destroyer; ///< Объект-уничтожитель
    QSqlDatabase db; ///< Объект базы данных

    Database();
    ~Database();
    Database(const Database&) = delete;
    void operator=(const Database&) = delete;
    friend class DatabaseDestroyer;

public:
    /**
     * @brief Создание таблицы в базе данных
     */
    void createTable();

    /**
     * @brief Получение экземпляра базы данных
     * @return Ссылка на экзем пляр базы данных
     */
    static Database& getInstance();

    /**
     * @brief Получение объекта базы данных
     * @return Ссылка на объект базы данных
     */
    QSqlDatabase& getDatabase();

    /**
     * @brief Выполнение запроса к базе данных
     * @param q Указатель на объект запроса
     * @return Результат выполнения запроса
     */
    bool queryToDatabase(QSqlQuery* q);
};

#endif // DATABASE_H
