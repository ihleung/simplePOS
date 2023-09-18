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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "NonPerishable.h"

using namespace std;

namespace sdds
{
    char NonPerishable::itemType() const
    {
        return 'N';
    }
    std::ostream& NonPerishable::write(std::ostream& ostr) const
    {
        Item::write(ostr);
        if (*this)
        {          
           if (Item::diaplayType == POS_FORM)
           {
                ostr << "=============^" << endl;
                ostr.unsetf(ios::fixed);
                ostr.unsetf(ios::left);
           }
           else if (Item::diaplayType == POS_LIST)
           {
               ostr << "     N / A   |";
               ostr.unsetf(ios::left);
               ostr.unsetf(ios::right);
               ostr.clear();
           }
        }

        return ostr;
    }
}