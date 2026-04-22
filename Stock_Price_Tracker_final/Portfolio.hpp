#pragma once

#include "Asset.hpp"

class Portfolio
{
public:
	Portfolio(int newNumAssets = 0);

	~Portfolio();
	
	double calculateProfit();
	void displayInfo();
private:
	std::vector<Asset> listOfAssets;
	int numAssets;
};