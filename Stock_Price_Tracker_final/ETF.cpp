#include "ETF.hpp"

using std::cout;
using std::endl;
using std::string;

// ETF.cpp
#include "ETF.hpp"

ETF::ETF(string newName,
    string newTickerSymbol,
    double newCurrentAssetPrice,
    double newPurchasePrice,
    int newNumShares,
    double newExpenseRatio,
    string newBenchmarkIndex)
    : Asset(newCurrentAssetPrice,
        newPurchasePrice,
        newName,
        newTickerSymbol,
        newNumShares)
{
    expenseRatio = newExpenseRatio;
    benchmarkIndex = newBenchmarkIndex;
}
ETF::ETF(std::ifstream& file)
{
    string line;
    getline(file, line);

    std::stringstream ss(line);
    string temp;

    getline(ss, name, ',');
    getline(ss, tickerSymbol, ',');

    getline(ss, temp, ',');
    currentAssetPrice = stod(temp);

    getline(ss, temp, ',');
    purchasePrice = stod(temp);

    getline(ss, temp, ',');
    quantity = stoi(temp);

    getline(ss, temp, ',');
    expenseRatio = stod(temp);

    getline(ss, benchmarkIndex, ',');
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