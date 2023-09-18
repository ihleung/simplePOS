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
#ifndef SDDS_NONPERISHABLE_H_
#define SDDS_NONPERISHABLE_H_
#include <iostream>
#include <cstring>
#include "Item.h"


namespace sdds
{

	class NonPerishable : public Item
	{
		public:
			virtual char itemType() const override;
			virtual std::ostream& write(std::ostream& ostr) const;

	};

	

}
#endif // !SDDS_NONPERISHABLE_H_

