#include "Portfolio.hpp"

Portfolio::Portfolio(int newNumAssets)
{
	numAssets = newNumAssets;
}

Portfolio::~Portfolio()
{
	
}

int Portfolio::getNumAssets() const
{
    return numAssets;
}

const std::vector<Asset*>& Portfolio::getAssets() const
{
    return listOfAssets;
}

double Portfolio::calculateProfit()
{
	double totalProfit = 0.0;
	for (int i = 0; i < numAssets; i++)
	{
		totalProfit += listOfAssets[i]->calculate_profit_and_loss();
	}
	return totalProfit;
}

void Portfolio::displayInfo()
{
	for (int i = 0; i < numAssets; i++)
	{
		std::cout << "Asset #" << i << std::endl;
		listOfAssets[i]->displayInfo();
	}
}

double Portfolio::calculate_total_value()
{

    double total = 0.0;

    for (int i = 0; i < listOfAssets.size(); i++)
    {
        total += listOfAssets[i]->get_value();
    }

    return total;
}

void Portfolio::removeAsset(string assetName)
{
	for (int i = 0; i < numAssets; i++)
	{
		if (listOfAssets[i]->get_name() == assetName)
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
    string header;

    getline(stock, header);
    while (stock.peek() != EOF)
    {
        listOfAssets.push_back(new Stock(stock));
         numAssets++;
    }

    getline(bond, header);
    while (bond.peek() != EOF)
    {
        listOfAssets.push_back(new Bond(bond));
        numAssets++;
    }

    getline(etf, header);
    while (etf.peek() != EOF)
    {
        listOfAssets.push_back(new ETF(etf));
        numAssets++;
    }

    getline(crypto, header);
    while (crypto.peek() != EOF)
    {
        listOfAssets.push_back(new Crypto(crypto));
        numAssets++;
    }

}
