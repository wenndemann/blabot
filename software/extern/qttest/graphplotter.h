#ifndef GRAPHPLOTTER_H
#define GRAPHPLOTTER_H

#include <qapplication.h>
#include <QTimer>
#include <QPushButton>
#include <QCheckBox>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <math.h>

#include <widgetcurvecontrol.h>

class GraphPlotter : public QwtPlot
{
    Q_OBJECT
public:
    explicit GraphPlotter(QObject *parent = 0);
    void initialize(int scaleYMin, int scaleYMax);
    void setCurveColor(int curve, QColor color);
    QColor getCurveColor(int curve);

    void setScaleYMin(int val) {m_scaleYMin = val; }
    void setScaleYMax(int val) {m_scaleYMax = val; }
    int getScaleYMin() { return m_scaleYMin; }
    int getScaleYMax() { return m_scaleYMax; }

private:
    int m_scaleYMin, m_scaleYMax;
signals:
    
public:

};

#endif // GRAPHPLOTTER_H
