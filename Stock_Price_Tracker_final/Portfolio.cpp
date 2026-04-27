#include "Portfolio.hpp"

Portfolio::Portfolio(int newNumAssets)
{
	numAssets = newNumAssets;
}

Portfolio::~Portfolio()
{}

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
