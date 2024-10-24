// AuthandReg.h
/**
 * @file AuthandReg.h
 * @brief Заголовочный файл виджета авторизации и регистрации
 */

#ifndef AUTHANDREG_H
#define AUTHANDREG_H

#include <QWidget>

    namespace Ui {
    class AuthandReg;
}

/**
 * @brief Класс виджета авторизации и регистрации
 *
 * Класс реализует интерфейс для авторизации существующих
 * пользователей и регистрации новых
 */
class AuthandReg : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief Сигнал авторизации
     * @param log Логин пользователя
     * @param pass Пароль пользователя
     * @warning Пароль передается в открытом виде, не используйте реальные пароли
     */
    void auth(QString log, QString pass);

    /**
     * @brief Сигнал регистрации
     * @param log Логин пользователя
     * @param pass Пароль пользователя
     * @param email Email пользователя
     * @warning Все данные передаются в открытом виде
     */
    void reg(QString log, QString pass, QString email);

public:
    /**
     * @brief Конструктор класса
     * @param parent Родительский виджет
     */
    explicit AuthandReg(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса
     */
    ~AuthandReg();

private slots:
    /**
     * @brief Обработчик нажатия кнопки авторизации
     */
    void on_authbutton_clicked();

    /**
     * @brief Обработчик нажатия кнопки регистрации
     */
    void on_regbutton_clicked();

    /**
     * @brief Обработчик нажатия кнопки создания аккаунта
     */
    void on_makeacc_clicked();

    /**
     * @brief Обработчик нажатия кнопки входа
     */
    void on_enter_clicked();

private:
    Ui::AuthandReg* ui; ///< Указатель на UI форму
};

#endif // AUTHANDREG_H
