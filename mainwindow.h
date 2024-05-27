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
    //Flag to check whether the previous button that was clicked was an operator
    bool operatorClicked;
    //Last operator requested
    QChar storedOperator;
    //Flag to check whether a number is stored in memory
    bool hasStoredNumber;
    //Stored number
    double storedNumber;
    //Calculate result based on stored number and displayed number
    void calcResult();

public slots:
    void numberGroupClicked(QAbstractButton*);
    void actionGroupClicked(QAbstractButton*);

    void onActionDelClicked();
    void onActionCalcClicked();
    void onCommaClicked();
    void onActionClearClicked();
    void onActionPercentClicked();
    void onActionSignClicked();

protected:
    void keyPressEvent(QKeyEvent *e);

};
#endif // MAINWINDOW_H
