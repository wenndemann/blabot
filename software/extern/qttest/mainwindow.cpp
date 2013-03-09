#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Graphplotter
    ui->widgetPlot->initialize();
    ui->widgetPlot->setEnableCurve(0,true);
    ui->widgetPlot->setEnableCurve(1,true);
    ui->widgetPlot->setEnableCurve(2,true);

    // MainWindow
    QPalette pal;
    QColor color = ui->widgetPlot->getCurveColor(0);
    pal.setColor(ui->pushButtonAccelXColor->backgroundRole(), color);
    ui->pushButtonAccelXColor->setPalette(pal);

    color = ui->widgetPlot->getCurveColor(1);
    pal.setColor(ui->pushButtonAccelYColor->backgroundRole(), color);
    ui->pushButtonAccelYColor->setPalette(pal);

    color = ui->widgetPlot->getCurveColor(2);
    pal.setColor(ui->pushButtonAccelZColor->backgroundRole(), color);
    ui->pushButtonAccelZColor->setPalette(pal);

    // TCP/IP
    pTcpIp = new TCPIP(this);
    connect(ui->pushButtonConnect, SIGNAL(clicked()), pTcpIp, SLOT(createConnection()));

    /*
    QSignalMapper* signalMapper = new QSignalMapper(this);
    connect(ui->pushButtonConnect, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButtonConnect, ui);
    connect(signalMapper, SIGNAL(mapped(std::string, int)), pTcpIp, SLOT(createConnection(std::string, int)));
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBoxAccelX_clicked(bool checked)
{
    ui->widgetPlot->setEnableCurve(0,checked);
}

void MainWindow::on_checkBoxAccelY_clicked(bool checked)
{
    ui->widgetPlot->setEnableCurve(1,checked);
}

void MainWindow::on_checkBoxAccelZ_clicked(bool checked)
{
    ui->widgetPlot->setEnableCurve(2,checked);
}

void MainWindow::on_pushButtonAccelXColor_clicked()
{
    QPushButton *sender = qobject_cast<QPushButton *>(this->sender());
    QPalette pal = sender->palette();
    QColor color = sender->palette().color(sender->backgroundRole());

    color = QColorDialog::getColor(color, this);
    pal.setColor(sender->backgroundRole(), color);
    sender->setPalette(pal);
    ui->widgetPlot->setCurveColor(0, color);
}

void MainWindow::on_pushButtonAccelYColor_clicked()
{
    QPushButton *sender = qobject_cast<QPushButton *>(this->sender());
    QPalette pal = sender->palette();
    QColor color = sender->palette().color(sender->backgroundRole());

    color = QColorDialog::getColor(color, this);
    pal.setColor(sender->backgroundRole(), color);
    sender->setPalette(pal);
    ui->widgetPlot->setCurveColor(1, color);
}

void MainWindow::on_pushButtonAccelZColor_clicked()
{
    QPushButton *sender = qobject_cast<QPushButton *>(this->sender());
    QPalette pal = sender->palette();
    QColor color = sender->palette().color(sender->backgroundRole());

    color = QColorDialog::getColor(color, this);
    pal.setColor(sender->backgroundRole(), color);
    sender->setPalette(pal);
    ui->widgetPlot->setCurveColor(2, color);
}
