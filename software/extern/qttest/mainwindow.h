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

#include "graphplotter.h"
#include "tcpip.h"

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
    void on_checkBoxAccelX_clicked(bool checked);
    void on_checkBoxAccelY_clicked(bool checked);
    void on_checkBoxAccelZ_clicked(bool checked);    
    void on_pushButtonAccelXColor_clicked();

    void on_pushButtonAccelYColor_clicked();

    void on_pushButtonAccelZColor_clicked();

private:
    Ui::MainWindow *ui;

    TCPIP *pTcpIp;
};

#endif // MAINWINDOW_H
