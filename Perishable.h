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
#ifndef SDDS_PERISHABLE_H_
#define SDDS_PERISHABLE_H_
#include <iostream>
#include <cstring>
#include "Item.h"
#include "Date.h"


namespace sdds
{

	class Perishable : public Item
	{
		Date expiry;

		public:
			virtual char itemType() const;
			virtual std::ostream& write(std::ostream& ostr) const;
			virtual std::istream& read(std::istream& istr);
			virtual std::ofstream& save(std::ofstream& oftr) const;
			virtual std::ifstream& load(std::ifstream& iftr);
	
	};



}
#endif // !SDDS_NONPERISHABLE_H_

