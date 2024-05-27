#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui-> setupUi(this);
    ui->displayView->clear();

    operatorClicked = false;
    hasStoredNumber = false;

    ui->numberGroup->connect(
                ui->numberGroup,
                SIGNAL(buttonClicked(QAbstractButton*)),
                this,
                SLOT(numberGroup_clicked(QAbstractButton*)));

    ui->actionGroup->connect(
                ui->actionGroup,
                SIGNAL(buttonClicked(QAbstractButton*)),
                this,
                SLOT(actionGroup_clicked(QAbstractButton*)));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::numberGroupClicked(QAbstractButton* button){
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

void MainWindow::actionGroupClicked(QAbstractButton* button) {
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

void MainWindow::onActionDelClicked(){
    QString displayLabel = ui->displayView->text();
    if (displayLabel.length() == 0) return;

    displayLabel.QString::chop(1);
    ui->displayView->setText(displayLabel);
}

void MainWindow::onActionCalcClicked(){
    QString displayLabel = ui->displayView->text();
    if (!hasStoredNumber || displayLabel.length() < 1 || operatorClicked) {
        return;
    }
    calcResult();
    hasStoredNumber = false;
}

void MainWindow::onCommaClicked(){
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

void MainWindow::onActionClearClicked(){
    ui->displayView->clear();
    operatorClicked = false;
    hasStoredNumber = false;
}

void MainWindow::onActionPercentClicked(){
    QString displayLabel = ui->displayView->text();
    displayLabel = QString::number(displayLabel.toDouble() * 0.01,'g', DIGIT_LIMIT);
    ui->displayView->setText(displayLabel);
}

void MainWindow::onActionSignClicked(){
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

void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        case Qt::Key_1:
            numberGroupClicked(ui->num1);
            break;
        case Qt::Key_2:
            numberGroup_clicked(ui->num2);
            break;
        case Qt::Key_3:
            numberGroup_clicked(ui->num3);
            break;
        case Qt::Key_4:
            numberGroup_clicked(ui->num4);
            break;
        case Qt::Key_5:
            numberGroup_clicked(ui->num5);
            break;
        case Qt::Key_6:
            numberGroup_clicked(ui->num6);
            break;
        case Qt::Key_7:
            numberGroup_clicked(ui->num7);
            break;
        case Qt::Key_8:
            numberGroup_clicked(ui->num8);
            break;
        case Qt::Key_9:
            numberGroup_clicked(ui->num9);
            break;
        case Qt::Key_0:
            numberGroup_clicked(ui->num0);
            break;
        case Qt::Key_Plus:
            actionGroup_clicked(ui->actionPlus);
            break;
        case Qt::Key_Minus:
            actionGroup_clicked(ui->actionMinus);
            break;
        case Qt::Key_Asterisk:
            actionGroup_clicked(ui->actionMul);
            break;
        case Qt::Key_Slash:
            actionGroup_clicked(ui->actionDiv);
            break;
        case Qt::Key_Period:
            onCommaClicked();
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            onActionCalcClicked();
            break;
        case Qt::Key_Backspace:
            onActionDelClicked();
            break;
        case Qt::Key_Delete:
            onActionClearClicked();
            break;
        case Qt::Key_Percent:
            onActionPercentClicked();
            break;
    }
}


