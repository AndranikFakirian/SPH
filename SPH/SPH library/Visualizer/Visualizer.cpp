#pragma once
#include "../Classes&Structures/Liquid.hpp"
#include "Environment_Parameters.cpp"
#include <SFML/Graphics.hpp>
#include <iterator>

void Liquid::Visualize()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(E_WX, E_WY), "SPH", sf::Style::Fullscreen, settings);
    window.setFramerateLimit(60);
    sf::RectangleShape bg(sf::Vector2f(E_WX, E_WY));
    bg.setPosition(0, 0);
    sf::RectangleShape wall1(sf::Vector2f(E_width, E_height));
    wall1.setPosition((E_WX-E_length)/2-E_width, E_indent);
    wall1.setFillColor(sf::Color::Black);
    sf::RectangleShape wall2(sf::Vector2f(E_width, E_height));
    wall2.setPosition((E_WX+E_length)/2, E_indent);
    wall2.setFillColor(sf::Color::Black);
    sf::RectangleShape bottom(sf::Vector2f(E_length+2*E_width, E_width));
    bottom.setPosition((E_WX-E_length)/2-E_width, E_height+E_indent);
    sf::RectangleShape bg(sf::Vector2f(E_WX, E_WY));
    bg.setPosition(0, 0);
    sf::RectangleShape wall1(sf::Vector2f(E_width, E_height));
    wall1.setPosition((E_WX-E_length)/2-E_width, E_indent);
    wall1.setFillColor(sf::Color::Black);
    sf::RectangleShape wall2(sf::Vector2f(E_width, E_height));
    wall2.setPosition((E_WX+E_length)/2, E_indent);
    wall2.setFillColor(sf::Color::Black);
    sf::RectangleShape bottom(sf::Vector2f(E_length+2*E_width, E_width));
    bottom.setPosition((E_WX-E_length)/2-E_width, E_height+E_indent);
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
        fluid[i].setRadius(E_rad);
        fluid[i].setOrigin(E_rad, E_rad);
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
            for (int i=0; i<10; i++)
            {
                Solve();
                for (unsigned j=0; j<liq.size(); j++)
                {
                    fluid[j].setPosition(liq[j].x, liq[j].y);
                }
            }
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
