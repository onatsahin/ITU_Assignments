//Onat ŞAHİN No: 150150129

#ifndef CANDY_H
#define CANDY_H
#include <iostream>
#include <string>

class Candy{
    std::string name;
    std::string type;
    float weight;
    float pricePerKg;
    float totalPrice;
public:
    Candy(std::string, float, float);
    const std::string& getType() const;
    const std::string& getName() const;
    float getQuantity() const;
    float getTotalPrice() const;
    float getPricePerKg() const;
};

Candy::Candy(std::string nname, float nweight, float nprice){
    name = nname;
    type = "candies";
    weight = nweight;
    pricePerKg = nprice;
    totalPrice = weight * pricePerKg;
}

const std::string& Candy::getType() const{
    return type;
}

const std::string& Candy::getName() const{
    return name;
}

float Candy::getQuantity() const{
    return weight;
}

float Candy::getTotalPrice() const{
    return totalPrice;
}

float Candy::getPricePerKg() const{
    return pricePerKg;
}

std::ostream& operator <<(std::ostream& out, const Candy& toPrint){
    out << toPrint.getName() << " #" << toPrint.getQuantity() << " " << toPrint.getTotalPrice() << std::endl;
    return out;
}

#endif // CANDY_H
