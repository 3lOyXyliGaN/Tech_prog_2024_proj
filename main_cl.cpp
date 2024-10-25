// main_cl.cpp
/**
 * @file main_cl.cpp
 * @brief Файл главной функции клиента
 */
#include "FuncForCl.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FuncForCl w;

    return a.exec();
}
