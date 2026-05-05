#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "System.h"
#include "loginscreen.h"
#include "usersearch.h"
#include "providerdashboard.h"
#include "userbooking.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(System* system);
    ~MainWindow();

private slots:
    void showLogin();
    void showCustomerDashboard();
    void showProviderDashboard();
    void showBooking();

    void handleLogin(QString username, QString password, bool isProvider);
    void handleRegister(QString username, QString password, bool isProvider);
    void handleSearch(QString category);
    void handleBookService(QString providerName, QString date);
    void handleShowBooking();
    void handleCancelBook( QString, QString);

    void on_readReady();

private:
    Ui::MainWindow*    ui;
    QStackedWidget*    stackedWidget;
    LoginScreen*       loginScreen;
    UserSearch*        usersearch;
    ProviderDashboard* providerDashboard;
    System*            sys;
    QTcpSocket*        socket;
    UserBooking* userBooking;

    bool    isProvider;
    QString loggedInUsername;

    void sendJson(const QJsonObject& obj);
};

#endif
