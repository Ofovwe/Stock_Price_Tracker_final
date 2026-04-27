#include "Portfolio.hpp"

Portfolio::Portfolio(int newNumAssets)
{
	numAssets = newNumAssets;
}

Portfolio::~Portfolio()
{
	
}

double Portfolio::calculateProfit()
{
	double totalProfit = 0.0;
	for (int i = 0; i < numAssets; i++)
	{
		totalProfit += listOfAssets[i].calculate_profit_and_loss();
	}
	return totalProfit;
}

void Portfolio::displayInfo()
{
	for (int i = 0; i < numAssets; i++)
	{
		std::cout << "Asset #" << i << std::endl;
		listOfAssets[i].displayInfo();
	}
}

void Portfolio::removeAsset(string assetName)
{
	for (int i = 0; i < numAssets; i++)
	{
		if (listOfAssets[i].get_name() == assetName)
		{
			numAssets--;
			listOfAssets.erase(listOfAssets.begin()+i);
			break;
		}
	}
}

void Portfolio::load_file(std::ifstream& stock,
    std::ifstream& bond,
    std::ifstream& etf,
    std::ifstream& crypto)
{
    string line;

    // skip headers
    getline(stock, line);
    getline(bond, line);
    getline(etf, line);
    getline(crypto, line);

    while (stock.peek() != EOF)
    {
        Stock newStock(stock);
        listOfAssets.push_back(newStock);
    }

    while (bond.peek() != EOF)
    {
        Bond newBond(bond);
        listOfAssets.push_back(newBond);
    }

    while (etf.peek() != EOF)
    {
        ETF newETF(etf);
        listOfAssets.push_back(newETF);
    }

    while (crypto.peek() != EOF)
    {
        Crypto newCrypto(crypto);
        listOfAssets.push_back(newCrypto);
    }
}
