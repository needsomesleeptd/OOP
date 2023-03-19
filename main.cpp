#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	w.setMinimumSize(700,700);
//w.setSizePolicy(QSizePolicy::MinimumE, QSizePolicy::Minimum);
    w.show();
    return a.exec();
}
