#pragma once

#include "Stock.hpp"
#include"Bond.hpp"
#include "Crypto.hpp"
#include"ETF.hpp"


class Portfolio
{
public:
	Portfolio(int newNumAssets = 0);

	~Portfolio();
	
	double calculateProfit();
	void displayInfo();
	double calculate_total_value();
	void addStock();
	void addCrypto();
	void addEtf();
	void addBond();
	void best_performing_asset();
	void worst_performing_asset();
	void removeAsset(string assetName);
	void load_file(std::ifstream& stock, std::ifstream& bond, std::ifstream& etf, std::ifstream& crypto);

private:
	std::vector<Asset*> listOfAssets;
	int numAssets;
};