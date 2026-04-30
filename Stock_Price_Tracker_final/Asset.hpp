#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
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

	virtual string get_ticker() { return tickerSymbol; };

	virtual double getCurrentAssetPrice() { return currentAssetPrice; };

	virtual double getPurchasePrice() { return purchasePrice; };

	virtual double getPerformancePercent();
	virtual double getPortfolioPercentage(double totalPortfolioValue);

	virtual void setCurrentPrice(double newPrice) { currentAssetPrice = newPrice; };
	virtual void setQuantity(double newQuantity) { quantity = newQuantity; };
	virtual void setPurchasePrice(double newPurchasePrice) { purchasePrice = newPurchasePrice; };
	virtual string getType() const = 0;
	virtual double get_quantity();
	
protected:
	double currentAssetPrice;
	double purchasePrice;
	string name;
	
	
	string tickerSymbol;
	double quantity;
};