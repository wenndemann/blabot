#include "graphplotter.h"

GraphPlotter::GraphPlotter(QObject *parent) :
    QwtPlot()
{
}

void GraphPlotter::initialize(int scaleYMin, int scaleYMax) {
    m_scaleYMin = scaleYMin;
    m_scaleYMax = scaleYMax;
    setTitle( "plot" );                                              //prepare GraphPlotter
    setCanvasBackground( Qt::lightGray );
    setAxisScale( QwtPlot::yLeft, m_scaleYMin, m_scaleYMax);

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( this );
}
