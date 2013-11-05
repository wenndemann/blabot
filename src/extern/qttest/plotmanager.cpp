#include "plotmanager.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

PlotManager::PlotManager(Ui::MainWindow *ui, QObject *parent) :
    QObject(parent)
{
    m_pGraphPlotter = ui->widgetPlot;
    m_pGraphPlotter->initialize(ui->spinBoxPlotAreaSize->value() * -1, ui->spinBoxPlotScaleYMin->value(),ui->spinBoxPlotScaleYMax->value());

    m_scrollBarPlotArea = ui->horizontalScrollBarPlotArea;
    m_plotDataLength = ui->spinBoxPlotAreaSize->value();

    m_timeData.resize(BB_PLOT_DATA_LENGTH);
    m_timeData.front() = 0;
    for(unsigned int i = 1; i < m_timeData.size(); i++)
        m_timeData.at(i) = m_timeData.at(i-1) - 1;

    m_vecCurves.resize(BB_PLOT_NCURVES);
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

    m_vecCurves[0]->setParams(m_pGraphPlotter, QPen(QColor(255,106,  0),2), "X");
    m_vecCurves[1]->setParams(m_pGraphPlotter, QPen(QColor(255,216,  0),2), "Y");
    m_vecCurves[2]->setParams(m_pGraphPlotter, QPen(QColor(191,255,  0),2), "Z");
    m_vecCurves[3]->setParams(m_pGraphPlotter, QPen(QColor( 85,255,  0),2), "X");
    m_vecCurves[4]->setParams(m_pGraphPlotter, QPen(QColor(  0,255, 21),2), "Y");
    m_vecCurves[5]->setParams(m_pGraphPlotter, QPen(QColor(  0,255,128),2), "Z");
    m_vecCurves[6]->setParams(m_pGraphPlotter, QPen(QColor(  0,255,234),2), "X");
    m_vecCurves[7]->setParams(m_pGraphPlotter, QPen(QColor(  0,170,255),2), "Y");
    m_vecCurves[8]->setParams(m_pGraphPlotter, QPen(QColor(  0, 64,255),2), "Z");
    m_vecCurves[9]->setParams(m_pGraphPlotter, QPen(QColor( 43,  0,255),2), "X");

    for(unsigned int i = 0; i < m_vecCurves.size(); i++)                            //add data to curves
    {
        if (m_vecCurves[i])
            m_vecCurves[i]->setRawSamples(m_timeData, BB_PLOT_DATA_LENGTH);
    }


    connect(ui->pushButtonPausePlay, SIGNAL(clicked()),this,SLOT(pausePlay()));
    connect(ui->spinBoxPlotScaleYMin, SIGNAL(valueChanged(int)), this, SLOT(changeGraphPlotterScaleYMin(int)));
    connect(ui->spinBoxPlotScaleYMax, SIGNAL(valueChanged(int)), this, SLOT(changeGraphPlotterScaleYMax(int)));
    connect(ui->spinBoxPlotsPerSecond, SIGNAL(valueChanged(int)), this, SLOT(changeReplotFPS(int)));
    connect(ui->spinBoxDataShiftsPerSecond, SIGNAL(valueChanged(int)), this, SLOT(changeShiftsFPS(int)));
    connect(m_scrollBarPlotArea, SIGNAL(valueChanged(int)), this, SLOT(changePlotArea(int)));
    connect(ui->spinBoxPlotAreaSize, SIGNAL(valueChanged(int)), this, SLOT(changePlotAreaSize(int)));



    connect(&m_timerPlot, SIGNAL(timeout()), m_pGraphPlotter, SLOT(replot()));      //connect timer to replot
    connect(&m_timerShift, SIGNAL(timeout()), this, SLOT(shift()));                 //connect timer to replot
    m_timerPlot.start(1000/BB_PLOT_REPLOT_FPS);                                     //start timer to replot
    m_timerShift.start(1000/BB_PLOT_READ_FPS);                                      //start timer to replot

    // pseudo data
    m_bDrawPseudo = ui->groupBoxPseudo->isChecked();
    connect(ui->checkBoxPseudo, SIGNAL(toggled(bool)), this, SLOT(setDrawPseudo(bool)));

    m_pUi = ui;
}

void PlotManager::addNewValue(int curve, double val) {
    m_vecCurves[curve]->addNewVal(val);
}

void PlotManager::shift() {

    if (m_bDrawPseudo) {
        static float offset=0.0f;
        offset+=0.003f;

        float accX, accY, accZ;
        accX = accY = accZ = 0.0f;

        for(unsigned int i = 0; i < m_vecCurves.size(); i++) {

            float val = 0.0f;

            if (i < 3) {
                val = sin(offset + (i*M_PI)/3)*500;
            }
            else {
                val = sin(offset+(i*M_2PI)/m_vecCurves.size())*500;
            }

            if (m_vecCurves[i])
                m_vecCurves[i]->addNewVal(val);

            switch(i) {
                case 0: accX = val; break;
                case 1: accY = val; break;
                case 2: accZ = val; break;
                default: break;
            }

            if (i == 2) {
                SensorData::sensorData_s data;
                data.acc.x = accX; data.acc.y = accY; data.acc.z = accZ;
                m_pUi->widgetVisualization->setRotation(data);
            }

        }

    }


    for(unsigned int i = 0; i < m_vecCurves.size(); i++)                            //shift data in data array
    {
        if (m_vecCurves[i])
            m_vecCurves[i]->shift();
    }
}

void PlotManager::pausePlay() {
    if (m_timerPlot.isActive())
        m_timerPlot.stop();
    else
        m_timerPlot.start(1000/BB_PLOT_REPLOT_FPS);
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

void PlotManager::changePlotAreaSize(int val) {
    int iLastDiff = m_scrollBarPlotArea->maximum() - m_scrollBarPlotArea->value();
    m_plotDataLength = val;
    m_scrollBarPlotArea->setMaximum(BB_PLOT_DATA_LENGTH - val);
    m_scrollBarPlotArea->setMinimum(0);
    m_scrollBarPlotArea->setSliderPosition(m_scrollBarPlotArea->maximum() - iLastDiff);
}

void PlotManager::changePlotArea(int val) {
    m_pGraphPlotter->setAxisScale(QwtPlot::xBottom, (BB_PLOT_DATA_LENGTH - val ) * -1, (BB_PLOT_DATA_LENGTH - val - m_plotDataLength) * -1);
}

// psuedo data
void PlotManager::setDrawPseudo(bool bChecked) {
    m_bDrawPseudo = bChecked;
}
