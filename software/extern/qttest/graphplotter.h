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
    explicit GraphPlotter();
    void initialize();
    void setCurveColor(int curve, QColor color);
    QColor getCurveColor(int curve);

private:

signals:
    
public slots:

};

#endif // GRAPHPLOTTER_H
