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
    connect(ui->pushButtonDisconnect, SIGNAL(clicked()), this, SLOT(tcpIpDisconnect()));
    connect(ui->toolButtonGetMeasuingInterval, SIGNAL(clicked()), this, SLOT(tcpIpGetMeasuringInterval()));
    connect(ui->toolButtonSetMeasuingInterval, SIGNAL(clicked()), this, SLOT(tcpIpSetMeasuringInterval()));

    // Visualization
    connect(pTcpIp, SIGNAL(measuredRotation(float)), this->ui->widgetVisualization, SLOT(setRotation(float)));

    // other connections
    connect(ui->pushButtonScreenshot, SIGNAL(clicked()), this, SLOT(takeScreenshot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

PlotManager* MainWindow::getPlotManagerPtr() {
    return plotManager;
}

VisWidget* MainWindow::getWidgetVisualizationPtr() {
    return this->ui->widgetVisualization;
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
    pTcpIp->connect(ui->lineEditIP->text(), ui->spinBoxPort->value(), this);
}

void MainWindow::tcpIpDisconnect() {
    pTcpIp->disconnect();
}

void MainWindow::tcpIpGetMeasuringInterval() {
    pTcpIp->getMeasuringIntervalMs(); // send the command to get the measuring interva
}

void MainWindow::tcpIpGetMeasuringInterval(quint16 val) {
    ui->spinBoxMeasuingInterval->setValue(val); // receive the new measuring data
}

void MainWindow::tcpIpSetMeasuringInterval() {
    pTcpIp->setMeasuringIntervalMs(ui->spinBoxMeasuingInterval->value());
}
