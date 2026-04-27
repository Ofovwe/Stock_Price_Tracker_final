#pragma once
#pragma once
#include "Asset.hpp"

using std::string;

class Bond : public Asset
{
public:
    Bond(std::ifstream& file); 
    Bond(string newName = "",
        string newTickerSymbol = "",
        double newCurrentAssetPrice = 0.0,
        double newPurchasePrice = 0.0,
        int newNumShares = 0,
        double newInterestRate = 0.0,
        int newYearsToMaturity = 0);
       

    virtual ~Bond();

    double calculate_profit_and_loss() override;
    double get_value() override;
    void displayInfo() override;

private:
    double interestRate;   // coupon / annual yield %
    int yearsToMaturity;
};