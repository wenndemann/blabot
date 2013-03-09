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

namespace Ui {
    class MainWindow;
}

class GraphPlotter : public QwtPlot
{
    Q_OBJECT
public:
    explicit GraphPlotter(QObject *parent = 0);
    void initialize(Ui::MainWindow *ui);
    void setCurveColor(int curve, QColor color);
    QColor getCurveColor(int curve);

private:

signals:
    
public slots:

};

#endif // GRAPHPLOTTER_H
