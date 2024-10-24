// Mainwindow.h
/**
 * @file Mainwindow.h
 * @brief Заголовочный файл главного окна приложения
 */

#ifndef MAINWIND_H
#define MAINWIND_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Mainwindow;
}
QT_END_NAMESPACE

/**
 * @brief Класс главного окна приложения
 *
 * Класс реализует основной интерфейс приложения с функционалом
 */
class Mainwindow : public QMainWindow
{
    Q_OBJECT

signals:
    /**
     * @brief Сигнал для RSA шифрования
     * @param text Текст для шифрования
     * @warning Не являеться рабочим, создан только для примера!
     */
    void RSA(QString text);

    /**
     * @brief Сигнал для хеширования
     * @param text Текст для хеширования
     * @warning Не являеться рабочим, создан только для примера!
     */
    void hash(QString text);

public slots:
    /**
     * @brief Слот для отображения результата вычислений
     * @param text Текст для отображения
     * @warning Не являеться рабочим, создан только для примера!
     */
    void solv(QString text);

public:
    /**
     * @brief Конструктор класса
     * @param parent Родительский виджет
     */
    Mainwindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса
     */
    ~Mainwindow();

private slots:
    /**
     * @brief Обработчик нажатия кнопки решения
     */
    void on_Solve_clicked();

    /**
     * @brief Обработчик нажатия кнопки смены режима
     */
    void on_Change_clicked();

private:
    Ui::Mainwindow *ui; ///< Указатель на UI форму

    /**
     * @brief Перечисление доступных задач
     * @warning Не являеться рабочим, создан только для примера!
     */
    enum Task {
        rsa,    ///< Режим RSA шифрования
        sha512  ///< Режим SHA-512 хеширования
    };
    Task currentTask; ///< Текущая выбранная задача
};

#endif // MAINWIND_H
