#include "Portfolio.hpp"

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
