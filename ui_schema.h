/********************************************************************************
** Form generated from reading UI file 'schema.ui'
**
** Created: Fri 11. Mar 18:05:37 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEMA_H
#define UI_SCHEMA_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SchemaMainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *schemaLabel;
    QLabel *instanceLabel;
    QProgressBar *progressBar;
    QPlainTextEdit *instanceEdit;
    QLabel *label;
    QPushButton *validateButton;
    QLabel *validationStatus;
    QPlainTextEdit *schemaView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SchemaMainWindow)
    {
        if (SchemaMainWindow->objectName().isEmpty())
            SchemaMainWindow->setObjectName(QString::fromUtf8("SchemaMainWindow"));
        SchemaMainWindow->resize(641, 520);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SchemaMainWindow->sizePolicy().hasHeightForWidth());
        SchemaMainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(SchemaMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        schemaLabel = new QLabel(centralwidget);
        schemaLabel->setObjectName(QString::fromUtf8("schemaLabel"));

        gridLayout->addWidget(schemaLabel, 0, 0, 1, 2);

        instanceLabel = new QLabel(centralwidget);
        instanceLabel->setObjectName(QString::fromUtf8("instanceLabel"));

        gridLayout->addWidget(instanceLabel, 2, 0, 1, 3);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);
        progressBar->setTextVisible(false);

        gridLayout->addWidget(progressBar, 3, 0, 1, 3);

        instanceEdit = new QPlainTextEdit(centralwidget);
        instanceEdit->setObjectName(QString::fromUtf8("instanceEdit"));
        instanceEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        instanceEdit->setUndoRedoEnabled(false);
        instanceEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        instanceEdit->setReadOnly(false);
        instanceEdit->setPlainText(QString::fromUtf8(""));

        gridLayout->addWidget(instanceEdit, 4, 0, 1, 3);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label, 5, 0, 1, 1);

        validateButton = new QPushButton(centralwidget);
        validateButton->setObjectName(QString::fromUtf8("validateButton"));

        gridLayout->addWidget(validateButton, 5, 2, 1, 1);

        validationStatus = new QLabel(centralwidget);
        validationStatus->setObjectName(QString::fromUtf8("validationStatus"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(validationStatus->sizePolicy().hasHeightForWidth());
        validationStatus->setSizePolicy(sizePolicy2);
        validationStatus->setWordWrap(true);

        gridLayout->addWidget(validationStatus, 5, 1, 1, 1);

        schemaView = new QPlainTextEdit(centralwidget);
        schemaView->setObjectName(QString::fromUtf8("schemaView"));
        schemaView->setLineWrapMode(QPlainTextEdit::NoWrap);
        schemaView->setReadOnly(true);
        schemaView->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(schemaView, 1, 0, 1, 3);

        SchemaMainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SchemaMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SchemaMainWindow->setStatusBar(statusbar);

        retranslateUi(SchemaMainWindow);

        QMetaObject::connectSlotsByName(SchemaMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SchemaMainWindow)
    {
        SchemaMainWindow->setWindowTitle(QApplication::translate("SchemaMainWindow", "XML Schema Validation", 0, QApplication::UnicodeUTF8));
        schemaLabel->setText(QApplication::translate("SchemaMainWindow", "XML Schema Document:", 0, QApplication::UnicodeUTF8));
        instanceLabel->setText(QApplication::translate("SchemaMainWindow", "XML Instance Document:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SchemaMainWindow", "Status:", 0, QApplication::UnicodeUTF8));
        validateButton->setText(QApplication::translate("SchemaMainWindow", "Validate", 0, QApplication::UnicodeUTF8));
        validationStatus->setText(QApplication::translate("SchemaMainWindow", "not validated", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SchemaMainWindow: public Ui_SchemaMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEMA_H
