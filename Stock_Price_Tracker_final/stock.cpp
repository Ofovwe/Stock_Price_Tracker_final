#include "Stock.hpp"

double Stock::calulate_divivdend_income()
{
	return numShares*dividendYield*currentAssetPrice;
}
