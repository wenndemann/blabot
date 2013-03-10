#include "graphplotter.h"

GraphPlotter::GraphPlotter(QObject *parent) :
    QwtPlot()
{
}

void GraphPlotter::initialize(int scaleXMin, int scaleYMin, int scaleYMax) {
    m_scaleXMin = scaleXMin;
    m_scaleYMin = scaleYMin;
    m_scaleYMax = scaleYMax;

    setTitle( "plot" );                                              //prepare GraphPlotter
    setCanvasBackground( Qt::black );
    setAxisScale( QwtPlot::yLeft, m_scaleYMin, m_scaleYMax);
    setAxisScale( QwtPlot::xBottom, m_scaleXMin, 0.0);

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen(QPen(QColor(100,100,100)));
    grid->attach( this );
}
