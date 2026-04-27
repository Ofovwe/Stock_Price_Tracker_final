#include "Crypto.hpp"

using std::cout;
using std::endl;
using std::string;

#include <sstream>

Crypto::Crypto(std::ifstream& file)
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
    quantity = stod(temp);

    getline(ss, temp, ',');
    apy = stod(temp);

    getline(ss, temp, ',');

    if (temp == "true")
        stakingEnabled = true;
    else
        stakingEnabled = false;
}

Crypto::Crypto(string newName,
    string newTickerSymbol,
    double newCurrentAssetPrice,
    double newPurchasePrice,
    int newNumShares,
    double apy ,
    bool Staking)
    : Asset(newCurrentAssetPrice,
        newPurchasePrice,
        newName,
        newTickerSymbol,
        newNumShares)
{
    this->apy = apy;
    this->stakingEnabled = Staking;
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