#include "Stock.hpp"
using std::cout;
using std::endl;
using std::string;


Stock::Stock(string newName,
    string newTickerSymbol,
    double newCurrentAssetPrice,
    double newPurchasePrice,
    int newNumShares,
    string newSector,
    double newDividendYield)
    : Asset(newCurrentAssetPrice,
        newPurchasePrice,
        newName,
        newTickerSymbol,
        newNumShares)
{
    sector = newSector;
    dividendYield = newDividendYield;
}

Stock::Stock(std::ifstream& file)
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

    getline(ss, sector, ',');

    getline(ss, temp, ',');
    dividendYield = stod(temp);
}

Stock::~Stock()
{}

double Stock::calculate_profit_and_loss()
{
    return (currentAssetPrice - purchasePrice) * quantity;
}

double Stock::get_value()
{
    return currentAssetPrice *quantity;
}

void Stock::displayInfo()
{
    cout << "Stock Name: " << name << endl;
    cout << "Ticker: " << tickerSymbol << endl;
    cout << "Shares: " << quantity << endl;
    cout << "Current Price: $" << currentAssetPrice << endl;
    cout << "Purchase Price: $" << purchasePrice << endl;
    cout << "Sector: " << sector << endl;
    cout << "Dividend Yield: " << dividendYield << "%" << endl;
    cout << "Current Value: $" << get_value() << endl;
    cout << "Profit/Loss: $" << calculate_profit_and_loss() << endl;
}
string Stock::getType() const
{
    return "Stock";
}
void Stock::saveToFile(std::ofstream& file)
{
    file << name << ","
        << tickerSymbol << ","
        << currentAssetPrice << ","
        << purchasePrice << ","
        << quantity<< ","
        << sector << ","
        << dividendYield << "\n";
}
