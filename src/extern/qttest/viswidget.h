#ifndef VISWIDGET_H
#define VISWIDGET_H

#include <QGLWidget>
#include <QQuaternion>
#include <QTimer>
#include <QMutex>

#include "defs.h"

class VisWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit VisWidget(QWidget *parent = 0);
    virtual ~VisWidget();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void setRotation(SensorData::sensorData_s data);
    void setEulerAngles(float pitch, float yaw, float roll);

signals:
    
public slots:
    void setEulerX(int pitch);
    void setEulerY(int yaw);
    void setEulerZ(int roll);
    
private:
    float m_yaw, m_pitch, m_roll;

    QTimer *m_qtimer;
    QMutex *m_qmutex;
};

#endif // VISWIDGET_H
