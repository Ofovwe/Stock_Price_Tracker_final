#pragma once
#pragma once
#include "Asset.hpp"

using std::string;

class Bond : public Asset
{
public:
    Bond(std::ifstream& file); 
       

    virtual ~Bond();

    double calculate_profit_and_loss() override;
    double get_value() override;
    void displayInfo() override;

private:
    double interestRate;   // coupon / annual yield %
    int yearsToMaturity;
};