#ifndef DeliveryOrder_H
#define DeliveryOrder_H

#include <string>
#include <iostream>
using namespace std;

class DeliveryOrder {
private:
    string name;
    string date;
    string phone;
    float miles;
    static int orderCount;
    static const float taxRate;
    static const int deliveryRate;
protected:
    float orderBalance; //doesn't include delivery fee and tax
public:  
    static int getOrderCount(); 
    virtual float VIPdiscount() const = 0; //a pure virtual function,calculate and return the discount for the order
    //Constructor
    DeliveryOrder(string name, string date, string phone, float miles);
    //a virtual destructor
    virtual ~DeliveryOrder(); 
    void receipt() const;
    float getTotalBalance() const;// return the total balance(with delivery fee and tax)
};

#endif //DeliveryOrder_H