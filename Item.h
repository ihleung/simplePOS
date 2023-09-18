/* Citation and Sources...
Final Project Milestone 5
Module: PosApp
Filename: PosApp.cpp
Version 1.3
Author	Ivan Leung
Revision History
-----------------------------------------------------------
Date      Reason
2023/3/21 updated citation and sources information for all related files
2023/3/21 updated the Error.cpp
2023/4/7  updated the Date.h and Date.cpp
2023/4/7  updated the Item.cpp
2023/4/10 updated the PosApp.cpp and PosApp.h
-----------------------------------------------------------*/
#ifndef SDDS_ITEM_H_
#define SDDS_ITEM_H_
#include <iostream>
#include <cstring>
#include "POS.h"
#include "Error.h"
#include "PosIO.h"

namespace sdds
{
	
	class Item : public PosIO
	{
		char SKU[MAX_SKU_LEN];
		char* m_name;
		double Price = 0.0;
		bool Taxed = false;
		int Quantity = 0;
		
	protected:
		int diaplayType = 0;
		Error m_error;
		
	public:
		int displayType() const;
		Item& setName(const char* name);
		
		Item();
		~Item();
		Item(const Item& copy);
		Item& operator=(const Item& copy);
		bool operator==(const char* a) const;
		bool operator>(const Item& copy) const;
		int operator+=(int number);
		int operator-=(int value);
		operator bool() const;
		Item& clear();
		virtual char* Name() const;
		virtual Item& displayType(int value);
		virtual double cost() const;
		virtual int quantity() const;
		virtual char itemType() const = 0;
		virtual std::ostream& write(std::ostream& ostr) const;
		virtual std::ofstream& save(std::ofstream& ofstr) const;
		virtual std::istream& read(std::istream& istr);
		virtual std::ifstream& load(std::ifstream& ifstr);
		std::ostream& bprint(std::ostream& ostr) const;
		
		 
	};
	double& operator+=(double& total, const Item& copy);
	
}
#endif // !SDDS_ITEM_H_

