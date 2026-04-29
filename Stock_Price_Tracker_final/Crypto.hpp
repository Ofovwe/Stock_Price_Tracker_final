#pragma once
#pragma once
#include "Asset.hpp"

using std::string;

class Crypto : public Asset
{
public:
    Crypto(std::ifstream& file);
    Crypto(string newName = "",
        string newTickerSymbol = "",
        double newCurrentAssetPrice = 0.0,
        double newPurchasePrice = 0.0,
        int newNumShares = 0,
        double apy = 0,
        bool Staking=false);

    virtual ~Crypto();
   void saveToFile(std::ofstream& file);

    double calculate_profit_and_loss() override;
    double get_value() override;
    void displayInfo() override;

private:
    double apy;            // annual percentage yield
    bool stakingEnabled;  // true if staking rewards enabled
};