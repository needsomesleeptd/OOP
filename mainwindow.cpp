#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "request.h"


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

	model_t model;
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_apply_rotate_clicked()
{

    scaler_t scaler = { ui->rotate_x->value(), ui->rotate_y->value(),ui->rotate_z->value()};
	request_t request;
	request.type = request::rotate;
	request.action.scaler = scaler;
	handle_request(request);


	scene = new QGraphicsScene(this);
	ui->graphicsView->setScene(scene);

	request.type = request::draw_model;
	request.action.canvas = ui->graphicsView->scene();
	handle_request(request);
}






void MainWindow::on_load_model_clicked()
{
    FILE *f_in = fopen("../test.txt","r");

	request_t request;
    request.type = request::load_model;
	request.action.f_pointer = f_in;
    handle_request(request);
	fclose(f_in);
}
