#pragma once
#include "Asset.hpp"
class Stock : public Asset
{
public:
    Stock(string newName = "",
        string newTickerSymbol = "",
        double newCurrentAssetPrice = 0.0,
        double newPurchasePrice = 0.0,
        int newNumShares = 0,
        string newSector = "",
        double newDividendYield = 0.0);

    Stock(std::ifstream& file);
    void saveToFile(std::ofstream& file);

    virtual ~Stock();

    double calculate_profit_and_loss() override;
    double get_value() override;
    void displayInfo() override;

private:
    string sector;
    double dividendYield;
};
