#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QString>
#include <QList>
#include <QTimer>
#include <QKeyEvent>


namespace Ui {
class MainWindow;
}
 const QString allChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

class staticLetter
{
public:
    staticLetter(){
        name = allChar.at(qrand()%(allChar.length()-1));
        alpha = 255;
    }
    QString getName(){
        return name;
    }
    int getAlpha(){
        return alpha;
    }
    bool decrisAlpha()
    {
        alpha -= 4;
        if(alpha <=0){
            alpha =0;
            return true;
        }
        return false;
    }

private:
    QString name;
    int alpha;
};

class movedLetter{
public:
    movedLetter(){
        name = allChar.at(qrand()%(allChar.length()-1));
        x = ((double)(qrand()%10000))/10000.0;
        y = 0;
        step = ((double)(qrand()%600+400))/100000.0;
    }

    void nextStep();
    bool isOutOfScreen();
    QString name;
    double x,y,step;

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString userName = "", QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent* e);



private:
    Ui::MainWindow *ui;
    QList<movedLetter *> *letters;
    QList<staticLetter *> *staticLetters;
    QTimer *timer;
    int timerCount = 0;
    int countScore = 0;
    int fails = 0;
    bool whatProgramm = true;
    int speed = 25;
    QString userName;

    void addStaticLatters();
    void addMovedLatters();
    void changeGameType();


public slots:
    void timerSlot();
    void startUpShow();
};


#endif // MAINWINDOW_H
