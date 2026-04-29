#pragma once

#include "Stock.hpp"
#include"Bond.hpp"
#include "Crypto.hpp"
#include"ETF.hpp"
#include <algorithm>


class Portfolio
{
public:
	Portfolio(int newNumAssets = 0);

	~Portfolio();

	int getNumAssets() const;

	const std::vector<Asset*>& getAssets() const;
	
	double calculateProfit();
	void displayInfo();
	double calculate_total_value();
	void removeAsset(string assetName);
	void load_file(std::ifstream& stock, std::ifstream& bond, std::ifstream& etf, std::ifstream& crypto);

	void sortByValue();
	void sortByProfit();
private:
	std::vector<Asset*> listOfAssets;
	int numAssets;
};