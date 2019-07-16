//Programmer: Kylie Outlaw & Olivia Dougan
//Date: 5/7/19
//Assignment: HW10
/*Purpose: This program will implement the business class and implement each of
its functions and variables*/

#include "customer.h"
#include "business.h"



//Initialize business with default values
business::business()
{
  m_cash = 0;
  m_numCust = 0;
  m_name = "NULLBUSINESS"; //I used null as a placeholder
}



//Initialize a business object with name and cash in register
business::business(string name, float cash)
{
  string word;
  m_name = name;
  m_cash = cash;
  m_numCust = 0;
}



//Functions
void business::addCustomer(const customer & customer)
{
  //Add customer #m_numCust to the list of customers in store
  customers[m_numCust] = customer;
  //Output a nice statement saying customer entered the store
  cout<<customers[m_numCust].getName()<<" entered "<<m_name<<endl;

  m_numCust++; //increment m_numCust
  return;
}



void business::sell_stuff()
{
  bool saleMade; //to tell if a purchase was made
  int randomNum; //store sells 7 items, choose one of the 7
  
  for(int i=0; i < m_numCust ; i++)
  {
    randomNum = rand()%7;

    //See if the customer has successfully purchased something 
    saleMade = customers[i].buy_something(products[randomNum]);

    if(saleMade == true)
    {
      //Add money to the business for completing a successful sale
      m_cash += products[randomNum].m_price; 
    }
  }
  return;
}



int business::customers_leave(customer street[], int & num)
{
  int j = num;

  //for every customer in the business, return them to the street
  for(int i = 0; i<m_numCust; i++)
  {
    street[j] = customers[i];
    j++;
    //and increment the number of customers in the street
    num++;
    
  }
  
  m_numCust = 0; //set number of customers to 0 since all have left the store
  return num;
}



void business::setUpShop(const string fileName) //COMPLETED CODE
{
  float itemCost;
  //open a new filestream with the filename containing items for the business
  ifstream fin2(fileName);
  //make sure it can open properly
  if(!fin2)
  {
  cout<<"Cannot open "<< fileName << "!\n";
  exit(1);
  }

  for(int i=0; i<NUMITEMS; i++) //add the items into the shop
  {
    fin2>>itemCost;
    products[i].m_price = itemCost;
    fin2.ignore(10, ' ');
    getline(fin2, products[i].m_productname);
  }
  //clear and close the file stream to ensure next setup is smooth :)
  fin2.clear();
  fin2.close();
  return;
}



ostream & operator <<(ostream & os, const business & business)
{
  //Output important information about business
  os << "The name of the business is "<< business.m_name<<endl;

  os << "The customers currently in the business are: ";
  for(int i = 0; i<business.m_numCust; i++)
  {
    os<<business.customers[i].getName()<<", ";
  }
  cout<<endl;

  os<<"The items sold by this business are: ";
  for(int i=0; i<7; i++)
  {
    os<<business.products[i].m_productname<<", ";
  }
  os<<endl;
  os<<"The business has $"<<business.m_cash;
  cout<<endl<<endl;
  return os;
}

//Implementation for Business Class