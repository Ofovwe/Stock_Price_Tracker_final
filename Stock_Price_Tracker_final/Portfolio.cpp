#include "Portfolio.hpp"

Portfolio::Portfolio(int newNumAssets)
{
	numAssets = newNumAssets;
}

Portfolio::~Portfolio()
{
	
}

double Portfolio::calculateProfit()
{
	double totalProfit = 0.0;
	for (int i = 0; i < numAssets; i++)
	{
		totalProfit += listOfAssets[i]->calculate_profit_and_loss();
	}
	return totalProfit;
}

void Portfolio::displayInfo()
{
	for (int i = 0; i < numAssets; i++)
	{
		std::cout << "Asset #" << i << std::endl;
		listOfAssets[i]->displayInfo();
	}
}

double Portfolio::calculate_total_value()
{

    double total = 0.0;

    for (int i = 0; i < listOfAssets.size(); i++)
    {
        total += listOfAssets[i]->get_value();
    }

    return total;
}

void Portfolio::addStock()
{
    if (numAssets >= 100)
    {
        cout << "Portfolio is full.\n";
        return;
    }

    string name;
    string tickerSymbol;
    string sector;

    double currentAssetPrice;
    double purchasePrice;
    double dividendYield;

    int numShares;

    // Name
    do
    {
        cout << "Enter company name: ";
        cin >> std::ws;
        getline(cin, name);

        if (name.empty())
        {
            cout << "Name cannot be empty.\n";
        }

    } while (name.empty());

    // Ticker
    do
    {
        cout << "Enter ticker symbol: ";
        cin >> tickerSymbol;

        if (tickerSymbol.length() < 1 || tickerSymbol.length() > 5)
        {
            cout << "Ticker must be 1 to 5 characters.\n";
        }

    } while (tickerSymbol.length() < 1 || tickerSymbol.length() > 5);

    // Current Price
    do
    {
        cout << "Enter current stock price: ";
        cin >> currentAssetPrice;

        if (cin.fail() || currentAssetPrice < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid price.\n";
            currentAssetPrice = -1;
        }

    } while (currentAssetPrice < 0);

    // Purchase Price
    do
    {
        cout << "Enter purchase price: ";
        cin >> purchasePrice;

        if (cin.fail() || purchasePrice < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid price.\n";
            purchasePrice = -1;
        }

    } while (purchasePrice < 0);

    // Shares
    do
    {
        cout << "Enter number of shares: ";
        cin >> numShares;

        if (cin.fail() || numShares <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Shares must be greater than 0.\n";
            numShares = -1;
        }

    } while (numShares <= 0);

    // Sector
    do
    {
        cout << "Enter sector: ";
        getline(cin >> std::ws, sector);

        if (sector.empty())
        {
            cout << "Sector cannot be empty.\n";
        }

    } while (sector.empty());

    // Dividend Yield
    do
    {
        cout << "Enter dividend yield (%): ";
        cin >> dividendYield;

        if (cin.fail() || dividendYield < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid dividend yield.\n";
            dividendYield = -1;
        }

    } while (dividendYield < 0);

    listOfAssets[numAssets] =
        new Stock(name, tickerSymbol, currentAssetPrice,
            purchasePrice, numShares, sector, dividendYield);

    numAssets++;

    cout << "Stock added successfully.\n";
}

void Portfolio::addEtf()
{
    if (numAssets >= 100)
    {
        cout << "Portfolio is full.\n";
        return;
    }

    string name;
    string tickerSymbol;
    string benchmarkIndex;

    double currentAssetPrice;
    double purchasePrice;
    double expenseRatio;

    int numShares;

    // Name
    do
    {
        cout << "Enter ETF name: ";
        cin >> std::ws;
        getline(cin, name);

        if (name.empty())
        {
            cout << "Name cannot be empty.\n";
        }

    } while (name.empty());

    // Ticker Symbol
    do
    {
        cout << "Enter ticker symbol: ";
        cin >> tickerSymbol;

        if (tickerSymbol.length() < 1 || tickerSymbol.length() > 5)
        {
            cout << "Ticker must be 1 to 5 characters.\n";
        }

    } while (tickerSymbol.length() < 1 || tickerSymbol.length() > 5);

    // Current Price
    do
    {
        cout << "Enter current ETF price: ";
        cin >> currentAssetPrice;

        if (cin.fail() || currentAssetPrice < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            currentAssetPrice = -1;
            cout << "Invalid price.\n";
        }

    } while (currentAssetPrice < 0);

    // Purchase Price
    do
    {
        cout << "Enter purchase price: ";
        cin >> purchasePrice;

        if (cin.fail() || purchasePrice < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            purchasePrice = -1;
            cout << "Invalid price.\n";
        }

    } while (purchasePrice < 0);

    // Shares
    do
    {
        cout << "Enter number of shares: ";
        cin >> numShares;

        if (cin.fail() || numShares <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            numShares = -1;
            cout << "Shares must be greater than 0.\n";
        }

    } while (numShares <= 0);

    // Expense Ratio
    do
    {
        cout << "Enter expense ratio (%): ";
        cin >> expenseRatio;

        if (cin.fail() || expenseRatio < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            expenseRatio = -1;
            cout << "Invalid expense ratio.\n";
        }

    } while (expenseRatio < 0);

    // Benchmark Index
    do
    {
        cout << "Enter benchmark index: ";
        cin >> std::ws;
        getline(cin, benchmarkIndex);

        if (benchmarkIndex.empty())
        {
            cout << "Benchmark index cannot be empty.\n";
        }

    } while (benchmarkIndex.empty());

    listOfAssets[numAssets] =
        new ETF(name,
            tickerSymbol,
            currentAssetPrice,
            purchasePrice,
            numShares,
            expenseRatio,
            benchmarkIndex);

    numAssets++;

    cout << "ETF added successfully.\n";
}

void Portfolio::addBond()
{
    if (numAssets >= 100)
    {
        cout << "Portfolio is full.\n";
        return;
    }

    string name;
    string tickerSymbol;

    double currentAssetPrice;
    double purchasePrice;
    double interestRate;

    int numShares;
    int yearsToMaturity;

    // Name
    do
    {
        cout << "Enter bond name: ";
        cin >> std::ws;
        getline(cin, name);

        if (name.empty())
        {
            cout << "Name cannot be empty.\n";
        }

    } while (name.empty());

    // Ticker Symbol
    do
    {
        cout << "Enter ticker symbol: ";
        cin >> tickerSymbol;

        if (tickerSymbol.length() < 1 || tickerSymbol.length() > 6)
        {
            cout << "Ticker must be 1 to 6 characters.\n";
        }

    } while (tickerSymbol.length() < 1 || tickerSymbol.length() > 6);

    // Current Price
    do
    {
        cout << "Enter current bond price: ";
        cin >> currentAssetPrice;

        if (cin.fail() || currentAssetPrice < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            currentAssetPrice = -1;
            cout << "Invalid price.\n";
        }

    } while (currentAssetPrice < 0);

    // Purchase Price
    do
    {
        cout << "Enter purchase price: ";
        cin >> purchasePrice;

        if (cin.fail() || purchasePrice < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            purchasePrice = -1;
            cout << "Invalid price.\n";
        }

    } while (purchasePrice < 0);

    // Number Owned
    do
    {
        cout << "Enter number of bonds: ";
        cin >> numShares;

        if (cin.fail() || numShares <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            numShares = -1;
            cout << "Amount must be greater than 0.\n";
        }

    } while (numShares <= 0);

    // Interest Rate
    do
    {
        cout << "Enter interest rate (%): ";
        cin >> interestRate;

        if (cin.fail() || interestRate < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            interestRate = -1;
            cout << "Invalid interest rate.\n";
        }

    } while (interestRate < 0);

    // Years to Maturity
    do
    {
        cout << "Enter years to maturity: ";
        cin >> yearsToMaturity;

        if (cin.fail() || yearsToMaturity < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            yearsToMaturity = -1;
            cout << "Invalid years.\n";
        }

    } while (yearsToMaturity < 0);

    listOfAssets[numAssets] =
        new Bond(name,
            tickerSymbol,
            currentAssetPrice,
            purchasePrice,
            numShares,
            interestRate,
            yearsToMaturity);

    numAssets++;

    cout << "Bond added successfully.\n";
}

void Portfolio::best_performing_asset()
{
    if (numAssets == 0)
    {
        cout << "No assets in portfolio.\n";
        return;
    }

    int bestIndex = 0;
    double bestProfit =
        listOfAssets[0]->calculate_profit_and_loss();

    for (int i = 1; i < numAssets; i++)
    {
        double currentProfit =
            listOfAssets[i]->calculate_profit_and_loss();

        if (currentProfit > bestProfit)
        {
            bestProfit = currentProfit;
            bestIndex = i;
        }
    }

    cout << "Best Performing Asset:\n";
    listOfAssets[bestIndex]->displayInfo();

    cout << "Profit/Loss: $"
        << bestProfit << std::endl;
}

void Portfolio::worst_performing_asset()
{
    if (numAssets == 0)
    {
        cout << "No assets in portfolio.\n";
        return;
    }

    int worstIndex = 0;
    double worstProfit =
        listOfAssets[0]->calculate_profit_and_loss();

    for (int i = 1; i < numAssets; i++)
    {
        double currentProfit =
            listOfAssets[i]->calculate_profit_and_loss();

        if (currentProfit < worstProfit)
        {
            worstProfit = currentProfit;
            worstIndex = i;
        }
    }

    cout << "Worst Performing Asset:\n";
    listOfAssets[worstIndex]->displayInfo();

    cout << "Profit/Loss: $"
        << worstProfit << std::endl;
}

void Portfolio::addCrypto()
{
    if (numAssets >= 100)
    {
        cout << "Portfolio is full.\n";
        return;
    }

    string name;
    string tickerSymbol;

    double currentAssetPrice;
    double purchasePrice;
    double apy;

    int numShares;
    bool stakingEnabled;

    // Name
    do
    {
        cout << "Enter crypto name: ";
        cin >> std::ws;
        getline(cin, name);

        if (name.empty())
        {
            cout << "Name cannot be empty.\n";
        }

    } while (name.empty());

    // Ticker
    do
    {
        cout << "Enter ticker symbol: ";
        cin >> tickerSymbol;

        if (tickerSymbol.length() < 1 || tickerSymbol.length() > 6)
        {
            cout << "Ticker must be 1 to 6 characters.\n";
        }

    } while (tickerSymbol.length() < 1 || tickerSymbol.length() > 6);

    // Current Price
    do
    {
        cout << "Enter current crypto price: ";
        cin >> currentAssetPrice;

        if (cin.fail() || currentAssetPrice < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            currentAssetPrice = -1;
            cout << "Invalid price.\n";
        }

    } while (currentAssetPrice < 0);

    // Purchase Price
    do
    {
        cout << "Enter purchase price: ";
        cin >> purchasePrice;

        if (cin.fail() || purchasePrice < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            purchasePrice = -1;
            cout << "Invalid price.\n";
        }

    } while (purchasePrice < 0);

    // Units
    do
    {
        cout << "Enter amount owned: ";
        cin >> numShares;

        if (cin.fail() || numShares <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            numShares = -1;
            cout << "Amount must be greater than 0.\n";
        }

    } while (numShares <= 0);

    // APY
    do
    {
        cout << "Enter APY (%): ";
        cin >> apy;

        if (cin.fail() || apy < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            apy = -1;
            cout << "Invalid APY.\n";
        }

    } while (apy < 0);

    // Staking Enabled
    int choice;

    do
    {
        cout << "Enable staking? (1 = Yes, 0 = No): ";
        cin >> choice;

        if (cin.fail() || (choice != 0 && choice != 1))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
            cout << "Enter 1 or 0 only.\n";
        }

    } while (choice != 0 && choice != 1);

    stakingEnabled = choice;

    listOfAssets[numAssets] =
        new Crypto(name,
            tickerSymbol,
            currentAssetPrice,
            purchasePrice,
            numShares,
            apy,
            stakingEnabled);

    numAssets++;

    cout << "Crypto added successfully.\n";
}

void Portfolio::removeAsset(string assetName)
{
	for (int i = 0; i < numAssets; i++)
	{
		if (listOfAssets[i]->get_name() == assetName)
		{
			numAssets--;
			listOfAssets.erase(listOfAssets.begin()+i);
			break;
		}
	}
}
void Portfolio::load_file(std::ifstream& stock,
    std::ifstream& bond,
    std::ifstream& etf,
    std::ifstream& crypto)
{
    string header;

    getline(stock, header);
    while (stock.peek() != EOF)
    {
        listOfAssets.push_back(new Stock(stock));
         numAssets++;
    }

    getline(bond, header);
    while (bond.peek() != EOF)
    {
        listOfAssets.push_back(new Bond(bond));
        numAssets++;
    }

    getline(etf, header);
    while (etf.peek() != EOF)
    {
        listOfAssets.push_back(new ETF(etf));
        numAssets++;
    }

    getline(crypto, header);
    while (crypto.peek() != EOF)
    {
        listOfAssets.push_back(new Crypto(crypto));
        numAssets++;
    }

}
