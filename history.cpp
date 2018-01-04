#include "history.h"
#include "ui_history.h"
#include "startup.h"
#include <QFile>
#include <QDebug>
#include <iostream>
#include <QTextEdit>


History::History(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);
    story();
}

History::~History()
{
    delete ui;
}

void History::story()
{
    QFile playerHistory("score.txt");
    playerHistory.open(QFile::ReadOnly);
    QTextStream out(&playerHistory);
    ui->textBrowser->setText(out.readAll());
    playerHistory.close();
}

void History::on_pushButton_clicked()
{
    StartUp *w = new StartUp();
    w->show();
    this->close();
}
