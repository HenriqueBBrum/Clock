#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<ctime>
#include<cmath>

#define ALT 600
#define LARG 600

#define PI 3.14159

const std::string title("ClockSystem");

namespace Time{

    class Clock {

        sf::CircleShape clock;
        sf::CircleShape centerCircle;

        sf::RectangleShape secondsLine;
        sf::RectangleShape minutesLine;
        sf::RectangleShape hoursLine;


        float seconds;
        float minutes;
        float hours;

        sf::SoundBuffer secondsBuffer;
        sf::SoundBuffer hoursBuffer[2];

        sf::Sound soundSec;
        sf::Sound soundHour;

        void linePosition(sf::Vector2f size_, sf::RectangleShape& line, sf::Color color);

        void update_time();

        void draw(sf::RenderWindow& win);

        void drawMarkers(sf::RenderWindow& win, int ratio);

        void movePointer();


        public:

            Clock();

            void update(sf::RenderWindow& win);

    };


}
