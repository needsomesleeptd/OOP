#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QKeyEvent>

#include "commands/base_command.h"
#include "commands/camera_command.h"
#include "commands/model_command.h"
#include "commands/scene_command.h"
#include "exceptions.h"
#include "drawer/abstract_drawer_factory.h"
#include "drawer/drawer_qt_factory.h"
#include "facade/facade.h"
#include "draw_manager_creator.h"
#include "load_manager_creator.h"
#include "transform_manager_creator.h"
#include "scene_manager_creator.h"



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
    void on_pushButton_move_clicked();
    void on_pushButton_scale_clicked();
    void on_pushButton_spin_clicked();
    void on_pushButton_del_model_cur_clicked();
    void on_pushButton_del_model_all_clicked();
    void on_pushButton_load_model_clicked();
    void on_pushButton_camera_move_up_clicked();
    void on_pushButton_camera_move_left_clicked();
    void on_pushButton_camera_move_down_clicked();
    void on_pushButton_camera_move_right_clicked();
    void on_pushButton_del_camera_cur_clicked();
    void on_pushButton_add_camera_clicked();
    void change_cam();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void setup_scene();
    void update_scene();
    void check_cam_exist();
    void check_can_delete_cam();
    void check_models_exist();
	void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;

    QGraphicsScene *_scene;
    std::shared_ptr<Facade> _facade;
	std::shared_ptr<DrawManager> _draw_manager;
	std::shared_ptr<LoadManager> _load_manager;
	std::shared_ptr<TransformManager> _transform_manager;
	std::shared_ptr<SceneManager> _scene_manager;
    std::shared_ptr<AbstractDrawer> _drawer;
};
#endif
