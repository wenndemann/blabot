#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

#include <QObject>
#include <QTimer>
#include "graphplotter.h"
#include "widgetcurvecontrol.h"

namespace Ui{
    class MainWindow;
}

class PlotManager : public QObject
{
    Q_OBJECT
public:
    explicit PlotManager(Ui::MainWindow *ui, QObject *parent = 0);
    void addNewValue(int curve, double val);

private:
    GraphPlotter *m_pGraphPlotter;
    double m_timeData[BB_PLOT_DATA_LENGTH];
    std::vector<widgetCurveControl*> m_vecCurves;

    QTimer m_timerPlot;
    QTimer m_timerShift;
signals:

private slots:
    void shift();
    void pausePlay();
    void changeGraphPlotterScaleYMin(int val);
    void changeGraphPlotterScaleYMax(int val);

public slots:
    
};

#endif // PLOTMANAGER_H
