#include "Test.hpp"

#include <iostream>
#include <cmath>

bool nearlyEqual(double a, double b)
{
    return std::abs(a - b) < 0.01;
}

void Test::runTests()
{
    std::cout << "\n===== Running Application Tests =====\n";

    printResult("Test 1: Stock value calculation", testStockValue());
    printResult("Test 2: Stock profit/loss calculation", testStockProfitLoss());
    printResult("Test 3: Portfolio total value calculation", testPortfolioTotalValue());
    printResult("Test 4: Best performing asset", testBestPerformingAsset());
    printResult("Test 5: Worst performing asset", testWorstPerformingAsset());

    std::cout << "===== Tests Complete =====\n";
}

void Test::printResult(const std::string& testName, bool passed)
{
    if (passed)
    {
        std::cout << "[PASS] " << testName << "\n";
    }
    else
    {
        std::cout << "[FAIL] " << testName << "\n";
    }
}

bool Test::testStockValue()
{
    Stock stock("Apple", "AAPL", 200.0, 150.0, 10, "Technology", 0.50);

    double expectedValue = 200.0 * 10;

    return nearlyEqual(stock.get_value(), expectedValue);
}

bool Test::testStockProfitLoss()
{
    Stock stock("Apple", "AAPL", 200.0, 150.0, 10, "Technology", 0.50);

    double expectedProfit = (200.0 - 150.0) * 10;

    return nearlyEqual(stock.calculate_profit_and_loss(), expectedProfit);
}

bool Test::testPortfolioTotalValue()
{
    Stock stock("Apple", "AAPL", 200.0, 150.0, 10, "Technology", 0.50);
    ETF etf("Vanguard ETF", "VOO", 100.0, 80.0, 5, 0.03, "S&P 500");

    double total = stock.get_value() + etf.get_value();
    double expected = (200.0 * 10) + (100.0 * 5);

    return nearlyEqual(total, expected);
}

bool Test::testBestPerformingAsset()
{
    Stock stock1("Apple", "AAPL", 200.0, 100.0, 10, "Technology", 0.50);
    Stock stock2("Tesla", "TSLA", 150.0, 100.0, 10, "Auto", 0.00);

    Asset* best = &stock1;

    if (stock2.getPerformancePercent() > best->getPerformancePercent())
    {
        best = &stock2;
    }

    return best->get_ticker() == "AAPL";
}

bool Test::testWorstPerformingAsset()
{
    Stock stock1("Apple", "AAPL", 200.0, 100.0, 10, "Technology", 0.50);
    Stock stock2("Tesla", "TSLA", 80.0, 100.0, 10, "Auto", 0.00);

    Asset* worst = &stock1;

    if (stock2.getPerformancePercent() < worst->getPerformancePercent())
    {
        worst = &stock2;
    }

    return worst->get_ticker() == "TSLA";
}