#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileInfoList>
#include <QStandardItem>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->overallProgressBar->reset(); //让进度条重新回到开始
    ui->overallProgressBar->setVisible(false);  //false:隐藏进度条  true:显示进度条
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_scanDisk_clicked()
{
    QFileInfoList list =  QDir::drives();  //获取当前系统的盘符
    this->ui->disksView->setRowCount(list.size());
     this->ui->disksView->setColumnCount(3);
    QString path;
    for(int i=0;i<list.count();i++){
        path = list[i].filePath();
        UINT ret = GetDriveType((WCHAR *) path.utf16());
        if(ret == DRIVE_REMOVABLE)
            this->ui->disksView->setItem(i,0, new QTableWidgetItem(path + u8" (可移动磁盘)"));
        else
            this->ui->disksView->setItem(i,0, new QTableWidgetItem(path));
    }

}
