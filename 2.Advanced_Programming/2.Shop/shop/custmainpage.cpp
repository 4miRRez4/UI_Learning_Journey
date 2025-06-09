#include "custmainpage.h"
#include "ui_custmainpage.h"


custMainPage::custMainPage(QVector<customerClass>::iterator *currentUsr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::custMainPage), currentUsr(currentUsr)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    setWindowTitle(tr("Customer Page"));

    totalPrice = new double(0.0);
    allProducts = new QVector<productClass>;
    basketProducts = new QVector<productClass>;
    loadProductsFromFile("products.txt", allProducts);
    showProducts();
    ui->priceLabel->setText("Total Price: $0.00");
    ui->welcomeLable->setText("Welcome " + (*currentUsr)->get_name());
}

custMainPage::~custMainPage()
{
    delete ui;
    delete totalPrice;
}

void custMainPage::showProducts(){
        QTreeWidget *prods = ui->prodTree;
        for(auto it = allProducts->begin(); it != allProducts->end(); ++it){
            QTreeWidgetItem *item = new QTreeWidgetItem(prods);
            item->setText(0, it->get_name());
            item->setText(1, QString::number(it->get_price()));
            item->setForeground(0, QBrush(Qt::white));
            item->setForeground(1, QBrush(Qt::white));
    //        item->setBackground(0, QColor(64,64,64));
    //        item->setBackground(1, QColor(64,64,64));
            prods->addTopLevelItem(item);
        }
}

void custMainPage::on_addButt_clicked()
{
//    qDebug() << "Add button clicked";
    //adding selected item to list
    QList<QTreeWidgetItem*> selectedItems = ui->prodTree->selectedItems();
    for (QTreeWidgetItem *item : selectedItems) {
        QString key = item->text(0);
        QString value = item->text(1);
        if(!addedItems.contains(key)){
            addedItems.insert(key);
            productClass tmpProd(key, value.toDouble());
            basketProducts->push_back(tmpProd);
            *totalPrice += value.toDouble();
        }
    }

    //showing new list
    ui->baskTree->clear();
    for (auto it = basketProducts->begin(); it != basketProducts->end(); ++it) {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->baskTree);
        item->setText(0, it->get_name());
        item->setText(1, QString::number(it->get_price()));
        item->setForeground(0, QBrush(Qt::white));
        item->setForeground(1, QBrush(Qt::white));
        ui->baskTree->addTopLevelItem(item);
    }
    connect(ui->addButt, &QPushButton::clicked, this, &custMainPage::on_addButt_clicked);

    //updating total price
    ui->priceLabel->setText(QString("Total: $%1").arg(*totalPrice, 0, 'f', 2));
}

void custMainPage::on_buyButt_clicked()
{
    *totalPrice = 0;
    ui->priceLabel->setText(QString("Total: $%1").arg(*totalPrice, 0, 'f', 2));
    ui->baskTree->clear();
    basketProducts->clear();
    QMessageBox::information(this, "status", "Your purchase was successful.");
}

