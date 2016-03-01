#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("E:\image.jpg");
    ui->label_3->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}
