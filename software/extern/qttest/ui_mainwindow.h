/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Mar 9 17:52:45 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "graphplotter.h"
#include "widgetcurvecontrol.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tabControl;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QWidget *tabParameter;
    QGroupBox *groupBoxConnection;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout_2;
    QLabel *labelPort;
    QLabel *labelIP;
    QLineEdit *lineEditIP;
    QSpinBox *spinBoxPort;
    QPushButton *pushButtonConnect;
    QWidget *tabPlot;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayoutPlot;
    GraphPlotter *widgetPlot;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBoxAccel;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayoutAccel;
    QCheckBox *checkBoxAccelY;
    QCheckBox *checkBoxAccelZ;
    QPushButton *pushButtonAccelYColor;
    QPushButton *pushButtonAccelZColor;
    QCheckBox *checkBoxAccelX;
    QPushButton *pushButtonAccelXColor;
    QGroupBox *groupBoxGyro;
    QVBoxLayout *verticalLayout;
    widgetCurveControl *widgetCurveControlGyroX;
    widgetCurveControl *widgetCurveControlGyroY;
    widgetCurveControl *widgetCurveControlGyroZ;
    QGroupBox *groupBoxMag;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout_5;
    QCheckBox *checkBoxMagX;
    QCheckBox *checkBoxMagY;
    QCheckBox *checkBoxMagZ;
    QGroupBox *groupBoxPoti;
    QHBoxLayout *horizontalLayout_5;
    QGridLayout *gridLayout_6;
    QCheckBox *checkBoxPotiX;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(815, 610);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabControl = new QWidget();
        tabControl->setObjectName(QString::fromUtf8("tabControl"));
        gridLayoutWidget = new QWidget(tabControl);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(120, 50, 278, 108));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_4 = new QPushButton(gridLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_2, 1, 1, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 2, 1, 1, 1);

        pushButton_5 = new QPushButton(gridLayoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 1, 2, 1, 1);

        tabWidget->addTab(tabControl, QString());
        tabParameter = new QWidget();
        tabParameter->setObjectName(QString::fromUtf8("tabParameter"));
        groupBoxConnection = new QGroupBox(tabParameter);
        groupBoxConnection->setObjectName(QString::fromUtf8("groupBoxConnection"));
        groupBoxConnection->setGeometry(QRect(10, 10, 187, 123));
        verticalLayout_6 = new QVBoxLayout(groupBoxConnection);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelPort = new QLabel(groupBoxConnection);
        labelPort->setObjectName(QString::fromUtf8("labelPort"));

        gridLayout_2->addWidget(labelPort, 1, 0, 1, 1);

        labelIP = new QLabel(groupBoxConnection);
        labelIP->setObjectName(QString::fromUtf8("labelIP"));

        gridLayout_2->addWidget(labelIP, 0, 0, 1, 1);

        lineEditIP = new QLineEdit(groupBoxConnection);
        lineEditIP->setObjectName(QString::fromUtf8("lineEditIP"));

        gridLayout_2->addWidget(lineEditIP, 0, 1, 1, 1);

        spinBoxPort = new QSpinBox(groupBoxConnection);
        spinBoxPort->setObjectName(QString::fromUtf8("spinBoxPort"));
        spinBoxPort->setMaximum(99999);
        spinBoxPort->setValue(6665);

        gridLayout_2->addWidget(spinBoxPort, 1, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_2);

        pushButtonConnect = new QPushButton(groupBoxConnection);
        pushButtonConnect->setObjectName(QString::fromUtf8("pushButtonConnect"));

        verticalLayout_6->addWidget(pushButtonConnect);

        tabWidget->addTab(tabParameter, QString());
        tabPlot = new QWidget();
        tabPlot->setObjectName(QString::fromUtf8("tabPlot"));
        horizontalLayout_7 = new QHBoxLayout(tabPlot);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayoutPlot = new QHBoxLayout();
        horizontalLayoutPlot->setSpacing(6);
        horizontalLayoutPlot->setObjectName(QString::fromUtf8("horizontalLayoutPlot"));
        widgetPlot = new GraphPlotter(tabPlot);
        widgetPlot->setObjectName(QString::fromUtf8("widgetPlot"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetPlot->sizePolicy().hasHeightForWidth());
        widgetPlot->setSizePolicy(sizePolicy1);
        widgetPlot->setMinimumSize(QSize(640, 480));

        horizontalLayoutPlot->addWidget(widgetPlot);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBoxAccel = new QGroupBox(tabPlot);
        groupBoxAccel->setObjectName(QString::fromUtf8("groupBoxAccel"));
        horizontalLayout_2 = new QHBoxLayout(groupBoxAccel);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gridLayoutAccel = new QGridLayout();
        gridLayoutAccel->setSpacing(6);
        gridLayoutAccel->setObjectName(QString::fromUtf8("gridLayoutAccel"));
        checkBoxAccelY = new QCheckBox(groupBoxAccel);
        checkBoxAccelY->setObjectName(QString::fromUtf8("checkBoxAccelY"));
        checkBoxAccelY->setChecked(true);

        gridLayoutAccel->addWidget(checkBoxAccelY, 1, 0, 1, 1);

        checkBoxAccelZ = new QCheckBox(groupBoxAccel);
        checkBoxAccelZ->setObjectName(QString::fromUtf8("checkBoxAccelZ"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkBoxAccelZ->sizePolicy().hasHeightForWidth());
        checkBoxAccelZ->setSizePolicy(sizePolicy2);
        checkBoxAccelZ->setChecked(true);

        gridLayoutAccel->addWidget(checkBoxAccelZ, 2, 0, 1, 1);

        pushButtonAccelYColor = new QPushButton(groupBoxAccel);
        pushButtonAccelYColor->setObjectName(QString::fromUtf8("pushButtonAccelYColor"));

        gridLayoutAccel->addWidget(pushButtonAccelYColor, 1, 1, 1, 1);

        pushButtonAccelZColor = new QPushButton(groupBoxAccel);
        pushButtonAccelZColor->setObjectName(QString::fromUtf8("pushButtonAccelZColor"));

        gridLayoutAccel->addWidget(pushButtonAccelZColor, 2, 1, 1, 1);

        checkBoxAccelX = new QCheckBox(groupBoxAccel);
        checkBoxAccelX->setObjectName(QString::fromUtf8("checkBoxAccelX"));
        checkBoxAccelX->setChecked(true);

        gridLayoutAccel->addWidget(checkBoxAccelX, 0, 0, 1, 1);

        pushButtonAccelXColor = new QPushButton(groupBoxAccel);
        pushButtonAccelXColor->setObjectName(QString::fromUtf8("pushButtonAccelXColor"));

        gridLayoutAccel->addWidget(pushButtonAccelXColor, 0, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayoutAccel);


        verticalLayout_5->addWidget(groupBoxAccel);

        groupBoxGyro = new QGroupBox(tabPlot);
        groupBoxGyro->setObjectName(QString::fromUtf8("groupBoxGyro"));
        verticalLayout = new QVBoxLayout(groupBoxGyro);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widgetCurveControlGyroX = new widgetCurveControl(groupBoxGyro);
        widgetCurveControlGyroX->setObjectName(QString::fromUtf8("widgetCurveControlGyroX"));

        verticalLayout->addWidget(widgetCurveControlGyroX);

        widgetCurveControlGyroY = new widgetCurveControl(groupBoxGyro);
        widgetCurveControlGyroY->setObjectName(QString::fromUtf8("widgetCurveControlGyroY"));

        verticalLayout->addWidget(widgetCurveControlGyroY);

        widgetCurveControlGyroZ = new widgetCurveControl(groupBoxGyro);
        widgetCurveControlGyroZ->setObjectName(QString::fromUtf8("widgetCurveControlGyroZ"));

        verticalLayout->addWidget(widgetCurveControlGyroZ);


        verticalLayout_5->addWidget(groupBoxGyro);

        groupBoxMag = new QGroupBox(tabPlot);
        groupBoxMag->setObjectName(QString::fromUtf8("groupBoxMag"));
        horizontalLayout_4 = new QHBoxLayout(groupBoxMag);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        checkBoxMagX = new QCheckBox(groupBoxMag);
        checkBoxMagX->setObjectName(QString::fromUtf8("checkBoxMagX"));

        gridLayout_5->addWidget(checkBoxMagX, 0, 0, 1, 1);

        checkBoxMagY = new QCheckBox(groupBoxMag);
        checkBoxMagY->setObjectName(QString::fromUtf8("checkBoxMagY"));

        gridLayout_5->addWidget(checkBoxMagY, 1, 0, 1, 1);

        checkBoxMagZ = new QCheckBox(groupBoxMag);
        checkBoxMagZ->setObjectName(QString::fromUtf8("checkBoxMagZ"));

        gridLayout_5->addWidget(checkBoxMagZ, 2, 0, 1, 1);


        horizontalLayout_4->addLayout(gridLayout_5);


        verticalLayout_5->addWidget(groupBoxMag);

        groupBoxPoti = new QGroupBox(tabPlot);
        groupBoxPoti->setObjectName(QString::fromUtf8("groupBoxPoti"));
        horizontalLayout_5 = new QHBoxLayout(groupBoxPoti);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        checkBoxPotiX = new QCheckBox(groupBoxPoti);
        checkBoxPotiX->setObjectName(QString::fromUtf8("checkBoxPotiX"));

        gridLayout_6->addWidget(checkBoxPotiX, 0, 0, 1, 1);


        horizontalLayout_5->addLayout(gridLayout_6);


        verticalLayout_5->addWidget(groupBoxPoti);


        horizontalLayoutPlot->addLayout(verticalLayout_5);


        horizontalLayout_7->addLayout(horizontalLayoutPlot);

        tabWidget->addTab(tabPlot, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 815, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "blaplot", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "quit", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MainWindow", "turn\n"
"left", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "stop", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "forward", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "backward", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("MainWindow", "turn\n"
"right", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabControl), QApplication::translate("MainWindow", "control", 0, QApplication::UnicodeUTF8));
        groupBoxConnection->setTitle(QApplication::translate("MainWindow", "Connection", 0, QApplication::UnicodeUTF8));
        labelPort->setText(QApplication::translate("MainWindow", "port", 0, QApplication::UnicodeUTF8));
        labelIP->setText(QApplication::translate("MainWindow", "IP", 0, QApplication::UnicodeUTF8));
        lineEditIP->setText(QApplication::translate("MainWindow", "192.168.178.4", 0, QApplication::UnicodeUTF8));
        pushButtonConnect->setText(QApplication::translate("MainWindow", "connect", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabParameter), QApplication::translate("MainWindow", "parameter", 0, QApplication::UnicodeUTF8));
        groupBoxAccel->setTitle(QApplication::translate("MainWindow", "Accelerometer", 0, QApplication::UnicodeUTF8));
        checkBoxAccelY->setText(QApplication::translate("MainWindow", "Y", 0, QApplication::UnicodeUTF8));
        checkBoxAccelZ->setText(QApplication::translate("MainWindow", "Z", 0, QApplication::UnicodeUTF8));
        pushButtonAccelYColor->setText(QString());
        pushButtonAccelZColor->setText(QString());
        checkBoxAccelX->setText(QApplication::translate("MainWindow", "X", 0, QApplication::UnicodeUTF8));
        pushButtonAccelXColor->setText(QString());
        groupBoxGyro->setTitle(QApplication::translate("MainWindow", "Gyroscope", 0, QApplication::UnicodeUTF8));
        groupBoxMag->setTitle(QApplication::translate("MainWindow", "Magnetometer", 0, QApplication::UnicodeUTF8));
        checkBoxMagX->setText(QApplication::translate("MainWindow", "X", 0, QApplication::UnicodeUTF8));
        checkBoxMagY->setText(QApplication::translate("MainWindow", "Y", 0, QApplication::UnicodeUTF8));
        checkBoxMagZ->setText(QApplication::translate("MainWindow", "Z", 0, QApplication::UnicodeUTF8));
        groupBoxPoti->setTitle(QApplication::translate("MainWindow", "Potentiometer", 0, QApplication::UnicodeUTF8));
        checkBoxPotiX->setText(QApplication::translate("MainWindow", "X", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabPlot), QApplication::translate("MainWindow", "plot", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
