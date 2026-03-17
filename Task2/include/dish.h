#ifndef DISH_H
#define DISH_H

#include <string>
#include <vector>
#include <memory>
#include "ingredient.h"

class Dish {
public:
    Dish(const std::string& name, int cookTimeMinutes, double price);
    virtual ~Dish() = default;
    
    virtual std::string getType() const = 0;
    
    void addIngredient(std::shared_ptr<Ingredient> ingredient);
    void cook();
    
    std::string getName() const;
    int getCookTime() const;
    double getPrice() const { return price; }
    double getCost() const;  // Себестоимость (из ингредиентов)
    bool getIsCooked() const;
    
protected:
    std::string name;
    std::vector<std::shared_ptr<Ingredient>> ingredients;
    int cookTimeMinutes;
    double price;
    bool isCooked;
};

class BreakfastDish : public Dish {
public:
    BreakfastDish(const std::string& name, int cookTime, double price);
    std::string getType() const override;
};

class Omelette : public BreakfastDish {
public:
    Omelette();
};

class Porridge : public BreakfastDish {
public:
    Porridge();
};

class LunchDish : public Dish {
public:
    LunchDish(const std::string& name, int cookTime, double price);
    std::string getType() const override;
};

class Soup : public LunchDish {
public:
    Soup();
};

class MainCourse : public LunchDish {
public:
    MainCourse();
};

class DinnerDish : public Dish {
public:
    DinnerDish(const std::string& name, int cookTime, double price);
    std::string getType() const override;
};

class Steak : public DinnerDish {
public:
    Steak();
};

class Cocktail : public DinnerDish {
public:
    Cocktail();
};

class Drink : public Dish {
public:
    Drink(const std::string& name, int cookTime, double price);
    std::string getType() const override;
};

class TeaDrink : public Drink {
public:
    TeaDrink();
};

class CoffeeDrink : public Drink {
public:
    CoffeeDrink();
};

#endif