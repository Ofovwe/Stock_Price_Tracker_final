#include "Dashboard.hpp"
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>


Dashboard::Dashboard(float width, float height)
    : mWindow(sf::VideoMode({ static_cast<unsigned int>(width),
        static_cast<unsigned int>(height) }),
        "Portfolio Dashboard"),
    mWidth(width),
    mHeight(height)
{
    if (!mFont.openFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load arial.ttf" << std::endl;
    }
}

void Dashboard::run(Portfolio& portfolio)
{
    while (mWindow.isOpen())
    {
        handleEvents();
        render(portfolio);
    }
}

void Dashboard::handleEvents()
{
    while (const std::optional event = mWindow.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            mWindow.close();
        }
    }
}

void Dashboard::render(Portfolio& portfolio)
{
    mWindow.clear(sf::Color(18, 18, 28));

    drawBackground();
    drawHeader(portfolio);
    drawAssetTable(portfolio);
    drawBarChart(portfolio);

    mWindow.display();
}

void Dashboard::drawText(const std::string& text,
    float x,
    float y,
    unsigned int size,
    sf::Color color)
{
    sf::Text drawableText(mFont, sf::String(text), size);

    drawableText.setPosition(sf::Vector2f(x, y));
    drawableText.setFillColor(color);

    mWindow.draw(drawableText);
}

void Dashboard::drawBackground()
{
    sf::RectangleShape headerPanel({ mWidth - 40.0f, 110.0f });
    headerPanel.setPosition({ 20.0f, 20.0f });
    headerPanel.setFillColor(sf::Color(35, 35, 50));
    mWindow.draw(headerPanel);

    sf::RectangleShape tablePanel({ 700.0f, mHeight - 180.0f });
    tablePanel.setPosition({ 20.0f, 150.0f });
    tablePanel.setFillColor(sf::Color(28, 28, 42));
    mWindow.draw(tablePanel);

    sf::RectangleShape chartPanel({ 420.0f, mHeight - 180.0f });
    chartPanel.setPosition({ 750.0f, 150.0f });
    chartPanel.setFillColor(sf::Color(28, 28, 42));
    mWindow.draw(chartPanel);
}

void Dashboard::drawHeader(Portfolio& portfolio)
{
    drawText("Portfolio Dashboard", 40.0f, 35.0f, 30, sf::Color::White);

    std::ostringstream totalStream;
    totalStream << std::fixed << std::setprecision(2)
        << "Total Value: $" << portfolio.calculate_total_value();

    drawText(totalStream.str(), 40.0f, 80.0f, 22, sf::Color(180, 255, 180));

    std::ostringstream profitStream;
    profitStream << std::fixed << std::setprecision(2)
        << "Total P/L: $" << portfolio.calculateProfit();

    sf::Color profitColor = (portfolio.calculateProfit() >= 0.0)
        ? sf::Color(120, 255, 120)
        : sf::Color(255, 120, 120);

    drawText(profitStream.str(), 340.0f, 80.0f, 22, profitColor);

    std::ostringstream countStream;
    countStream << "Assets: " << portfolio.getNumAssets();

    drawText(countStream.str(), 650.0f, 80.0f, 22, sf::Color::White);
}

void Dashboard::drawAssetTable(Portfolio& portfolio)
{
    drawText("Assets", 40.0f, 165.0f, 24, sf::Color::White);

    // Column headers (only using what your Asset class supports)
    drawText("Name", 40.0f, 205.0f, 18, sf::Color(200, 200, 255));
    drawText("Value", 280.0f, 205.0f, 18, sf::Color(200, 200, 255));
    drawText("Profit/Loss", 480.0f, 205.0f, 18, sf::Color(200, 200, 255));

    float y = 245.0f;

    const std::vector<Asset*>& assets = portfolio.getAssets();

    for (size_t i = 0; i < assets.size(); ++i)
    {
        Asset* pAsset = assets[i];

        // alternating row background
        sf::RectangleShape rowBg({ 660.0f, 32.0f });
        rowBg.setPosition({ 35.0f, y - 3.0f });

        if (i % 2 == 0)
        {
            rowBg.setFillColor(sf::Color(40, 40, 60));
        }
        else
        {
            rowBg.setFillColor(sf::Color(34, 34, 52));
        }

        mWindow.draw(rowBg);

        drawText(pAsset->get_name(), 40.0f, y, 16);

        std::ostringstream valueStream;
        valueStream << "$" << std::fixed << std::setprecision(2)
            << pAsset->get_value();
        drawText(valueStream.str(), 280.0f, y, 16, sf::Color(180, 255, 180));

        double profit = pAsset->calculate_profit_and_loss();

        std::ostringstream profitAssetStream;
        profitAssetStream << "$" << std::fixed << std::setprecision(2)
            << profit;

        sf::Color rowProfitColor = (profit >= 0.0)
            ? sf::Color(120, 255, 120)
            : sf::Color(255, 120, 120);

        drawText(profitAssetStream.str(), 480.0f, y, 16, rowProfitColor);

        y += 38.0f;

        if (y > mHeight - 50.0f)
        {
            break;
        }
    }
}

void Dashboard::drawBarChart(Portfolio& portfolio)
{
    drawText("Asset Values", 770.0f, 165.0f, 24, sf::Color::White);

    const std::vector<Asset*>& assets = portfolio.getAssets();

    if (assets.empty())
    {
        drawText("No assets to display.", 780.0f, 230.0f, 18, sf::Color(200, 200, 200));
        return;
    }

    double maxValue = 1.0;
    for (const auto& asset : assets)
    {
        if (asset->get_value() > maxValue)
        {
            maxValue = asset->get_value();
        }
    }

    const float chartLeft = 790.0f;
    const float chartBottom = 650.0f;
    const float maxBarHeight = 350.0f;
    const float barWidth = 50.0f;
    const float spacing = 25.0f;

    float x = chartLeft;

    for (size_t i = 0; i < assets.size(); ++i)
    {
        Asset* pAsset = assets[i];

        float barHeight = static_cast<float>((pAsset->get_value() / maxValue) * maxBarHeight);

        sf::RectangleShape bar({ barWidth, barHeight });
        bar.setPosition({ x, chartBottom - barHeight });

        // Simple color cycling since your base class doesn't expose type yet
        switch (i % 4)
        {
        case 0:
            bar.setFillColor(sf::Color(100, 180, 255));
            break;
        case 1:
            bar.setFillColor(sf::Color(255, 200, 100));
            break;
        case 2:
            bar.setFillColor(sf::Color(180, 100, 255));
            break;
        default:
            bar.setFillColor(sf::Color(120, 220, 150));
            break;
        }

        mWindow.draw(bar);

        drawText(pAsset->get_name(), x - 5.0f, chartBottom + 10.0f, 14, sf::Color::White);

        x += barWidth + spacing;

        if (x > mWidth - 80.0f)
        {
            break;
        }
    }

    // x-axis
    sf::RectangleShape axis({ 330.0f, 2.0f });
    axis.setPosition({ chartLeft - 10.0f, chartBottom });
    axis.setFillColor(sf::Color::White);
    mWindow.draw(axis);
}