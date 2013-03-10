#include "widgetcurvecontrol.h"

#include "graphplotter.h"

#include <QPainter>


widgetCurveControl::widgetCurveControl(QWidget *parent)
 : QWidget(parent) {
    button = new QPushButton(this);
    checkBox = new QCheckBox(this);
    curve = new QwtPlotCurve;
    m_pGraphPlotter = NULL;

    button->setMaximumHeight(20);
    button->setMaximumWidth(40);
    checkBox->setChecked(true);

    this->setLayout(new QHBoxLayout);
    this->layout()->setContentsMargins(0,0,0,0);
    this->layout()->addWidget(checkBox);
    this->layout()->addWidget(button);
    this->layout()->addItem(new QSpacerItem(20,20,QSizePolicy::Preferred,QSizePolicy::Minimum));

    m_value.reserve(BB_PLOT_DATA_LENGTH);
    m_value.resize(BB_PLOT_DATA_LENGTH);

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
    m_buttonPixmap = QPixmap(35, 15);
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
    on_groupbox_toogled(false);
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

void widgetCurveControl::setRawSamples(std::vector<double>& timeData, int length) {
    curve->setRawSamples((double*) timeData.data(), (double*) m_value.data(), length);
}

void widgetCurveControl::shift() {
    m_value.pop_back();
    m_value.insert(m_value.begin(), m_value.front());
}

void widgetCurveControl::addNewVal(double val) {
    m_value[0] = val;
}

void widgetCurveControl::changeNValue(int val, std::vector<double>& timeData) {
    m_value.resize(val,m_value.back());
    curve->setRawSamples((double*) timeData.data(), (double*) m_value.data(), val);
}
