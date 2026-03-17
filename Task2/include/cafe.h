#ifndef CAFE_H
#define CAFE_H

#include <random>
#include <chrono>
#include <memory>
#include <iostream>
#include <map>
#include "chef.h"
#include "customer.h"
#include "order_strategy.h"
#include "time_of_day.h"

class Cafe {
public:
    Cafe();
    void simulateDay();
    
private:
    void simulateHour(int hour);
    std::shared_ptr<OrderStrategy> getStrategyForTime(TimeOfDay time);
    std::shared_ptr<Customer> createCustomer(std::shared_ptr<OrderStrategy> strategy);
    HungerLevel getRandomHungerLevel();
    void serveCustomer(std::shared_ptr<Customer> customer, int startHour);
    int getCustomerCountForHour();
    int getTotalCookTime(const std::vector<std::shared_ptr<Dish>>& dishes);
    void printDailyReport();
    void printCustomerStats();
    
    std::mt19937 rng;
    std::uniform_int_distribution<> hourDist;
    std::uniform_int_distribution<> customerCountDist;
    Chef chef;
    double totalRevenue;
    double totalWasteCost;
    
    int totalCustomers;
    int veryHungryCount;
    int normalCount;
    int leftHungryCount;
    std::map<HungerLevel, int> leftByHunger;
};

#endif