#include "App.hpp"

#include "Portfolio.hpp"
#include "Dashboard.hpp"

int main()
{
    std::ifstream stockFile("Stock.csv");
    std::ifstream bondFile("Bond.csv");
    std::ifstream etfFile("ETF.csv");
    std::ifstream cryptoFile("Crypto.csv");

    Portfolio myPortfolio;

    myPortfolio.load_file(stockFile, bondFile, etfFile, cryptoFile);

    myPortfolio.displayInfo();

    std::cout << "Total Portfolio Value: $"
        << myPortfolio.calculate_total_value() << std::endl;
   

    std::cout << "Total Profit/Loss: $"
        << myPortfolio.calculateProfit() << std::endl;

    return 0;
}