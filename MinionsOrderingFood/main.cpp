#include "DeliveryOrder.h"
#include "Account.h"
#include "BobaOrder.h"
#include "FoodOrder.h"
#include "InvalidInput.h"
#include <string>
#include <iostream>
using namespace std;

float applyDiscount(DeliveryOrder*,   const Account&);

int main(){
    const Account account1("Stuart","Owner");
    Account account2("Kevin","VIP");
    Account account3("Bob");
    DeliveryOrder*  deliveryOrderPtr;

    //1. Kevin Placing Order
    cout << "Kevin placing order.\n";
    BobaOrder order1("Kevin", "1/20/2022", "123-456-0000", 10.4, "Tiger Sugar");  
    try{
        order1.addDrink("Green Tea Latte");
        order1.addDrink("Brown Sugar Pearl Milk", false);
        order1.addDrink("Brown Sugar Boba Milk", false, 2);
        order1.addDrink("Iron Goddess");
    }
    catch (InvalidInput& e) {
        e.print_reason();
        cout << "Not serving requested drinks. Drink order ignored.\n\n";
    }   
    order1.receipt();
    cout << "Balance: $" << order1.getTotalBalance() << endl;
    deliveryOrderPtr = &order1;
    cout << "Discounted Balance: $" << applyDiscount(deliveryOrderPtr, account2) << endl;
    cout << endl << endl;

    //2. Stuart  Placing Order
    cout << "Stuart  placing order.\n";
    FoodOrder order2("Stuart", "1/20/2022", "123-456-1111", 25.5, "Tavern Green"); 
    try{
        order2.addFood("Thick Cauliflower Steak", 1, true);
        order2.addFood("Organic Scottish Salmon");
        order2.addFood("Rack of Lamb", 0, true); //have to enumerate the previous default para before specifying the latter default para      
    }
    catch (InvalidInput& e) {
        e.print_reason();
        cout << "Not serving requested food. Food order ignored.\n\n";
    }   
    order2.receipt();
    cout << "Balance: $" << order2.getTotalBalance() << endl;
    deliveryOrderPtr = &order2;
    cout << "Discounted Balance: $" << applyDiscount(deliveryOrderPtr, account1) << endl;
    cout << endl << endl;

    //3. Bob   Placing Order
    cout << "Bob decided to log in to his account and see whether he can afford ordering the same order as Stuart.\n";
    //Bob is trying to place the same order, so he's using the same order object that Stuart created. 
    order2.receipt(); 
    cout << "Balance: $" << order2.getTotalBalance() << endl;
    //still use Stuart's pointer but pass in Bob's account
    cout << "Discounted Balance: $" << applyDiscount(deliveryOrderPtr, account3) << endl;
    cout << "Bob upset, cancelling order :(\n\n"; 
    cout << "Total order placed: " << DeliveryOrder::getOrderCount() << ".\n\n";
    return 0;
}

float applyDiscount(DeliveryOrder* m,  const Account& acct) {
    float sum;
    if (acct.getStatus() == "Owner"){
        sum = 0.1 * m->getTotalBalance(); // "Owner" status return 0.1 
    }
    if (acct.getStatus() == "VIP"){
        sum =  m->VIPdiscount() * m->getTotalBalance(); // VIPdiscount() is dynamic binding btw BobaOrder or a FoodOrder 
    }
    if (acct.getStatus() == "Regular"){ //"Owner" status means no discount 
        sum = m->getTotalBalance();
    }
    return sum;
}