#include "customqmessagebox.h"

CustomQMessageBox::CustomQMessageBox(QWidget *parent) : QMessageBox(parent)
{
    // Setting a custom stylesheet
    this->setStyleSheet(
        "QMessageBox {"
        "    background-color: #808080;"
        "    color: #808080;"
        "}"
        "QPushButton {"
        "    background-color: #A9A9A9;"
        "    color: #ffffff;"
        "    border: none;"
        "    padding: 5px;"
        "    border-radius: 3px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #0056b3;"
        "}"
    );
}
