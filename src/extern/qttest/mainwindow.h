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
#include "viswidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    PlotManager* getPlotManagerPtr();
    VisWidget* getWidgetVisualizationPtr();
    
private slots:
    void takeScreenshot();
    void tcpIpConnect();
    void tcpIpDisconnect();
    void tcpIpGetMeasuringInterval();
    void tcpIpGetMeasuringInterval(quint16 val);
    void tcpIpSetMeasuringInterval();

private:
    Ui::MainWindow *ui;
    PlotManager *plotManager;
    TCPIP *pTcpIp;
};

#endif // MAINWINDOW_H
