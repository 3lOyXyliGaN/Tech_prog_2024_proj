/**
 * @file main.cpp
 * @brief Главный файл программы
 * @author Safarov Timur
 */
#include <QCoreApplication>
#include "TCPsrvr.h"

/**
 * @brief Точка входа в программу
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return Код завершения программы
 */
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TcpServer server;

    return app.exec();
}


