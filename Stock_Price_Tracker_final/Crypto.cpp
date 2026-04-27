#include "Crypto.hpp"

using std::cout;
using std::endl;
using std::string;

Crypto::Crypto(double newCurrentPrice,
    double newPurchasePrice,
    string newName,
    string newTicker,
    double newShares,
    double newApy,
    bool newStaking)
    : Asset(newCurrentPrice, newPurchasePrice, newName, newTicker, newShares)
{
    apy = newApy;
    stakingEnabled = newStaking;
}

Crypto::~Crypto()
{}

double Crypto::calculate_profit_and_loss()
{
    return (currentAssetPrice - purchasePrice) * quantity;
}

double Crypto::get_value()
{
    return currentAssetPrice * quantity;
}

void Crypto::displayInfo()
{
    cout << "Crypto Name: " << name << endl;
    cout << "Ticker: " << tickerSymbol << endl;
    cout << "Coins Owned: " << quantity << endl;
    cout << "Current Price: $" << currentAssetPrice << endl;
    cout << "Purchase Price: $" << purchasePrice << endl;
    if (stakingEnabled)
    {
        cout << "Staking: Enabled" << endl;
        cout << "APY: " << apy << "%" << endl;
    }
    else
    {
        cout << "Staking: Disabled" << endl;
    }

    cout << "Current Value: $" << get_value() << endl;
    cout << "Profit/Loss: $" << calculate_profit_and_loss() << endl;
}