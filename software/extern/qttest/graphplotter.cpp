#include "graphplotter.h"

GraphPlotter::GraphPlotter() :
    QwtPlot()
{
}

void GraphPlotter::initialize() {
    setTitle( "plot" );                                              //prepare GraphPlotter
    setCanvasBackground( Qt::lightGray );
    setAxisScale( QwtPlot::yLeft, -500.0, 500.0 );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( this );
}
