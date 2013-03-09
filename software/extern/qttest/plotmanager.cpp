#include "plotmanager.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

PlotManager::PlotManager(Ui::MainWindow *ui, QObject *parent) :
    QObject(parent)
{
    ui->widgetPlot->initialize(ui);
    m_pGraphPlotter = ui->widgetPlot;

    m_timeData[0] = 0;
    for(int i = 1; i < BB_PLOT_DATA_LENGTH; i++)
        m_timeData[i] = m_timeData[i-1] - 1;

    m_vecCurves.resize(BB_PLOT_NCURVES, NULL);

    m_vecCurves[0] = ui->widgetCurveControlAccelX;
    m_vecCurves[1] = ui->widgetCurveControlAccelY;
    m_vecCurves[2] = ui->widgetCurveControlAccelZ;

    m_vecCurves[0]->setParams(m_pGraphPlotter, QPen(Qt::red,2), "X");
    m_vecCurves[1]->setParams(m_pGraphPlotter, QPen(Qt::green,2), "Y");
    m_vecCurves[2]->setParams(m_pGraphPlotter, QPen(Qt::blue,2), "Z");

    for(unsigned int i = 0; i < m_vecCurves.size(); i++)                            //add data to curves
    {
        if (m_vecCurves[i])
            m_vecCurves[i]->setRawSamples(m_timeData, BB_PLOT_DATA_LENGTH);
    }


    connect(ui->pushButtonPausePlay, SIGNAL(clicked()),this,SLOT(pausePlay()));
    connect(&m_timerPlot, SIGNAL(timeout()), m_pGraphPlotter, SLOT(replot()));      //connect timer to replot
    connect(&m_timerShift, SIGNAL(timeout()), this, SLOT(shift()));                 //connect timer to replot
    m_timerPlot.start(1000/BB_PLOT_REPLOT_FPS);                                     //start timer to replot
    m_timerShift.start(1000/BB_PLOT_READ_FPS);                                      //start timer to replot
}

void PlotManager::shift() {
    static float i=0;
    i+=0.03;

    for(unsigned int i = 0; i < m_vecCurves.size(); i++)                            //shift data in data array
    {
        if (m_vecCurves[i])
            m_vecCurves[i]->shift();
    }
    m_vecCurves[0]->addNewVal(sin(i)*250);                                    //add new value to data array
    m_vecCurves[1]->addNewVal(sin(i+M_2PI/3)*250);
    m_vecCurves[2]->addNewVal(sin(i+M_2PI/3*2)*250);
}

void PlotManager::pausePlay() {
    if (m_timerPlot.isActive())
        m_timerPlot.stop();
    else
        m_timerPlot.start(1000/BB_PLOT_REPLOT_FPS);
}
