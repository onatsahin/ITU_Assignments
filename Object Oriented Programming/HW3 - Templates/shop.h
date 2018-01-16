//Onat ŞAHİN No: 150150129

#ifndef SHOP_H
#define SHOP_H
#include <iostream>
#include <vector>
#include <string>

template <class Type>

class Shop{
    std::vector<Type> list;
    int discount;
public:
    Shop();
    Shop(Type);
    void add(Type);
    void setDiscount(int);
    int getDiscount() const;
    int getSize() const;
    const Type& operator[](int) const;
};

template <class Type>
Shop<Type>::Shop(){
    discount = 0;
}

template <class Type>
Shop<Type>::Shop(Type item){
    discount = 0;
    list.push_back(item);
}

template <class Type>
void Shop<Type>::add(Type toAdd){
    list.push_back(toAdd);
}

template <class Type>
void Shop<Type>::setDiscount(int toSet){
    if(toSet > 30 || toSet < 0)
        throw std::string("Discount rate is out of range!");

    discount = toSet;
}

template <class Type>
int Shop<Type>::getDiscount() const{
    return discount;
}

template <class Type>
int Shop<Type>::getSize() const{
    return list.size();
}

template <class Type>
const Type& Shop<Type>::operator[](int index) const{
    if(index >= list.size())
        throw "We don't have enough" + list[0].getType() + "!";

    return list[index];
}

template <class Type>
std::ostream& operator <<(std::ostream& out, const Shop<Type>& toPrint){    //This operator overloading also includes the calculations related to tax and discount
    float totalCost = 0;
    float totalCostWithTax;
    int size = toPrint.getSize();
    out << "**********************" << std::endl << std::endl;
    out << "Number of items: " << size << std::endl;

    for(int i=0; i<size; i++){
        out << i+1 << ": " << toPrint[i].getName() << " #" << toPrint[i].getQuantity() << " Cost: " << toPrint[i].getTotalPrice() << std::endl << std::endl;
        totalCost += toPrint[i].getTotalPrice();
    }

    totalCostWithTax = totalCost/100*108;
    out << "**********************" << std::endl<< std::endl;
    if(toPrint.getDiscount() == 0){
        out << "Total Cost: " << totalCostWithTax << std::endl;
    }
    else{
        out << "Total Cost: " << totalCostWithTax << std::endl;
        out << "Discount: " << toPrint.getDiscount() << "%" <<std::endl;
        out << "Discount amount: -" << totalCostWithTax / 100 * toPrint.getDiscount() << std::endl;
        out << "Discounted cost: " << totalCostWithTax - (totalCostWithTax / 100 * toPrint.getDiscount()) << std::endl;
    }
    out << "**********************" << std::endl << std::endl;
    return out;
}

#endif // SHOP_H
