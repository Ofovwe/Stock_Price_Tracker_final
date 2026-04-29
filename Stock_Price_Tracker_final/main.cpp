
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

    Dashboard Dashboard;
    Dashboard.run(myPortfolio);

    return 0;
}