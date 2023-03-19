#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_apply_rotate_clicked();

	void on_load_model_clicked();

	void on_apply_scale_clicked();

	void on_apply_move_clicked();

	void on_save_model_clicked();

    void on_revert_step_clicked();

	void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
	void redraw_figure();

};
#endif // MAINWINDOW_H
