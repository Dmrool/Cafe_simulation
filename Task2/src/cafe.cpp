#include "cafe.h"
#include <iomanip>

Cafe::Cafe() : rng(std::chrono::steady_clock::now().time_since_epoch().count()),
               hourDist(8, 23), customerCountDist(2, 3), chef(200.0) {
    totalRevenue = 0;
    totalWasteCost = 0;
    totalCustomers = 0;
    veryHungryCount = 0;
    normalCount = 0;
    leftHungryCount = 0;
}

void Cafe::simulateDay() {
    std::cout << "=== НАЧАЛО РАБОЧЕГО ДНЯ ===\n\n";
    
    for (int hour = 8; hour <= 23; ++hour) {
        simulateHour(hour);
    }
    
    printCustomerStats();
    printDailyReport();
}

HungerLevel Cafe::getRandomHungerLevel() {
    std::uniform_int_distribution<> dist(0, 99);
    int roll = dist(rng);
    
    if (roll < 15) return HungerLevel::VERY_HUNGRY;
    return HungerLevel::NORMAL;
}

void Cafe::simulateHour(int hour) {
    std::cout << "\n--- Час " << hour << ":00 ---\n";
    
    TimeOfDay timeOfDay = getTimeOfDay(hour);
    int customerCount = getCustomerCountForHour();
    
    std::cout << "Пришло посетителей: " << customerCount << "\n";
    
    for (int i = 0; i < customerCount; ++i) {
        auto strategy = getStrategyForTime(timeOfDay);
        auto customer = createCustomer(strategy);
        
        totalCustomers++;
        if (customer->getHungerLevel() == HungerLevel::VERY_HUNGRY) {
            veryHungryCount++;
        } else {
            normalCount++;
        }
        
        serveCustomer(customer, hour);
    }
}

std::shared_ptr<OrderStrategy> Cafe::getStrategyForTime(TimeOfDay time) {
    std::uniform_int_distribution<> dist(0, 99);
    int roll = dist(rng);
    
    switch (time) {
        case TimeOfDay::MORNING:
            if (roll < 70) return std::make_shared<BreakfastStrategy>();
            if (roll < 90) return std::make_shared<LunchStrategy>();
            return std::make_shared<DinnerStrategy>();
            
        case TimeOfDay::AFTERNOON:
            if (roll < 20) return std::make_shared<BreakfastStrategy>();
            if (roll < 80) return std::make_shared<LunchStrategy>();
            return std::make_shared<DinnerStrategy>();
            
        case TimeOfDay::EVENING:
            if (roll < 10) return std::make_shared<BreakfastStrategy>();
            if (roll < 30) return std::make_shared<LunchStrategy>();
            return std::make_shared<DinnerStrategy>();
    }
    return std::make_shared<BreakfastStrategy>();
}

std::shared_ptr<Customer> Cafe::createCustomer(std::shared_ptr<OrderStrategy> strategy) {
    HungerLevel hungerLevel = getRandomHungerLevel();
    
    int patienceMinutes;
    
    switch(hungerLevel) {
        case HungerLevel::VERY_HUNGRY:
            patienceMinutes = std::uniform_int_distribution<>(15, 20)(rng);
            break;
        case HungerLevel::NORMAL:
            patienceMinutes = 1000;
            break;
    }
    
    auto customer = std::make_shared<Customer>(patienceMinutes, hungerLevel);
    
    auto dishes = strategy->createOrder();
    for (auto& dish : dishes) {
        customer->addToOrder(dish);
    }
    
    std::cout << "Клиент [" << customer->getHungerLevelStr() << "] заказал (" 
              << strategy->getName() << "): ";
    for (const auto& dish : dishes) {
        std::cout << dish->getName() << " ";
    }
    std::cout << "(время приг.: " << getTotalCookTime(dishes) << " мин";
    
    if (hungerLevel == HungerLevel::VERY_HUNGRY) {
        std::cout << ", терпение: " << patienceMinutes << " мин";
    }
    std::cout << ")\n";
    
    return customer;
}

void Cafe::serveCustomer(std::shared_ptr<Customer> customer, int startHour) {
    int elapsedTime = 0;
    bool firstDish = true;
    double servedCost = 0;  // Себестоимость поданных блюд
    
    for (auto& dish : customer->getOrder()) {
        if (customer->getHungerLevel() == HungerLevel::VERY_HUNGRY && firstDish) {
            if (dish->getCookTime() > customer->getPatience()) {
                std::cout << "  !!! ОЧЕНЬ ГОЛОДНЫЙ клиент не дождался первого блюда! Уходит.\n";
                std::cout << "     Первое блюдо \"" << dish->getName() 
                          << "\" готовится " << dish->getCookTime() 
                          << " мин, а терпение " << customer->getPatience() << " мин\n";
                std::cout << "     Утилизируется весь заказ (себестоимость " 
                          << customer->getTotalOrderCost() << " руб.):\n";
                
                for (auto& d : customer->getOrder()) {
                    totalWasteCost += d->getCost();  // Утилизация по себестоимости
                    std::cout << "       - " << d->getName() 
                              << " (себест. " << d->getCost() << " руб.)\n";
                }
                
                leftHungryCount++;
                leftByHunger[customer->getHungerLevel()]++;
                return;
            }
            firstDish = false;
        }
        
        chef.cookDish(dish, startHour * 60 + elapsedTime);
        elapsedTime += dish->getCookTime();
        servedCost += dish->getCost();  // Считаем себестоимость поданных блюд
    }
    
    double orderPrice = customer->getTotalOrderPrice();
    double orderCost = customer->getTotalOrderCost();
    double profit = orderPrice - orderCost;
    
    totalRevenue += orderPrice;
    std::cout << "  !!! " << customer->getHungerLevelStr() 
              << " клиент оплатил: " << orderPrice << " руб. "
              << "(себест. " << orderCost << " руб., прибыль " << profit << " руб.)\n";
}

int Cafe::getCustomerCountForHour() {
    std::poisson_distribution<> dist(2.2);
    return std::min(4, std::max(1, (int)dist(rng)));
}

int Cafe::getTotalCookTime(const std::vector<std::shared_ptr<Dish>>& dishes) {
    int total = 0;
    for (const auto& dish : dishes) {
        total += dish->getCookTime();
    }
    return total;
}

void Cafe::printCustomerStats() {
    std::cout << "\n=== СТАТИСТИКА КЛИЕНТОВ ===\n";
    std::cout << "Всего клиентов: " << totalCustomers << "\n";
    std::cout << "  Очень голодных: " << veryHungryCount << "\n";
    std::cout << "  Обычных: " << normalCount << "\n";
    std::cout << "ОБСЛУЖЕНО: " << totalCustomers - leftHungryCount << "\n";
    std::cout << "УШЛИ ГОЛОДНЫМИ: " << leftHungryCount << "\n";
    
    if (leftByHunger.count(HungerLevel::VERY_HUNGRY)) {
        std::cout << "  - Очень голодные ушли: " << leftByHunger[HungerLevel::VERY_HUNGRY] << "\n";
    }
    
    std::cout << "Потери от утилизации: " << totalWasteCost << " руб.\n";
}

void Cafe::printDailyReport() {
    double laborCost = chef.getLaborCost();
    double netProfit = totalRevenue - laborCost - totalWasteCost;
    double margin = (netProfit / totalRevenue) * 100;
    
    std::cout << "\n=== ИТОГИ ДНЯ ===\n";
    std::cout << "Выручка: " << totalRevenue << " руб.\n";
    std::cout << "Затраты на оплату труда: " << laborCost << " руб.\n";
    std::cout << "Потери от утилизации: " << totalWasteCost << " руб.\n";
    std::cout << "----------------------------------------\n";
    std::cout << "ЧИСТАЯ ПРИБЫЛЬ: " << netProfit << " руб.";
    
    if (netProfit > 0) {
        std::cout << " (рентабельность " << std::fixed << std::setprecision(1) << margin << "%)\n";
        std::cout << "КАФЕ ЗАКОНЧИЛО ДЕНЬ С ПРИБЫЛЬЮ\n";
    } else {
        std::cout << "\nКАФЕ ЗАКОНЧИЛО ДЕНЬ С УБЫТКОМ\n";
    }
}