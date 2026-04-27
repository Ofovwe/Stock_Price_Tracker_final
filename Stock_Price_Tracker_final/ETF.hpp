#pragma once
#include "Asset.hpp"
class ETF : public Asset
{
public:
    ETF(double newCurrentPrice = 0.0,
        double newPurchasePrice = 0.0,
        string newName = "",
        string newTicker = "",
        double newShares = 0,
        double newExpenseRatio = 0.0,
        string newIndex = "");

    ~ETF();

    double calculate_profit_and_loss() override;
    double get_value() override;
    void displayInfo() override;

private:
    double expenseRatio;   
    string benchmarkIndex; 
};