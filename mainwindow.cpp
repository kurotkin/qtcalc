#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui-> setupUi(this);
    ui->displayView->clear();

    operatorClicked = false;
    hasStoredNumber = false;

    connect(ui->button0, SIGNAL(clicked()), this, SLOT(numberClicked()));
    connect(ui->button1, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->button2, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->button3, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->button4, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->button5, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->button6, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->button7, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->button8, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->button9, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->actionGroup,SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(actionClicked(QAbstractButton*)));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::numberClicked(){
    QPushButton *button = static_cast<QPushButton*>(QObject::sender());
    QString displayLabel = ui->displayView->text();

    if (operatorClicked) {
        displayLabel.clear();
        operatorClicked = false;
    }

    if (displayLabel.length() >= DIGIT_LIMIT) {
        return;
    }

    displayLabel.append(button->text());
    ui->displayView->setText(displayLabel);
}

void MainWindow::actionClicked(QAbstractButton* button) {
    if (operatorClicked) {
        storedOperator = button->text().at(0);
    } else {
        if (hasStoredNumber) {
            calcResult();
        }
        else {
            hasStoredNumber = true;
            QString displayLabel = ui->displayView->text();
            storedNumber = displayLabel.toDouble();
        }
        operatorClicked = true;
        storedOperator = button->text().at(0);
    }
}

void MainWindow::on_buttonClear_clicked(){
    QString displayLabel = ui->displayView->text();
    if (displayLabel.length() == 0) return;

    displayLabel.QString::chop(1);
    ui->displayView->setText(displayLabel);
}

// =
void MainWindow::on_buttonEquals_clicked(){
    QString displayLabel = ui->displayView->text();
    if (!hasStoredNumber || displayLabel.length() < 1 || operatorClicked) {
        return;
    }
    calcResult();
    hasStoredNumber = false;
}

void MainWindow::on_buttonDot_clicked(){
    QString displayLabel = ui->displayView->text();
    if (displayLabel.length() >= (DIGIT_LIMIT - 1) ||displayLabel.contains('.', Qt::CaseSensitive)) {
        return;
    }

    if (displayLabel.length() == 0) {
        displayLabel = "0";
    }

    displayLabel.append('.');
    ui->displayView->setText(displayLabel);
}

void MainWindow::on_buttonDelAll_clicked(){
    ui->displayView->clear();
    operatorClicked = false;
    hasStoredNumber = false;
}

void MainWindow::on_buttonPercent_clicked(){
    QString displayLabel = ui->displayView->text();
    displayLabel = QString::number(displayLabel.toDouble() * 0.01,'g', DIGIT_LIMIT);
    ui->displayView->setText(displayLabel);
}

void MainWindow::on_buttonPlusMinus_clicked(){
    QString displayLabel = ui->displayView->text();
    displayLabel = QString::number(displayLabel.toDouble() * -1,'g', DIGIT_LIMIT);
    ui->displayView->setText(displayLabel);
}


void MainWindow::calcResult() {
    QString displayLabel = ui->displayView->text();
     if (displayLabel.endsWith('.',Qt::CaseSensitive)) {
         displayLabel.QString::chop(1);
     }

     if (storedOperator == '+') {
         storedNumber += displayLabel.toDouble();
     }
     else if (storedOperator == '-') {
         storedNumber -= displayLabel.toDouble();
     }
     else if (storedOperator == 'x') {
         storedNumber *= displayLabel.toDouble();
     }
     else if (storedOperator == '/') {
         storedNumber /= displayLabel.toDouble();
     }

     displayLabel = QString::number(storedNumber,'g', DIGIT_LIMIT);
     ui->displayView->setText(displayLabel);
}
