#include "userbooking.h"
#include "ui_userbooking.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QPushButton>

UserBooking::UserBooking(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserBooking)
{
    ui->setupUi(this);
    ui->bookingsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

UserBooking::~UserBooking()
{
    delete ui;
}

void UserBooking::loadBookingsFromJson(const QJsonArray& bookings)
{

    ui->bookingsTable->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    ui->bookingsTable->setRowCount(0);
    ui->bookingsTable->setColumnCount(3);
    ui->bookingsTable->setHorizontalHeaderLabels({"Provider", "Date", ""});

    for (int i = 0; i < bookings.size(); i++)
    {
        ui->bookingsTable->insertRow(i);
        QJsonObject obj = bookings[i].toObject();
        ui->bookingsTable->setItem(i, 0,
                                 new QTableWidgetItem(obj["provider"].toString()));
        ui->bookingsTable->setItem(i, 1,
                                 new QTableWidgetItem(obj["date"].toString()));

        QPushButton* button = new QPushButton("Cancel");
        connect(button, &QPushButton::clicked, this, [this, button](){

            for(int r =0; r< ui->bookingsTable->rowCount(); r++)
            {
                if(ui->bookingsTable->cellWidget(r,2) == button)
                {   onCancelRowClicked(r);
                    return;
                }
            }
            ;});
        ui->bookingsTable->setCellWidget(i, 2, button);
    }

    ui->bookingsTable->horizontalHeader()
        ->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->bookingsTable->horizontalHeader()
        ->setSectionResizeMode(2, QHeaderView::ResizeToContents);
}

void UserBooking::onCancelRowClicked(int row)
{
    QString provider = ui->bookingsTable->item(row, 0)->text();
    QString date = ui->bookingsTable->item(row, 1)->text();

    ui->bookingsTable->removeRow(row);

    emit cancelBook(provider, date);
}

// void UserBooking::setUserName(const QString &user)
// {
//     loggedInUsername = user;
// }



