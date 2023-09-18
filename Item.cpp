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
#include "Item.h"

using namespace std;

namespace sdds
{
	Item& Item::setName(const char* name)
	{
		if (name && name[0] != '\0')
		{
			m_name = new char[strlen(name) + 1];
			strcpy(m_name, name);
		}
		else
		{
			m_name = nullptr;
		}
		return *this;
	}
	Item::Item() : PosIO()
	{
		SKU[0] = '\0';
		m_name = nullptr;
		Price = 0;
		Taxed = false;
		Quantity = 0;
		diaplayType = POS_LIST;
	}

	int Item::displayType() const
	{
		return diaplayType;
	}

	Item::~Item()
	{
		delete[] m_name;
		m_name = nullptr;
	}

	Item::Item(const Item& copy)
	{
		*this = copy;
	}

	Item& Item::operator=(const Item& copy)
	{
		if (this != &copy)
		{
			delete[] m_name;
			m_name = nullptr;
			strcpy(SKU, copy.SKU);
			setName(copy.m_name);
			Price = copy.Price;
			Taxed = copy.Taxed;
			Quantity = copy.Quantity;
			diaplayType = copy.diaplayType;
			m_error = copy.m_error;
		}
		return *this;
	}

	bool Item::operator==(const char* a) const
	{
		return strcmp(SKU, a) == 0;
	}

	bool Item::operator>(const Item& copy) const
	{
		bool stop = false;
		if (copy.m_name && m_name) 
		{
			if (strcmp(m_name, copy.m_name) > 0) 
			{
				stop = true;
			}
			else 
			{
				stop = false;
			}
		}
		else 
		{
			stop = false;
		}

		return stop;
	}

	int Item::operator-=(int value) 
	{
		Quantity -= value;
		if (value > Quantity)
		{
			Quantity = 0;
			m_error = ERROR_POS_STOCK;
		}
		
		return Quantity;
	 
	}

	int Item::operator+=( int number) 
	{
		Quantity += number;
		if (Quantity > MAX_STOCK_NUMBER)
		{
			Quantity = MAX_STOCK_NUMBER;
			m_error = ERROR_POS_QTY;
		}
		
		return Quantity;
	}

	Item::operator bool() const
	{
		return !m_error;
	}

	double& operator+=(double& total, const Item& copy)
	{
		total += (copy.cost() * copy.quantity());
		return total;
	}


	Item& Item::displayType(int value)
	{
		if (value == POS_FORM)
		{
			diaplayType = POS_FORM;
		}
		else if (value == POS_LIST)
		{
			diaplayType = POS_LIST;
		}
		
		return *this;
	}

	double Item::cost() const
	{
		double total = 0.0;
		total = Price * (1 + Taxed * TAX);
		return total;
	}

	int Item::quantity() const
	{
		return Quantity;
	}

	
	Item& Item::clear()
	{
		m_error.clear();
		return *this;
	}

	char* Item::Name() const
	{
		return m_name;
	}

	std::ostream& Item::write(std::ostream& ostr) const
	{
		if (!*this)
		{
			cerr << m_error;
		}
		else
		{
			char name[MAX_NAME_LEN + 1] = { 0 };
			switch (diaplayType)
			{
			case POS_LIST:
				
				if (strlen(name) <= 20) 
				{
					if (m_name && m_name[0] != '\0')
					{
						strncpy(name, m_name, 20);
						name[20] = '\0';
					}

					ostr << left << setw(7) << setfill(' ') << SKU << "|";
					ostr << left << setw(20) << setfill(' ') << name << "|" << right << setw(7);
					ostr << setfill(' ') << fixed << setprecision(2) << Price << "| ";
					ostr << (Taxed ? 'X' : ' ') << " |" << right << setw(4) << setfill(' ');
					ostr << fixed << setprecision(2) << Quantity << "|" << right << setw(9);
					ostr << setfill(' ') << fixed << setprecision(2) << cost() * Quantity << "|";
				}
				break;

			case POS_FORM:

				ostr << "=============v" << endl;
				ostr << setw(13) << setfill(' ') << left << "Name:" << m_name << endl;
				ostr << setw(13) << setfill(' ') << left << "Sku:" << SKU << endl;
				ostr << setw(13) << setfill(' ') << left << fixed << setprecision(2) << "Price:" << Price << endl;
				ostr << setw(13) << setfill(' ') << left << "Price + tax:";

				if (!Taxed)
				{
					ostr << "N/A" << endl;
					
				}
				else
				{
					ostr << fixed << setprecision(2) << cost() << endl;
				}
				ostr << setw(13) << setfill(' ') << left << "Stock Qty:" << Quantity << endl;
				break;

			}
		}
		
		return ostr;
	}

	std::ofstream& Item::save(std::ofstream& ofstr) const
	{
		
		if (!*this)
		{
			cerr << m_error << endl; 
		}
		else
		{
			ofstr << itemType() << ',' << SKU << ',' << m_name << ',';
			ofstr << fixed << setprecision(2) << Price << ',';
			ofstr << (Taxed ? '1' : '0') << ',' << Quantity;
		}

		return ofstr;
	}

	std::istream& Item::read(std::istream& istr)
	{
		char sku[MAX_SKU_LEN + 1] = { 0 };
		char name[MAX_NAME_LEN + 1] = { 0 };
		double price = 0.0;
		char tax = '\0';
		int qty = 0;
		int stop = 1;

		cout << "Sku" << endl
			<< "> ";
		istr.getline(sku, MAX_SKU_LEN + 1, '\n');
		do
		{
			if (istr.fail() || strlen(sku) == 0 || strlen(sku) > MAX_SKU_LEN)
			{
				cout << ERROR_POS_SKU << endl << "> ";
				istr.clear();
				istr.ignore(1000, '\n');
				istr.getline(sku, MAX_SKU_LEN + 1, '\n');
				stop = 1;
			}
			else
			{
				stop = 0;
			}

		} while (stop != 0);
		cout << "Name" << endl
			<< "> ";
		istr.getline(name, MAX_NAME_LEN + 1, '\n');
		do
		{
			if (istr.fail() || strlen(name) == 0 || strlen(name) > MAX_NAME_LEN)
			{
				cout << ERROR_POS_NAME << endl << "> ";
				istr.clear();
				istr.ignore(1000, '\n');
				istr.getline(name, MAX_NAME_LEN + 1, '\n');
				stop = 1;
			}
			else
			{
				stop = 0;
			}
		} while (stop != 0);
		cout << "Price" << endl
			<< "> ";
		istr >> price;
		do
		{
			if (istr.fail() || price < 0)
			{
				cout << ERROR_POS_PRICE << endl
					<< "> ";
				istr.clear();
				istr.ignore(1000, '\n');
				istr >> price;
				stop = 1;
			}
			else
			{
				stop = 0;
			}
		} while (stop != 0);
		istr.ignore(1000, '\n');

		cout << "Taxed?" << endl << "(Y)es/(N)o: ";
		istr.get(tax);
		do
		{
			if (istr.fail() || (tax != 'y' && tax != 'Y' && tax != 'n' && tax != 'N'))
			{
				cout << "Only 'y' and 'n' are acceptable: ";
				istr.clear();
				istr.ignore(1000, '\n');
				istr.get(tax);
				stop = 1;
			}
			else
			{
				stop = 0;
			}

		} while (stop != 0);
		istr.ignore(1000, '\n');

		cout << "Quantity" << endl
			<< "> ";
		istr >> qty;
		do
		{
			if (istr.fail() || qty <= 0 || qty >= MAX_STOCK_NUMBER)
			{
				cout << ERROR_POS_QTY << endl
					<< "> ";
				istr.clear();
				istr.ignore(1000, '\n');
				istr >> qty;
				stop = 1;
			}
			else
			{
				stop = 0;
			}

		} while (stop != 0);
		strncpy(SKU, sku, MAX_SKU_LEN);
		delete[] m_name;
		m_name = nullptr;
		m_name = new char[strlen(name) + 1];
		strncpy(m_name, name, strlen(name));
		m_name[strlen(name)] = '\0';
		Price = price;
		Taxed = (tax == 'y' || tax == 'Y');
		Quantity = qty;

		return istr;
	}

	std::ifstream& Item::load(std::ifstream& ifstr)
	{
		m_error.clear();
		char sku[MAX_SKU_LEN + 2] = {};
		char name[MAX_NAME_LEN + 2] = {};
		double price = 0.0;
		int tax = 0;
		int qty = 0;

		ifstr.get(sku, MAX_SKU_LEN + 2, ',');
		ifstr.ignore(1000, ',');
		ifstr.get(name, MAX_NAME_LEN + 2, ',');
		ifstr.ignore(1000, ',');
		ifstr >> price;
		ifstr.ignore();
		ifstr >> tax;
		ifstr.ignore();
		ifstr >> qty;

		if (!ifstr.fail())
		{
			if (strlen(sku) > MAX_SKU_LEN)
			{
				m_error = ERROR_POS_SKU;
			}
			else if (strlen(name) > MAX_NAME_LEN)
			{
				m_error = ERROR_POS_NAME;
			}
			else if (price < 0.0)
			{
				m_error = ERROR_POS_PRICE;
			}
			else if (tax != 0 && tax != 1)
			{
				m_error = ERROR_POS_TAX;
			}
			else if (qty > MAX_STOCK_NUMBER)
			{
				m_error = ERROR_POS_QTY;
			}
			else
			{
				strcpy(SKU, sku);
				delete[] m_name;
				m_name = nullptr;
				m_name = new char[strlen(name) + 1];
				strcpy(m_name, name);
				Price = price;
				Taxed = tax;
				Quantity = qty;
			}
		}

		return ifstr;

	}

	std::ostream& Item::bprint(std::ostream& ostr) const
	{
		
		char name[MAX_NAME_LEN + 1] = { 0 };
		if (m_name)
		{
			strncpy(name, m_name, 20);
			name[20] = '\0';
		}
		ostr << "| ";
		ostr << setw(20) << setfill(' ') << left << name << "| ";
		ostr << setw(9) << setfill(' ') << right;
		ostr << fixed << setprecision(2) << cost();
		ostr << " |  " << (Taxed ? itemType() : ' ') << "  |" << endl;

		return ostr;
	}
}