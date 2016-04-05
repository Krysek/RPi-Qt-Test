/********************************************************************************
** Form generated from reading UI file 'HelloForm.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLOFORM_H
#define UI_HELLOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_HelloForm
{
public:
    QDialogButtonBox *buttonBox;
    QDial *dial;
    QGroupBox *groupBox;
    QSlider *horizontalSlider;
    QLabel *label_2;
    QLabel *label;

    void setupUi(QDialog *HelloForm)
    {
        if (HelloForm->objectName().isEmpty())
            HelloForm->setObjectName(QStringLiteral("HelloForm"));
        HelloForm->resize(400, 300);
        buttonBox = new QDialogButtonBox(HelloForm);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        dial = new QDial(HelloForm);
        dial->setObjectName(QStringLiteral("dial"));
        dial->setGeometry(QRect(40, 120, 51, 61));
        dial->setCursor(QCursor(Qt::PointingHandCursor));
        dial->setInvertedAppearance(false);
        groupBox = new QGroupBox(HelloForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 131, 61));
        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(40, 20, 51, 41));
        horizontalSlider->setCursor(QCursor(Qt::PointingHandCursor));
        horizontalSlider->setMaximum(1);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 30, 21, 16));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 30, 21, 16));

        retranslateUi(HelloForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), HelloForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), HelloForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(HelloForm);
    } // setupUi

    void retranslateUi(QDialog *HelloForm)
    {
        HelloForm->setWindowTitle(QApplication::translate("HelloForm", "HelloForm", 0));
        groupBox->setTitle(QApplication::translate("HelloForm", "LED", 0));
        label_2->setText(QApplication::translate("HelloForm", "On", 0));
        label->setText(QApplication::translate("HelloForm", "Off", 0));
    } // retranslateUi

};

namespace Ui {
    class HelloForm: public Ui_HelloForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOFORM_H
