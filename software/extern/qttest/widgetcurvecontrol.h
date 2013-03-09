#ifndef WIDGETCURVECONTROL_H
#define WIDGETCURVECONTROL_H

#include <QWidget>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <qwt_plot_curve.h>

#define BB_PLOT_DATA_LENGTH 200

class widgetCurveControl : public QWidget
{
    Q_OBJECT
public:
    explicit widgetCurveControl(QWidget *parent = 0);
    ~widgetCurveControl();
    void setText(const std::string& text);

private:
    QPushButton *button;
    QCheckBox *checkBox;
    QwtPlotCurve *curve;
    double value[BB_PLOT_DATA_LENGTH];

signals:
    
public slots:
    void on_button_clicked();
    
};

#endif // WIDGETCURVECONTROL_H
