#pragma once

#include "Asset.hpp"
#include "Portfolio.hpp"

class Dashboard
{
private:
    sf::RenderWindow mWindow;
    sf::Font mFont;

    float mWidth;
    float mHeight;

    int mSelectedIndex;   // which asset is selected

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
    void drawBarChart(Portfolio& portfolio);

    void drawText(const std::string& text,
        float x,
        float y,
        unsigned int size = 20,
        sf::Color color = sf::Color::White);
};