#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    connect(ui -> button0, SIGNAL(clicked()), this, SLOT(showNumbers()));
    connect(ui -> button1, SIGNAL(clicked()), this, SLOT(showNumbers()));
    connect(ui -> button2, SIGNAL(clicked()), this, SLOT(showNumbers()));
    connect(ui -> button3, SIGNAL(clicked()), this, SLOT(showNumbers()));
    connect(ui -> button4, SIGNAL(clicked()), this, SLOT(showNumbers()));
    connect(ui -> button5, SIGNAL(clicked()), this, SLOT(showNumbers()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showNumbers(){
    QPushButton *button = static_cast<QPushButton*>(QObject::sender());
    QString name = button->objectName();

    int disp = ui -> lcdNumber -> value();
    if(name == "button0"){
        disp = disp * 10;
    } else if (name == "button1") {
        disp = disp * 10 + 1;
    } else if (name == "button2") {
        disp = disp * 10 + 2;
    } else if (name == "button3") {
        disp = disp * 10 + 3;
    } else if (name == "button4") {
        disp = disp * 10 + 4;
    } else if (name == "button5") {
        disp = disp * 10 + 5;
    }

    ui -> lcdNumber -> display(disp);
}



