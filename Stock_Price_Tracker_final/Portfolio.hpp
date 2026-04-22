#pragma once

#include "Asset.hpp"

class Portfolio
{
public:
	double calculateProfit();
	void displayInfo();
private:
	std::vector<Asset> listOfAssets;
	int numAssets;
};