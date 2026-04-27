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
	return (currentAssetPrice - purchasePrice) * quantity;
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
