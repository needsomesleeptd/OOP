#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "drawer_qt_factory.h"
#include "load_scene_controller_creator.h"
#include "load_model_controller_creator.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setup_scene();

	std::string config ="/home/andrew/OOP/OOP/lab_3/data/config.cfg";
	auto moderator = LoadModelControllerCreator(config).create_controller();
	_facade = std::make_shared<Facade>(Facade());
	_transform_manager = CreatorTransformManager().create_manager();

	_load_manager = CreatorLoadManager().create_manager(moderator);
	_scene_manager = CreatorSceneManager().create_manager();
	_draw_manager = CreatorDrawManager().create_manager();
	std::shared_ptr<AbstractDrawerFactory> factory(new DrawerQtFactory(_scene));
	_drawer = factory->graphic_create();

	connect(ui->pushButton_load_model, &QPushButton::clicked, this, &MainWindow::on_pushButton_load_model_clicked);
	connect(ui->pushButton_del_model_cur,
		&QPushButton::clicked,
		this,
		&MainWindow::on_pushButton_del_model_cur_clicked);

	connect(ui->pushButton_add_camera, &QPushButton::clicked, this, &MainWindow::on_pushButton_add_camera_clicked);
	connect(ui->pushButton_del_camera_cur,
		&QPushButton::clicked,
		this,
		&MainWindow::on_pushButton_del_camera_cur_clicked);

	connect(ui->pushButton_del_model_all,
		&QPushButton::clicked,
		this,
		&MainWindow::on_pushButton_del_model_all_clicked);

	connect(ui->pushButton_camera_move_right,
		&QPushButton::clicked,
		this,
		&MainWindow::on_pushButton_camera_move_right_clicked);
	connect(ui->pushButton_camera_move_left,
		&QPushButton::clicked,
		this,
		&MainWindow::on_pushButton_camera_move_left_clicked);
	connect(ui->pushButton_camera_move_up,
		&QPushButton::clicked,
		this,
		&MainWindow::on_pushButton_camera_move_up_clicked);
	connect(ui->pushButton_camera_move_down,
		&QPushButton::clicked,
		this,
		&MainWindow::on_pushButton_camera_move_down_clicked);

	connect(ui->pushButton_move, &QPushButton::clicked, this, &MainWindow::on_pushButton_move_clicked);
	connect(ui->pushButton_scale, &QPushButton::clicked, this, &MainWindow::on_pushButton_scale_clicked);
	connect(ui->pushButton_spin, &QPushButton::clicked, this, &MainWindow::on_pushButton_spin_clicked);

	connect(ui->comboBox_cameras, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::change_cam);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setup_scene()
{
	_scene = new QGraphicsScene(this);
	_scene = new QGraphicsScene(this);

	ui->graphicsView->setScene(_scene);
	ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");

	auto cont = ui->graphicsView->contentsRect();
	_scene->setSceneRect(0, 0, cont.width(), cont.height());

	std::shared_ptr<AbstractDrawerFactory> factory(new DrawerQtFactory(_scene));
	_drawer = factory->graphic_create();
}

void MainWindow::check_cam_exist()
{
	auto camera_count = std::make_shared<size_t>(0);

	CountCameraCommand camera_cmd(_scene_manager, camera_count);

	_facade->execute(camera_cmd);

	if (!*camera_count)
	{
		std::string msg = "No camera found.";
		throw CameraException(msg);
	}
}

void MainWindow::check_can_delete_cam()
{
	auto model_count = std::make_shared<size_t>(0);
	CountModelCommand model_cmd(_scene_manager, model_count);
	_facade->execute(model_cmd);

	auto camera_count = std::make_shared<size_t>(0);
	CountCameraCommand camera_cmd(_scene_manager, camera_count);
	_facade->execute(camera_cmd);

	if (*camera_count <= 1 && *model_count)
	{
		std::string msg = "Can not delete the last camera with the loaded models";
		throw CameraException(msg);
	}
}

void MainWindow::check_models_exist()
{
	auto model_count = std::make_shared<size_t>(0);
	CountModelCommand model_cmd(_scene_manager, model_count);
	_facade->execute(model_cmd);

	if (!*model_count)
	{
		std::string msg = "No models found.";
		throw ModelException(msg);
	}
}

void MainWindow::on_pushButton_move_clicked()
{
	try
	{
		check_cam_exist();
		check_models_exist();
	}
	catch (const CameraException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
		return;
	}
	catch (const ModelException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
		return;
	}
	Dot move_vector
		(ui->doubleSpinBox_move_x->value(), ui->doubleSpinBox_move_y->value(), ui->doubleSpinBox_move_z->value());

	TransformParams transform_params;
	transform_params.setMoveParams(move_vector);


	TransformVisitor visitor;
	visitor.set_params(transform_params);

	auto ref_to_vis = std::make_shared<TransformVisitor>(visitor);

	TransformModelCommand move_cmd(_scene_manager,
		ui->comboBox_models->currentIndex(), ref_to_vis);

	_facade->execute(move_cmd);
	update_scene();
}

void MainWindow::on_pushButton_scale_clicked()
{
	try
	{
		check_cam_exist();
		check_models_exist();
	}
	catch (const CameraException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
		return;
	}
	catch (const ModelException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
		return;
	}

	Dot scale_vector
		(ui->doubleSpinBox_scale_x->value(), ui->doubleSpinBox_scale_y->value(), ui->doubleSpinBox_scale_z->value());

	TransformParams transform_params;
	transform_params.setScaleParams(scale_vector);


	TransformVisitor visitor;
	visitor.set_params(transform_params);

	auto ref_to_vis = std::make_shared<TransformVisitor>(visitor);

	TransformModelCommand scale_cmd(_scene_manager,
		ui->comboBox_models->currentIndex(), ref_to_vis);

	_facade->execute(scale_cmd);
	update_scene();
}

void MainWindow::on_pushButton_spin_clicked()
{
	try
	{
		check_cam_exist();
		check_models_exist();
	}
	catch (const CameraException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
		return;
	}
	catch (const ModelException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
		return;
	}

	Dot scale_vector
		(ui->doubleSpinBox_spin_x->value(), ui->doubleSpinBox_spin_y->value(), ui->doubleSpinBox_spin_z->value());

	TransformParams transform_params;
	transform_params.setRotateParams(scale_vector);


	TransformVisitor visitor;
	visitor.set_params(transform_params);

	auto ref_to_vis = std::make_shared<TransformVisitor>(visitor);

	TransformModelCommand rotate_cmd(_scene_manager,
		ui->comboBox_models->currentIndex(), ref_to_vis);

	_facade->execute(rotate_cmd);
	update_scene();
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
	int key = e->key();
	try
	{
		check_cam_exist();
		check_models_exist();
	}
	catch (const CameraException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
		return;
	}
	catch (const ModelException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
		return;
	}

	int cam_index = ui->comboBox_cameras->currentIndex();



	TransformParams transform_params;


	TransformVisitor visitor;
	visitor.set_params(transform_params);


	if (key == Qt::Key_E)
	{
		Dot rotation = Dot{0,-10,0};
		transform_params.setRotateParams(rotation);
		visitor.set_params(transform_params);
		std::shared_ptr<Visitor> ref_to_vis = std::make_shared<TransformVisitor>(visitor);
		TransformCameraCommand rotate_camera_cmd(_scene_manager,cam_index,ref_to_vis);
		_facade->execute(rotate_camera_cmd);
	}

	else if (key == Qt::Key_Q)
	{
		Dot rotation = Dot{0,10,0};
		transform_params.setRotateParams(rotation);
		visitor.set_params(transform_params);
		std::shared_ptr<Visitor> ref_to_vis = std::make_shared<TransformVisitor>(visitor);
		TransformCameraCommand rotate_camera_cmd(_scene_manager,cam_index,ref_to_vis);
		_facade->execute(rotate_camera_cmd);
	}
	else if (key == Qt::Key_Z)
	{
		Dot rotation = Dot{10,0,0};
		transform_params.setRotateParams(rotation);
		visitor.set_params(transform_params);
		std::shared_ptr<Visitor> ref_to_vis = std::make_shared<TransformVisitor>(visitor);
		TransformCameraCommand rotate_camera_cmd(_scene_manager,cam_index,ref_to_vis);
		_facade->execute(rotate_camera_cmd);
	}

	else if (key == Qt::Key_C)
	{
		Dot rotation = Dot{-10,0,0};
		transform_params.setRotateParams(rotation);
		visitor.set_params(transform_params);
		std::shared_ptr<Visitor> ref_to_vis = std::make_shared<TransformVisitor>(visitor);
		TransformCameraCommand rotate_camera_cmd(_scene_manager,cam_index,ref_to_vis);
		_facade->execute(rotate_camera_cmd);
	}

	update_scene();

}

void MainWindow::on_pushButton_del_model_cur_clicked()
{
	try
	{
		check_models_exist();
	}
	catch (const ModelException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Прежде чем удалять модель, добавьте хотя бы одну.");
		return;
	}

	RemoveModelCommand remove_command(_scene_manager,ui->comboBox_models->currentIndex());
	_facade->execute(remove_command);

	ui->comboBox_models->removeItem(ui->comboBox_models->currentIndex());

	update_scene();
}

void MainWindow::on_pushButton_del_model_all_clicked()
{
	try
	{
		check_models_exist();
	}
	catch (const ModelException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Прежде чем удалять модели, добавьте хотя бы одну.");
		return;
	}

	for (int i = ui->comboBox_models->count() - 1; i >= 0; --i)
	{
		RemoveModelCommand remove_command(_scene_manager,i);
		_facade->execute(remove_command);

		ui->comboBox_models->removeItem(i);
	}

	update_scene();
}

void MainWindow::on_pushButton_load_model_clicked()
{
	try
	{
		check_cam_exist();
	}
	catch (const CameraException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Прежде чем добавлять модель, добавьте хотя бы одну камеру.");
		return;
	}

	auto file = QFileDialog::getOpenFileName();

	if (file.isNull())
		return;

	LoadModelCommand load_command(_load_manager,  file.toUtf8().data(),_scene_manager->get_scene());

	try
	{
		_facade->execute(load_command);
	}
	catch (const CameraException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Что-то пошло не так при загрузке файла...");
		return;
	}

	update_scene();
	ui->comboBox_models->addItem(QFileInfo(file.toUtf8().data()).fileName());
	ui->comboBox_models->setCurrentIndex(ui->comboBox_models->count() - 1);

}

void MainWindow::on_pushButton_camera_move_up_clicked()
{
	try
	{
		check_cam_exist();
		check_models_exist();
	}
	catch (const CameraException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
		return;
	}
	catch (const ModelException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
		return;
	}
	TransformVisitor visitor;
	TransformParams transform_params;
	Dot move = Dot{0,10,0};
	transform_params.setMoveParams(move);
	visitor.set_params(transform_params);
	std::shared_ptr<Visitor> ref_to_vis = std::make_shared<TransformVisitor>(visitor);

	std::size_t cam_index = ui->comboBox_cameras->currentIndex();
	TransformCameraCommand move_camera_cmd(_scene_manager,cam_index,ref_to_vis);
	_facade->execute(move_camera_cmd);

	update_scene();
}

void MainWindow::on_pushButton_camera_move_left_clicked()
{
	try
	{
		check_cam_exist();
		check_models_exist();
	}
	catch (const CameraException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
		return;
	}
	catch (const ModelException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
		return;
	}

	TransformVisitor visitor;
	TransformParams transform_params;
	Dot move = Dot{-10,0,0};
	transform_params.setMoveParams(move);
	visitor.set_params(transform_params);
	std::shared_ptr<Visitor> ref_to_vis = std::make_shared<TransformVisitor>(visitor);

	std::size_t cam_index = ui->comboBox_cameras->currentIndex();
	TransformCameraCommand move_camera_cmd(_scene_manager,cam_index,ref_to_vis);
	_facade->execute(move_camera_cmd);
	update_scene();
}

void MainWindow::on_pushButton_camera_move_down_clicked()
{
	try
	{
		check_cam_exist();
		check_models_exist();
	}
	catch (const CameraException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
		return;
	}
	catch (const ModelException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
		return;
	}

	TransformVisitor visitor;
	TransformParams transform_params;
	Dot move = Dot{0,10,0};
	transform_params.setMoveParams(move);
	visitor.set_params(transform_params);
	std::shared_ptr<Visitor> ref_to_vis = std::make_shared<TransformVisitor>(visitor);

	std::size_t cam_index = ui->comboBox_cameras->currentIndex();
	TransformCameraCommand move_camera_cmd(_scene_manager,cam_index,ref_to_vis);
	_facade->execute(move_camera_cmd);
	update_scene();
}

void MainWindow::on_pushButton_camera_move_right_clicked()
{
	try
	{
		check_cam_exist();
		check_models_exist();
	}
	catch (const CameraException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
		return;
	}
	catch (const ModelException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
		return;
	}

	TransformVisitor visitor;
	TransformParams transform_params;
	Dot move = Dot{10,0,0};
	transform_params.setMoveParams(move);
	visitor.set_params(transform_params);
	std::shared_ptr<Visitor> ref_to_vis = std::make_shared<TransformVisitor>(visitor);

	std::size_t cam_index = ui->comboBox_cameras->currentIndex();
	TransformCameraCommand move_camera_cmd(_scene_manager,cam_index,ref_to_vis);
	_facade->execute(move_camera_cmd);
	update_scene();
}

void MainWindow::on_pushButton_del_camera_cur_clicked()
{
	try
	{
		check_cam_exist();
	}
	catch (const CameraException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Прежде чем удалять камеру, добавьте хотя бы одну.");
		return;
	}

	try
	{
		check_can_delete_cam();
	}
	catch (const CameraException& error)
	{
		QMessageBox::critical(nullptr, "Ошибка", "Прежде чем удалять камеру, необходимо удалить оставшиеся модели.");
		return;
	}

	RemoveCameraCommand remove_command(_scene_manager,ui->comboBox_cameras->currentIndex());
	_facade->execute(remove_command);

	ui->comboBox_cameras->removeItem(ui->comboBox_cameras->currentIndex());

	try
	{
		check_cam_exist();
	}
	catch (const CameraException& error)
	{
		return;
	}

	update_scene();
}

void MainWindow::on_pushButton_add_camera_clicked()
{
	auto cont = ui->graphicsView->contentsRect();
	Dot position{cont.width() / 2.0, cont.height() / 2.0, 0.};
	AddCameraCommand camera_command(position,_scene_manager);
	_facade->execute(camera_command);

	update_scene();

	auto cam = ui->comboBox_cameras;

	if (0 == cam->count())
		cam->addItem(QString::number(1));
	else
		cam->addItem(QString::number(cam->itemText(cam->count() - 1).toInt() + 1));

	ui->comboBox_cameras->setCurrentIndex(ui->comboBox_cameras->count() - 1);
}

void MainWindow::update_scene()
{
	DrawSceneCommand draw_command(_scene_manager,_draw_manager,_drawer);
	_facade->execute(draw_command);
}

void MainWindow::change_cam()
{
	try
	{
		check_cam_exist();
	}
	catch (const CameraException& error)
	{
		return;
	}

	SetCameraCommand camera_command(_scene_manager,ui->comboBox_cameras->currentIndex());
	_facade->execute(camera_command);
	update_scene();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);

	_scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

	auto cont = ui->graphicsView->contentsRect();
	_scene->setSceneRect(0, 0, cont.width(), cont.height());
}

