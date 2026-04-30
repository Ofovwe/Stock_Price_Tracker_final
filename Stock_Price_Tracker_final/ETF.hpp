#pragma once
#include "Asset.hpp"
class ETF : public Asset
{
public:
    ETF(string newName = "",
        string newTickerSymbol = "",
        double newCurrentAssetPrice = 0.0,
        double newPurchasePrice = 0.0,
        int newNumShares = 0,
        double newExpenseRatio = 0.0,
        string newBenchmarkIndex = "");
        std::string getType() const override;
  

    ETF(std::ifstream& file);
    void saveToFile(std::ofstream& file);
    
    

    ~ETF();

    double calculate_profit_and_loss() override;
    double get_value() override;
    void displayInfo() override;

private:
    double expenseRatio;   
    string benchmarkIndex; 
};