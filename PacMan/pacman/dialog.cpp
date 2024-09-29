#include "dialog.h"
#include "ui_dialog.h"
#include <QPixmap>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    fullImageDialog(nullptr),
    imageLabel(nullptr),
    backButton(nullptr)
{
    ui->setupUi(this);
    QPixmap pix1(":/resrcs/imgs/gallery/Opera Snapshot_2024-07-07_155650_www.canva.com.png");
    int w = ui->label_pic1->width();
    int h = ui->label_pic1->height();
    ui->label_pic1->setPixmap(pix1.scaled(w, h, Qt::KeepAspectRatio));
    QPixmap pix2(":/resrcs/imgs/gallery/Opera Snapshot_2024-07-07_155341_www.canva.com.png");
    ui->label_pic2->setPixmap(pix2.scaled(w, h, Qt::KeepAspectRatio));
    QPixmap pix3(":/resrcs/imgs/gallery/Opera Snapshot_2024-07-07_161223_www.canva.com.png");
    ui->label_pic3->setPixmap(pix3.scaled(w, h, Qt::KeepAspectRatio));
    QPixmap pix4(":/resrcs/imgs/gallery/Opera Snapshot_2024-07-07_155911_www.canva.com.png");
    ui->label_pic4->setPixmap(pix4.scaled(w, h, Qt::KeepAspectRatio));
    QPixmap pix5(":/resrcs/imgs/gallery/Opera Snapshot_2024-07-07_160231_www.canva.com.png");
    ui->label_pic5->setPixmap(pix5.scaled(w, h, Qt::KeepAspectRatio));
    QPixmap pix6(":/resrcs/imgs/gallery/Opera Snapshot_2024-07-07_160924_www.canva.com.png");
    ui->label_pic6->setPixmap(pix6.scaled(w, h, Qt::KeepAspectRatio));
}

Dialog::~Dialog()
{
    delete ui;
    delete fullImageDialog;
    delete imageLabel;
    delete backButton;
}



void Dialog::showFullImage(const QString &imagePath)
{
    if (!fullImageDialog) {
        fullImageDialog = new QDialog(this);
        fullImageDialog->setWindowTitle("Full Image");
        imageLabel = new QLabel(fullImageDialog);
        backButton = new QPushButton("Back", fullImageDialog);

        QVBoxLayout *layout = new QVBoxLayout(fullImageDialog);
        layout->addWidget(imageLabel);
        layout->addWidget(backButton);
        fullImageDialog->setLayout(layout);

        connect(backButton, &QPushButton::clicked, fullImageDialog, &QDialog::accept);
    }

    QPixmap pixmap(imagePath);
    imageLabel->setPixmap(pixmap.scaled(400, 400, Qt::KeepAspectRatio));
    fullImageDialog->exec();
}

void Dialog::on_pushButton_clicked()
{
    showFullImage(":/resrcs/imgs/gallery/Opera Snapshot_2024-07-07_155650_www.canva.com.png");
}

void Dialog::on_pushButton_4_clicked()
{
    showFullImage(":/resrcs/imgs/gallery/Opera Snapshot_2024-07-07_155341_www.canva.com.png");
}

void Dialog::on_pushButton_3_clicked()
{
    showFullImage(":/resrcs/imgs/gallery/Opera Snapshot_2024-07-07_161223_www.canva.com.png");
}

void Dialog::on_pushButton_2_clicked()
{
    showFullImage(":/resrcs/imgs/gallery/Opera Snapshot_2024-07-07_155911_www.canva.com.png");
}

void Dialog::on_pushButton_6_clicked()
{
    showFullImage(":/resrcs/imgs/gallery/Opera Snapshot_2024-07-07_160231_www.canva.com.png");
}

void Dialog::on_pushButton_5_clicked()
{
    showFullImage(":/resrcs/imgs/gallery/Opera Snapshot_2024-07-07_160924_www.canva.com.png");
}
