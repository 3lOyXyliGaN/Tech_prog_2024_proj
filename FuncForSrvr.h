/**
 * @file FuncForSrvr.h
 * @brief Заголовочный файл с функциями для обработки серверных запросов
 */
#ifndef FUNCFORSRVR_H
#define FUNCFORSRVR_H
#include <QString>
#include <queue>
#include <QStringList>
#include <QByteArray>
#include <QtSql>

/**
 * @brief Класс для обработки серверных функций
 */
class FuncForSrvr
{
public:
    /**
     * @brief Парсит входящие данные и вызывает соответствующую функцию
     * @param data Входящая строка данных
     * @return QByteArray с результатом выполнения функции
     * @warning Входные данные должны соответствовать определенному формату.
     * Некорректные данные могут привести к ошибкам
     */
    static QByteArray parse(QString data);

private:
    /**
     * @brief Функция авторизации пользователя
     * @param log Логин пользователя
     * @param pass Пароль пользователя
     * @return QByteArray с результатом авторизации
     */
    static QByteArray auth(QString log, QString pass); // авторизация
    /**
     * @brief Функция регистрации нового пользователя
     * @param log Логин нового пользователя
     * @param pass Пароль нового пользователя
     * @param mail Email нового пользователя
     * @return QByteArray с результатом регистрации
     */
    static QByteArray reg(QString log, QString pass, QString mail); // регистрация

    /**
     * \brief Константы SHA-512
     *
     * Массив констант, используемых в алгоритме SHA-512.
     */
    constexpr static const std::array<uint64_t, 80> k =
        {
        0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
        0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
        0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
        0x72be5d74f27b896f, 0x80deb1fe3b1789b4, 0x9bdc06a725c71235, 0xc19bf174cf692694,
        0xe49b69c19c6ebf2f, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
        0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
        0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
        0x27b70a85c6ca6351, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
        0x650a73548baf63de, 0x766a0abb3c6ef372, 0x81c2c92e47edaee6, 0x92722c851482353b,
        0xa2bfe8a14cf10364, 0xa81a664bfb00327f, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
        0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
        0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774c8d359fba, 0x34b0bcb5e19b48a8,
        0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
        0x748f82ee5defb2fc, 0x78
    };

    /**
     * \brief Инициализационные векторы SHA-512
     *
     * Массив инициализационных векторов, используемых в алгоритме SHA-512.
     */
    constexpr static const std::array<uint64_t, 8> initial_hash = {
        0x6a09e667f3bcc908,
        0xbb67ae8584caa73b,
        0x3c6ef372fe94f82b,
        0xa54ff53a5f1d36f1,
        0x510e527fade682d1,
        0x9b05688c2b3e6c1f,
        0x1f83d9abfb41bd6b,
        0x5be0cd19137e2179
    };

    /**
     * \brief Функция шифрования RSA
     * \param message Сообщение для шифрования
     * \param e Открытая экспонента
     * \param n Модуль
     * \return QByteArray с зашифрованным сообщением
     */
    static QByteArray rsa(const QString &message, int e, int n); // шифрование

    /**
     * \brief Вычисление наибольшего общего делителя
     * \param a Первое число
     * \param b Второе число
     * \return Наибольший общий делитель a и b
     */
    static int gcd(int a, int b);

    /**
     * \brief Вычисление мультипликативного обратного по модулю
     * \param e Число, для которого нужно найти обратное
     * \param phi Модуль
     * \return Мультипликативное обратное e по модулю phi
     */
    static int modInverse(int e, int phi);

    /**
     * \brief Возведение в степень по модулю
     * \param base Основание
     * \param exponent Показатель степени
     * \param mod Модуль
     * \return Результат возведения в степень по модулю
     */
    static int powerMod(int base, int exponent, int mod);

    /**
     * \brief Генерация ключей RSA
     * \param n [out] Модуль
     * \param e [out] Открытая экспонента
     * \param d [out] Закрытая экспонента
     */
    static void generateKeys(int &n, int &e, int &d);

    /**
     * \brief Преобразование строки в массив байтов
     * \param input Входная строка
     * \return Вектор байтов
     */
    static std::vector<uint8_t> string_to_bytes(const std::string& input);

    /**
     * \brief Преобразование 64-битного целого числа в массив из 8 байтов
     * \param num 64-битное целое число
     * \return Массив из 8 байтов
     */
    static std::array<uint8_t, 8> uint64_to_bytes(uint64_t num);

    /**
     * \brief Преобразование массива байтов в шестнадцатеричную строку
     * \param bytes Вектор байтов
     * \return Шестнадцатеричная строка
     */
    static std::string bytes_to_hex_string(const std::vector<uint8_t>& bytes);

    /**
     * \brief Вычисление хеша SHA-512
     * \param input Входная строка для хеширования
     * \return QByteArray с результатом хеширования
     */
    static QByteArray sha_512(const std::string& input); // хэширование
};


#endif // FUNCFORSRVR_H
