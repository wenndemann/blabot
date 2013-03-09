#include "widgetcurvecontrol.h"

#include "graphplotter.h"

#include <QPainter>


widgetCurveControl::widgetCurveControl(QWidget *parent)
 : QWidget(parent) {
    button = new QPushButton(this);
    checkBox = new QCheckBox(this);
    curve = new QwtPlotCurve;
    m_pGraphPlotter = NULL;

    checkBox->setChecked(true);

    this->setLayout(new QHBoxLayout);
    this->layout()->addWidget(checkBox);
    this->layout()->addWidget(button);

    bzero(value, sizeof(value));

    connect(this->button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
    connect(this->checkBox, SIGNAL(toggled(bool)), this, SLOT(on_checkBox_toggled(bool)));
    connect(qobject_cast<QGroupBox*>(parent),SIGNAL(toggled(bool)),this, SLOT(on_groupbox_toogled(bool)));
}

widgetCurveControl::~widgetCurveControl() {
    delete curve;
}

void widgetCurveControl::on_button_clicked() {
    m_qcolor = QColorDialog::getColor(m_qcolor, this);
    curve->setPen(QPen(m_qcolor, 2));
    redrawButton();
}

void widgetCurveControl::redrawButton() {
    m_buttonPixmap = QPixmap(60, 20);
    m_buttonPixmap.fill(m_qcolor);
    m_buttonPixmap.fill(m_qcolor);
    QIcon icon(m_buttonPixmap);
    button->setIcon(icon);
    button->setIconSize(m_buttonPixmap.size());
}

void widgetCurveControl::on_groupbox_toogled(bool val) {
    if (!val)
        curve->detach();
    else if (m_bState)
        curve->attach(m_pGraphPlotter);
}

void widgetCurveControl::on_checkBox_toggled(bool val) {
    m_bState = val;
    if (m_pGraphPlotter) {
        if(m_bState)
            curve->attach(m_pGraphPlotter);
        else
            curve->detach();
    }
}


void widgetCurveControl::setParams(GraphPlotter *pGraphPlotter, const QPen& pen, const std::string& text) {
    m_pGraphPlotter = pGraphPlotter;
    setText(text);
    setPen(pen);
    on_checkBox_toggled(true);
}

void widgetCurveControl::setText(const std::string& text) {
    checkBox->setText(text.c_str());
}

void widgetCurveControl::setPen(const QPen& pen) {
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    curve->setPen(pen);
    m_qcolor = pen.color();
    redrawButton();
}

void widgetCurveControl::setRawSamples(double *timeData, int length) {
    curve->setRawSamples(timeData, value, length);
}

void widgetCurveControl::addNewVal(double val) {
    value[0] = val;
}

void widgetCurveControl::shift() {
    memmove(&value[1], &value[0], sizeof(value)-sizeof(double));
}
