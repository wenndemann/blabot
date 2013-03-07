#include "graphplotter.h"

GraphPlotter::GraphPlotter(QObject *parent) :
    QwtPlot()
{
    connect(&m_timer, SIGNAL(timeout()),this, SLOT(plot()));            //connect timer to replot
}

void GraphPlotter::initialize() {
    setTitle( "plot" );                                              //prepare GraphPlotter
    setCanvasBackground( Qt::lightGray );
    setAxisScale( QwtPlot::yLeft, -500.0, 500.0 );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( this );

    m_timeData[0] = 0;
    for(int i = 1; i < BB_PLOT_SIZE; i++)
        m_timeData[i] = m_timeData[i-1] - 1;

    for(int i = 0; i < BB_PLOT_NCURVES; i++)
        bzero(&m_data[i], sizeof(m_data[i]));

    QwtPlotCurve *curve;                                                //add curves to GraphPlotter

    curve = new QwtPlotCurve;
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    curve->setPen(QPen(Qt::red,2));
    m_data[0].curve = curve;

    curve = new QwtPlotCurve;
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    curve->setPen(QPen(Qt::blue,2));
    m_data[1].curve = curve;

    curve = new QwtPlotCurve;
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    curve->setPen(QPen(Qt::green,2));
    m_data[2].curve = curve;

    for(int i = 0; i < BB_PLOT_NCURVES; i++)                            //add data to curves
        m_data[i].curve->setRawSamples(m_timeData, m_data[i].value,BB_PLOT_SIZE);

    m_timer.start(10);                                                  //start timer to replot
}

void GraphPlotter::plot() {
    static float i=0;
    i+=0.03;

    for(int i = 0; i < BB_PLOT_NCURVES; i++)                            //shift data in data array
        memcpy(&m_data[i].value[1], &m_data[i].value[0], sizeof(m_data[i].value)-sizeof(double));
    m_data[0].value[0] = sin(i)*250;                                    //add new value to data array
    m_data[1].value[0] = sin(i+M_2PI/3)*250;
    m_data[2].value[0] = sin(i+M_2PI/3*2)*250;

    this->replot();
}

void GraphPlotter::setEnableCurve(int curve, bool state) {
    if(state) {
        m_data[curve].curve->attach(this);
    }
    else {
        m_data[curve].curve->detach();
    }
}

void GraphPlotter::setCurveColor(int curve, QColor color) {
    m_data[curve].curve->setPen(QPen(color,2));
}

QColor GraphPlotter::getCurveColor(int curve) {
    return m_data[curve].curve->pen().color();
}
