#ifndef SEND_H
#define SEND_H

#include <QDialog>

namespace Ui {
class Send;
}

class Send : public QDialog
{
    Q_OBJECT

public:
    explicit Send(QWidget *parent = 0);
    ~Send();

private slots:
    void on_returnButton_clicked();

    void on_timeButton_clicked();

    void on_notimeButton_clicked();

    void on_sendButton_clicked();

    void on_addButton_clicked();

private:
    Ui::Send *ui;
};

#endif // SEND_H
