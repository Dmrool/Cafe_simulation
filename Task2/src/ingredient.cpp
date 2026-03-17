#include "ingredient.h"

Ingredient::Ingredient(const std::string& name, double cost) : name(name), cost(cost) {}

std::string Ingredient::getName() const { return name; }
double Ingredient::getCost() const { return cost; }

Egg::Egg() : Ingredient("Яйцо", 5.0) {}
Milk::Milk() : Ingredient("Молоко", 10.0) {}
Flour::Flour() : Ingredient("Мука", 8.0) {}
Meat::Meat() : Ingredient("Мясо", 50.0) {}
Potato::Potato() : Ingredient("Картофель", 15.0) {}
Tea::Tea() : Ingredient("Чай", 3.0) {}
Coffee::Coffee() : Ingredient("Кофе", 20.0) {}
Sugar::Sugar() : Ingredient("Сахар", 2.0) {}