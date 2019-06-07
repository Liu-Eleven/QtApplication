/********************************************************************************
** Form generated from reading UI file 'misdemo.ui'
**
** Created: Sun Apr 22 14:22:34 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISDEMO_H
#define UI_MISDEMO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MISDemo
{
public:
    QWidget *centralWidget;
    QTableView *tableView;
    QPushButton *DeleteBtn;
    QPushButton *AddBtn;
    QPushButton *FindBtn;
    QLineEdit *FindEdit;
    QComboBox *FindStd;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MISDemo)
    {
        if (MISDemo->objectName().isEmpty())
            MISDemo->setObjectName(QString::fromUtf8("MISDemo"));
        MISDemo->resize(397, 390);
        centralWidget = new QWidget(MISDemo);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(15, 10, 351, 192));
        DeleteBtn = new QPushButton(centralWidget);
        DeleteBtn->setObjectName(QString::fromUtf8("DeleteBtn"));
        DeleteBtn->setGeometry(QRect(80, 220, 75, 23));
        AddBtn = new QPushButton(centralWidget);
        AddBtn->setObjectName(QString::fromUtf8("AddBtn"));
        AddBtn->setGeometry(QRect(250, 220, 75, 23));
        FindBtn = new QPushButton(centralWidget);
        FindBtn->setObjectName(QString::fromUtf8("FindBtn"));
        FindBtn->setGeometry(QRect(250, 270, 75, 23));
        FindEdit = new QLineEdit(centralWidget);
        FindEdit->setObjectName(QString::fromUtf8("FindEdit"));
        FindEdit->setGeometry(QRect(132, 270, 81, 20));
        FindStd = new QComboBox(centralWidget);
        FindStd->setObjectName(QString::fromUtf8("FindStd"));
        FindStd->setGeometry(QRect(18, 270, 91, 22));
        MISDemo->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MISDemo);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 397, 19));
        MISDemo->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MISDemo);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MISDemo->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MISDemo);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MISDemo->setStatusBar(statusBar);

        retranslateUi(MISDemo);

        QMetaObject::connectSlotsByName(MISDemo);
    } // setupUi

    void retranslateUi(QMainWindow *MISDemo)
    {
        MISDemo->setWindowTitle(QApplication::translate("MISDemo", "MISDemo", 0, QApplication::UnicodeUTF8));
        DeleteBtn->setText(QApplication::translate("MISDemo", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        AddBtn->setText(QApplication::translate("MISDemo", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        FindBtn->setText(QApplication::translate("MISDemo", "\346\237\245\346\211\276", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MISDemo: public Ui_MISDemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISDEMO_H
