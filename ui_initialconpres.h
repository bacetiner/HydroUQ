/********************************************************************************
** Form generated from reading UI file 'initialconpres.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIALCONPRES_H
#define UI_INITIALCONPRES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_initialconPres
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_H1;
    QLabel *Lbl_Notice;
    QHBoxLayout *HLY_Pres;
    QLabel *Lbl_Pres;
    QDoubleSpinBox *DSpBx_Pres;
    QLabel *Lbl_Regions;
    QTableWidget *Tbl_IniCondTable;
    QHBoxLayout *HLY_AddRegion;
    QToolButton *Btn_AddRegion;
    QToolButton *Btn_RemRegion;
    QSpacerItem *VSp;

    void setupUi(QFrame *initialconPres)
    {
        if (initialconPres->objectName().isEmpty())
            initialconPres->setObjectName(QString::fromUtf8("initialconPres"));
        initialconPres->resize(427, 996);
        verticalLayout = new QVBoxLayout(initialconPres);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        Lbl_H1 = new QLabel(initialconPres);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Lbl_H1);

        Lbl_Notice = new QLabel(initialconPres);
        Lbl_Notice->setObjectName(QString::fromUtf8("Lbl_Notice"));
        Lbl_Notice->setFont(font);

        verticalLayout->addWidget(Lbl_Notice);

        HLY_Pres = new QHBoxLayout();
        HLY_Pres->setObjectName(QString::fromUtf8("HLY_Pres"));
        Lbl_Pres = new QLabel(initialconPres);
        Lbl_Pres->setObjectName(QString::fromUtf8("Lbl_Pres"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        Lbl_Pres->setFont(font1);
        Lbl_Pres->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_Pres->setWordWrap(true);

        HLY_Pres->addWidget(Lbl_Pres);

        DSpBx_Pres = new QDoubleSpinBox(initialconPres);
        DSpBx_Pres->setObjectName(QString::fromUtf8("DSpBx_Pres"));
        DSpBx_Pres->setFont(font);
        DSpBx_Pres->setAlignment(Qt::AlignCenter);

        HLY_Pres->addWidget(DSpBx_Pres);


        verticalLayout->addLayout(HLY_Pres);

        Lbl_Regions = new QLabel(initialconPres);
        Lbl_Regions->setObjectName(QString::fromUtf8("Lbl_Regions"));
        Lbl_Regions->setFont(font);
        Lbl_Regions->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(Lbl_Regions);

        Tbl_IniCondTable = new QTableWidget(initialconPres);
        if (Tbl_IniCondTable->columnCount() < 3)
            Tbl_IniCondTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setFont(font);
        Tbl_IniCondTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem1->setFont(font);
        Tbl_IniCondTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem2->setFont(font);
        Tbl_IniCondTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        Tbl_IniCondTable->setObjectName(QString::fromUtf8("Tbl_IniCondTable"));
        Tbl_IniCondTable->setFont(font);
        Tbl_IniCondTable->setToolTipDuration(10000);
        Tbl_IniCondTable->setAlternatingRowColors(true);

        verticalLayout->addWidget(Tbl_IniCondTable);

        HLY_AddRegion = new QHBoxLayout();
        HLY_AddRegion->setObjectName(QString::fromUtf8("HLY_AddRegion"));
        Btn_AddRegion = new QToolButton(initialconPres);
        Btn_AddRegion->setObjectName(QString::fromUtf8("Btn_AddRegion"));
        Btn_AddRegion->setToolTipDuration(10000);

        HLY_AddRegion->addWidget(Btn_AddRegion);

        Btn_RemRegion = new QToolButton(initialconPres);
        Btn_RemRegion->setObjectName(QString::fromUtf8("Btn_RemRegion"));
        Btn_RemRegion->setToolTipDuration(10000);

        HLY_AddRegion->addWidget(Btn_RemRegion);


        verticalLayout->addLayout(HLY_AddRegion);

        VSp = new QSpacerItem(20, 404, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(VSp);


        retranslateUi(initialconPres);

        QMetaObject::connectSlotsByName(initialconPres);
    } // setupUi

    void retranslateUi(QFrame *initialconPres)
    {
        initialconPres->setWindowTitle(QCoreApplication::translate("initialconPres", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("initialconPres", "<html><head/><body><p><span style=\" font-weight:600;\">INITIAL CONDITIONS (PRESSURE)</span></p></body></html>", nullptr));
        Lbl_Notice->setText(QCoreApplication::translate("initialconPres", "Initial conditions are already prescribed through \n"
"the shallow water solvers", nullptr));
        Lbl_Pres->setText(QCoreApplication::translate("initialconPres", "Pressure", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_Pres->setToolTip(QCoreApplication::translate("initialconPres", "Global value of pressure", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_Regions->setText(QCoreApplication::translate("initialconPres", "<html><head/><body><p><span style=\" font-weight:600;\">Regions</span></p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Tbl_IniCondTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("initialconPres", "P1(x,y,z)", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Tbl_IniCondTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("initialconPres", "P2(x,y,z)", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = Tbl_IniCondTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("initialconPres", "Value", nullptr));
#if QT_CONFIG(tooltip)
        Tbl_IniCondTable->setToolTip(QCoreApplication::translate("initialconPres", "Regions for initial condition (Pressure)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Btn_AddRegion->setToolTip(QCoreApplication::translate("initialconPres", "Add regions for defining initial conditions", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_AddRegion->setText(QCoreApplication::translate("initialconPres", "Add region", nullptr));
#if QT_CONFIG(tooltip)
        Btn_RemRegion->setToolTip(QCoreApplication::translate("initialconPres", "Remove regions for defining initial conditions", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_RemRegion->setText(QCoreApplication::translate("initialconPres", "Remove region", nullptr));
    } // retranslateUi

};

namespace Ui {
    class initialconPres: public Ui_initialconPres {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIALCONPRES_H
