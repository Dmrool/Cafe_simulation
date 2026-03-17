#include "dish.h"

Dish::Dish(const std::string& name, int cookTimeMinutes, double price) 
    : name(name), cookTimeMinutes(cookTimeMinutes), price(price), isCooked(false) {}

double Dish::getCost() const {
    double total = 0;
    for (const auto& ing : ingredients) {
        total += ing->getCost();
    }
    return total;
}

void Dish::addIngredient(std::shared_ptr<Ingredient> ingredient) {
    ingredients.push_back(ingredient);
}

void Dish::cook() { 
    isCooked = true; 
}

std::string Dish::getName() const { return name; }
int Dish::getCookTime() const { return cookTimeMinutes; }
bool Dish::getIsCooked() const { return isCooked; }

BreakfastDish::BreakfastDish(const std::string& name, int cookTime, double price) 
    : Dish(name, cookTime, price) {}
std::string BreakfastDish::getType() const { return "Завтрак"; }

Omelette::Omelette() : BreakfastDish("Омлет", 8, 120) {
    addIngredient(std::make_shared<Egg>());
    addIngredient(std::make_shared<Egg>());
    addIngredient(std::make_shared<Milk>());
}

Porridge::Porridge() : BreakfastDish("Каша", 12, 90) {
    addIngredient(std::make_shared<Milk>());
    addIngredient(std::make_shared<Sugar>());
}

LunchDish::LunchDish(const std::string& name, int cookTime, double price) 
    : Dish(name, cookTime, price) {}
std::string LunchDish::getType() const { return "Обед"; }

Soup::Soup() : LunchDish("Суп", 15, 150) {
    addIngredient(std::make_shared<Meat>());
    addIngredient(std::make_shared<Potato>());
}

MainCourse::MainCourse() : LunchDish("Второе", 18, 180) {
    addIngredient(std::make_shared<Meat>());
    addIngredient(std::make_shared<Potato>());
}

DinnerDish::DinnerDish(const std::string& name, int cookTime, double price) 
    : Dish(name, cookTime, price) {}
std::string DinnerDish::getType() const { return "Ужин"; }

Steak::Steak() : DinnerDish("Стейк", 20, 250) {
    addIngredient(std::make_shared<Meat>());
    addIngredient(std::make_shared<Meat>());
}

Cocktail::Cocktail() : DinnerDish("Коктейль", 4, 80) {
    addIngredient(std::make_shared<Milk>());
    addIngredient(std::make_shared<Sugar>());
}

Drink::Drink(const std::string& name, int cookTime, double price) 
    : Dish(name, cookTime, price) {}
std::string Drink::getType() const { return "Напиток"; }

TeaDrink::TeaDrink() : Drink("Чай", 4, 50) {
    addIngredient(std::make_shared<Tea>());
    addIngredient(std::make_shared<Sugar>());
}

CoffeeDrink::CoffeeDrink() : Drink("Кофе", 5, 80) {
    addIngredient(std::make_shared<Coffee>());
    addIngredient(std::make_shared<Sugar>());
}