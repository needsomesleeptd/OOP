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
}



MainWindow::~MainWindow()
{
	request_t request;
	request.type = request::clear_model;
	handle_request(request);
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
    error_category_t rc = handle_request(request);
	if (rc == OK)
	{
		fclose(f_in);
		redraw_figure();
	}
	else
		handle_error(rc);
}

void MainWindow::on_apply_scale_clicked()
{
	scaler_t scaler = { ui->scale_x->value(), ui->scale_y->value(),ui->scale_z->value()};
	request_t request;
	request.type = request::scale;
	request.action.scaler = scaler;
	error_category_t rc = handle_request(request);
	if (rc != OK)
		handle_error(rc);
	else
		redraw_figure();
}

void MainWindow::on_apply_move_clicked()
{
    dot_t center = {ui->move_x->value(), ui->move_y->value(),ui->move_z->value()};
    request_t request;
    request.type = request::move;
    request.action.vector = center;
    error_category_t rc = handle_request(request);
	if (rc != OK)
		handle_error(rc);
	else
        redraw_figure();

}

void MainWindow::on_apply_rotate_clicked()
{

	rotator_t rotator = { ui->rotate_x->value(), ui->rotate_y->value(),ui->rotate_z->value()};
	request_t request;
	request.type = request::rotate;
	request.action.rotator = rotator;
	error_category_t rc = handle_request(request);
	if (rc != OK)
		handle_error(rc);
	else
		redraw_figure();
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
	error_category_t rc;
    rc = handle_request(request);
	if (rc == OK)
        fclose(f_out);
	else if (rc == MODEL_NOT_INITIALIZED)
	{
		fclose(f_out);
		handle_error(rc);
	}
	else
		handle_error(rc);


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

