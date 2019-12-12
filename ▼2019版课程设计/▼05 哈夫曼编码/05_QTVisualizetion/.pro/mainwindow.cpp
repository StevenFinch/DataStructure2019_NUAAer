#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HuffmanCoding.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //固定窗口大小
    setFixedSize(800, 300);
    //调色板
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(215,219,228));
    setPalette(pal);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString aFile = QFileDialog::getOpenFileName(this,"选择要压缩的文件","","所有文件(*.*)");
    ui->lineEdit->setText(aFile);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString aFile = QFileDialog::getExistingDirectory();
    ui->lineEdit_2->setText(aFile);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString s = ui->lineEdit->text();
    QString t = ui->lineEdit_2->text();
    HuffmanCoding huf(s.toStdString(),t.toStdString());
    ui->progressBar->setValue(10);
    huf.WriteCodeTxt();
    ui->progressBar->setValue(30);
    huf.WriteSourceCodeTxt();
    ui->progressBar->setValue(50);
    int left = huf.WriteSourceCodeDat();
    ui->progressBar->setValue(left);
    ui->progressBar->setValue(70);
    huf.DecodeTargetCodeTxt(left);
    ui->progressBar->setValue(90);
    huf.DecodeTargetTxt();
    ui->progressBar->setValue(100);
}

void MainWindow::on_progressBar_valueChanged(int value)
{
    if(100 == value)
    {
        QMessageBox::information(NULL, "解压完成", "解压完成，欢迎再次使用！");
    }
}
