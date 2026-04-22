#include "Asset.hpp"



double Asset::calculate_profit_and_loss()
{
	if (this->purchasePrice > this->currentAssetPrice)
	{
		return (this->purchasePrice - this->currentAssetPrice) * this->numShares;
	}
	else
	{
		return  -1 * this->numShares * (this->currentAssetPrice - this->purchasePrice);
	}
}
void Asset::displayInfo()
{
	std::cout << "Asset Information:" << std::endl;
	std::cout << "Name of Asset: " << name << std::endl;
	std::cout << "Asset Symbol: " << tickerSymbol << std::endl;
	std::cout << "Current Asset Price: " << currentAssetPrice << std::endl;
	std::cout << "Price Purchased for: " << purchasePrice << std::endl;
	std::cout << "Number of shares owned: " << numShares << std::endl;

}

double Asset::get_value()
{
	return this->currentAssetPrice* this->numShares;
}
