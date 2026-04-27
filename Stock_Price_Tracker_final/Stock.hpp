#pragma once
#include "Asset.hpp"
class Stock : public Asset
{
public:
    Stock(std::ifstream& file);

    virtual ~Stock();

    double calculate_profit_and_loss() override;
    double get_value() override;
    void displayInfo() override;

private:
    string sector;
    double dividendYield;
};
