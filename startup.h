#ifndef STARTUP_H
#define STARTUP_H

#include <QWidget>

namespace Ui {
class StartUp;
}

class StartUp : public QWidget
{
    Q_OBJECT

public:
    explicit StartUp(QWidget *parent = 0);
    struct history{
            QString name;
            int score;
            int fails;
        };
    ~StartUp();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::StartUp *ui;
};

#endif // STARTUP_H
