#include "graphplotter.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

GraphPlotter::GraphPlotter(QObject *parent) :
    QwtPlot()
{
}

void GraphPlotter::initialize(Ui::MainWindow *ui) {
    setTitle( "plot" );                                              //prepare GraphPlotter
    setCanvasBackground( Qt::lightGray );
    setAxisScale( QwtPlot::yLeft, -500.0, 500.0 );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( this );

}
