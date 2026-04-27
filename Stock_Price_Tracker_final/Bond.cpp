#include "Bond.hpp"

using std::cout;
using std::endl;
using std::string;

Bond::Bond(std::ifstream& file)
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
    interestRate = stod(temp);

    getline(ss, temp, ',');
    yearsToMaturity = stoi(temp);
}

Bond::~Bond()
{}

double Bond::calculate_profit_and_loss()
{
    return (currentAssetPrice - purchasePrice) * quantity;
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