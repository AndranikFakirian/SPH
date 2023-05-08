#pragma once
#include "../Classes&Structures/Liquid.hpp"
#include <SFML/Graphics.hpp>
#include <iterator>

void Liquid::Visualize()
{
    const double WX=1938;
    const double WY=1156;
    const double p_length=77;
    const double p_heigth=100;
    const double heigth=950.0;
    const double indent=50.0;
    const double width=3.0;
    const double length=p_length*(rad*2+1)+1;
    const double rad=4.0;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WX, WY), "SPH", sf::Style::Fullscreen, settings);
    window.setFramerateLimit(60);
    sf::RectangleShape bg(sf::Vector2f(WX, WY));
    bg.setPosition(0, 0);
    sf::RectangleShape wall1(sf::Vector2f(width, heigth));
    wall1.setPosition((WX-length)/2-width, indent);
    wall1.setFillColor(sf::Color::Black);
    sf::RectangleShape wall2(sf::Vector2f(width, heigth));
    wall2.setPosition((WX+length)/2, indent);
    wall2.setFillColor(sf::Color::Black);
    sf::RectangleShape bottom(sf::Vector2f(length+2*width, width));
    bottom.setPosition((WX-length)/2-width, heigth+indent);
    bottom.setFillColor(sf::Color::Black);
    vector <sf::CircleShape> fluid;
    fluid.resize(liq.size());
    for (unsigned i=0; i<liq.size(); i++)
    {
        sf::Color c;
        if (liq[i].color=="red")
            c=sf::Color::Red;
        if (liq[i].color=="blue")
            c=sf::Color::Blue;
        if (liq[i].color=="green")
            c=sf::Color::Green;
        fluid[i].setFillColor(c);
        fluid[i].setRadius(rad);
        fluid[i].setOrigin(rad, rad);
        fluid[i].setPosition(liq[i].x, liq[i].y);
    }
    Starting();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //Moving realization
            //There's a refinement algorithm for movement (through partition of dtime)
            //Here's a place for Solve function
            //Algorithm can be done in two ways: through setPosition and move

            window.clear();
            window.draw(bg);
            window.draw(wall1);
            window.draw(wall2);
            window.draw(bottom);
            for (vector <sf::CircleShape>::iterator it=fluid.begin(); it!=fluid.end(); ++it)
            {
                window.draw((*it));
            }
            window.display();
    }
}
