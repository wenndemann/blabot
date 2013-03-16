#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QApplication>
#include <QSignalMapper>
#include <QColorDialog>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

#include "tcpip.h"
#include "plotmanager.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void takeScreenshot();
    void tcpIpConnect();
    void tcpIpDisconnect();
private:
    Ui::MainWindow *ui;
    PlotManager *plotManager;
    TCPIP *pTcpIp;
};

#endif // MAINWINDOW_H
