#ifndef THREADDIALOG_H
#define THREADDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ThreadDialog; }
QT_END_NAMESPACE

class ThreadDialog : public QDialog
{
    Q_OBJECT

public:
    ThreadDialog(QWidget *parent = nullptr);
    ~ThreadDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::ThreadDialog *ui;
};
#endif // THREADDIALOG_H
