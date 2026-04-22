#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include <vector>


using std::cout;
using std::cin;
using std::string;

class Asset
{
public:
	virtual double calculate_profit_and_loss(); /*Calculate the profit and loss of the asset*/
	virtual void displayInfo();

protected:
	double currentAssetPrice;
	double purchasePrice;
	string name;
	string tickerSymbol;
	int numShares;
};