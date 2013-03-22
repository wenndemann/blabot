#include "viswidget.h"
#include <math.h>

VisWidget::VisWidget(QWidget *parent) :
    QGLWidget(parent)
{
    m_qtimer = new QTimer();
    connect(m_qtimer, SIGNAL(timeout()), this, SLOT(updateGL()));

    m_qmutex = new QMutex();
}

VisWidget::~VisWidget() {
    delete m_qtimer;
    delete m_qmutex;
}

void VisWidget::initializeGL() {
    glClearColor(0.25,0.25,0.25,1);
    glEnable(GL_CULL_FACE);

    m_fAngleRot = m_fNormX = m_fNormY = m_fNormZ = 0.0f;
    m_qtimer->start(25);

}

void VisWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,0.0f);

    m_qmutex->lock();
    glRotatef(m_fAngleRot, m_fNormX, m_fNormY, m_fNormZ);
    m_qmutex->unlock();

    glBegin(GL_QUADS);

        glColor3f(0.0f,1.0f,0.0f);          // Set The Color To Green
        glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f, 1.0f);          // Bottom Left Of The Quad (Top)
        glVertex3f( 1.0f, 1.0f, 1.0f);          // Bottom Right Of The Quad (Top)


        glColor3f(1.0f,0.5f,0.0f);          // Set The Color To Orange
        glVertex3f( 1.0f,-1.0f, 1.0f);          // Top Right Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f, 1.0f);          // Top Left Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Bottom)
        glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Bottom)

        glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
        glVertex3f( 1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Front)
        glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Front)
        glVertex3f(-1.0f,-1.0f, 1.0f);          // Bottom Left Of The Quad (Front)
        glVertex3f( 1.0f,-1.0f, 1.0f);          // Bottom Right Of The Quad (Front)

        glColor3f (1.0f,1.0f,0.0f);          // Set The Color To Yellow
        glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Back)
        glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Back)
        glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Back)
        glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Back)

        glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
        glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Left)
        glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Left)
        glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Left)
        glVertex3f(-1.0f,-1.0f, 1.0f);          // Bottom Right Of The Quad (Left)

        glColor3f(1.0f,0.0f,1.0f);          // Set The Color To Violet
        glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Right)
        glVertex3f( 1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Right)
        glVertex3f( 1.0f,-1.0f, 1.0f);          // Bottom Left Of The Quad (Right)
        glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Right)

     glEnd();
}

void VisWidget::resizeGL(int w, int h) {
    double Aspect;
    if(h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    Aspect=(double)w/(double)h;
            glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           double Range = 2;
    if (w <= h)
        glOrtho(-(Range),Range,-Range/Aspect,Range/Aspect,-(Range*2),Range*2);
    else
        glOrtho(-(Range*Aspect),Range*Aspect,-Range,Range,-(Range*2),Range*2);

    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
}

void VisWidget::setRotation(float NormX, float NormY, float NormZ) {
    if (m_qmutex->tryLock()) {
        float fNorm = sqrt(pow(double(NormX), 2.0) + pow(double(NormY), 2.0) + pow(double(NormZ), 2.0));
        float x = NormX / fNorm;
        float y = NormY / fNorm;
        float z = NormZ / fNorm;
        m_qmutex->unlock();

        m_fNormX = y * 0.0f - z * 1.0f;
        m_fNormY = z * 0.0f - x * 0.0f;
        m_fNormZ = x * 1.0f - y * 0.0f;

        m_fAngleRot = acos((x * 0.0f + y * 1.0f + z * 0.0f) /
                           (sqrt(pow(double(x), 2.0) + pow(double(y), 2.0) + pow(double(z), 2.0)) +
                            sqrt(pow(double(0.0f), 2.0) + pow(double(1.0f), 2.0) + pow(double(0.0f), 2.0))));
        m_fAngleRot = m_fAngleRot / M_PI * 180;
    }
}
