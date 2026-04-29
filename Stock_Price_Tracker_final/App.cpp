#include "App.hpp"
#include <iostream>
#include <fstream>

App::App()
    : mWindow(sf::VideoMode({ 1000, 700 }), "Stock Portfolio Tracker"),
    mDashboard(),
    mStatusMessage("Welcome! Load your portfolio to begin.")
{
    if (!mFont.openFromFile("C:/Windows/Fonts/segoeui.ttf"))
    {
        std::cerr << "Failed to load menu font.\n";
    }

    initializeButtons();
}

App::~App()
{}

double Asset::getPerformancePercent()
{
    if (purchasePrice == 0.0)
    {
        return 0.0;  // avoid divide-by-zero
    }

    return ((currentAssetPrice - purchasePrice) / purchasePrice) * 100.0;
}

double Asset::getPortfolioPercentage(double totalPortfolioValue)
{
    if (totalPortfolioValue == 0.0)
    {
        return 0.0;  // avoid divide-by-zero
    }

    return (get_value() / totalPortfolioValue) * 100.0;
}

void App::initializeButtons()
{
    mLoadButton.setSize({ 280.0f, 55.0f });
    mLoadButton.setPosition({ 80.0f, 150.0f });
    mLoadButton.setFillColor(sf::Color(70, 110, 180));

    mDashboardButton.setSize({ 280.0f, 55.0f });
    mDashboardButton.setPosition({ 80.0f, 230.0f });
    mDashboardButton.setFillColor(sf::Color(90, 140, 100));

    mSortValueButton.setSize({ 280.0f, 55.0f });
    mSortValueButton.setPosition({ 80.0f, 310.0f });
    mSortValueButton.setFillColor(sf::Color(120, 90, 180));

    mSortProfitButton.setSize({ 280.0f, 55.0f });
    mSortProfitButton.setPosition({ 80.0f, 390.0f });
    mSortProfitButton.setFillColor(sf::Color(180, 140, 70));

    mSummaryButton.setSize({ 280.0f, 55.0f });
    mSummaryButton.setPosition({ 80.0f, 470.0f });
    mSummaryButton.setFillColor(sf::Color(80, 150, 150));

    mExitButton.setSize({ 280.0f, 55.0f });
    mExitButton.setPosition({ 80.0f, 550.0f });
    mExitButton.setFillColor(sf::Color(180, 80, 80));
}

bool App::isMouseOverButton(const sf::RectangleShape& button, float mouseX, float mouseY)
{
    sf::Vector2f pos = button.getPosition();
    sf::Vector2f size = button.getSize();

    return (mouseX >= pos.x && mouseX <= pos.x + size.x &&
        mouseY >= pos.y && mouseY <= pos.y + size.y);
}

void App::run()
{
    while (mWindow.isOpen())
    {
        handleEvents();
        render();
    }
}

void App::handleEvents()
{
    while (const std::optional event = mWindow.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            mWindow.close();
        }

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button == sf::Mouse::Button::Left)
            {
                float mouseX = static_cast<float>(mousePressed->position.x);
                float mouseY = static_cast<float>(mousePressed->position.y);

                if (isMouseOverButton(mLoadButton, mouseX, mouseY))
                {
                    loadPortfolioFiles();
                }
                else if (isMouseOverButton(mDashboardButton, mouseX, mouseY))
                {
                    if (mPortfolio.getNumAssets() == 0)
                    {
                        mStatusMessage = "Load portfolio files before opening dashboard.";
                    }
                    else
                    {
                        mDashboard.run(mPortfolio);
                        mStatusMessage = "Returned from dashboard.";
                    }
                }
                else if (isMouseOverButton(mSortValueButton, mouseX, mouseY))
                {
                    if (mPortfolio.getNumAssets() == 0)
                    {
                        mStatusMessage = "No assets loaded to sort.";
                    }
                    else
                    {
                        mPortfolio.sortByValue();
                        mStatusMessage = "Portfolio sorted by value.";
                    }
                }
                else if (isMouseOverButton(mSortProfitButton, mouseX, mouseY))
                {
                    if (mPortfolio.getNumAssets() == 0)
                    {
                        mStatusMessage = "No assets loaded to sort.";
                    }
                    else
                    {
                        mPortfolio.sortByProfit();
                        mStatusMessage = "Portfolio sorted by profit/loss.";
                    }
                }
                else if (isMouseOverButton(mSummaryButton, mouseX, mouseY))
                {
                    showSummary();
                }
                else if (isMouseOverButton(mExitButton, mouseX, mouseY))
                {
                    mWindow.close();
                }
            }
        }
    }
}

void App::render()
{
    mWindow.clear(sf::Color(18, 18, 28));

    // Title panel
    sf::RectangleShape titlePanel({ 920.0f, 90.0f });
    titlePanel.setPosition({ 40.0f, 30.0f });
    titlePanel.setFillColor(sf::Color(35, 35, 50));
    mWindow.draw(titlePanel);

    // Right info panel
    sf::RectangleShape infoPanel({ 520.0f, 520.0f });
    infoPanel.setPosition({ 420.0f, 150.0f });
    infoPanel.setFillColor(sf::Color(28, 28, 42));
    mWindow.draw(infoPanel);

    drawText("Stock Portfolio Tracker", 70.0f, 55.0f, 32, sf::Color::White);
    drawText("Graphical Main Menu", 500.0f, 60.0f, 22, sf::Color(200, 200, 255));

    // Draw buttons
    drawButton(mLoadButton, "Load Portfolio", 140.0f, 165.0f);
    drawButton(mDashboardButton, "Open Dashboard", 135.0f, 245.0f);
    drawButton(mSortValueButton, "Sort by Value", 145.0f, 325.0f);
    drawButton(mSortProfitButton, "Sort by Profit", 140.0f, 405.0f);
    drawButton(mSummaryButton, "Show Summary", 145.0f, 485.0f);
    drawButton(mExitButton, "Exit", 195.0f, 565.0f);

    // Right panel info
    drawText("Application Status", 450.0f, 180.0f, 28, sf::Color::White);

    drawText("Assets Loaded: " + std::to_string(mPortfolio.getNumAssets()),
        450.0f, 240.0f, 22, sf::Color(200, 200, 255));

    std::ostringstream valueStream;
    valueStream << std::fixed << std::setprecision(2)
        << "Total Value: $" << mPortfolio.calculate_total_value();

    drawText(valueStream.str(), 450.0f, 290.0f, 22, sf::Color(180, 255, 180));

    double totalProfit = mPortfolio.calculateProfit();

    std::ostringstream profitStream;
    profitStream << std::fixed << std::setprecision(2)
        << "Total Profit/Loss: $" << totalProfit;

    sf::Color profitColor = (totalProfit >= 0.0)
        ? sf::Color(120, 255, 120)
        : sf::Color(255, 120, 120);

    drawText(profitStream.str(), 450.0f, 340.0f, 22, profitColor);

    drawText("Status Message:", 450.0f, 420.0f, 22, sf::Color::White);
    drawText(mStatusMessage, 450.0f, 460.0f, 18, sf::Color(220, 220, 220));

    drawText("Tip: Load files first, then open the dashboard.",
        450.0f, 600.0f, 16, sf::Color(180, 180, 220));

    mWindow.display();
}

void App::drawButton(const sf::RectangleShape& button, const string& label, float textX, float textY)
{
    mWindow.draw(button);
    drawText(label, textX, textY, 18, sf::Color::White);
}

void App::drawText(const string& text, float x, float y, unsigned int size, sf::Color color)
{
    sf::Text drawableText(mFont, sf::String(text), size);
    drawableText.setPosition(sf::Vector2f(x, y));
    drawableText.setFillColor(color);

    mWindow.draw(drawableText);
}

void App::loadPortfolioFiles()
{
    std::cout << "Working directory: " << std::filesystem::current_path() << std::endl;

    std::ifstream stockFile("Stock.csv");
    std::ifstream bondFile("Bond.csv");
    std::ifstream etfFile("ETF.csv");
    std::ifstream cryptoFile("Crypto.csv");

    if (!stockFile.is_open()) std::cout << "Failed to open stocks.csv\n";
    if (!bondFile.is_open()) std::cout << "Failed to open bonds.csv\n";
    if (!etfFile.is_open()) std::cout << "Failed to open etfs.csv\n";
    if (!cryptoFile.is_open()) std::cout << "Failed to open crypto.csv\n";

    if (!stockFile.is_open() || !bondFile.is_open() || !etfFile.is_open() || !cryptoFile.is_open())
    {
        mStatusMessage = "Error: Could not open one or more portfolio CSV files.";
        return;
    }

    mPortfolio.load_file(stockFile, bondFile, etfFile, cryptoFile);

    stockFile.close();
    bondFile.close();
    etfFile.close();
    cryptoFile.close();

    mStatusMessage = "Portfolio CSV files loaded successfully!";
}

void App::showSummary()
{
    if (mPortfolio.getNumAssets() == 0)
    {
        mStatusMessage = "No assets loaded yet.";
        return;
    }

    std::ostringstream summary;
    summary << "Assets: " << mPortfolio.getNumAssets()
        << " | Value: $" << std::fixed << std::setprecision(2) << mPortfolio.calculate_total_value()
        << " | P/L: $" << std::fixed << std::setprecision(2) << mPortfolio.calculateProfit();

    mStatusMessage = summary.str();
}
