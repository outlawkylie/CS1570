//Programmer: Kylie Outlaw & Olivia Dougan
//Date: 5/7/19
//Assignment: HW10
/*Purpose: This program will implement the customer class and implement each of
its functions and variables*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include<iomanip>
#include "customer.h"
#include "business.h"
using namespace std;

int main()
{
  srand(time(NULL)); //seed the rand function
  cout<<setprecision(2)<<fixed; //set precision for $$$ purposes

  //Initialize all variables (purpose given by names)
  int numCustomers = 20, numInStreet = 20, randCustNum;
  int inclination, cycleNum = 0, customersLeaving=0;
  business MoesBar("Moe's Bar", 500), ComicStore("CBG's Comics", 300);
  customer street[20];
  string name;

  //create a temporary customer to shuffle array and null for when people leave
  customer null("null", 0), temp;  


  //Open file of customers and read in data
  ifstream fin("customers.txt");
  if(!fin) //Make sure file can open
  {
    cout<<"Cannot open customers.txt" << "!\n";
    exit(1);
  }

  //Setup the customers in the street//
  for(int i=0; i<numCustomers; i++)
  {
    getline(fin, name, ',');
    street[i].setName(name);
    fin.ignore(10, ' ');
    fin>>inclination;
    street[i].setInc(inclination);
    fin.ignore(10, '\n');
  }
  //close and clear for #code reasons
  fin.close();
  fin.clear();
  
  //Setup Shops//
  MoesBar.setUpShop("MoesItems.txt");
  ComicStore.setUpShop("CBGItems.txt");


  /* ******************************************************************* */
  /* **********************First Entering Stores *********************** */
  for(int i = 0; i<numCustomers; i++)
  {
    //based on their inclination, add them to a certain store
    if(street[i].getInc() == -1)
    {
      MoesBar.addCustomer(street[i]);
      numInStreet--;
    }
    else if (street[i].getInc() == 1)
    {
      ComicStore.addCustomer(street[i]);
      numInStreet--;
    }
  }

  /* ************************************************************ */
  /* ************************************************************ */

  /* LOOP TO RUN THROUGH OF PEOPLE GOING INTO STORES AND FIGHTING */

  do{
    cycleNum ++; 
    cout<<endl<<endl;

    //output each person's information at the beginning of each round
    for(int i =0; i<numCustomers;i++)
    {
      cout<<street[i]<<endl;
    }

    //state which cycle number the simulation is on
    cout<<" *********** ROUND "<<cycleNum<<" **********"<<endl;
    
    //sell stuff at both stores
    MoesBar.sell_stuff();
    ComicStore.sell_stuff();
    
    //move customers back into the street from the store
    numInStreet = 0;
    numInStreet = MoesBar.customers_leave(street, numInStreet);
    numInStreet = ComicStore.customers_leave(street, numInStreet);

    //shuffle the customers in the street using swap function format
    for(int i = 0 ; i<numCustomers; i++)
    {
      randCustNum = rand()%numCustomers;
      temp = street[i];
      street[i] = street[randCustNum];
      street[randCustNum] = temp;
    }



    //STEAL AND / OR HURL OBJECTS//
    cout<<endl<<endl<<" *** CHAOS ON THE STREETS *** "<<endl;
    for(int i = 0; i<numCustomers; i++)
    {
      //the people in my town aren't really dumb so they don't steal from self
      //( it also gave me a few errors when they did shh )
      randCustNum = rand()%numCustomers; 

      //find a target for the perp to attack/steal from
      while(randCustNum == i)
      {
        randCustNum = rand()%numCustomers;
      }
      
      //if their inclination is the same, steal; otherwise throw at the victim
      if(street[i].getInc() == street[randCustNum].getInc())
      {
        //Steal from the other customer
        street[i].steal(street[randCustNum]);
    
      }
      else
      {
        //Throw at the customer
        street[i].hurl(street[randCustNum]);
  
      }
    }



    cout<<endl<<endl; //time to enter their respective businesses
    cout<<" *** DING DONG TIME TO SHOP OR LEAVE *** "<<endl;
    customersLeaving = 0; //clear num of customers leaving for the cycle
    for(int i = 0; i<numCustomers; i++)
    {
      if(street[i].getHappiness() > 90 || street[i].getHappiness()<10)
      {
        if(street[i].getHappiness() < 10)
        {
          //They're unhappy so kick them out
          cout<<"Wow, "<<street[i].getName()<<" is feeling really down!";
          cout<<" Better to go the House of Depression to feel better!\n";
          street[i] = null; //replace them with an NPC
          numInStreet --; //decrement number of people in town
          customersLeaving++; //increment number of people leaving
        }
        else if(street[i].getHappiness() > 90)
        {
          //They're too happy so kick them out
          cout<<"Wow, "<<street[i].getName()<<" is in euphoria!";
          cout<<" Better become lord of Shelbyville!!!\n";
          street[i] = null; //replace with NPC
          numInStreet--; //decrement number of people in town
          customersLeaving++; //increment number of people leaving
        }
      }

      else
      {
        //Add customers to the stores and decrement number of cust on street
        if(street[i].getInc() == -1)
        {
          MoesBar.addCustomer(street[i]);
          numInStreet--;
        }
        else if (street[i].getInc() == 1)
        {
          ComicStore.addCustomer(street[i]);
          numInStreet--;
        }
      }  
    }
    numCustomers -= customersLeaving;

    //Sort the street array so null customers are at the end!!
    int j = 0;
    for(int i=0; i<20; i++) //for every customer array slot
    {
      if(street[i].getName() != "null") //if it still has a customer
      {
        street[j] = street[i];
        j++;
      }
    }
  /* END OF CYCLE */
  } while(numCustomers>1 && cycleNum < 20);


  //AT THE END OF 20 ROUNDS OR IF ONE PERSON IS LEFT//
  cout<<endl<<endl;
  cout<<"*************** THE END OF THE SIMULATION ****************"<<endl;
  if(numCustomers == 1) //if there's only one person left
  {
    //output which person is left and a sad statement 
    cout<<"There is only one person left in town: "<<street[0].getName();
    cout<<endl;
    cout<<"There is no one to run the town. "<<street[0].getName();
    cout<<" dies alone."<<endl<<endl;
  }

  else if(cycleNum >= 20) //if the cycles ran out
  {
    //output who is left in town and a sad message
    cout<<"The people still left in town after 20 fights are: ";
    for(int i = 0;  i<numCustomers; i++)
    {
      cout<<street[i].getName()<<", ";
    }
    cout<<endl;
    cout<<"There aren't enough people left to run the town."<<endl;
    cout<<"It looks like this is the end of the world....."<<endl<<endl;
  }
  else //if everyone left town (last two left at same time)
  {
    //output a sad message
    cout<<"Everyone left town... such a distructive world we live in..."<<endl;
    cout<<"All of this over a comic store and a bar..."<<endl<<endl;
  }
  return 0;
}