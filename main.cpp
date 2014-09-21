#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QDialog>
#include "login.h"
#include <QtGui>
#include <QFrame>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Login login;

    if(login.exec()==QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
    return 0;

}
