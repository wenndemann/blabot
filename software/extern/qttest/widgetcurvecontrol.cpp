#include "widgetcurvecontrol.h"

widgetCurveControl::widgetCurveControl(QWidget *parent) :
    QWidget(parent)
{
    button = new QPushButton(this);
    checkBox = new QCheckBox(this);
    curve = new QwtPlotCurve;

    this->setLayout(new QHBoxLayout);
    this->layout()->addWidget(checkBox);
    this->layout()->addWidget(button);

    connect(this->button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
}

widgetCurveControl::~widgetCurveControl() {
    delete curve;
}

void widgetCurveControl::setText(const std::string& text) {
    checkBox->setText(text.c_str());
}

void widgetCurveControl::on_button_clicked() {

}
