#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QDialog>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login *login=new Login();
    login->show();

   return a.exec();


}
