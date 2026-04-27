#include "Dashboard.hpp"
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

Dashboard::Dashboard(double width, double height)
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
