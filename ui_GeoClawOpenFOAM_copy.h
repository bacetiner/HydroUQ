/********************************************************************************
** Form generated from reading UI file 'GeoClawOpenFOAM_copy.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GEOCLAWOPENFOAM_COPY_H
#define UI_GEOCLAWOPENFOAM_COPY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qt3dframe.h"

QT_BEGIN_NAMESPACE

class Ui_GeoClawOpenFOAM
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *parameterFrame;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *SimOptions;
    QLabel *Lbl_DescriptTitle;
    QLabel *Lbl_Descript;
    QSpacerItem *VSp_ParaFrame;
    QFrame *parameterFrame_2;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QFrame *frame;
    QGridLayout *gridLayout;
    QT3DFrame *graphicswidget;

    void setupUi(QWidget *GeoClawOpenFOAM)
    {
        if (GeoClawOpenFOAM->objectName().isEmpty())
            GeoClawOpenFOAM->setObjectName(QString::fromUtf8("GeoClawOpenFOAM"));
        GeoClawOpenFOAM->resize(1600, 1200);
        GeoClawOpenFOAM->setMinimumSize(QSize(800, 600));
        horizontalLayout = new QHBoxLayout(GeoClawOpenFOAM);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        parameterFrame = new QFrame(GeoClawOpenFOAM);
        parameterFrame->setObjectName(QString::fromUtf8("parameterFrame"));
        QFont font;
        font.setPointSize(14);
        parameterFrame->setFont(font);
        parameterFrame->setFrameShape(QFrame::Box);
        parameterFrame->setFrameShadow(QFrame::Sunken);
        verticalLayout_2 = new QVBoxLayout(parameterFrame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        SimOptions = new QTreeWidget(parameterFrame);
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("Simulation data"));
        __qtreewidgetitem->setFont(0, font1);
        SimOptions->setHeaderItem(__qtreewidgetitem);
        new QTreeWidgetItem(SimOptions);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(SimOptions);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(SimOptions);
        new QTreeWidgetItem(SimOptions);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(SimOptions);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(SimOptions);
        new QTreeWidgetItem(SimOptions);
        new QTreeWidgetItem(SimOptions);
        SimOptions->setObjectName(QString::fromUtf8("SimOptions"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SimOptions->sizePolicy().hasHeightForWidth());
        SimOptions->setSizePolicy(sizePolicy);
        SimOptions->setFont(font);

        verticalLayout_2->addWidget(SimOptions);

        Lbl_DescriptTitle = new QLabel(parameterFrame);
        Lbl_DescriptTitle->setObjectName(QString::fromUtf8("Lbl_DescriptTitle"));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        Lbl_DescriptTitle->setFont(font2);
        Lbl_DescriptTitle->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(Lbl_DescriptTitle);

        Lbl_Descript = new QLabel(parameterFrame);
        Lbl_Descript->setObjectName(QString::fromUtf8("Lbl_Descript"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Lbl_Descript->sizePolicy().hasHeightForWidth());
        Lbl_Descript->setSizePolicy(sizePolicy1);
        Lbl_Descript->setFont(font);
        Lbl_Descript->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_2->addWidget(Lbl_Descript);

        VSp_ParaFrame = new QSpacerItem(20, 394, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(VSp_ParaFrame);


        horizontalLayout->addWidget(parameterFrame);

        parameterFrame_2 = new QFrame(GeoClawOpenFOAM);
        parameterFrame_2->setObjectName(QString::fromUtf8("parameterFrame_2"));
        parameterFrame_2->setFont(font);
        parameterFrame_2->setFrameShape(QFrame::Box);
        parameterFrame_2->setFrameShadow(QFrame::Sunken);
        verticalLayout = new QVBoxLayout(parameterFrame_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        stackedWidget = new QStackedWidget(parameterFrame_2);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));

        verticalLayout->addWidget(stackedWidget);


        horizontalLayout->addWidget(parameterFrame_2);

        frame = new QFrame(GeoClawOpenFOAM);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        graphicswidget = new QT3DFrame(frame);
        graphicswidget->setObjectName(QString::fromUtf8("graphicswidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(graphicswidget->sizePolicy().hasHeightForWidth());
        graphicswidget->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(graphicswidget, 0, 0, 1, 1);


        horizontalLayout->addWidget(frame);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 5);

        retranslateUi(GeoClawOpenFOAM);

        QMetaObject::connectSlotsByName(GeoClawOpenFOAM);
    } // setupUi

    void retranslateUi(QWidget *GeoClawOpenFOAM)
    {
        GeoClawOpenFOAM->setWindowTitle(QCoreApplication::translate("GeoClawOpenFOAM", "GeoClawOpenFOAM", nullptr));

        const bool __sortingEnabled = SimOptions->isSortingEnabled();
        SimOptions->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem = SimOptions->topLevelItem(0);
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Project settings", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = SimOptions->topLevelItem(1);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Geometry", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Bathymetry", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "SW-CFD interface", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Buildings", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(3);
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Floating bodies", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = SimOptions->topLevelItem(2);
        ___qtreewidgetitem6->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Meshing", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = SimOptions->topLevelItem(3);
        ___qtreewidgetitem7->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Materials", nullptr));
        QTreeWidgetItem *___qtreewidgetitem8 = SimOptions->topLevelItem(4);
        ___qtreewidgetitem8->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Initial conditions", nullptr));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem8->child(0);
        ___qtreewidgetitem9->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Initial velocity", nullptr));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem8->child(1);
        ___qtreewidgetitem10->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Initial pressure", nullptr));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem8->child(2);
        ___qtreewidgetitem11->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Initial phase", nullptr));
        QTreeWidgetItem *___qtreewidgetitem12 = SimOptions->topLevelItem(5);
        ___qtreewidgetitem12->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Boundary conditions", nullptr));
        QTreeWidgetItem *___qtreewidgetitem13 = SimOptions->topLevelItem(6);
        ___qtreewidgetitem13->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Solver", nullptr));
        QTreeWidgetItem *___qtreewidgetitem14 = SimOptions->topLevelItem(7);
        ___qtreewidgetitem14->setText(0, QCoreApplication::translate("GeoClawOpenFOAM", "Post-processing", nullptr));
        SimOptions->setSortingEnabled(__sortingEnabled);

        Lbl_DescriptTitle->setText(QCoreApplication::translate("GeoClawOpenFOAM", "Description", nullptr));
        Lbl_Descript->setText(QCoreApplication::translate("GeoClawOpenFOAM", "Use this box to setup the project settings: \n"
"", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GeoClawOpenFOAM: public Ui_GeoClawOpenFOAM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GEOCLAWOPENFOAM_COPY_H
