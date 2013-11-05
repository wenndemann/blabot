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

    m_qtimer->start(25);

}

void VisWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    //glTranslatef(0.0f,0.0f,0.0f);

    static float yaw, pitch, roll;

    m_qmutex->lock();
        yaw = m_yaw; pitch = m_pitch; roll = m_roll;
    m_qmutex->unlock();

    glPushMatrix();

        m_yaw = 0.0f;
        glRotatef(m_yaw,0,1,0); // rotate y
        glRotatef(m_pitch,1,0,0); // rotate x
        glRotatef(m_roll,0,0,1); // rotate z

        glBegin(GL_QUADS);
            glColor3f(0.0f,1.0f,0.0f);          // Set The Color To Green
            glVertex3f( 1.0f, 0.1f,-2.0f);          // Top Right Of The Quad (Top)
            glVertex3f(-1.0f, 0.1f,-2.0f);          // Top Left Of The Quad (Top)
            glVertex3f(-1.0f, 0.1f, 2.0f);          // Bottom Left Of The Quad (Top)
            glVertex3f( 1.0f, 0.1f, 2.0f);          // Bottom Right Of The Quad (Top)

            glColor3f(1.0f,0.5f,0.0f);          // Set The Color To Orange
            glVertex3f( 1.0f,-0.1f, 2.0f);          // Top Right Of The Quad (Bottom)
            glVertex3f(-1.0f,-0.1f, 2.0f);          // Top Left Of The Quad (Bottom)
            glVertex3f(-1.0f,-0.1f,-2.0f);          // Bottom Left Of The Quad (Bottom)
            glVertex3f( 1.0f,-0.1f,-2.0f);          // Bottom Right Of The Quad (Bottom)

            glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
            glVertex3f( 1.0f, 0.1f, 2.0f);          // Top Right Of The Quad (Front)
            glVertex3f(-1.0f, 0.1f, 2.0f);          // Top Left Of The Quad (Front)
            glVertex3f(-1.0f,-0.1f, 2.0f);          // Bottom Left Of The Quad (Front)
            glVertex3f( 1.0f,-0.1f, 2.0f);          // Bottom Right Of The Quad (Front)

            glColor3f (1.0f,1.0f,0.0f);          // Set The Color To Yellow
            glVertex3f( 1.0f,-0.1f,-2.0f);          // Bottom Left Of The Quad (Back)
            glVertex3f(-1.0f,-0.1f,-2.0f);          // Bottom Right Of The Quad (Back)
            glVertex3f(-1.0f, 0.1f,-2.0f);          // Top Right Of The Quad (Back)
            glVertex3f( 1.0f, 0.1f,-2.0f);          // Top Left Of The Quad (Back)

            glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
            glVertex3f(-1.0f, 0.1f, 2.0f);          // Top Right Of The Quad (Left)
            glVertex3f(-1.0f, 0.1f,-2.0f);          // Top Left Of The Quad (Left)
            glVertex3f(-1.0f,-0.1f,-2.0f);          // Bottom Left Of The Quad (Left)
            glVertex3f(-1.0f,-0.1f, 2.0f);          // Bottom Right Of The Quad (Left)

            glColor3f(1.0f,0.0f,1.0f);          // Set The Color To Violet
            glVertex3f( 1.0f, 0.1f,-2.0f);          // Top Right Of The Quad (Right)
            glVertex3f( 1.0f, 0.1f, 2.0f);          // Top Left Of The Quad (Right)
            glVertex3f( 1.0f,-0.1f, 2.0f);          // Bottom Left Of The Quad (Right)
            glVertex3f( 1.0f,-0.1f,-2.0f);          // Bottom Right Of The Quad (Right)
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

void VisWidget::setRotation(SensorData::sensorData_s data) {
    //qDebug("setRotation()");
    if (m_qmutex->tryLock()) {

        // PITCH _______________________________________________________________________
        m_pitch = -atan2(data.acc.x, sqrt(data.acc.y*data.acc.y + data.acc.z*data.acc.z)) * 180.0 / M_PI;
        //qDebug("setRotation() - pitch(%.2f)", m_pitch);

        // ROLL ________________________________________________________________________
        SensorData::vector accel(data.acc.x, data.acc.y, data.acc.z);
        const static SensorData::vector xAxis(1.0,0.0,0.0);

        SensorData::vector tmp1, tmp2;
        SensorData::vector::cross(accel, xAxis, tmp1);
        SensorData::vector::cross(xAxis, tmp1, tmp2);

        m_roll = atan2(tmp2.y, tmp2.z) * 180.0 / M_PI;

        // YAW _________________________________________________________________________
        m_yaw = 0.0;


        float mag_x;
        float mag_y;
        float cos_roll;
        float sin_roll;
        float cos_pitch;
        float sin_pitch;
        float MAG_Heading;

        cos_roll = cos(m_roll);
        sin_roll = sin(m_roll);
        cos_pitch = cos(m_pitch);
        sin_pitch = sin(m_pitch);

        // Tilt compensated magnetic field X
        mag_x = data.mag.x * cos_pitch + data.mag.y * sin_roll * sin_pitch + data.mag.z * cos_roll * sin_pitch;
        // Tilt compensated magnetic field Y
        mag_y = data.mag.y * cos_roll - data.mag.z * sin_roll;
        // Magnetic Heading
        MAG_Heading = atan2(-mag_y, mag_x);

        m_roll = MAG_Heading * 180.0 / M_PI;


        m_qmutex->unlock();

    }
}

void VisWidget::setEulerAngles(float pitch, float yaw, float roll) {
    m_yaw = yaw; m_pitch = pitch; m_roll = roll;
}

void VisWidget::setEulerX(int pitch) {
    m_pitch = static_cast<float>(pitch);
}

void VisWidget::setEulerY(int yaw) {
    m_yaw = static_cast<float>(yaw);
}

void VisWidget::setEulerZ(int roll) {
    m_roll = static_cast<float>(roll);
}
