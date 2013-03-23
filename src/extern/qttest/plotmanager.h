#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

#include <QObject>
#include <QScrollBar>
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
    QScrollBar *m_scrollBarPlotArea;
    long m_plotDataLength;

    Ui::MainWindow *m_pUi;

    // psuedo data
    bool m_bDrawPseudo;

signals:

private slots:
    void shift();
    void pausePlay();
    void changeGraphPlotterScaleYMin(int val);
    void changeGraphPlotterScaleYMax(int val);
    void changeReplotFPS(int val);
    void changeShiftsFPS(int val);
    void changePlotAreaSize(int);
    void changePlotArea(int val);

    // psuedo data
    void setDrawPseudo(bool);

public slots:
    
};

#endif // PLOTMANAGER_H
