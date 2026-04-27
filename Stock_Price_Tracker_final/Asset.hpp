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
	Asset(double newAssetPrice = 0.0, double newPurchasePrice = 0.0, string newName = "", string newTicker = "", int newNumShares = 0);

	virtual ~Asset();

	virtual double calculate_profit_and_loss(); /*Calculate the profit and loss of the asset*/
	virtual void displayInfo();
	virtual double get_value();
	virtual string get_name() { return name; };

	
protected:
	double currentAssetPrice;
	double purchasePrice;
	string name;
	string tickerSymbol;
	double quantity;
};