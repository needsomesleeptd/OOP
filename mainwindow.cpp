#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "request.h"
#include <QFileDialog>
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);





	connect(ui->about_creator, SIGNAL(triggered()),this,SLOT(on_actionabout_creator_triggered()));



	connect(ui->about_program, SIGNAL(triggered()),this,SLOT(on_actionabout_program_triggered()));


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


	request_t request;
    request.type = request::load_model;
	request.filename = filename.toUtf8().data();
    error_category_t rc = handle_request(request);
	handle_error(rc);
	if (rc == OK)
		redraw_figure();
}

void MainWindow::on_apply_scale_clicked()
{
	scaler_t scaler = { ui->scale_x->value(), ui->scale_y->value(),ui->scale_z->value()};
	request_t request;
	request.type = request::scale;
	request.scaler = scaler;
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
    request.vector = center;
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
	request.rotator = rotator;
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



    request_t request;
    request.type = request::save_model;
    request.filename = filename.toUtf8().data();
	error_category_t rc;
    rc = handle_request(request);
	handle_error(rc);
}

void MainWindow::on_revert_step_clicked()
{
    request_t request;
    request.type = request::revert_changes;
    request.filename = "../.last_change";
    error_category_t rc = handle_request(request);
    //handle_error(rc);
	redraw_figure();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	int flag = 0;
	if (this->width() < 1200)
	{
		this->resize(1200, this->height());
		flag = 1;
	}
	{
		if (this->height() < 700)
		{
			this->resize(this->width(), 700);
			flag = 1;
		}
	}
	if (flag == 0)
		QMainWindow::resizeEvent(event);

	redraw_figure();

}


void MainWindow::redraw_figure()
{
	scene->clear();
	scene->update();
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());
	ui->graphicsView->mapFromScene(ui->graphicsView->viewport()->rect().center());
	ui->graphicsView->setScene(scene);

	request_t request;
	request.type = request::draw_model;
	request.canvas = ui->graphicsView->scene();
	handle_request(request);
}




void MainWindow::on_change_center_clicked()
{
	request_t request;
	request.type = request::change_center;
	dot_t center = {ui->center_x->value(),ui->center_y->value(),ui->center_z->value()};
	request.dot = center;
	error_category_t rc = handle_request(request);
	handle_error(rc);
	if (rc == OK)
		redraw_figure();

}

void MainWindow::on_reset_center_clicked()
{
    request request;
	request.type = request::reset_center;
	handle_request(request);

	redraw_figure();

}

void MainWindow::on_actionabout_creator_triggered()
{
	QMessageBox::information(this,"Об авторе","Данная работа была выполнена студентом Разиным Андреем группы ИУ7-44Б");

}

void MainWindow::on_actionabout_program_triggered()
{

	QMessageBox::information(this,"О программе","Цель работы:Нарисовать исходный рисунок, затем его переместить,\n"
	                                            "\n"
	                                            "промасштабировать, повернуть\n"
												"С помощью центральной красной точки задается центр вращения и масштабирования модели\n"
												"При перемещении модели центр перемещается с ней ,для отдельного перемещения центра\n"
												"Необходимо использовать отдельные параметры смещения центра\n"
												"При  нажатии на кнопку переместить перемещается модель а также ее центр вращения\n"
												"При нажатии кнопки поворот ,поворот осуществляется вокруг соответствующей системы координат вокруг центра координат\n"
												"При нажатии кнопки  вернуть в центр ,центр координат возвращается в центр масс фигуры\n"
												"При нажатии кнопки масштабировать фигура масштабируется относительно заданного центра масштабирования"
												);

}