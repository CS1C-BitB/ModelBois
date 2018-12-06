#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

/**
 * @brief Login class
 *
 * This class represents objects associate with the login screen
 */
class Login : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent
     */
    explicit Login(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~Login();

private slots:
    /**
     * @brief This function checks login credentials
     *
     * Note -- accepts credentials or informs user that login credentials are invalid
     */
    void on_pushButton_login_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
