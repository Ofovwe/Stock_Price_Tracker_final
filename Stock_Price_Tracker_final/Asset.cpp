#include "Asset.hpp"

void Asset::displayInfo()
{
	std::cout << "Asset Information:" << std::endl;
	std::cout << "Name of Asset: " << name << std::endl;
	std::cout << "Asset Symbol: " << tickerSymbol << std::endl;
	std::cout << "Current Asset Price: " << currentAssetPrice << std::endl;
	std::cout << "Price Purchased for: " << purchasePrice << std::endl;
	std::cout << "Number of shares owned: " << numShares << std::endl;
}
