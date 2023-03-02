#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QPen blackpen(Qt::black);
    blackpen.setWidth(6);
    ellipse = scene->addEllipse(10,10,100,100,blackpen);


}

MainWindow::~MainWindow()
{
    delete ui;
}


