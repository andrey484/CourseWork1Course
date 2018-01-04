#include "startup.h"
#include "ui_startup.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <fstream>
#include <string>
#include <QDebug>
#include "history.h"
#include <QList>


StartUp::StartUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartUp)
{
    ui->setupUi(this);
}

StartUp::~StartUp()
{
    delete ui;
}

void StartUp::on_pushButton_clicked()
{
    QList <history> players;
    players.append(history());
    history hPlayer;
    std::string buff;
    std::ifstream result;
    result.open("score.txt");
    while(result >> buff >> players.last().score >> players.last().fails){
        players.last().name = QString::fromStdString(buff);
        players.append(history());
    }
    if(players.size()>10){
        std::ofstream result;
        result.open("score.txt", std::ios_base::trunc);
        result.close();
        return;
    }
    QString player;
    player = ui->lineEdit->text();
    for(int i = 0;i < players.length(); i++){
        if(player == players.at(i).name){
            QMessageBox* dialog = new QMessageBox(this);
            dialog->setText("Enter the new player");
            dialog->setInformativeText("This player have already registed");
            dialog->show();
            return;
        }
    }
    if(player.isEmpty()){
        QMessageBox* dialog = new QMessageBox(this);
        dialog->setText("dasldkjas");
        dialog->setInformativeText("fvcxvsdff");
        dialog->show();
        return;
    }
    result.close();
    MainWindow *w = new MainWindow(player);
    w->show();
    this->close();
}

void StartUp::on_pushButton_2_clicked()
{
    History *w = new History();
    w->show();
    this->close();
}
