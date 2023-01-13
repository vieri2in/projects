#include "BobaOrder.h"
#include "InvalidInput.h"
#include <string>
#include <iostream>
using namespace std;

//Foundamental type static member is by default 0
int BobaOrder :: drinksCount = 0;

//Constructor
BobaOrder :: BobaOrder(string name, string date, string phone, float miles, string shopName)
          :DeliveryOrder(name,date,phone, miles)//explicitly calling the base class's constructor
{
    this->shopName = shopName;
}

//Destructor
BobaOrder ::~BobaOrder(){
    cout << "BobaOrder destroyed.\n";
}

//override the receipt() function
void BobaOrder ::receipt() const{
    DeliveryOrder::receipt();
    cout << "\tDrinks Count: " << BobaOrder :: drinksCount << endl;
}

//overriding a base class's pure virtual function 
float BobaOrder ::VIPdiscount() const{
    if(drinksCount > 10){
        return 0.85;
    }
    else if (drinksCount > 5){
        return 0.9;
    }
    else if (drinksCount > 2){
        return 0.95;
    }
    else if (drinksCount >=1){
        return 1;
    }
    else {
        cout << "Invalid input." << endl; 
        return -9999;
    }
}

//default arguments
float BobaOrder :: addDrink(string drinkName,bool addBoba, int count){
    float sum;
    //Green Tea Latte: $6.6; Brown Sugar Boba Milk: $8.8; Brown Sugar Pearl Milk: $9.9 
    //Adding boba will cost $1.5 per drink 
    if(drinkName == "Green Tea Latte"){
        sum = (addBoba)?(6.6  + 1.5 ) * count:6.6 * count ;        
    }
    else if(drinkName == "Brown Sugar Boba Milk"){
        sum = (addBoba)?(8.8  + 1.5 ) * count:8.8 * count ; 
    }
    else  if (drinkName == "Brown Sugar Pearl Milk") {      
        sum = (addBoba)?(9.9  + 1.5 ) * count:9.9 * count ; 
    }   
    else {
        throw InvalidInput(drinkName);
    } 
    orderBalance+=sum; //add the cost of this drink order to the orderBalance of the order (the protected variable)
    BobaOrder :: drinksCount+=count;//update the static variable drinksCount
    return sum;
}