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
    std::vector<double> m_timeData;
    std::vector<widgetCurveControl*> m_vecCurves;

    QTimer m_timerPlot;
    QTimer m_timerShift;
signals:

private slots:
    void shift();
    void pausePlay();
    void changeGraphPlotterScaleXMin(int val);
    void changeGraphPlotterScaleYMin(int val);
    void changeGraphPlotterScaleYMax(int val);
    void changeReplotFPS(int val);
    void changeShiftsFPS(int val);

public slots:
    
};

#endif // PLOTMANAGER_H
