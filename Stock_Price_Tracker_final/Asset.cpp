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
	std::cout << "Assest Information:" << std::endl;
	std::cout << "Name of Assest: " << name << std::endl;
	std::cout << "Assest Symbol: " << tickerSymbol << std::endl;
	std::cout << "Current Asset Price: " << currentAssetPrice << std::endl;
	std::cout << "Price Purchased for: " << purchasePrice << std::endl;
	std::cout << "Number of shares owned: " << numShares << std::endl;

}
