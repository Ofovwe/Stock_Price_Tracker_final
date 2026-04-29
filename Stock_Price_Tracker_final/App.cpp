#include "App.hpp"
#include <iostream>

App::App()
{}

void App::run()
{
    std::ifstream stockFile("Stock.csv");
    std::ifstream bondFile("Bond.csv");
    std::ifstream etfFile("ETF.csv");
    std::ifstream cryptoFile("Crypto.csv");

    portfolio.load_file(stockFile, bondFile, etfFile, cryptoFile);
    int choice = 0;
    

    do
    {
        displayMenu();
        std::cin >> choice;

        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid choice. Enter a number: ";
            std::cin >> choice;
        }

        handleChoice(choice);

    } while (choice != 14);
}

void App::displayMenu()
{
    std::cout << "\n===== Portfolio Tracker =====\n";
    std::cout << "1. View Full Portfolio\n";
    std::cout << "2. View Stocks\n";
    std::cout << "3. View ETFs\n";
    std::cout << "4. View Crypto\n";
    std::cout << "5. View Bonds\n";
    std::cout << "6. Add Stock\n";
    std::cout << "7. Add ETF\n";
    std::cout << "8. Add Crypto\n";
    std::cout << "9. Add Bond\n";
    std::cout << "10. Best Performing Asset\n";
    std::cout << "11. Worst Performing Asset\n";
    std::cout << "12. Remove an Asset\n";
    std::cout << "13. Save Portfolio\n";
    std::cout << "14. Exit\n";
    std::cout << "Enter choice: ";
}

void App::handleChoice(int choice)
{
    switch (choice)
    {
    case 1:
        portfolio.displayInfo();
        break;

    case 2:
        portfolio.viewStocks();
        break;

    case 3:
        portfolio.viewETFs();
        break;

    case 4:
        portfolio.viewCryptos();
        break;

    case 5:
        portfolio.viewBonds();
        break;

    case 6:
        portfolio.addStock();
        break;

    case 7:
        portfolio.addEtf();
        break;

    case 8:
        portfolio.addCrypto();
        break;

    case 9:
        portfolio.addBond();
        break;

    case 10:
        portfolio.best_performing_asset();
        break;

    case 11:
        portfolio.worst_performing_asset();
        break;

    case 12:
        portfolio.removeAsset();
        break;

    case 13:
        portfolio.saveToFile();
        break;

    case 14:
        portfolio.saveToFile();
        std::cout << "Portfolio saved. Exiting program.\n";
        break;

    default:
        std::cout << "Invalid choice.\n";
        break;
    }
}
