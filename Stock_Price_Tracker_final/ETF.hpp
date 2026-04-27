#pragma once
#include "Asset.hpp"
class ETF : public Asset
{
public:
    ETF(std::ifstream& file);

    ~ETF();

    double calculate_profit_and_loss() override;
    double get_value() override;
    void displayInfo() override;

private:
    double expenseRatio;   
    string benchmarkIndex; 
};