//Programmer: Kylie Outlaw & Olivia Dougan
//Date: 5/7/19
//Assignment: HW10
/*Purpose: This program will declare the customer class and introduce each of
its functions, mutators and accessors, and variables*/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <cstring>
#include <time.h>
#include <random>
using namespace std;

struct product
{
  string m_productname;
  float m_price;
};


class customer
{
  private:
    product purchases[20]; //list of products (structs!!!)
    short m_numItemsInPocket; //number of purchases completed
    float m_money; //amount of money
    string m_name; //name of customer
    int m_happiness; //customer's happiness
    int m_inclination; //customer's inclination

  public:
  // *** Constructors ***
  customer();
  customer(string name, float money);


  // ***Accessors and Mutators***
  string getName()const{return m_name;} //returns name
  int getInc()const{return m_inclination;} //returns inclination
  int getHappiness()const{return m_happiness;} //returns customer happiness

  //sets name of customer (used in initialization from list)
  void setName(string name){m_name = name;} 
  //sets inclination of customer (used in initialization from list)
  void setInc(int inc){m_inclination = inc;} 
  //so many get/set - ters... privacy is dead in consumers anyways amirite?


  // *** Functions ***
  //checks if a customer can buy an item. adds item to list, changes
  //money and happiness as necessary. returns t/f if successful or not
  bool buy_something(const product & item); 

  //attempts to steal an object from another customer. changes happiness
  //and items in pocket of both people as needed
  void steal(customer & cust);

  //attempts to throw an object at another customer. changes happiness
  //and items in pocket as needed
  void hurl(customer & cust);

  //Print function - outputs information
  friend ostream & operator <<(ostream & os, const customer & customer);
};


#endif