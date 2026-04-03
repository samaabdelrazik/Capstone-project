#include "System.h"

void System::registerUser(std::string username, std::string password) {
    users.push_back(User(username, password));
}

bool System::login(std::string username, std::string password) {
    for (const auto& user : users) {
        if (user.getUserName() == username && user.checkPassword(password)) {
            return true;
        }
    }
    return false;
}

void System::addProvider(const Provider& provider) {
    providers.push_back(provider);
}

std::vector<Provider> System::filterByCategory(std::string category) {
    std::vector<Provider> result;

    for (const auto& p : providers) {
        if (p.getCategory() == category) {
            result.push_back(p);
        }
    }

    return result;
}

bool System::bookService(std::string user, std::string provider, std::string date) {
    bookings.push_back(Booking(user, provider, date));
    return true;
}

std::vector<Booking> System::getBookings() const {
    return bookings;
}
