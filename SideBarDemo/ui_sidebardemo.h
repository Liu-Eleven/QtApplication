/********************************************************************************
** Form generated from reading UI file 'sidebardemo.ui'
**
** Created: Thu Mar 8 13:39:36 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEBARDEMO_H
#define UI_SIDEBARDEMO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideBarDemo
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QToolButton *toolButton_1;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QWidget *widget_2;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SideBarDemo)
    {
        if (SideBarDemo->objectName().isEmpty())
            SideBarDemo->setObjectName(QString::fromUtf8("SideBarDemo"));
        SideBarDemo->resize(423, 402);
        centralWidget = new QWidget(SideBarDemo);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 121, 361));
        widget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        gridLayoutWidget = new QWidget(widget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 121, 362));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        toolButton_1 = new QToolButton(gridLayoutWidget);
        toolButton_1->setObjectName(QString::fromUtf8("toolButton_1"));
        toolButton_1->setMinimumSize(QSize(64, 64));
        toolButton_1->setStyleSheet(QString::fromUtf8("border-image: url(:/images/images/button-1.png);"));

        gridLayout->addWidget(toolButton_1, 0, 0, 1, 1);

        toolButton_2 = new QToolButton(gridLayoutWidget);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setMinimumSize(QSize(64, 64));
        toolButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/images/images/button-2.png);"));

        gridLayout->addWidget(toolButton_2, 1, 0, 1, 1);

        toolButton_3 = new QToolButton(gridLayoutWidget);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setMinimumSize(QSize(64, 64));
        toolButton_3->setStyleSheet(QString::fromUtf8("border-image: url(:/images/images/button-3.png);"));

        gridLayout->addWidget(toolButton_3, 2, 0, 1, 1);

        toolButton_4 = new QToolButton(gridLayoutWidget);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        toolButton_4->setMinimumSize(QSize(64, 64));
        toolButton_4->setStyleSheet(QString::fromUtf8("border-image: url(:/images/images/button-4.png);"));

        gridLayout->addWidget(toolButton_4, 3, 0, 1, 1);

        toolButton_5 = new QToolButton(gridLayoutWidget);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
        toolButton_5->setMinimumSize(QSize(64, 64));
        toolButton_5->setStyleSheet(QString::fromUtf8("border-image: url(:/images/images/button-5.png);"));

        gridLayout->addWidget(toolButton_5, 4, 0, 1, 1);

        widget_2 = new QWidget(gridLayoutWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));

        gridLayout->addWidget(widget_2, 5, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(133, 0, 271, 351));
        label->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 178, 102, 255), stop:0.55 rgba(235, 148, 61, 255), stop:0.98 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 0, 0));\n"
"background-color: rgb(255, 170, 127);"));
        SideBarDemo->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SideBarDemo);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 423, 19));
        SideBarDemo->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SideBarDemo);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SideBarDemo->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SideBarDemo);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SideBarDemo->setStatusBar(statusBar);

        retranslateUi(SideBarDemo);

        QMetaObject::connectSlotsByName(SideBarDemo);
    } // setupUi

    void retranslateUi(QMainWindow *SideBarDemo)
    {
        SideBarDemo->setWindowTitle(QApplication::translate("SideBarDemo", "SideBarDemo", 0, QApplication::UnicodeUTF8));
        widget->setProperty("class", QVariant(QString()));
        toolButton_1->setText(QApplication::translate("SideBarDemo", "...", 0, QApplication::UnicodeUTF8));
        toolButton_2->setText(QApplication::translate("SideBarDemo", "...", 0, QApplication::UnicodeUTF8));
        toolButton_3->setText(QApplication::translate("SideBarDemo", "...", 0, QApplication::UnicodeUTF8));
        toolButton_4->setText(QApplication::translate("SideBarDemo", "...", 0, QApplication::UnicodeUTF8));
        toolButton_5->setText(QApplication::translate("SideBarDemo", "...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SideBarDemo", "\350\277\231\351\207\214\346\230\257\345\261\225\347\244\272\345\214\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SideBarDemo: public Ui_SideBarDemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEBARDEMO_H
