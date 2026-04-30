
#pragma once

#include "Portfolio.hpp"
#include "Stock.hpp"
#include "ETF.hpp"
#include "Crypto.hpp"
#include "Bond.hpp"

class Test
{
public:
    void runTests();

private:
    bool testStockValue();
    bool testStockProfitLoss();
    bool testPortfolioTotalValue();
    bool testBestPerformingAsset();
    bool testWorstPerformingAsset();

    void printResult(const std::string& testName, bool passed);
};