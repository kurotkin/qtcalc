#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    const int DIGIT_LIMIT = 16;
    bool operatorClicked;
    QChar storedOperator;
    bool hasStoredNumber;
    double storedNumber;
    void calcResult();

public slots:
    void numberClicked();
    void actionClicked(QAbstractButton*);
    // button slots
    void on_buttonEquals_clicked();
    void on_buttonDelAll_clicked();
    void on_buttonDot_clicked();
    void on_buttonClear_clicked();
    void on_buttonPercent_clicked();
    void on_buttonPlusMinus_clicked();
};
#endif // MAINWINDOW_H
