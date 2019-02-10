#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(289, 372);

    //Text
    cellStyle = new QFont;

    //First player turn
    playerTurn = 1;

    //Matrix declaration
    field = new char* [SCALE];

    for(int i = 0; i < SCALE; ++i)
    {
        field[i] = new char [SCALE];
    }

    for(int i = 0; i < SCALE; ++i)
    {
        for(int j = 0; j < SCALE; ++j)
        {
            field[i][j] = *"";
        }
    }

    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(gameProcess()));
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(gameProcess()));
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(gameProcess()));
    connect(ui->pushButton_21, SIGNAL(clicked()), this, SLOT(gameProcess()));
    connect(ui->pushButton_22, SIGNAL(clicked()), this, SLOT(gameProcess()));
    connect(ui->pushButton_23, SIGNAL(clicked()), this, SLOT(gameProcess()));
    connect(ui->pushButton_31, SIGNAL(clicked()), this, SLOT(gameProcess()));
    connect(ui->pushButton_32, SIGNAL(clicked()), this, SLOT(gameProcess()));
    connect(ui->pushButton_33, SIGNAL(clicked()), this, SLOT(gameProcess()));
}

MainWindow::~MainWindow()
{
    //Free memory
    for(int i = 0; i < SCALE; ++i)
    {
        delete [] field[i];
    }

    delete [] field;

    delete cellStyle;

    delete ui;
}

WinType MainWindow::horisontalCheck()
{
    int countCross = 0;
    int countCircle = 0;

    for(int i = 0; i < SCALE; ++i)
    {
        countCross = 0;
        countCircle = 0;

        for(int j = 0; j < SCALE && (countCross < SCALE || countCircle < SCALE); ++j)
        {
           if(field[i][j] == CROSS)
           {
               countCross++;
           }
           if(field[i][j] == CIRCULE)
           {
               countCircle++;
           }
        }

        if(countCross == SCALE)
        {
            return CrossWin;
        }

        if(countCircle == SCALE)
        {
            return CirculeWin;
        }
    }

    return Continue;

}

WinType MainWindow::verticalCheck()
{
    int countCross = 0;
    int countCircle = 0;

    for(int i = 0; i < SCALE; ++i)
    {
        countCross = 0;
        countCircle = 0;

        for(int j = 0; j < SCALE && (countCross < SCALE || countCircle < SCALE); ++j)
        {
           if(field[j][i] == CROSS)
           {
               countCross++;
           }
           if(field[j][i] == CIRCULE)
           {
               countCircle++;
           }

        }

        if(countCross == SCALE)
        {
            return CrossWin;
        }

        if(countCircle == SCALE)
        {
            return CirculeWin;
        }
    }

    return Continue;

}

WinType MainWindow::diagCheck()
{
    int countCross = 0;
    int countCircle = 0;

    for(int i = 0; i < SCALE; ++i)
    {
        if( (field[i][i] == CROSS) || (field[i][SCALE-i-1] == CROSS) )
        {
            countCross++;
        }
        if( (field[i][i] == CIRCULE) || (field[i][SCALE-i-1] == CIRCULE) )
        {
            countCircle++;
        }
    }

    if(countCross == SCALE)
    {
        return CrossWin;
    }

    if(countCircle == SCALE)
    {
        return CirculeWin;
    }

    return Continue;
}

WinType MainWindow::whoWin()
{
    WinType horizontal = horisontalCheck();
    WinType vertical = verticalCheck();
    WinType diag = diagCheck();

    if(horizontal == CrossWin || vertical == CrossWin || diag == CrossWin)
    {
        return CrossWin;
    }

    if(horizontal == CirculeWin || vertical == CirculeWin || diag == CirculeWin)
    {
        return CirculeWin;
    }

    if(playerTurn == SCALE*SCALE+1)
    {
        return Draw;
    }

    return Continue;
}

void MainWindow::clearField()
{
    ui->lbl_playerTurn->setText("First player turn " + CROSS_TEXT);

    ui->pushButton_11->setText("");
    ui->pushButton_12->setText("");
    ui->pushButton_13->setText("");
    ui->pushButton_21->setText("");
    ui->pushButton_22->setText("");
    ui->pushButton_23->setText("");
    ui->pushButton_31->setText("");
    ui->pushButton_32->setText("");
    ui->pushButton_33->setText("");

    for(int i = 0; i < SCALE; ++i)
    {
        for(int j = 0; j < SCALE; ++j)
        {
            field[i][j] = *"";
        }
    }
    playerTurn = 1;
}

void MainWindow::gameProcess()
{
    QPushButton *button = dynamic_cast<QPushButton*>(sender());

    if(button->text() != "")
    {
        return;
    }

    //Getting button name and converting it into the matrix position
    QStringList buttonName = button->objectName().split("_");
    int colIndex = buttonName[1].toInt() % 10 - 1;
    int rowIndex = buttonName[1].toInt() / 10 - 1;

    if(playerTurn % 2 != 0)
    {
        ui->lbl_playerTurn->setText("Second player turn " + CIRCULE_TEXT);

        cellStyle->setPixelSize(60);
        button->setFont(*cellStyle);
        button->setPalette(Qt::white);
        button->setText(CROSS_TEXT);

        field[rowIndex][colIndex] = CROSS;
    }
    else
    {
        ui->lbl_playerTurn->setText("First player turn " + CROSS_TEXT);
        cellStyle->setPixelSize(60);
        button->setFont(*cellStyle);
        button->setPalette(Qt::black);
        button->setText(CIRCULE_TEXT);

        field[rowIndex][colIndex] = CIRCULE;
    }

    playerTurn++;

    switch (whoWin())
    {
        case Draw:
            QMessageBox::information(this, "Draw!", "No one won this game!");
            clearField();
            break;

        case CrossWin:
            QMessageBox::information(this, "You win", "Player " + CROSS_TEXT + " won this game!");
            clearField();
            break;

        case CirculeWin:
            QMessageBox::information(this, "You win", "Player " + CIRCULE_TEXT + " won this game!");
            clearField();
            break;

        default:
            break;
    }
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNew_Game_triggered()
{
    clearField();
}
