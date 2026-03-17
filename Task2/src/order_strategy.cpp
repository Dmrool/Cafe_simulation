#include "order_strategy.h"

std::vector<std::shared_ptr<Dish>> BreakfastStrategy::createOrder() const {
    return {
        std::make_shared<Omelette>(),
        std::make_shared<Porridge>(),
        std::make_shared<TeaDrink>()
    };
}

std::string BreakfastStrategy::getName() const { 
    return "Завтрак"; 
}

std::vector<std::shared_ptr<Dish>> LunchStrategy::createOrder() const {
    return {
        std::make_shared<Soup>(),
        std::make_shared<MainCourse>(),
        std::make_shared<CoffeeDrink>()
    };
}

std::string LunchStrategy::getName() const { 
    return "Обед"; 
}

std::vector<std::shared_ptr<Dish>> DinnerStrategy::createOrder() const {
    return {
        std::make_shared<Steak>(),
        std::make_shared<Cocktail>()
    };
}

std::string DinnerStrategy::getName() const { 
    return "Ужин"; 
}