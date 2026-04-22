#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

using std::cout;
using std::cin;
using std::string;

class Asset
{
public:
	
private:
	double currentStockPrice;
	double purchasePrice;
	string name;
	string tickerSymbol;
	int numShares;
};