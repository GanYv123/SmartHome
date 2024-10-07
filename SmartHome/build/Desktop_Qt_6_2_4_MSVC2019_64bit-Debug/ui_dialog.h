/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_status;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QComboBox *comboBox_COM;
    QLabel *label_4;
    QComboBox *comboBox_baudRate;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_scan;
    QPushButton *pushButton_connetCOM;
    QPushButton *pushButton_disconnet;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_send;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_ClearRecv;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QTextBrowser *textBrowser;
    QTextBrowser *textBrowser_2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(800, 300);
        Dialog->setMinimumSize(QSize(800, 300));
        Dialog->setMaximumSize(QSize(800, 300));
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\271\274\345\234\206")});
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);

        verticalLayout->addWidget(label);

        label_status = new QLabel(Dialog);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setFont(font);

        verticalLayout->addWidget(label_status);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        comboBox_COM = new QComboBox(groupBox);
        comboBox_COM->setObjectName(QString::fromUtf8("comboBox_COM"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, comboBox_COM);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_4);

        comboBox_baudRate = new QComboBox(groupBox);
        comboBox_baudRate->setObjectName(QString::fromUtf8("comboBox_baudRate"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, comboBox_baudRate);


        horizontalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setChecked(true);

        horizontalLayout_3->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        horizontalLayout_3->addWidget(radioButton_2);


        horizontalLayout_4->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButton_scan = new QPushButton(Dialog);
        pushButton_scan->setObjectName(QString::fromUtf8("pushButton_scan"));

        horizontalLayout_7->addWidget(pushButton_scan);

        pushButton_connetCOM = new QPushButton(Dialog);
        pushButton_connetCOM->setObjectName(QString::fromUtf8("pushButton_connetCOM"));

        horizontalLayout_7->addWidget(pushButton_connetCOM);

        pushButton_disconnet = new QPushButton(Dialog);
        pushButton_disconnet->setObjectName(QString::fromUtf8("pushButton_disconnet"));

        horizontalLayout_7->addWidget(pushButton_disconnet);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_7);

        line = new QFrame(Dialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setLineWidth(4);
        line->setMidLineWidth(3);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_send = new QPushButton(Dialog);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));

        horizontalLayout_2->addWidget(pushButton_send);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_ClearRecv = new QPushButton(Dialog);
        pushButton_ClearRecv->setObjectName(QString::fromUtf8("pushButton_ClearRecv"));

        horizontalLayout_2->addWidget(pushButton_ClearRecv);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        textBrowser = new QTextBrowser(Dialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setReadOnly(false);

        horizontalLayout->addWidget(textBrowser);

        textBrowser_2 = new QTextBrowser(Dialog);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setReadOnly(false);

        horizontalLayout->addWidget(textBrowser_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "\344\270\262\345\217\243\347\212\266\346\200\201\357\274\232", nullptr));
        label_status->setText(QCoreApplication::translate("Dialog", "NULL", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog", "COM\345\217\243\351\200\211\346\213\251\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "COM\345\217\243\351\200\211\346\213\251", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "\346\263\242\347\211\271\347\216\207\351\200\211\346\213\251", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Dialog", "\346\250\241\345\274\217\345\210\207\346\215\242", nullptr));
        radioButton->setText(QCoreApplication::translate("Dialog", "\346\225\260\345\200\274\346\250\241\345\274\217", nullptr));
        radioButton_2->setText(QCoreApplication::translate("Dialog", "\345\255\227\347\254\246\346\250\241\345\274\217", nullptr));
        pushButton_scan->setText(QCoreApplication::translate("Dialog", "\346\211\253\346\217\217\344\270\262\345\217\243", nullptr));
        pushButton_connetCOM->setText(QCoreApplication::translate("Dialog", "\350\277\236\346\216\245", nullptr));
        pushButton_disconnet->setText(QCoreApplication::translate("Dialog", "\346\226\255\345\274\200", nullptr));
        pushButton_send->setText(QCoreApplication::translate("Dialog", "\345\217\221\351\200\201", nullptr));
        pushButton_ClearRecv->setText(QCoreApplication::translate("Dialog", "\346\270\205\347\251\272\346\216\245\346\224\266\345\214\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
