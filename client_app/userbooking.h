#ifndef USERBOOKING_H
#define USERBOOKING_H

#include <QDialog>
#include <QJsonArray>
#include <QHeaderView>

namespace Ui {
class UserBooking;
}

class UserBooking : public QDialog
{
    Q_OBJECT

public:
    explicit UserBooking(QWidget *parent = nullptr);
    ~UserBooking();
    void loadBookingsFromJson(const QJsonArray& bookings);
    void onCancelRowClicked(int row);
    // void setUserName(const QString &);

private:
    Ui::UserBooking *ui;
    // QString loggedInUsername;

signals:
    void cancelBook( QString, QString);

};

#endif // USERBOOKING_H
