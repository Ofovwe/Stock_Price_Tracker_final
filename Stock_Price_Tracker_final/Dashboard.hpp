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

    int mSelectedIndex;

    // Buttons
    sf::RectangleShape mSortValueButton;
    sf::RectangleShape mSortProfitButton;
    sf::RectangleShape mRemoveButton;
    sf::RectangleShape mResetButton;

public:
    Dashboard(float width = 1450.0f, float height = 900.0f);
    void run(Portfolio& portfolio);

private:
    void handleEvents(Portfolio& portfolio);
    void render(Portfolio& portfolio);

    void initializeButtons();
    bool isMouseOverButton(const sf::RectangleShape& button, float mouseX, float mouseY);

    void drawBackground();
    void drawHeader(Portfolio& portfolio);
    void drawButtons();
    void drawAssetTable(Portfolio& portfolio);
    void drawSelectedAssetPanel(Portfolio& portfolio);
    void drawBarChart(Portfolio& portfolio);

    void drawText(const std::string& text,
        float x,
        float y,
        unsigned int size = 20,
        sf::Color color = sf::Color::White);
};