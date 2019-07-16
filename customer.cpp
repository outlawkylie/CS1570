//Programmer: Kylie Outlaw & Olivia Dougan
//Date: 5/7/19
//Assignment: HW10
/*Purpose: This program will implement the customer class and implement each of
its functions and variables*/

#include "customer.h"
#include "business.h"


customer::customer()
{
  //set money to random amount between 4 and 250 & nullify other variables
  m_money = static_cast<float>(rand()%247) + 4.00;
  m_numItemsInPocket = 0;
  m_name = "";
  m_happiness = rand()%101;
}



customer::customer(string name, float money)
{
  //initializes name, money, and numitems
  m_name = name;
  m_money = money;
  m_numItemsInPocket = 0;
}



bool customer::buy_something(const product & item)
{
  
  bool topurchase = false;
  int determinePurchase = rand()%2; //decides if customer wants to buy or not

  if(determinePurchase == 0)
  {
    //dont buy anything
    m_happiness -= 10; 
    cout<<m_name<<" decided not to buy anything."<<endl;
  }

  else if(determinePurchase == 1 && m_numItemsInPocket <= 20)
  {
    if(m_money <= item.m_price) //if the customer doesn't have enough to buy
    {
      topurchase = false;
      //doesn't allow a purchase if not enough money
      cout<<m_name<<" did not have enough $ to buy a(n) "<<item.m_productname;
    }
    else //customer can purchase 
    {
      cout<<m_name<<" has purchased a(n) "<<item.m_productname;
      cout<<" for $"<<item.m_price<<endl;

      //decrements money by item price & sets bool to true
      topurchase = true;
      m_money -= item.m_price;

      //adds product to purchase list
      purchases[m_numItemsInPocket] = item;

      //increments number of items in pocket&add 15 happiness
      m_numItemsInPocket++;
      m_happiness += 15; 
    }
  }
  return topurchase; //returns true or false
}



void customer::steal(customer & cust)
{
  //victim has to have an item & perp has pocket space
  if(cust.m_numItemsInPocket > 0 && m_numItemsInPocket < 10)
  {
    cout<<m_name<<" stole a ";
    cout<<cust.purchases[cust.m_numItemsInPocket-1].m_productname;
    cout<<" from "<<cust.m_name<<endl;

    //add victim's item to the perp's pocket
    purchases[m_numItemsInPocket] = cust.purchases[cust.m_numItemsInPocket-1];

    //increment perp's items and happiness, decrement victim's (rip) 
    m_numItemsInPocket++;
    cust.m_numItemsInPocket--;
    m_happiness += 25;
    cust.m_happiness -=20;
  }
  else //if there's no item to steal
  {
    //decrement happiness and output a nice message
    m_happiness -= 5; 
    cout<<m_name<<" fails to steal an item from "<<cust.m_name<<endl;
  }
  return;
}




void customer::hurl(customer & cust)
{
  //perp has to have an item to throw
  if(m_numItemsInPocket > 0)
  {
    cout<<m_name<<" throws a "<<purchases[(m_numItemsInPocket-1)].m_productname;
    cout<<" at "<<cust.m_name<<endl;

    //increment happiness of perp, decrement for victim. remove item from perp
    m_happiness += 5;
    cust.m_happiness -= 20;
    m_numItemsInPocket -- ;
  }

  else //if the perp has no item to throw
  {
    //decrement happiness and output message
    cout<<m_name<<"fails to throw an object at "<<cust.m_name<<endl;
    m_happiness -= 25;
  }

  return;
}



ostream & operator <<(ostream & os, const customer&customer)
{
  //outputs essential information about customer object
  os << " *** "<< customer.m_name << " *** "<<endl;
  os << "Money: $"<<customer.m_money<<endl;
  os << "Happiness: "<<customer.m_happiness<<endl;
  os << "Inclination: "<<customer.m_inclination<<endl;
  os << customer.m_numItemsInPocket << " Purchases: ";

  //outputs each item in the customer's list
  for(int i = 0; i < (customer.m_numItemsInPocket); i++)
  {
    cout<<customer.purchases[i].m_productname;
    cout<<", ";
  }
  os<<endl<<endl;
  return os;
}

