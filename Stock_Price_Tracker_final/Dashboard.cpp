#include "Dashboard.hpp"

#include <iostream>
#include <optional>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

Dashboard::Dashboard(float width, float height)
    : mWidth(width),
    mHeight(height),
    mSelectedIndex(0),
    mScrollOffset(0)
{
    if (!mFont.openFromFile("C:/Windows/Fonts/segoeui.ttf"))
    {
        std::cerr << "Failed to load font.\n";
    }
}

void Dashboard::run(Portfolio& portfolio)
{
    // Recreate window every time dashboard is opened
    mWindow.create(
        sf::VideoMode({ static_cast<unsigned int>(mWidth),
                        static_cast<unsigned int>(mHeight) }),
        "Interactive Portfolio Dashboard"
    );

    mSelectedIndex = 0;
    mScrollOffset = 0;

    while (mWindow.isOpen())
    {
        handleEvents(portfolio);
        render(portfolio);
    }
}

void Dashboard::handleEvents(Portfolio& portfolio)
{
    const int visibleRows = 10;

    while (const std::optional event = mWindow.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            mWindow.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            const std::vector<Asset*>& assets = portfolio.getAssets();

            if (!assets.empty())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                {
                    if (mSelectedIndex < static_cast<int>(assets.size()) - 1)
                    {
                        mSelectedIndex++;

                        if (mSelectedIndex >= mScrollOffset + visibleRows)
                        {
                            mScrollOffset++;
                        }
                    }
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                {
                    if (mSelectedIndex > 0)
                    {
                        mSelectedIndex--;

                        if (mSelectedIndex < mScrollOffset)
                        {
                            mScrollOffset--;
                        }
                    }
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::P)
                {
                    editSelectedPrice(portfolio);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Q)
                {
                    editSelectedQuantity(portfolio);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::B)
                {
                    editSelectedPurchasePrice(portfolio);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
                {
                    portfolio.saveToFile();
                    std::cout << "Portfolio saved.\n";
                }
            }

            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                mWindow.close();
            }
        }

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button == sf::Mouse::Button::Left)
            {
                float mouseX = static_cast<float>(mousePressed->position.x);
                float mouseY = static_cast<float>(mousePressed->position.y);

                float startY = 245.0f;
                float rowHeight = 38.0f;

                const std::vector<Asset*>& assets = portfolio.getAssets();

                for (int visibleIndex = 0; visibleIndex < visibleRows; ++visibleIndex)
                {
                    int actualIndex = mScrollOffset + visibleIndex;

                    if (actualIndex >= static_cast<int>(assets.size()))
                    {
                        break;
                    }

                    float rowTop = startY + static_cast<float>(visibleIndex) * rowHeight;
                    float rowBottom = rowTop + 32.0f;

                    if (mouseX >= 35.0f && mouseX <= 695.0f &&
                        mouseY >= rowTop - 3.0f && mouseY <= rowBottom)
                    {
                        mSelectedIndex = actualIndex;
                        break;
                    }
                }
            }
        }
    }

    // Keep selection + scroll valid
    const std::vector<Asset*>& assets = portfolio.getAssets();

    if (assets.empty())
    {
        mSelectedIndex = 0;
        mScrollOffset = 0;
    }
    else
    {
        if (mSelectedIndex >= static_cast<int>(assets.size()))
        {
            mSelectedIndex = static_cast<int>(assets.size()) - 1;
        }

        if (mScrollOffset > static_cast<int>(assets.size()) - visibleRows)
        {
            mScrollOffset = static_cast<int>(assets.size()) - visibleRows;
        }

        if (mScrollOffset < 0)
        {
            mScrollOffset = 0;
        }

        if (mSelectedIndex < mScrollOffset)
        {
            mScrollOffset = mSelectedIndex;
        }
        else if (mSelectedIndex >= mScrollOffset + visibleRows)
        {
            mScrollOffset = mSelectedIndex - visibleRows + 1;
        }
    }
}

void Dashboard::render(Portfolio& portfolio)
{
    mWindow.clear(sf::Color(18, 18, 28));

    drawBackground();
    drawHeader(portfolio);
    drawAssetTable(portfolio);
    drawSelectedAssetPanel(portfolio);
    drawDonutChart(portfolio);

    mWindow.display();
}

void Dashboard::drawBackground()
{
    sf::RectangleShape headerPanel({ mWidth - 40.0f, 110.0f });
    headerPanel.setPosition({ 20.0f, 20.0f });
    headerPanel.setFillColor(sf::Color(35, 35, 50));
    mWindow.draw(headerPanel);

    sf::RectangleShape tablePanel({ 700.0f, 500.0f });
    tablePanel.setPosition({ 20.0f, 150.0f });
    tablePanel.setFillColor(sf::Color(28, 28, 42));
    mWindow.draw(tablePanel);

    sf::RectangleShape detailsPanel({ 620.0f, 220.0f });
    detailsPanel.setPosition({ 750.0f, 150.0f });
    detailsPanel.setFillColor(sf::Color(28, 28, 42));
    mWindow.draw(detailsPanel);

    sf::RectangleShape chartPanel({ 620.0f, 360.0f });
    chartPanel.setPosition({ 750.0f, 400.0f });
    chartPanel.setFillColor(sf::Color(28, 28, 42));
    mWindow.draw(chartPanel);
}

void Dashboard::drawHeader(Portfolio& portfolio)
{
    drawText("Interactive Portfolio Dashboard", 40.0f, 35.0f, 30, sf::Color::White);

    std::ostringstream totalStream;
    totalStream << std::fixed << std::setprecision(2)
        << "Total Value: $" << portfolio.calculate_total_value();
    drawText(totalStream.str(), 40.0f, 80.0f, 22, sf::Color(180, 255, 180));

    double totalProfit = portfolio.calculateProfit();

    std::ostringstream profitStream;
    profitStream << std::fixed << std::setprecision(2)
        << "Total P/L: $" << totalProfit;

    sf::Color profitColor = totalProfit >= 0.0
        ? sf::Color(120, 255, 120)
        : sf::Color(255, 120, 120);

    drawText(profitStream.str(), 360.0f, 80.0f, 22, profitColor);

    std::ostringstream countStream;
    countStream << "Assets: " << portfolio.getNumAssets();
    drawText(countStream.str(), 700.0f, 80.0f, 22, sf::Color::White);

    drawText("UP/DOWN Select | P Edit Price | Q Edit Qty | B Edit Buy Price | S Save | ESC Exit",
        850.0f, 80.0f, 15, sf::Color(200, 200, 255));
}

void Dashboard::drawAssetTable(Portfolio& portfolio)
{
    drawText("Assets", 40.0f, 165.0f, 24, sf::Color::White);

    drawText("Name", 40.0f, 205.0f, 18, sf::Color(200, 200, 255));
    drawText("Value", 280.0f, 205.0f, 18, sf::Color(200, 200, 255));
    drawText("Profit/Loss", 480.0f, 205.0f, 18, sf::Color(200, 200, 255));

    float y = 245.0f;
    const int visibleRows = 10;

    const std::vector<Asset*>& assets = portfolio.getAssets();

    for (int visibleIndex = 0; visibleIndex < visibleRows; ++visibleIndex)
    {
        int actualIndex = mScrollOffset + visibleIndex;

        if (actualIndex >= static_cast<int>(assets.size()))
        {
            break;
        }

        Asset* pAsset = assets[actualIndex];

        sf::RectangleShape rowBg({ 660.0f, 32.0f });
        rowBg.setPosition({ 35.0f, y - 3.0f });

        if (actualIndex == mSelectedIndex)
        {
            rowBg.setFillColor(sf::Color(70, 100, 170));
        }
        else if (actualIndex % 2 == 0)
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

        std::ostringstream profitStream;
        profitStream << "$" << std::fixed << std::setprecision(2)
            << profit;

        sf::Color rowProfitColor = profit >= 0.0
            ? sf::Color(120, 255, 120)
            : sf::Color(255, 120, 120);

        drawText(profitStream.str(), 480.0f, y, 16, rowProfitColor);

        y += 38.0f;
    }

    if (!assets.empty())
    {
        std::ostringstream scrollInfo;
        scrollInfo << "Showing " << (mScrollOffset + 1)
            << " - " << std::min(mScrollOffset + visibleRows, static_cast<int>(assets.size()))
            << " of " << assets.size();

        drawText(scrollInfo.str(), 40.0f, 630.0f, 14, sf::Color(180, 180, 220));
    }
}

void Dashboard::drawSelectedAssetPanel(Portfolio& portfolio)
{
    drawText("Selected Asset", 770.0f, 165.0f, 24, sf::Color::White);

    const std::vector<Asset*>& assets = portfolio.getAssets();

    if (assets.empty())
    {
        drawText("No assets loaded.", 780.0f, 220.0f, 18, sf::Color(200, 200, 200));
        return;
    }

    Asset* selected = assets[mSelectedIndex];

    double totalValue = portfolio.calculate_total_value();

    drawText("Name: " + selected->get_name(), 780.0f, 210.0f, 18, sf::Color::White);
    drawText("Ticker: " + selected->get_ticker(), 780.0f, 240.0f, 18, sf::Color::White);

    std::ostringstream quantityStream;
    quantityStream << std::fixed << std::setprecision(4)
        << "Quantity: " << selected->get_value();
    drawText(quantityStream.str(), 780.0f, 270.0f, 18, sf::Color::White);

    std::ostringstream priceStream;
    priceStream << std::fixed << std::setprecision(2)
        << "Current Price: $" << selected->getCurrentAssetPrice();
    drawText(priceStream.str(), 780.0f, 300.0f, 18, sf::Color::White);

    std::ostringstream purchaseStream;
    purchaseStream << std::fixed << std::setprecision(2)
        << "Purchase Price: $" << selected->getPurchasePrice();
    drawText(purchaseStream.str(), 780.0f, 330.0f, 18, sf::Color::White);

    std::ostringstream valueStream;
    valueStream << std::fixed << std::setprecision(2)
        << "Value: $" << selected->get_value();
    drawText(valueStream.str(), 1050.0f, 210.0f, 18, sf::Color(180, 255, 180));

    double profit = selected->calculate_profit_and_loss();

    std::ostringstream profitStream;
    profitStream << std::fixed << std::setprecision(2)
        << "P/L: $" << profit;

    sf::Color profitColor = profit >= 0.0
        ? sf::Color(120, 255, 120)
        : sf::Color(255, 120, 120);

    drawText(profitStream.str(), 1050.0f, 240.0f, 18, profitColor);

    std::ostringstream performanceStream;
    performanceStream << std::fixed << std::setprecision(2)
        << "Performance: " << selected->getPerformancePercent() << "%";
    drawText(performanceStream.str(), 1050.0f, 270.0f, 18, profitColor);

    std::ostringstream percentStream;
    percentStream << std::fixed << std::setprecision(2)
        << "Portfolio %: " << selected->getPortfolioPercentage(totalValue) << "%";
    drawText(percentStream.str(), 1050.0f, 300.0f, 18, sf::Color(200, 200, 255));
}

void Dashboard::drawDonutChart(Portfolio& portfolio)
{
    drawText("Portfolio Allocation", 770.0f, 415.0f, 24, sf::Color::White);

    const std::vector<Asset*>& assets = portfolio.getAssets();

    if (assets.empty())
    {
        drawText("No assets to display.", 780.0f, 470.0f, 18, sf::Color(200, 200, 200));
        return;
    }

    double totalValue = portfolio.calculate_total_value();

    if (totalValue <= 0)
    {
        drawText("Portfolio value is zero.", 780.0f, 470.0f, 18, sf::Color(200, 200, 200));
        return;
    }

    sf::Vector2i mousePixel = sf::Mouse::getPosition(mWindow);
    sf::Vector2f mousePos = mWindow.mapPixelToCoords(mousePixel);

    int hoveredIndex = getHoveredChartIndex(portfolio, mousePos);

    const float centerX = 1060.0f;
    const float centerY = 575.0f;
    const float radius = 125.0f;
    const float hoverRadius = 145.0f;
    const float innerRadius = 65.0f;

    float startAngle = -90.0f;

    for (size_t i = 0; i < assets.size(); ++i)
    {
        double percentage = assets[i]->getPortfolioPercentage(totalValue);
        float sweepAngle = static_cast<float>((percentage / 100.0) * 360.0f);

        float currentRadius = radius;

        if (static_cast<int>(i) == hoveredIndex)
        {
            currentRadius = hoverRadius;
        }

        sf::ConvexShape slice;
        int pointCount = 40;
        slice.setPointCount(pointCount + 2);

        slice.setPoint(0, sf::Vector2f(centerX, centerY));

        for (int p = 0; p <= pointCount; ++p)
        {
            float angle = startAngle + (sweepAngle * p / pointCount);
            float radians = angle * 3.14159265f / 180.0f;

            float x = centerX + std::cos(radians) * currentRadius;
            float y = centerY + std::sin(radians) * currentRadius;

            slice.setPoint(p + 1, sf::Vector2f(x, y));
        }

        slice.setFillColor(getChartColor(static_cast<int>(i)));
        mWindow.draw(slice);

        startAngle += sweepAngle;
    }

    // Inner circle
    sf::CircleShape innerCircle(innerRadius);
    innerCircle.setOrigin(sf::Vector2f(innerRadius, innerRadius));
    innerCircle.setPosition(sf::Vector2f(centerX, centerY));
    innerCircle.setFillColor(sf::Color(28, 28, 42));
    mWindow.draw(innerCircle);

    std::ostringstream totalStream;
    totalStream << "$" << std::fixed << std::setprecision(2) << totalValue;

    // Create centered total value text
    sf::Text totalValueText(mFont, sf::String(totalStream.str()), 20);
    totalValueText.setFillColor(sf::Color::White);

    // Use local bounds to center text properly
    sf::FloatRect totalBounds = totalValueText.getLocalBounds();
    totalValueText.setPosition(sf::Vector2f(
        centerX - (totalBounds.size.x / 2.0f),
        centerY - 18.0f
    ));

    mWindow.draw(totalValueText);

    // Create centered label text
    sf::Text labelText(mFont, sf::String("Total Value"), 14);
    labelText.setFillColor(sf::Color(200, 200, 200));

    sf::FloatRect labelBounds = labelText.getLocalBounds();
    labelText.setPosition(sf::Vector2f(
        centerX - (labelBounds.size.x / 2.0f),
        centerY + 12.0f
    ));

    mWindow.draw(labelText);

    if (hoveredIndex != -1)
    {
        Asset* hovered = assets[hoveredIndex];

        double hoveredPercent = hovered->getPortfolioPercentage(totalValue);

        std::ostringstream percentStream;
        percentStream << std::fixed << std::setprecision(2)
            << hoveredPercent << "% of portfolio";

        std::ostringstream priceStream;
        priceStream << "$" << std::fixed << std::setprecision(2)
            << hovered->getCurrentAssetPrice() << " per share";

        drawText(hovered->get_name(), 790.0f, 690.0f, 18, sf::Color::White);
        drawText(priceStream.str(), 790.0f, 720.0f, 16, sf::Color(180, 255, 180));
        drawText(percentStream.str(), 790.0f, 745.0f, 16, sf::Color(200, 200, 255));
    }
    else
    {
        drawText("Hover over a slice for details", 790.0f, 705.0f, 16, sf::Color(200, 200, 200));
    }
}

int Dashboard::getHoveredChartIndex(Portfolio& portfolio, sf::Vector2f mousePos)
{
    const std::vector<Asset*>& assets = portfolio.getAssets();

    double totalValue = portfolio.calculate_total_value();

    if (assets.empty() || totalValue <= 0)
    {
        return -1;
    }

    const float centerX = 1060.0f;
    const float centerY = 575.0f;
    const float radius = 145.0f;
    const float innerRadius = 65.0f;

    float dx = mousePos.x - centerX;
    float dy = mousePos.y - centerY;

    float distance = std::sqrt((dx * dx) + (dy * dy));

    if (distance < innerRadius || distance > radius)
    {
        return -1;
    }

    float angle = std::atan2(dy, dx) * 180.0f / 3.14159265f;
    angle += 90.0f;

    if (angle < 0)
    {
        angle += 360.0f;
    }

    float currentAngle = 0.0f;

    for (size_t i = 0; i < assets.size(); ++i)
    {
        double percentage = assets[i]->getPortfolioPercentage(totalValue);
        float sweepAngle = static_cast<float>((percentage / 100.0) * 360.0f);

        if (angle >= currentAngle && angle <= currentAngle + sweepAngle)
        {
            return static_cast<int>(i);
        }

        currentAngle += sweepAngle;
    }

    return -1;
}

sf::Color Dashboard::getChartColor(int index)
{
    switch (index % 8)
    {
    case 0: return sf::Color(110, 90, 255);
    case 1: return sf::Color(55, 210, 190);
    case 2: return sf::Color(255, 140, 80);
    case 3: return sf::Color(120, 220, 120);
    case 4: return sf::Color(255, 90, 140);
    case 5: return sf::Color(90, 180, 255);
    case 6: return sf::Color(230, 210, 90);
    default: return sf::Color(190, 120, 255);
    }
}

void Dashboard::editSelectedPrice(Portfolio& portfolio)
{
    const std::vector<Asset*>& assets = portfolio.getAssets();

    if (assets.empty())
    {
        return;
    }

    double newPrice;

    std::cout << "\nEnter new current price for "
        << assets[mSelectedIndex]->get_name() << ": ";

    std::cin >> newPrice;

    if (!std::cin.fail() && newPrice >= 0)
    {
        assets[mSelectedIndex]->setCurrentPrice(newPrice);
        std::cout << "Current price updated.\n";
    }
    else
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid price.\n";
    }
}

void Dashboard::editSelectedQuantity(Portfolio& portfolio)
{
    const std::vector<Asset*>& assets = portfolio.getAssets();

    if (assets.empty())
    {
        return;
    }

    double newQuantity;

    std::cout << "\nEnter new quantity for "
        << assets[mSelectedIndex]->get_name() << ": ";

    std::cin >> newQuantity;

    if (!std::cin.fail() && newQuantity >= 0)
    {
        assets[mSelectedIndex]->setQuantity(newQuantity);
        std::cout << "Quantity updated.\n";
    }
    else
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid quantity.\n";
    }
}

void Dashboard::editSelectedPurchasePrice(Portfolio& portfolio)
{
    const std::vector<Asset*>& assets = portfolio.getAssets();

    if (assets.empty())
    {
        return;
    }

    double newPurchasePrice;

    std::cout << "\nEnter new purchase price for "
        << assets[mSelectedIndex]->get_name() << ": ";

    std::cin >> newPurchasePrice;

    if (!std::cin.fail() && newPurchasePrice >= 0)
    {
        assets[mSelectedIndex]->setPurchasePrice(newPurchasePrice);
        std::cout << "Purchase price updated.\n";
    }
    else
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid purchase price.\n";
    }
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