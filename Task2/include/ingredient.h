#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include <memory>

class Ingredient {
public:
    Ingredient(const std::string& name, double cost);
    virtual ~Ingredient() = default;
    
    std::string getName() const;
    double getCost() const;
    
private:
    std::string name;
    double cost;
};

class Egg : public Ingredient {
public:
    Egg();
};

class Milk : public Ingredient {
public:
    Milk();
};

class Flour : public Ingredient {
public:
    Flour();
};

class Meat : public Ingredient {
public:
    Meat();
};

class Potato : public Ingredient {
public:
    Potato();
};

class Tea : public Ingredient {
public:
    Tea();
};

class Coffee : public Ingredient {
public:
    Coffee();
};

class Sugar : public Ingredient {
public:
    Sugar();
};

#endif