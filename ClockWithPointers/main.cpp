#include"clock.hpp"


int main()
{
    sf::RenderWindow win(sf::VideoMode(LARG, ALT), title);

    sf::Event event;

    Time::Clock clk;



    while(win.isOpen()){

        while(win.pollEvent(event)){

            if(event.type == sf::Event::Closed)
                win.close();

        }


        win.clear(sf::Color::White);

        clk.update(win);

        win.display();

    }
    return 0;
}
