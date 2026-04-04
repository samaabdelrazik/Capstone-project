#include <iostream>
#include "System.h"

int main() {
    System system;

    system.registerUser("sama", "1234");
    system.registerUser("ezz", "abcd");

    Provider p1("chef1", "pass", "Cooking", 100);
    Provider p2("tech1", "pass", "Repair", 200);

    system.addProvider(p1);
    system.addProvider(p2);

    if (system.login("alice", "1234")) {
        std::cout << "Login successful\n";
    } else {
        std::cout << "Login failed\n";
    }

    auto cookingProviders = system.filterByCategory("Cooking");

    std::cout << "Cooking providers:\n";
    for (const auto& p : cookingProviders) {
        std::cout << p.getUserName() << " - $" << p.getPrice() << "\n";
    }

    system.bookService("alice", "chef1", "2026-04-10");

    auto bookings = system.getBookings();

    std::cout << "\nBookings:\n";
    for (const auto& b : bookings) {
        std::cout << b.getUser() << " booked " << b.getProvider()
                  << " on " << b.getDate() << "\n";
    }

    return 0;
}
