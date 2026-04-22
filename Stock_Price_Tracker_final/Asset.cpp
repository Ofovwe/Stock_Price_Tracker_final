#include "Asset.hpp"


double Asset::calculate_profit_and_loss()
{
	if (this->purchasePrice > this->currentAssetPrice)
	{
		return (this->purchasePrice - this->currentAssetPrice) * this->numShares;
	}
	else
	{
		return  -1 *this->numShares * (this->currentAssetPrice - this->purchasePrice);
	}
	
}
