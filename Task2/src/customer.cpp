#include "customer.h"

Customer::Customer(int patienceMinutes, HungerLevel hungerLevel) 
    : patienceMinutes(patienceMinutes), waitTime(0), hungerLevel(hungerLevel) {}

void Customer::addToOrder(std::shared_ptr<Dish> dish) {
    order.push_back(dish);
}

void Customer::wait(int minutes) {
    waitTime += minutes;
}

bool Customer::isPatient() const {
    return waitTime <= patienceMinutes;
}

double Customer::getTotalOrderPrice() const {
    double total = 0;
    for (const auto& dish : order) {
        total += dish->getPrice();
    }
    return total;
}

double Customer::getTotalOrderCost() const {
    double total = 0;
    for (const auto& dish : order) {
        total += dish->getCost();
    }
    return total;
}