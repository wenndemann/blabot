#ifndef VISWIDGET_H
#define VISWIDGET_H

#include <QGLWidget>
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

    void setRotation(float AngleX, float AngleY, float AngleZ);
    
signals:
    
public slots:
    
private:
    float m_fAngleRot, m_fNormX, m_fNormY, m_fNormZ;

    QTimer *m_qtimer;
    QMutex *m_qmutex;
};

#endif // VISWIDGET_H
