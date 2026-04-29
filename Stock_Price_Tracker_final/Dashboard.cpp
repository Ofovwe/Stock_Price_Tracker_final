#include "Dashboard.hpp"
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

Dashboard::Dashboard(float width, float height)
    : mWindow(sf::VideoMode({ static_cast<unsigned int>(width),
                              static_cast<unsigned int>(height) }),
        "Interactive Portfolio Dashboard"),
    mWidth(width),
    mHeight(height),
    mSelectedIndex(0)
{
    if (!mFont.openFromFile("C:/Windows/Fonts/segoeui.ttf"))
    {
        std::cerr << "Failed to load font.\n";
    }

    initializeButtons();
}

void Dashboard::initializeButtons()
{
    mSortValueButton.setSize({ 160.0f, 40.0f });
    mSortValueButton.setPosition({ 40.0f, 115.0f });
    mSortValueButton.setFillColor(sf::Color(70, 110, 180));

    mSortProfitButton.setSize({ 160.0f, 40.0f });
    mSortProfitButton.setPosition({ 220.0f, 115.0f });
    mSortProfitButton.setFillColor(sf::Color(90, 140, 100));

    mRemoveButton.setSize({ 180.0f, 40.0f });
    mRemoveButton.setPosition({ 400.0f, 115.0f });
    mRemoveButton.setFillColor(sf::Color(180, 80, 80));

    mResetButton.setSize({ 160.0f, 40.0f });
    mResetButton.setPosition({ 600.0f, 115.0f });
    mResetButton.setFillColor(sf::Color(120, 120, 120));
}

bool Dashboard::isMouseOverButton(const sf::RectangleShape& button, float mouseX, float mouseY)
{
    sf::Vector2f pos = button.getPosition();
    sf::Vector2f size = button.getSize();

    return (mouseX >= pos.x && mouseX <= pos.x + size.x &&
        mouseY >= pos.y && mouseY <= pos.y + size.y);
}

void Dashboard::run(Portfolio& portfolio)
{
    while (mWindow.isOpen())
    {
        handleEvents(portfolio);
        render(portfolio);
    }
}

void Dashboard::handleEvents(Portfolio& portfolio)
{
    while (const std::optional event = mWindow.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            mWindow.close();
        }

        // Keyboard navigation
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            std::vector<Asset*> assets = portfolio.getAssets();

            if (!assets.empty())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                {
                    if (mSelectedIndex < static_cast<int>(assets.size()) - 1)
                    {
                        mSelectedIndex++;
                    }
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                {
                    if (mSelectedIndex > 0)
                    {
                        mSelectedIndex--;
                    }
                }
            }
        }

        // Mouse clicks
        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button == sf::Mouse::Button::Left)
            {
                float mouseX = static_cast<float>(mousePressed->position.x);
                float mouseY = static_cast<float>(mousePressed->position.y);

                // -------- BUTTON CLICKS --------
                if (isMouseOverButton(mSortValueButton, mouseX, mouseY))
                {
                    portfolio.sortByValue();
                    mSelectedIndex = 0;
                }
                else if (isMouseOverButton(mSortProfitButton, mouseX, mouseY))
                {
                    portfolio.sortByProfit();
                    mSelectedIndex = 0;
                }
                else if (isMouseOverButton(mRemoveButton, mouseX, mouseY))
                {
                    std::vector<Asset*> assets = portfolio.getAssets();

                    if (!assets.empty() && mSelectedIndex >= 0 &&
                        mSelectedIndex < static_cast<int>(assets.size()))
                    {
                        string selectedName = assets[mSelectedIndex]->get_name();
                        portfolio.removeAsset(selectedName);

                        std::vector<Asset*> updatedAssets = portfolio.getAssets();

                        if (updatedAssets.empty())
                        {
                            mSelectedIndex = 0;
                        }
                        else if (mSelectedIndex >= static_cast<int>(updatedAssets.size()))
                        {
                            mSelectedIndex = static_cast<int>(updatedAssets.size()) - 1;
                        }
                    }
                }
                else if (isMouseOverButton(mResetButton, mouseX, mouseY))
                {
                    mSelectedIndex = 0;
                }
                else
                {
                    // -------- TABLE ROW CLICK --------
                    float startY = 290.0f;
                    float rowHeight = 38.0f;

                    std::vector<Asset*> assets = portfolio.getAssets();

                    for (size_t i = 0; i < assets.size(); ++i)
                    {
                        float rowTop = startY + static_cast<float>(i) * rowHeight;
                        float rowBottom = rowTop + 32.0f;

                        if (mouseX >= 35.0f && mouseX <= 695.0f &&
                            mouseY >= rowTop - 3.0f && mouseY <= rowBottom)
                        {
                            mSelectedIndex = static_cast<int>(i);
                            break;
                        }
                    }
                }
            }
        }
    }

    // Safety: keep selection valid
    std::vector<Asset*> assets = portfolio.getAssets();

    if (assets.empty())
    {
        mSelectedIndex = 0;
    }
    else if (mSelectedIndex >= static_cast<int>(assets.size()))
    {
        mSelectedIndex = static_cast<int>(assets.size()) - 1;
    }
}

void Dashboard::render(Portfolio& portfolio)
{
    mWindow.clear(sf::Color(18, 18, 28));

    drawBackground();
    drawHeader(portfolio);
    drawButtons();
    drawAssetTable(portfolio);
    drawSelectedAssetPanel(portfolio);
    drawBarChart(portfolio);

    mWindow.display();
}

void Dashboard::drawBackground()
{
    // Header panel
    sf::RectangleShape headerPanel({ mWidth - 40.0f, 80.0f });
    headerPanel.setPosition({ 20.0f, 20.0f });
    headerPanel.setFillColor(sf::Color(35, 35, 50));
    mWindow.draw(headerPanel);

    // Table panel
    sf::RectangleShape tablePanel({ 700.0f, 560.0f });
    tablePanel.setPosition({ 20.0f, 180.0f });
    tablePanel.setFillColor(sf::Color(28, 28, 42));
    mWindow.draw(tablePanel);

    // Selected asset panel
    sf::RectangleShape detailsPanel({ 650.0f, 230.0f });
    detailsPanel.setPosition({ 760.0f, 180.0f });
    detailsPanel.setFillColor(sf::Color(28, 28, 42));
    mWindow.draw(detailsPanel);

    // Chart panel
    sf::RectangleShape chartPanel({ 650.0f, 330.0f });
    chartPanel.setPosition({ 760.0f, 430.0f });
    chartPanel.setFillColor(sf::Color(28, 28, 42));
    mWindow.draw(chartPanel);
}

void Dashboard::drawHeader(Portfolio& portfolio)
{
    drawText("Interactive Portfolio Dashboard", 40.0f, 35.0f, 28, sf::Color::White);

    std::ostringstream totalStream;
    totalStream << std::fixed << std::setprecision(2)
        << "Total Value: $" << portfolio.calculate_total_value();
    drawText(totalStream.str(), 420.0f, 35.0f, 20, sf::Color(180, 255, 180));

    double totalProfit = portfolio.calculateProfit();

    std::ostringstream profitStream;
    profitStream << std::fixed << std::setprecision(2)
        << "Total P/L: $" << totalProfit;

    sf::Color profitColor = (totalProfit >= 0.0)
        ? sf::Color(120, 255, 120)
        : sf::Color(255, 120, 120);

    drawText(profitStream.str(), 720.0f, 35.0f, 20, profitColor);

    std::ostringstream countStream;
    countStream << "Assets: " << portfolio.getNumAssets();
    drawText(countStream.str(), 1040.0f, 35.0f, 20, sf::Color::White);

    drawText("Click rows or buttons | Use UP/DOWN arrows", 420.0f, 65.0f, 16, sf::Color(200, 200, 255));
}

void Dashboard::drawButtons()
{
    mWindow.draw(mSortValueButton);
    mWindow.draw(mSortProfitButton);
    mWindow.draw(mRemoveButton);
    mWindow.draw(mResetButton);

    drawText("Sort by Value", 58.0f, 123.0f, 16, sf::Color::White);
    drawText("Sort by Profit", 238.0f, 123.0f, 16, sf::Color::White);
    drawText("Remove Selected", 425.0f, 123.0f, 16, sf::Color::White);
    drawText("Reset Select", 625.0f, 123.0f, 16, sf::Color::White);
}

void Dashboard::drawAssetTable(Portfolio& portfolio)
{
    drawText("Assets", 40.0f, 195.0f, 24, sf::Color::White);

    drawText("Name", 40.0f, 245.0f, 18, sf::Color(200, 200, 255));
    drawText("Value", 280.0f, 245.0f, 18, sf::Color(200, 200, 255));
    drawText("Profit/Loss", 480.0f, 245.0f, 18, sf::Color(200, 200, 255));

    float y = 290.0f;

    std::vector<Asset*> assets = portfolio.getAssets();

    for (size_t i = 0; i < assets.size(); ++i)
    {
        Asset* pAsset = assets[i];

        sf::RectangleShape rowBg({ 660.0f, 32.0f });
        rowBg.setPosition({ 35.0f, y - 3.0f });

        if (static_cast<int>(i) == mSelectedIndex)
        {
            rowBg.setFillColor(sf::Color(70, 100, 170));
        }
        else if (i % 2 == 0)
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

        sf::Color rowProfitColor = (profit >= 0.0)
            ? sf::Color(120, 255, 120)
            : sf::Color(255, 120, 120);

        drawText(profitStream.str(), 480.0f, y, 16, rowProfitColor);

        y += 38.0f;

        if (y > 700.0f)
        {
            break;
        }
    }
}

void Dashboard::drawSelectedAssetPanel(Portfolio& portfolio)
{
    drawText("Selected Asset Details", 780.0f, 195.0f, 24, sf::Color::White);

    std::vector<Asset*> assets = portfolio.getAssets();

    if (assets.empty())
    {
        drawText("No assets loaded.", 790.0f, 250.0f, 18, sf::Color(200, 200, 200));
        return;
    }

    Asset* selected = assets[mSelectedIndex];

    drawText("Name: " + selected->get_name(), 790.0f, 255.0f, 20, sf::Color::White);

    std::ostringstream valueStream;
    valueStream << std::fixed << std::setprecision(2)
        << "Value: $" << selected->get_value();
    drawText(valueStream.str(), 790.0f, 300.0f, 20, sf::Color(180, 255, 180));

    double profit = selected->calculate_profit_and_loss();

    std::ostringstream profitStream;
    profitStream << std::fixed << std::setprecision(2)
        << "Profit / Loss: $" << profit;

    sf::Color profitColor = (profit >= 0.0)
        ? sf::Color(120, 255, 120)
        : sf::Color(255, 120, 120);

    drawText(profitStream.str(), 790.0f, 345.0f, 20, profitColor);
}

void Dashboard::drawBarChart(Portfolio& portfolio)
{
    drawText("Asset Value Chart", 780.0f, 445.0f, 24, sf::Color::White);

    std::vector<Asset*> assets = portfolio.getAssets();

    if (assets.empty())
    {
        drawText("No assets to display.", 790.0f, 500.0f, 18, sf::Color(200, 200, 200));
        return;
    }

    double maxValue = 1.0;
    for (size_t i = 0; i < assets.size(); ++i)
    {
        if (assets[i]->get_value() > maxValue)
        {
            maxValue = assets[i]->get_value();
        }
    }

    const float chartLeft = 800.0f;
    const float chartBottom = 720.0f;
    const float maxBarHeight = 220.0f;
    const float barWidth = 40.0f;
    const float spacing = 18.0f;

    float x = chartLeft;

    for (size_t i = 0; i < assets.size(); ++i)
    {
        Asset* pAsset = assets[i];

        float barHeight = static_cast<float>((pAsset->get_value() / maxValue) * maxBarHeight);

        sf::RectangleShape bar({ barWidth, barHeight });
        bar.setPosition({ x, chartBottom - barHeight });

        if (static_cast<int>(i) == mSelectedIndex)
        {
            bar.setFillColor(sf::Color(255, 120, 120));
        }
        else
        {
            switch (i % 4)
            {
            case 0: bar.setFillColor(sf::Color(100, 180, 255)); break;
            case 1: bar.setFillColor(sf::Color(255, 200, 100)); break;
            case 2: bar.setFillColor(sf::Color(180, 100, 255)); break;
            default: bar.setFillColor(sf::Color(120, 220, 150)); break;
            }
        }

        mWindow.draw(bar);

        drawText(pAsset->get_name(), x - 5.0f, chartBottom + 10.0f, 12, sf::Color::White);

        x += barWidth + spacing;

        if (x > mWidth - 70.0f)
        {
            break;
        }
    }

    sf::RectangleShape axis({ 560.0f, 2.0f });
    axis.setPosition({ chartLeft - 10.0f, chartBottom });
    axis.setFillColor(sf::Color::White);
    mWindow.draw(axis);
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