//Programmer: Kylie Outlaw & Olivia Dougan
//Date: 5/7/19
//Assignment: HW10
/*Purpose: This program will declare the business class and introduce each of
its functions, mutators and accessors, and variables*/

#ifndef BUSINESS_H
#define BUSINESS_H

#include <iostream>
#include <cstring>
#include <time.h>
#include <random>
#include <fstream>
using namespace std;

struct product;
class customer;

class business
{
  private:
    const int NUMITEMS = 7; //seven items in each shop
    string m_name; //name of business
    float m_cash; //amount of money in register
    product products[10]; //products it sells
    customer customers[10]; //customers in store
    short m_numCust; //]number of customers


  public:

  // *** Constructors ***
  business();
  business(string name, float cash);


  // *** Accessors and Mutators ***
  void addCash(const float cash){m_cash += cash;}  //adds money to register
  void addCustomer(const customer & customer);   //Add a customer to the store's array of customers


  // *** Functions ***
  //Make a sale to current customers (force a sale)
  void sell_stuff();

  //puts customers back in the street, returns number of customers in street
  int customers_leave(customer street[], int & num); 

  //establish the shop's list of items & prices
  void setUpShop(const string filename); 

  //Print function- outputs data about the store
  friend ostream & operator <<(ostream & os, const business & business); 
};

#endif