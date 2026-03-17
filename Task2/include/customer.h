#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <vector>
#include <memory>
#include <string>
#include "dish.h"

enum class HungerLevel {
    VERY_HUNGRY,
    NORMAL
};

inline std::string hungerLevelToString(HungerLevel level) {
    switch(level) {
        case HungerLevel::VERY_HUNGRY: return "ОЧЕНЬ ГОЛОДНЫЙ";
        case HungerLevel::NORMAL: return "ОБЫЧНЫЙ";
        default: return "НЕИЗВЕСТНЫЙ";
    }
}

class Customer {
public:
    Customer(int patienceMinutes, HungerLevel hungerLevel);
    
    void addToOrder(std::shared_ptr<Dish> dish);
    void wait(int minutes);
    bool isPatient() const;
    double getTotalOrderPrice() const;
    double getTotalOrderCost() const;  // Общая себестоимость заказа
    
    HungerLevel getHungerLevel() const { return hungerLevel; }
    std::string getHungerLevelStr() const { return hungerLevelToString(hungerLevel); }
    int getPatience() const { return patienceMinutes; }
    int getWaitTime() const { return waitTime; }
    std::vector<std::shared_ptr<Dish>>& getOrder() { return order; }
    
private:
    std::vector<std::shared_ptr<Dish>> order;
    int patienceMinutes;
    int waitTime;
    HungerLevel hungerLevel;
};

#endif