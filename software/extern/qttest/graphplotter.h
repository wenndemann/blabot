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

#define BB_PLOT_SIZE 200
#define BB_PLOT_NCURVES 3

class GraphPlotter : public QwtPlot
{
    Q_OBJECT
public:
    explicit GraphPlotter(QObject *parent = 0);
    void initialize();
    void setEnableCurve(int curve, bool state);
    void setCurveColor(int curve, QColor color);
    QColor getCurveColor(int curve);

private:
    QTimer m_timer;

    struct {
        double value[BB_PLOT_SIZE];
        QwtPlotCurve *curve;
    }m_data[BB_PLOT_NCURVES];

    double m_timeData[BB_PLOT_SIZE];

signals:
    
public slots:
    void plot();

};

#endif // GRAPHPLOTTER_H
