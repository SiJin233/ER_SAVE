#ifndef NOTES_H
#define NOTES_H

#include <QDialog>
#include<QSettings>
namespace Ui {
class notes;
}

class notes : public QDialog
{
    Q_OBJECT

public:
    explicit notes(QWidget *parent = nullptr);
    QString loc;
    ~notes();

signals:
    void notessuccess(QString);
private slots:
    void on_notescreate(QString,QWidget*);

    void on_save_clicked();

private:
    Ui::notes *ui;
};

#endif // NOTES_H
