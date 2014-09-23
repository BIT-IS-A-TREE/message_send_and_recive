#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_closeButton_clicked();

    void on_tosendButton_clicked();

    void on_searchButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H