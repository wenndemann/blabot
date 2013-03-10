#include "plotmanager.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

PlotManager::PlotManager(Ui::MainWindow *ui, QObject *parent) :
    QObject(parent)
{
    m_pGraphPlotter = ui->widgetPlot;
    m_pGraphPlotter->initialize(ui->spinBoxPlotScaleXMin->value() * -1, ui->spinBoxPlotScaleYMin->value(),ui->spinBoxPlotScaleYMax->value());


    m_timeData.reserve(ui->spinBoxPlotScaleXMin->value());
    m_timeData.resize(ui->spinBoxPlotScaleXMin->value());
    m_timeData.front() = 0;
    for(unsigned int i = 1; i < m_timeData.size(); i++)
        m_timeData.at(i) = m_timeData.at(i-1) - 1;

    m_vecCurves.resize(ui->spinBoxPlotScaleXMin->value());

    m_vecCurves[0] = ui->widgetCurveControlAccelX;
    m_vecCurves[1] = ui->widgetCurveControlAccelY;
    m_vecCurves[2] = ui->widgetCurveControlAccelZ;
    m_vecCurves[3] = ui->widgetCurveControlGyroX;
    m_vecCurves[4] = ui->widgetCurveControlGyroY;
    m_vecCurves[5] = ui->widgetCurveControlGyroZ;
    m_vecCurves[6] = ui->widgetCurveControlMagX;
    m_vecCurves[7] = ui->widgetCurveControlMagY;
    m_vecCurves[8] = ui->widgetCurveControlMagZ;
    m_vecCurves[9] = ui->widgetCurveControlPoti;

    m_vecCurves[0]->setParams(m_pGraphPlotter, QPen(QColor(255,106,  0),3), "X");
    m_vecCurves[1]->setParams(m_pGraphPlotter, QPen(QColor(255,216,  0),3), "Y");
    m_vecCurves[2]->setParams(m_pGraphPlotter, QPen(QColor(191,255,  0),3), "Z");
    m_vecCurves[3]->setParams(m_pGraphPlotter, QPen(QColor( 85,255,  0),3), "X");
    m_vecCurves[4]->setParams(m_pGraphPlotter, QPen(QColor(  0,255, 21),3), "Y");
    m_vecCurves[5]->setParams(m_pGraphPlotter, QPen(QColor(  0,255,128),3), "Z");
    m_vecCurves[6]->setParams(m_pGraphPlotter, QPen(QColor(  0,255,234),3), "X");
    m_vecCurves[7]->setParams(m_pGraphPlotter, QPen(QColor(  0,170,255),3), "Y");
    m_vecCurves[8]->setParams(m_pGraphPlotter, QPen(QColor(  0, 64,255),3), "Z");
    m_vecCurves[9]->setParams(m_pGraphPlotter, QPen(QColor( 43,  0,255),3), "X");

    for(unsigned int i = 0; i < m_vecCurves.size(); i++)                            //add data to curves
    {
        if (m_vecCurves[i])
            m_vecCurves[i]->setRawSamples(m_timeData, ui->spinBoxPlotScaleXMin->value());
    }


    connect(ui->pushButtonPausePlay, SIGNAL(clicked()),this,SLOT(pausePlay()));
    connect(ui->spinBoxPlotScaleXMin, SIGNAL(valueChanged(int)), this, SLOT(changeGraphPlotterScaleXMin(int)));
    connect(ui->spinBoxPlotScaleYMin, SIGNAL(valueChanged(int)), this, SLOT(changeGraphPlotterScaleYMin(int)));
    connect(ui->spinBoxPlotsPerSecond, SIGNAL(valueChanged(int)), this, SLOT(changeReplotFPS(int)));
    connect(ui->spinBoxDataShiftsPerSecond, SIGNAL(valueChanged(int)), this, SLOT(changeShiftsFPS(int)));



    connect(&m_timerPlot, SIGNAL(timeout()), m_pGraphPlotter, SLOT(replot()));      //connect timer to replot
    connect(&m_timerShift, SIGNAL(timeout()), this, SLOT(shift()));                 //connect timer to replot
    m_timerPlot.start(1000/BB_PLOT_REPLOT_FPS);                                     //start timer to replot
    m_timerShift.start(1000/BB_PLOT_READ_FPS);                                      //start timer to replot
}

void PlotManager::addNewValue(int curve, double val) {
    m_vecCurves[curve]->addNewVal(val);
}

void PlotManager::shift() {
    static float i=0;
    i+=0.03;

    for(unsigned int i = 0; i < m_vecCurves.size(); i++)                            //shift data in data array
    {
        if (m_vecCurves[i])
            m_vecCurves[i]->shift();
    }
    m_vecCurves[9]->addNewVal(sin(i)*250);                                          //add new value to data array
    //m_vecCurves[1]->addNewVal(sin(i+M_2PI/3)*250);
    //m_vecCurves[2]->addNewVal(sin(i+M_2PI/3*2)*250);
}

void PlotManager::pausePlay() {
    if (m_timerPlot.isActive())
        m_timerPlot.stop();
    else
        m_timerPlot.start(1000/BB_PLOT_REPLOT_FPS);
}

void PlotManager::changeGraphPlotterScaleXMin(int val) {
    m_pGraphPlotter->setScaleXMin(val * -1);
    m_pGraphPlotter->setAxisScale(QwtPlot::xBottom, val * -1, 0);

    m_timeData.resize(val);
    m_timeData[0] = 0;
    for(unsigned int i = 1; i < m_timeData.size(); i++)
        m_timeData.at(i) = m_timeData.at(i-1) - 1;

    for(unsigned int i = 0; i < m_vecCurves.size(); i++)
    {
        if (m_vecCurves[i])
            m_vecCurves[i]->changeNValue(val, m_timeData);
    }
}
void PlotManager::changeGraphPlotterScaleYMin(int val) {
    m_pGraphPlotter->setScaleYMin(val);
    m_pGraphPlotter->setAxisScale(QwtPlot::yLeft, val, m_pGraphPlotter->getScaleYMax());
}

void PlotManager::changeGraphPlotterScaleYMax(int val) {
    m_pGraphPlotter->setScaleYMax(val);
    m_pGraphPlotter->setAxisScale(QwtPlot::yLeft, m_pGraphPlotter->getScaleYMin(), val);
}
void PlotManager::changeReplotFPS(int val) {
    m_timerPlot.setInterval(1000/val);
}

void PlotManager::changeShiftsFPS(int val) {
    m_timerShift.setInterval(1000/val);
}
