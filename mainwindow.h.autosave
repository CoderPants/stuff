#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QFont>
#include <QString>
#include <QDebug>

enum WinType {Continue, CrossWin, CirculeWin, Draw};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Check, if smb win
    WinType horisontalCheck();
    WinType verticalCheck();
    WinType diagCheck();

    //Final check
    WinType whoWin();

    void clearField();

private slots:
    void gameProcess();

    void on_actionExit_triggered();

    void on_actionNew_Game_triggered();

private:

    //Game figures
    const char CROSS = *"X";
    const char CIRCULE = *"O";
    const QString CROSS_TEXT = "X";
    const QString CIRCULE_TEXT = "O";


    //Field 3x3
    const int SCALE = 3;

    //Text style
    QFont *cellStyle;

    //Variable for player info
    int playerTurn;

    //Matrix for saving placed figures
    char **field;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
