#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QSound>
#include <QFile>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* e) {
    QPainter painter(this);
    QImage s(":/arrows/MArrow","png");
    painter.drawImage(0,0,s.scaled(100,100,Qt::KeepAspectRatio,Qt::SmoothTransformation),0,0,1000,1000);
}
