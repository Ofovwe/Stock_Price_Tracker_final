#pragma once

#include "Asset.hpp"
#include "Portfolio.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class Dashboard
{
private:
    sf::RenderWindow mWindow;
    sf::Font mFont;

    float mWidth;
    float mHeight;

    int mSelectedIndex;
    int mScrollOffset;   // <-- ADD THIS

public:
    Dashboard(float width = 1400.0f, float height = 850.0f);
    void run(Portfolio& portfolio);

private:
    void handleEvents(Portfolio& portfolio);
    void render(Portfolio& portfolio);

    void drawBackground();
    void drawHeader(Portfolio& portfolio);
    void drawAssetTable(Portfolio& portfolio);
    void drawSelectedAssetPanel(Portfolio& portfolio);
    void drawDonutChart(Portfolio& portfolio);

    int getHoveredChartIndex(Portfolio& portfolio, sf::Vector2f mousePos);
    sf::Color getChartColor(int index);

    void editSelectedPrice(Portfolio& portfolio);
    void editSelectedQuantity(Portfolio& portfolio);
    void editSelectedPurchasePrice(Portfolio& portfolio);

    void drawText(const std::string& text,
        float x,
        float y,
        unsigned int size = 20,
        sf::Color color = sf::Color::White);
};