#include "Asset.hpp"

void Asset::displayInfo()
{
	std::cout << "Stock Information:" << std::endl;
	std::cout << "Name of Stock: " << name << std::endl;
	std::cout << "Stock Symbol: " << tickerSymbol << std::endl;
	std::cout << "Current Stock Price: " << currentStockPrice << std::endl;
	std::cout << "Price Purchased for: " << purchasePrice << std::endl;
	std::cout << "Number of shares owned: " << numShares << std::endl;
}
