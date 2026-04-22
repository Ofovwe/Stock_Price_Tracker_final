#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <forward_list>

using std::cout;
using std::cin;
using std::string;

class Asset
{
public:
	virtual void displayInfo();
private:
	double currentStockPrice;
	double purchasePrice;
	string name;
	string tickerSymbol;
	int numShares;
};