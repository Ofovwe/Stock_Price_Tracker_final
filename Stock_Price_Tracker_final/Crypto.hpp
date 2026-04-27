#pragma once
#pragma once
#include "Asset.hpp"

using std::string;

class Crypto : public Asset
{
public:
    Crypto(std::ifstream& file);

    virtual ~Crypto();

    double calculate_profit_and_loss() override;
    double get_value() override;
    void displayInfo() override;

private:
    double apy;            // annual percentage yield
    bool stakingEnabled;  // true if staking rewards enabled
};