#ifndef ORDER_STRATEGY_H
#define ORDER_STRATEGY_H

#include <vector>
#include <memory>
#include <string>
#include "dish.h"

class OrderStrategy {
public:
    virtual ~OrderStrategy() = default;
    virtual std::vector<std::shared_ptr<Dish>> createOrder() const = 0;
    virtual std::string getName() const = 0;
};

class BreakfastStrategy : public OrderStrategy {
public:
    std::vector<std::shared_ptr<Dish>> createOrder() const override;
    std::string getName() const override;
};

class LunchStrategy : public OrderStrategy {
public:
    std::vector<std::shared_ptr<Dish>> createOrder() const override;
    std::string getName() const override;
};

class DinnerStrategy : public OrderStrategy {
public:
    std::vector<std::shared_ptr<Dish>> createOrder() const override;
    std::string getName() const override;
};

#endif