#include "FoodOrder.h"
#include "InvalidInput.h"
#include <string>
#include <iostream>
using namespace std;

//Foundamental type static member is by default 0
int FoodOrder :: foodCount = 0;

//Constructor
FoodOrder :: FoodOrder(string name, string date, string phone, float miles, string restaurantName)
          :DeliveryOrder(name,date,phone, miles)//explicitly calling the base class's constructor
{
    this->restaurantName = restaurantName;
}

//Destructor
FoodOrder ::~FoodOrder() {
    cout << "FoodOrder destroyed.\n";
}

//override the receipt() function
void FoodOrder ::receipt() const{
    DeliveryOrder::receipt();
    cout << "\tDrinks Count: " << FoodOrder :: foodCount << endl;
}

//overriding a base class's pure virtual function 
float FoodOrder ::VIPdiscount() const{
    if(orderBalance > 50){
        return 0.85;
    }
    else if (orderBalance > 30){
        return 0.9;
    }
    else if (orderBalance > 20){
        return 0.95;
    }
    else if (orderBalance >0){
        return 1;
    }
    else {
        cout << "Invalid input." << endl; 
        return -9999;
    }
}

//default arguments
float FoodOrder ::addFood(string courseName, int sides, bool addSoup ){
    float sum;
    //Thick Cauliflower Steak: $15; Rack of Lamb: $38
    //Organic Scottish Salmon: $23; Grilled Lobster Risotto: $46
    //Adding soup costs $6, each additional side costs $5.
    if(courseName == "Thick Cauliflower Steak"){
        sum = (addSoup) ? 15 + 5 * sides + 6 : 15  + 5  * sides ;       
    }
    else if(courseName == "Rack of Lamb"){
        sum = (addSoup) ? 38  + 5 * sides + 6 : 38  + 5  * sides ;       
    }
     else if(courseName == "Organic Scottish Salmon"){
        sum = (addSoup) ? 23  + 5 * sides + 6 : 23  + 5  * sides ;            
    }
    else if (courseName == "Grilled Lobster Risotto") {      
        sum = (addSoup) ? 46  + 5 * sides + 6 : 46  + 5  * sides ;             
    } 
    else {
        throw InvalidInput(courseName);
    }    
    orderBalance+=sum; // add the cost of this food order to the orderBalance of the order(the protected variable)  
    FoodOrder :: foodCount++;//update the static variable drinksCount
    return sum;
}