#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "request.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);


	model_t model;
}



MainWindow::~MainWindow()
{
    delete ui;
}










void MainWindow::on_load_model_clicked()
{
	QString filename = QFileDialog::getOpenFileName(
		this,
		tr("Open File"),
		"../tests",
		"All files (*.*);;Model File (*.txt)"
	);

    FILE *f_in = fopen(filename.toUtf8(),"r");

	request_t request;
    request.type = request::load_model;
	request.action.f_pointer = f_in;
    handle_request(request);
	fclose(f_in);
	redraw_figure();
}

void MainWindow::on_apply_scale_clicked()
{
	scaler_t scaler = { ui->scale_x->value(), ui->scale_y->value(),ui->scale_z->value()};
	request_t request;
	request.type = request::scale;
	request.action.scaler = scaler;
	handle_request(request);


	redraw_figure();
}

void MainWindow::on_apply_move_clicked()
{
    dot_t center = {ui->move_x->value(), ui->move_y->value(),ui->move_z->value()};
    request_t request;
    request.type = request::move;
    request.action.vector = center;
    handle_request(request);


   redraw_figure();

}

void MainWindow::on_apply_rotate_clicked()
{

	rotator_t rotator = { ui->rotate_x->value(), ui->rotate_y->value(),ui->rotate_z->value()};
	request_t request;
	request.type = request::rotate;
	request.action.rotator = rotator;
	handle_request(request);


	redraw_figure();
}


void MainWindow::redraw_figure()
{
	scene->clear();
	scene->update();
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());
	ui->graphicsView->setScene(scene);

	request_t request;
	request.type = request::draw_model;
	request.action.canvas = ui->graphicsView->scene();
	handle_request(request);
}
void MainWindow::on_save_model_clicked()
{
    QString filename = QFileDialog::getSaveFileName(
        this,
        tr("Open File"),
        "../tests",
        "All files (*.*);;Model File (*.txt)"
    );

    FILE *f_out = fopen(filename.toUtf8(),"w");

    request_t request;
    request.type = request::save_model;
    request.action.f_pointer = f_out;
    handle_request(request);
    fclose(f_out);

}
