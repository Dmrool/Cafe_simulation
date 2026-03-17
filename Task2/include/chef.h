#ifndef CHEF_H
#define CHEF_H

#include <memory>
#include <iostream>
#include "dish.h"

class Chef {
public:
    Chef(double hourlyRate);
    
    void cookDish(std::shared_ptr<Dish> dish, int currentTime);
    double getLaborCost() const;
    
private:
    double hourlyRate;
    int totalWorkMinutes;
};

#endif