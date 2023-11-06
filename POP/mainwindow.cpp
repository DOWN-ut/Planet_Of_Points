#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "window.h"
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenuBar *menuBar = new QMenuBar;
    QMenu *menuWindow = menuBar->addMenu(tr("&Window"));

    setMenuBar(menuBar);
    initGLWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGLWindow()
{
    setCentralWidget(new Window(this));
}
