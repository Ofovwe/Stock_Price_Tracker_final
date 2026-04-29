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

	int getNumAssets() const;

	const std::vector<Asset*>& getAssets() const;
	
	double calculateProfit();
	void viewStocks();
	void viewETFs();
	void viewCryptos();
	void viewBonds();
	void displayInfo();
	double calculate_total_value();
	void addStock();
	void addCrypto();
	void addEtf();
	void addBond();
	void best_performing_asset();
	void worst_performing_asset();
	void  saveToFile();
	void removeAsset();
	void load_file(std::ifstream& stock, std::ifstream& bond, std::ifstream& etf, std::ifstream& crypto);

private:
	std::vector<Asset*> listOfAssets;
	int numAssets;
};