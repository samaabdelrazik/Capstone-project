#include "usersearch.h"
#include "ui_usersearch.h"
#include <QJsonObject>
#include <QDate>
#include <QMessageBox>

UserSearch::UserSearch(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::UserSearch)
{
    ui->setupUi(this);
}

UserSearch::~UserSearch()
{
    delete ui;
}

void UserSearch::editSearchTable(const QJsonArray& results)
{
    ui->searchTable->setRowCount(results.size());
    ui->searchTable->setColumnCount(4);
    ui->searchTable->setHorizontalHeaderLabels({"Name", "Category", "Price", ""});

    for (int i = 0; i < results.size(); i++)
    {
        QJsonObject obj = results[i].toObject();
        ui->searchTable->setItem(i, 0,
                                 new QTableWidgetItem(obj["name"].toString()));
        ui->searchTable->setItem(i, 1,
                                 new QTableWidgetItem(obj["category"].toString()));
        ui->searchTable->setItem(i, 2,
                                 new QTableWidgetItem(
                                     QString::number(obj["price"].toDouble(), 'f', 2)));

        QPushButton* button = new QPushButton("Book");
        connect(button, &QPushButton::clicked, this, [this, i](){onBookRowClicked(i);});
        ui->searchTable->setCellWidget(i, 3, button);
    }

    ui->searchTable->horizontalHeader()
        ->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->searchTable->horizontalHeader()
        ->setSectionResizeMode(3, QHeaderView::ResizeToContents);
}

void UserSearch::on_search_button_clicked()
{
    emit searchButtonClicked(ui->categoryLineEdit->text());
}

// Called when the user clicks the Book button.
// Reads the selected row from searchTable to get the provider name,
// and uses today's date as a placeholder (add a date picker to the UI later).
void UserSearch::onBookRowClicked(int row)
{
    QTableWidgetItem* nameItem = ui->searchTable->item(row,0);
    if(!nameItem) return;

    QString providerName = ui->searchTable->item(row, 0)->text();
    QString date         = QDate::currentDate().toString("yyyy-MM-dd");

    emit bookServiceRequested(providerName, date);
}
