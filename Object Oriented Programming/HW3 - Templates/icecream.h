//Onat ŞAHİN No: 150150129

#ifndef ICECREAM_H
#define ICECREAM_H
#include <string>

class Icecream{
    std::string name;
    std::string type;
    float litre;
    float pricePerLitre;
    float totalPrice;
public:
    Icecream(std::string, float, float);
    const std::string& getType() const;
    const std::string& getName() const;
    float getQuantity() const;
    float getTotalPrice() const;
    float getPricePerLitre() const;
};

Icecream::Icecream(std::string nname, float nlitre, float nprice){
    name = nname;
    type = "ice cream";
    litre = nlitre;
    pricePerLitre = nprice;
    totalPrice = litre * pricePerLitre;
}

const std::string& Icecream::getType() const{
    return type;
}

const std::string& Icecream::getName() const{
    return name;
}

float Icecream::getQuantity() const{
    return litre;
}

float Icecream::getTotalPrice() const{
    return totalPrice;
}

float Icecream::getPricePerLitre() const{
    return pricePerLitre;
}

std::ostream& operator <<(std::ostream& out, const Icecream& toPrint){
    out << toPrint.getName() << " #" << toPrint.getQuantity() << " " << toPrint.getTotalPrice() << std::endl;
    return out;
}

#endif // ICECREAM_H
