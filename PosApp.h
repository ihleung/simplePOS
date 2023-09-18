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
#ifndef SDDS_POSAPP_H_
#define SDDS_POSAPP_H_
#include <iostream>
#include "Item.h"
#include "NonPerishable.h"
#include "Perishable.h"

namespace sdds 
{
   const int MAX_CHARACTER = 128;
  
   class PosApp
   {    
       char m_filename[MAX_CHARACTER] = { '\0' };
       Item* Iptr[MAX_NO_ITEMS];
       int nptr = 0;
       void actionTitle();
       void sortItems();

       public:
       int menu();
       void addItem();
       int selectItem();
       void removeItem();
       void stockItem();
       void listItem(bool stop);
       void POS();
       void saveRecs() const;
       void loadRecs();
       void run();
       PosApp(const char* filename);
       PosApp();
       ~PosApp();
       PosApp(const PosApp& copy) = delete;
       PosApp& operator=(const PosApp& copy) = delete;
    
 
   };

}
#endif // !SDDS_POSAPP_H_

