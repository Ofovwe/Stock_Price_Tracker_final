#pragma once
#include "Asset.hpp"
class Stock : public Asset
{
public:
	double calulate_divivdend_income();
	double calculate_profit_and_loss() override;
	void displayInfo() override;
private:
	double dividendYield;

};
