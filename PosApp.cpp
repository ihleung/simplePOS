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
#include <fstream>
#include <cstring>
#include <iomanip>
#include "PosApp.h"


using namespace std;
namespace sdds 
{
    PosApp::PosApp(const char* filename)
    {
        int length = 0;
        length = strlen(filename);
        if (length > MAX_CHARACTER)
        {
          length = MAX_CHARACTER;
        }
        strncpy(m_filename, filename, length);
        m_filename[length] = '\0';

        for (int i = 0; i < MAX_NO_ITEMS; i++)
        {
            Iptr[i] = nullptr;
        }
    }
    PosApp::PosApp()
    {  
        for (int i = 0; i < MAX_NO_ITEMS; i++)
        {
           Iptr[i] = nullptr;
        }
        nptr = 0;
        m_filename[0] = '\0';
    }

    PosApp::~PosApp()
    {
        for (int i = 0; i < MAX_NO_ITEMS; i++)
        {
            delete Iptr[i];
            Iptr[i] = nullptr;
        }
    }

    void PosApp::actionTitle()
    {
        cout << ">>>> ";
        cout.fill('.');
        cout.width(72);
    }

    void PosApp::sortItems()
    {
        int i = 0, j = 0;
        Item* temp{};
        for (i = nptr - 1; i > 0; i--)
        {
            for (j = 0; j < i; j++)
            {
                if (strcmp(Iptr[j]->Name(), Iptr[j + 1]->Name()) > 0)
                {
                    temp = Iptr[j];
                    Iptr[j] = Iptr[j + 1];
                    Iptr[j + 1] = temp;
                }
            }
        }
    }

    int PosApp::menu()
    {   
        int input;
        int valid = 1;
        cout << "The Sene-Store" << endl;
        cout << "1- List items" << endl;
        cout << "2- Add item" << endl;
        cout << "3- Remove item" << endl;
        cout << "4- Stock item" << endl;
        cout << "5- POS" << endl;
        cout << "0- exit program" << endl;
        cout << "> ";
        do
        {
            cin >> input;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Integer, try again: ";
                valid = 1;

            }
            else if (input < 0 || input > 5)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "[0<=value<=5], retry: > ";
                valid = 1;
            }
            else
            {

                valid = 0;

            }
        } while (valid != 0);
       
        return input;
        
    }
     void PosApp::addItem()
     {
        cout.setf(ios::left);
        cout << "Adding Item to the store";
        cout.unsetf(ios::left);
        cout << endl;
        if (nptr != MAX_NO_ITEMS)
        {
            Item* ItemTmp = nullptr;
            char two;
            cout << "Is the Item perishable? (Y)es/(N)o: ";
            cin >> two;
            cin.ignore(1000, '\n');
            if (two == 'y' || two == 'Y')
            {
                ItemTmp = new Perishable();
            }
            else if (two == 'n' || two == 'N')
            {
                ItemTmp = new NonPerishable();
            }
            cin >> *ItemTmp;
            if (ItemTmp)
            {
                Iptr[nptr++] = ItemTmp;

            }
            else
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << *ItemTmp << endl;
                cout << ", try again..." << endl;

            }
           
        }
        else
        {
            cout << "Inventory Full!";
        }
        actionTitle();
        cout.setf(ios::left);
        cout << "DONE!";
        cout.unsetf(ios::left);
        cout << endl;
     }

     void PosApp::removeItem()
     {
        cout.setf(ios::left);
        cout << "Remove Item";
        cout.unsetf(ios::left);
        cout << endl;
        int row = selectItem();
        cout << "Removing...." << endl;
        row--; 
        Iptr[row]->displayType(POS_FORM);
        cout << *Iptr[row];
        delete Iptr[row];
        Iptr[row] = nullptr;
        for (int i = row; i < nptr - 1; i++) 
        {
            Iptr[i] = Iptr[i + 1];
        }
        nptr--;
        actionTitle();
        cout.setf(ios::left);
        cout << "DONE!";
        cout.unsetf(ios::left);
        cout << endl;
     }

     void PosApp::stockItem()
     {
        int stop = 1;
        int q = 0;
        cout.setf(ios::left);
        cout << "Select an item to stock";
        cout.unsetf(ios::left);
        cout << endl;
        int row = selectItem();
        cout.setf(ios::left);
        cout << "Selected Item:\n";
        Iptr[row - 1]->displayType(POS_FORM);
        cout << *Iptr[row - 1];
        cout.unsetf(ios::left);
        cout << "Enter quantity to add: "; 
       
        do
        {
            cin >> q;
            if (cin.fail())
            {
                cin.clear();
                cout << "Invalid Integer, try again: ";
                stop = 1;
            }
            else if (q < 1 || q > 69)
            {
                cin.clear();
                cout << "[1<=value<=69], retry: Enter quantity to add: ";
                stop = 1;
            }
            else
            {
                stop = 0;
            }
            cin.ignore(1000, '\n');
        } while (stop != 0);

        Iptr[row - 1]->operator+= (q);

        actionTitle();
        cout.setf(ios::left);
        cout << "DONE!";
        cout.unsetf(ios::left);
        cout << endl;
     }

     void PosApp::listItem(bool stop = true) 
     {
         double total = 0.0;
         cout.setf(ios::left);
         cout << "Listing Items";
         cout.unsetf(ios::left);
         cout << endl;
         cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
         cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
         
         sortItems();
         for (int i = 0; i < nptr; i++)
         {
             if (Iptr[i]->displayType(POS_LIST))
             {
                 cout << setw(4) << setfill(' ') << right << i + 1 << " | ";
                 Iptr[i]->write(cout);
                 cout << endl;
                 cout.unsetf(ios::right);
                 total += *Iptr[i];
             }
         }
         
         cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
         if (stop)
         {
             cout << setw(48) << setfill(' ') << right << "Total Asset: $  |";
             cout << setw(13) << setfill(' ') << right << fixed << setprecision(2) << total << " |" << endl;
             cout << "-----------------------------------------------^--------------^" << endl;
             cout << endl;
         }
         cout.unsetf(ios::right);

     }

     int PosApp::selectItem() 
     {
         int row = 0;
         int stop = 1;
         actionTitle();
         cout.setf(ios::left);
         cout << "Item Selection by row number";
         cout.unsetf(ios::left);
         cout << endl;
         cout << "Press <ENTER> to start....";
         cin.ignore(1000, '\n');
         cout << endl;
         actionTitle();
         listItem(false);
         cout << "Enter the row number: ";
         do 
         {
             cin >> row;
             if (cin.fail()) 
             {
                 cin.clear();
                 cout << "Invalid Integer, try again: ";
                 stop = 1;
             }
             else if (row < 1 || row > 26) 
             {
                 cout << "[1<=value<=26], retry: Enter the row number: ";
                 stop = 1;
             }
             else 
             {
                 stop = 0;
             }
             cin.ignore(1000, '\n');
         } while (stop != 0);
         return row;

     }

     void PosApp::POS()
     {
        cout.setf(ios::left);
        cout << "Starting Point of Sale";
        cout.unsetf(ios::left);
        cout << endl;
        cout << "Running POS()" << endl;
     }

     void PosApp::saveRecs() const
     {
        cout.setf(ios::left);
        cout << "Saving Data";
        cout.unsetf(ios::left);
        cout << endl;
        ofstream out;
        out.open(m_filename);
  
        for (int i = 0; i < nptr; i++)
        {
            Iptr[i]->save(out);
            out << endl;
        }
        out.close();

     }

     void PosApp::loadRecs()
     {
        cout.setf(ios::left);
        cout << "Loading Items";
        cout.unsetf(ios::left);
        cout << endl;
        if (nptr != 0)
        {
            for (int i = 0; i < MAX_NO_ITEMS; i++)
            {
                delete Iptr[i];
                Iptr[i] = nullptr;
            }
        }
        ifstream readInputFile(m_filename);
        if (!readInputFile)
        {
            ofstream readOutputFile(m_filename);
            readOutputFile.close();
        }
        else
        {
            nptr = 0;
            while (!readInputFile.eof())
            {
                char rectype = '\0';
                readInputFile.get(rectype);
                readInputFile.ignore(1, ',');
                if (rectype == 'N')
                {
                    Iptr[nptr] = new NonPerishable();
                }
                else if(rectype == 'P')
                {
                    Iptr[nptr] = new Perishable();
                }
                if (Iptr[nptr])
                {
                    Iptr[nptr]->load(readInputFile);
                    readInputFile.ignore(100, '\n');
                    nptr++;
                }
            }
           
            readInputFile.close();
        }
        
     }

     void PosApp::run()
     {
       int input = 0;
       int stop = 1;
       actionTitle();
       loadRecs();
       do
       {
           input = menu();
           if (input == 1)
           {
               actionTitle();
               listItem(true);
               stop = 1;
               cin.clear();
           }
           else if (input == 2)
           {
                actionTitle();
                addItem();
                stop = 1;
                cin.clear();
           }
           else if (input == 3)
           {
               actionTitle();
               removeItem();
               stop = 1;
               cin.clear();
           }
           else if (input == 4)
           {
               actionTitle();
               stockItem();
               stop = 1;
               cin.clear();
           }
           else if (input == 5)
           {
               actionTitle();
               POS();
               stop = 1;
               cin.clear();
           }
           else if (input == 0)
           {

               actionTitle();
               saveRecs();
               stop = 0;
               
           }

       } while (stop != 0);

       cout << "Goodbye!" << endl;
       
     }

}