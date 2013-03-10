#ifndef WIDGETCURVECONTROL_H
#define WIDGETCURVECONTROL_H

#include <QWidget>
#include <QCheckBox>
#include <QColorDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <qwt_plot_curve.h>
#include "defs.h"

class GraphPlotter;

class widgetCurveControl : public QWidget
{
    Q_OBJECT
public:
    explicit widgetCurveControl(QWidget *parent = 0);
    ~widgetCurveControl();

private:
    QPushButton *button;
    QCheckBox *checkBox;
    QwtPlotCurve *curve;
    GraphPlotter *m_pGraphPlotter;
    bool m_bState;
    double value[BB_PLOT_DATA_LENGTH];
    QColor m_qcolor;
    QPixmap m_buttonPixmap;

signals:
    
public slots:
    void on_button_clicked();
    void on_checkBox_toggled(bool val);
    void on_groupbox_toogled(bool val);

public:
    void setParams(GraphPlotter *pGraphPlotter, const QPen& pen, const std::string& text);
    void setPen(const QPen& pen);
    void setText(const std::string& text);
    void setRawSamples(double *timeData, int length);

    void shift();
    void addNewVal(double val);

    // TODO remove later
    QwtPlotCurve* getCurvePtr() { return curve; }

private:
    void redrawButton();
    
};

#endif // WIDGETCURVECONTROL_H
