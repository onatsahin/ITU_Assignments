//Onat ŞAHİN No: 150150129

#ifndef COOKIE_H
#define COOKIE_H
#include <string>

class Cookie{
    std::string name;
    std::string type;
    float number;
    float pricePerDozen;
    float totalPrice;
public:
    Cookie(std::string, float, float);
    const std::string getType() const;
    const std::string& getName() const;
    int getQuantity() const;
    float getTotalPrice() const;
    float getPricePerDozen() const;
};

Cookie::Cookie(std::string nname, float nnumber, float nprice){
    name = nname;
    type = "cookies";
    number = nnumber;
    pricePerDozen = nprice;
    totalPrice = number * pricePerDozen / 12;
}

const std::string Cookie::getType() const{
    return type;
}

const std::string& Cookie::getName() const{
    return name;
}

int Cookie::getQuantity() const{
    return number;
}

float Cookie::getTotalPrice() const{
    return totalPrice;
}

float Cookie::getPricePerDozen() const{
    return pricePerDozen;
}

std::ostream& operator <<(std::ostream& out, const Cookie& toPrint){
    out << toPrint.getName() << " #" << toPrint.getQuantity() << " " << toPrint.getTotalPrice() << std::endl;
    return out;
}

#endif // COOKIE_H
