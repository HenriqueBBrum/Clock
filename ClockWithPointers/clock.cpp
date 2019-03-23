#include"clock.hpp"


using namespace Time;

void Clock::linePosition(sf::Vector2f size_,sf::RectangleShape& line, sf::Color color){
    line.setPosition(LARG/2, ALT/2);
    line.setSize(size_);
    line.setFillColor(color);
}

void Clock::update_time(){
    std::time_t t =   std::time(0);
    std::tm* now =  std::localtime(&t);
    seconds = now->tm_sec;
    minutes = now->tm_min;
    hours = now->tm_hour;

}
Clock::Clock(){
    update_time();

    clock.setRadius(ALT/3);
    clock.setPosition(LARG/2-clock.getRadius(), ALT/2-clock.getRadius());
    clock.setFillColor(sf::Color::White);
    clock.setOutlineThickness(10.0f);
    clock.setOutlineColor(sf::Color::Black);

    centerCircle.setRadius(clock.getRadius()/10);
    centerCircle.setPosition(LARG/2-centerCircle.getRadius(), ALT/2-centerCircle.getRadius());
    centerCircle.setFillColor(sf::Color::Blue);

    linePosition({2,clock.getRadius()*20/21}, secondsLine, sf::Color::Red);
    linePosition({4,clock.getRadius()*19/21}, minutesLine, sf::Color::Black);
    linePosition({6,clock.getRadius()*15/21}, hoursLine, sf::Color::Black);

    secondsLine.setRotation((seconds/60*360-180)+0.5);
    minutesLine.setRotation((minutes/60*360-180)+0.5);
    hoursLine.setRotation((hours/12*360-180)+2);

    if(!secondsBuffer.loadFromFile("Sounds/secondsTick.wav"))
        std::abort();

    if(!hoursBuffer[0].loadFromFile("Sounds/hourCuckoo.wav"))
        std::abort();

    if(!hoursBuffer[1].loadFromFile("Sounds/hour12.wav"))
        std::abort();
}


void Clock::update(sf::RenderWindow& win){
    update_time();
    draw(win);
    movePointer();
}


void Clock::drawMarkers(sf::RenderWindow& win, int ratio){
    int i = 0;
    float radius = clock.getRadius();
    float centerX = clock.getPosition().x+radius;
    float centerY = clock.getPosition().y+radius;
    sf::RectangleShape aux;
    aux.setFillColor(sf::Color::Black);

    while(i<ratio){
        float angle_radians = PI*i*(360/ratio)/180;


        aux.setPosition(LARG/2+cos(angle_radians)*radius,ALT/2+sin(angle_radians)*radius);
        aux.setSize({60/(float)ratio, (radius/10)+60/(float)ratio});

        float posX = aux.getPosition().x;
        float posY = aux.getPosition().y;

        float angle = std::atan2(posY-centerY, posX-centerX)*180/PI;
        aux.setRotation(angle+90);
        win.draw(aux);
        i++;
    }


}

void Clock::draw(sf::RenderWindow& win){

    sf::RectangleShape edge({0,0});
    edge.setSize({LARG,ALT});
    edge.setFillColor(sf::Color::White);
    edge.setOutlineThickness(-20);
    edge.setOutlineColor(sf::Color::Red);

    win.draw(edge);
    win.draw(clock);

    drawMarkers(win, 12);
    drawMarkers(win, 60);


    win.draw(secondsLine);
    win.draw(minutesLine);
    win.draw(hoursLine);

    win.draw(centerCircle);

}


void Clock::movePointer(){

    float oldSecRotation = secondsLine.getRotation();
    float oldHourRotation = hoursLine.getRotation();

    secondsLine.setRotation((seconds/60*360-180)+0.5);
    minutesLine.setRotation((minutes/60*360-180)+0.5);
    hoursLine.setRotation((hours/12*360-180)+2);

    float newSecRotation = secondsLine.getRotation();
    float newHourRotation = hoursLine.getRotation();

    if(hours!=12 && oldHourRotation-newHourRotation<0){
        soundHour.setBuffer(hoursBuffer[0]);
        soundHour.play();

    }else if(oldHourRotation-newHourRotation<0 && hours == 12){
        soundHour.setBuffer(hoursBuffer[1]);
        soundHour.play();

    }else if(oldSecRotation-newSecRotation<0){
        soundSec.setBuffer(secondsBuffer);
        soundSec.play();
    }

}
