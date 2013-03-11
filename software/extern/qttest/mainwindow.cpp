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

    ui->spinBoxPlotAreaSize->setValue(1000);
    ui->horizontalScrollBarPlotArea->setMaximum(BB_PLOT_DATA_LENGTH - 1000);
    ui->horizontalScrollBarPlotArea->setValue(BB_PLOT_DATA_LENGTH - 1000);
    ui->spinBoxDataShiftsPerSecond->setValue(BB_PLOT_READ_FPS);
    ui->spinBoxPlotsPerSecond->setValue(BB_PLOT_REPLOT_FPS);

    // Graphplotter
    plotManager = new PlotManager(ui);

    // TCP/IP
    pTcpIp = new TCPIP(this);
    connect(ui->pushButtonConnect, SIGNAL(clicked()), this, SLOT(tcpIpConnect()));

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

void MainWindow::tcpIpConnect() {
    pTcpIp->connect(ui->lineEditIP->text(), ui->spinBoxPort->value(), plotManager);
}
