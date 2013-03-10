#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphplotter.h"

#include <QFileDialog>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Graphplotter
    plotManager = new PlotManager(ui);

    // TCP/IP
    pTcpIp = new TCPIP(this);
    connect(ui->pushButtonConnect, SIGNAL(clicked()), pTcpIp, SLOT(createConnection()));

    // other connections
    connect(ui->pushButtonScreenshot, SIGNAL(clicked()), this, SLOT(takeScreenshot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::takeScreenshot()
{
    QPixmap pixmap(this->width(), this->height());
    QPainter painter(&pixmap);
    this->render(&painter);
    painter.end();

    QString fileName(QFileDialog::getSaveFileName());
    if (!fileName.isEmpty())
        pixmap.save(fileName, "PNG");
}
