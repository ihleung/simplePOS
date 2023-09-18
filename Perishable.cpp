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
#include "Perishable.h"

using namespace std;

namespace sdds
{
    char Perishable::itemType() const
    {
        return 'P';
    }

    std::ostream& Perishable::write(std::ostream& ostr) const
    {
        Item::write(ostr);
        if (*this)
        {
            if (Item::diaplayType == POS_LIST)
            {
                ostr.setf(ios::right);
                ostr << ' ' << ' ' << setw(3) << std::right << expiry << ' ' << '|';
                ostr.unsetf(ios::right);
            }
            else if (Item::diaplayType == POS_FORM)
            {
                ostr << "Expiry date: " << std::right << expiry << endl;
                ostr << "=============^" << endl;
                ostr.unsetf(ios::left);
                ostr.unsetf(ios::right);
            }
        }
        return ostr;
    }

    std::istream& Perishable::read(std::istream& istr)
    {
        Item::read(istr);
        if (*this && istr)
        {
            Date expiryDate;
            expiryDate.dateOnly(true);
            cout << "Expiry date (YYYY/MM/DD)" << endl;
            cout << "> ";
            istr >> expiryDate;     
            if (istr.fail())
            {
                m_error = expiryDate.error();
                istr.setstate(std::ios::failbit);
            }
            else
            {
                expiry = expiryDate;
            }
        }
       
        return istr;
    }

    std::ofstream& Perishable::save(std::ofstream& oftr) const
    {
        Item::save(oftr);
        if (*this)
        {
            oftr << "," << expiry;
        }
        return oftr;
    }

    std::ifstream& Perishable::load(std::ifstream& iftr)
    {
        Item::load(iftr);
        if (*this && iftr)
        {
            Date expiryDate;
            expiryDate.dateOnly(true);
            
            iftr.ignore(1000, ',');
            iftr >> expiryDate;
            if (iftr.fail())
            {
                m_error = expiryDate.error();
                iftr.setstate(std::ios::failbit);
            }
            else
            {
                expiry = expiryDate;
            }
        }
       
        return iftr;
    }
  
}