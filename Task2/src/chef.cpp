#include "chef.h"

Chef::Chef(double hourlyRate) : hourlyRate(hourlyRate), totalWorkMinutes(0) {}

void Chef::cookDish(std::shared_ptr<Dish> dish, int currentTime) {
    std::cout << "  Повар готовит: " << dish->getName() << " (" << dish->getCookTime() << " мин)\n";
    totalWorkMinutes += dish->getCookTime();
    dish->cook();
}

double Chef::getLaborCost() const {
    return (totalWorkMinutes / 60.0) * hourlyRate;
}