#ifndef CUSTOMQMESSAGEBOX_H
#define CUSTOMQMESSAGEBOX_H

#include <QMessageBox>

class CustomQMessageBox : public QMessageBox
{
    Q_OBJECT

public:
    explicit CustomQMessageBox(QWidget *parent = nullptr);
};

#endif // CUSTOMMESSAGEBOX_H
