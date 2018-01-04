#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include <QTime>
#include <QDebug>
#include <QString>
#include <QFont>
#include <QMessageBox>
#include <fstream>
#include <iostream>
#include "startup.h"


MainWindow::MainWindow(QString userName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->userName = userName;
    letters = new QList<movedLetter*>();
    staticLetters = new QList<staticLetter*>();
    qsrand(static_cast<uint>(QTime::currentTime().msec()));

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
    timer->start(speed);

    if(whatProgramm){
        addMovedLatters();
    }else{
        addStaticLatters();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    for(int i = 0; i < letters->size();i++)
        delete letters->at(i);
    delete letters;
    delete timer;
    delete staticLetters;

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(whatProgramm){
        painter.setPen(Qt::red);
        for(int i = 0; i < letters->size(); i++){
            painter.drawText(letters->at(i)->x*width(), letters->at(i)->y*height(), letters->at(i)->name);
        }

    }
    else{
        QFont font("times",18);
        QFontMetrics staticLettersMetric(font);
        painter.setFont(font);
        int letterWide  = 0;
        int letterHihg = staticLettersMetric.height();
        for(int i = 0; i < staticLetters->size(); i++){
            letterWide+= staticLettersMetric.width(staticLetters->at(i)->getName());
        }
        int x = width()/2 - letterWide/2;
        int y = height()/2 - letterHihg/2;
        for(int i = 0; i < staticLetters->size(); i++){

            painter.setPen(QColor(0,0,0,staticLetters->at(i)->getAlpha()));
            painter.drawText(x,y,staticLetters->at(i)->getName());
            x+=staticLettersMetric.width(staticLetters->at(i)->getName());
        }

    }

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(whatProgramm){
        for(int i =0; i < letters->size(); i++){
            if (letters->at(i)->name.toUpper()==e->text().toUpper()){
                letters->removeAt(i);
                countScore++;
                ui->score->setText(QString::number(countScore));

            }
            else{
                fails++;
                ui->fails->setText(QString::number(fails));
                break;
            }

        }
    }

    else{
        for(int i = 0; i < staticLetters->size(); i++){
            if(staticLetters->first()->getName().toUpper()==e->text().toUpper()){
                staticLetters->removeAt(i);
                countScore++;
                ui->score->setText(QString::number(countScore));

            }
            else{
                fails++;
                ui->fails->setText(QString::number(fails));
                break;
            }

        }
    }

}

void MainWindow::addStaticLatters()
{
    for(int i =0; i < 10; i++)
        staticLetters->append(new staticLetter());
}

void MainWindow::addMovedLatters()
{
    letters->append(new movedLetter());
}

void MainWindow::changeGameType()
{
    if(whatProgramm){
        addStaticLatters();
    }else
    {
        addMovedLatters();
        timerCount = 0;
    }
    timer->stop();
    speed--;
    if(speed > 0){
        timer->start(speed);
    }
    else{
        QMessageBox* dialog = new QMessageBox(this);
        dialog->setText("dasldkjas");
        dialog->setInformativeText("fvcxvsdff");
        dialog->show();
        connect(dialog,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(close()));
        std::ofstream result;
        result.open("score.txt");
        result << userName.toStdString()<< "\t" << countScore << "\t" << fails;
        result.close();
        return;
    }

    whatProgramm = !whatProgramm;
}


void MainWindow::timerSlot()
{
    if(whatProgramm){
        for(int i =0; i < letters->size(); i++){
            if (letters->at(i)->isOutOfScreen()){
                letters->removeAt(i);
                fails++;
                ui->fails->setText(QString::number(fails));
                i--;
                continue;
            }
            letters->at(i)->nextStep();
        }
        timerCount++;

        if(timerCount%(1000/speed)==0&&timerCount<=(10000/speed)){
            letters->append(new movedLetter());

        }
        if(timerCount > 10000/speed&&letters->size() == 0&& staticLetters->size() == 0){
            changeGameType();
        }
    }
    else{
        if(staticLetters->size()>0){
            if(staticLetters->last()->decrisAlpha()){
                staticLetters->removeLast();
                fails++;
                ui->fails->setText(QString::number(fails));
            }

        }
        else
        {
            changeGameType();
        }
    }


    repaint();
    if(fails > 20 || countScore > 100){
        QMessageBox* dialog = new QMessageBox(this);
        dialog->setText("That's all!");
        dialog->setInformativeText("Try harder!");
        dialog->show();
        connect(dialog,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(startUpShow()));
        std::ofstream result;
        result.open("score.txt", std::ios_base::app);
        result << userName.toStdString()<< "\t" << countScore << "\t" << fails << "\n";
        result.close();
        timer->stop();
        return;
    }


}

void MainWindow::startUpShow()
{
    StartUp *w = new StartUp();
    w->show();
    this->close();
}


void movedLetter::nextStep()
{
    y += step;
}

bool movedLetter::isOutOfScreen()
{
    return y > 1;
}
