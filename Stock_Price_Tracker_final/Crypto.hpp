#pragma once
#pragma once
#include "Asset.hpp"

using std::string;

class Crypto : public Asset
{
public:
    Crypto(double newCurrentPrice = 0.0,
        double newPurchasePrice = 0.0,
        string newName = "",
        string newTicker = "",
        double newShares = 0,
        double newApy = 0.0,
        bool newStaking = false);

    virtual ~Crypto();

    double calculate_profit_and_loss() override;
    double get_value() override;
    void displayInfo() override;

private:
    double apy;            // annual percentage yield
    bool stakingEnabled;  // true if staking rewards enabled
};