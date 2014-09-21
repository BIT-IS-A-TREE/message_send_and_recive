#ifndef CHAT_H
#define CHAT_H

#include <QDialog>

namespace Ui {
class Chat;
}

class Chat : public QDialog
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = 0);
    ~Chat();

private slots:
    void on_clearButton_clicked();

    void on_deleteButton_clicked();

    void on_returnButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::Chat *ui;
};

#endif // CHAT_H
