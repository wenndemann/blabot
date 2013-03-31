#ifndef VISWIDGET_H
#define VISWIDGET_H

#include <QGLWidget>
#include <QQuaternion>
#include <QTimer>
#include <QMutex>

class VisWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit VisWidget(QWidget *parent = 0);
    virtual ~VisWidget();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void setRotation(float NormX, float NormY, float NormZ);
    void setRotation(float AngleRot, float NormX, float NormY, float NormZ);
    void setQuaternions(float SEq_1, float SEq_2, float SEq_3, float SEq_4);
    void setQuaternions(QQuaternion *q);

signals:
    
public slots:
    
private:
    float m_fAngleRot, m_fNormX, m_fNormY, m_fNormZ;

    QQuaternion m_qQuaternion;
    float m_fQuaternion_1, m_fQuaternion_2, m_fQuaternion_3, m_fQuaternion_4;

    QVector3D m_qvec3dRotation;

    QTimer *m_qtimer;
    QMutex *m_qmutex;
};

#endif // VISWIDGET_H
