#include "Asset.hpp"



Asset::Asset(double newAssetPrice, double newPurchasePrice, string newName, string newTicker, int newNumShares)
{
	currentAssetPrice = newAssetPrice;
	purchasePrice = newPurchasePrice;
	name = newName;
	tickerSymbol = newTicker;
	quantity = newNumShares;
}

Asset::~Asset()
{

}

double Asset::calculate_profit_and_loss()
{
	if (this->purchasePrice > this->currentAssetPrice)
	{
		return (this->purchasePrice - this->currentAssetPrice) * this->quantity;
	}
	else
	{
		return  -1 * this->quantity * (this->currentAssetPrice - this->purchasePrice);
	}
}
void Asset::displayInfo()
{
	std::cout << "Asset Information:" << std::endl;
	std::cout << "Name of Asset: " << name << std::endl;
	std::cout << "Asset Symbol: " << tickerSymbol << std::endl;
	std::cout << "Current Asset Price: " << currentAssetPrice << std::endl;
	std::cout << "Price Purchased for: " << purchasePrice << std::endl;
	std::cout << "Number of shares owned: " << quantity << std::endl;

}

double Asset::get_value()
{
	return this->currentAssetPrice* this->quantity;
}
