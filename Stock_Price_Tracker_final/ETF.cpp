#include "ETF.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::string;

ETF::ETF(double newCurrentPrice,
    double newPurchasePrice,
    string newName,
    string newTicker,
    double newShares,
    double newExpenseRatio,
    string newIndex)
    : Asset(newCurrentPrice, newPurchasePrice, newName, newTicker, newShares)
{
    expenseRatio = newExpenseRatio;
    benchmarkIndex = newIndex;
}

ETF::~ETF()
{}

double ETF::calculate_profit_and_loss()
{
    return (currentAssetPrice - purchasePrice) * quantity;
}

double ETF::get_value()
{
    return currentAssetPrice * quantity;
}

void ETF::displayInfo()
{
    cout << "ETF Name: " << name << endl;
    cout << "Ticker: " << tickerSymbol << endl;
    cout << "Shares: " << quantity << endl;
    cout << "Current Price: $" << currentAssetPrice << endl;
    cout << "Purchase Price: $" << purchasePrice << endl;
    cout << "Benchmark Index: " << benchmarkIndex << endl;
    cout << "Expense Ratio: " << expenseRatio << "%" << endl;
    cout << "Current Value: $" << get_value() << endl;
    cout << "Profit/Loss: $" << calculate_profit_and_loss() << endl;
}