#include "Bond.hpp"

using std::cout;
using std::endl;
using std::string;

Bond::Bond(double newCurrentPrice,
    double newPurchasePrice,
    string newName,
    string newTicker,
    double newShares,
    double newInterestRate,
    int newYearsToMaturity)
    : Asset(newCurrentPrice, newPurchasePrice, newName, newTicker, newShares)
{
    interestRate = newInterestRate;
    yearsToMaturity = newYearsToMaturity;
}

Bond::~Bond()
{}

double Bond::calculate_profit_and_loss()
{
    return (currentAssetPrice - purchasePrice) *quantity;
}

double Bond::get_value()
{
    return currentAssetPrice * quantity;
}

void Bond::displayInfo()
{
    cout << "Bond Name: " << name << endl;
    cout << "Ticker: " << tickerSymbol << endl;
    cout << "Units Owned: " << quantity << endl;
    cout << "Current Price: $" << currentAssetPrice << endl;
    cout << "Purchase Price: $" << purchasePrice << endl;
    cout << "Interest Rate: " << interestRate << "%" << endl;
    cout << "Years to Maturity: " << yearsToMaturity << endl;
    cout << "Current Value: $" << get_value() << endl;
    cout << "Profit/Loss: $" << calculate_profit_and_loss() << endl;
}