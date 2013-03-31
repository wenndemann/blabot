#include "viswidget.h"
#include <math.h>
#include "mainwindow.h"

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
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.0f,0.0f,0.0f);


    //m_qmutex->lock();
    //glRotatef(m_fAngleRot, m_fNormX, m_fNormY, m_fNormZ);
    //m_qmutex->unlock();


    // -----
    /*
    double ESq_1, ESq_2, ESq_3, ESq_4;                              // quaternion describing orientation of sensor relative to earth
    double ASq_1, ASq_2, ASq_3, ASq_4;                              // quaternion describing orientation of sensor relative to auxiliary frame
    double r_11, r_12, r_13, r_21, r_22, r_23, r_31, r_32, r_33;    // rotation matrix elements

    // world quaternions
    double AEq_1, AEq_2, AEq_3, AEq_4;
    AEq_1 = 1.0;
    AEq_2 = AEq_3 = AEq_4 = 0.0;

    // compute the quaternion conjugate
    ESq_1 = scalar;
    ESq_2 = -x;
    ESq_3 = -y;
    ESq_4 = -z;

    // compute the quaternion product
    ASq_1 = ESq_1 * AEq_1 - ESq_2 * AEq_2 - ESq_3 * AEq_3 - ESq_4 * AEq_4;
    ASq_2 = ESq_1 * AEq_2 + ESq_2 * AEq_1 + ESq_3 * AEq_4 - ESq_4 * AEq_3;
    ASq_3 = ESq_1 * AEq_3 - ESq_2 * AEq_4 + ESq_3 * AEq_1 + ESq_4 * AEq_2;
    ASq_4 = ESq_1 * AEq_4 + ESq_2 * AEq_3 - ESq_3 * AEq_2 + ESq_4 * AEq_1;

    /*
    // compute rotation matrix from quaternion
    r_11 = 2 * ASq_1 * ASq_1 - 1 + 2 * ASq_2 * ASq_2;
    r_12 = 2 * (ASq_2 * ASq_3 + ASq_1 * ASq_4);
    r_13 = 2 * (ASq_2 * ASq_4 - ASq_1 * ASq_3);
    r_21 = 2 * (ASq_2 * ASq_3 - ASq_1 * ASq_4);
    r_22 = 2 * ASq_1 * ASq_1 - 1 + 2 * ASq_3 * ASq_3;
    r_23 = 2 * (ASq_3 * ASq_4 + ASq_1 * ASq_2);
    r_31 = 2 * (ASq_2 * ASq_4 + ASq_1 * ASq_3);

    r_32 = 2 * (ASq_3 * ASq_4 - ASq_1 * ASq_2);
    r_33 = 2 * ASq_1 * ASq_1 - 1 + 2 * ASq_4 * ASq_4;

    // back transformation
    x = x*r_11 + y * r_21 + z * r_31;
    y = x*r_12 + y * r_22 + z * r_32;
    z = x*r_13 + y * r_23 + z * r_33;
    */

    //glRotatef(ASq_1, ASq_2, ASq_3, ASq_4);

    // -----


    //glRotatef(0, 0, 1, 0);

    m_qmutex->lock();

    float scalar = m_qQuaternion.scalar() * 360; // M_PI;
    float x = m_qQuaternion.x();
    float y = m_qQuaternion.y();
    float z = m_qQuaternion.z();

    m_qmutex->unlock();

    glPushMatrix();
        glRotatef(scalar, x, y, z);
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
    glPopMatrix();
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

        m_fNormX = y * 0.0f - z * 1.0f;
        m_fNormY = z * 0.0f - x * 0.0f;
        m_fNormZ = x * 1.0f - y * 0.0f;

        m_fAngleRot = acos((x * 0.0f + y * 1.0f + z * 0.0f) /
                           (sqrt(pow(double(x), 2.0) + pow(double(y), 2.0) + pow(double(z), 2.0)) +
                            sqrt(pow(double(0.0f), 2.0) + pow(double(1.0f), 2.0) + pow(double(0.0f), 2.0))));
        m_fAngleRot = m_fAngleRot / M_PI * 180;
        m_qmutex->unlock();
    }
}

void VisWidget::setRotation(float AngleRot, float NormX, float NormY, float NormZ) {
    if (m_qmutex->tryLock()) {

        m_fNormX = NormX;
        m_fNormY = NormY;
        m_fNormZ = NormZ;
        m_fAngleRot = AngleRot;

        m_qmutex->unlock();
    }
}

void VisWidget::setQuaternions(float SEq_1, float SEq_2, float SEq_3, float SEq_4) {
    if (m_qmutex->tryLock()) {

        m_qQuaternion = QQuaternion(SEq_1, SEq_2, SEq_3, SEq_4);

        m_fQuaternion_1 = SEq_1;
        m_fQuaternion_2 = SEq_2;
        m_fQuaternion_3 = SEq_3;
        m_fQuaternion_4 = SEq_4;

        m_qmutex->unlock();
    }
}

void VisWidget::setQuaternions(QQuaternion *q) {
    m_qQuaternion = *q;
}
