#include <SFML\Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <random>
#include <string>

uint32_t nLehmer = 0;
uint32_t Lehmer32()
{
    nLehmer += 0xe120fc15;
    uint64_t tmp;
    tmp = (uint64_t)nLehmer * 0x4a39b70d;
    uint32_t m1 = (tmp >> 32) ^ tmp;
    tmp = (uint64_t)m1 * 0x12fad5c9;
    uint32_t m2 = (tmp >> 32) ^ tmp;
    return m2;
}

int rndNum(int min, int max)
{
    return (Lehmer32() % (max - min)) + min;
}

unsigned int width = 1280;
unsigned int height = 1024;
sf::Color starColors[5];

struct Star
{
    Star(int x, int y);
    bool exists = false;
    float size = .0f;
    sf::Color color;
};

Star::Star(int x, int y)
{
    nLehmer = (x & 0xFFFF) << 16 | (y & 0xFFFF);

    exists = rndNum(0, 50) == 2;

    if (!exists)
        return;
    size = (float)rndNum(3, 35);
    color = starColors[rndNum(0,5)];

}

void initStarColors()
{
    starColors[0] = sf::Color::Yellow;
    starColors[1] = sf::Color::Red;
    starColors[2] = sf::Color::Blue;
    starColors[3] = sf::Color::White;
    starColors[4] = sf::Color::Magenta;
}

int main()
{
    initStarColors();
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");

    float screenCoordX = 0.0f;
    float screenCoordY = -0.0f;
    int sectorWidth = 35;
    int nSectorX = width / sectorWidth;
    int nSectorY = height / sectorWidth;
    sf::Clock clock;
    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\Ebrima.ttf");
    sf::Text coordinates;
    coordinates.setFont(font);
    coordinates.setPosition(0, 0);

    while (window.isOpen())
    {
        float dt = clock.getElapsedTime().asSeconds();
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            screenCoordX += 100*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            screenCoordX -= 100*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            screenCoordY += 100*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            screenCoordY -= 100*dt;
        }

        coordinates.setString(std::to_string(screenCoordX) + ", " + std::to_string(-screenCoordY));

        sf::Vector2i mousePos= sf::Mouse::getPosition(window);
        mousePos /= 35;
        mousePos += sf::Vector2i(screenCoordX, screenCoordY);
        window.clear();

        for (int x = 0; x < nSectorX; x++)
        {
            for (int y = 0; y < nSectorY; y++)
            {
                int coordX = x + screenCoordX;
                int coordY = y + screenCoordY;
                Star star(coordX, coordY);
                if (star.exists)
                {
                    sf::CircleShape tmp(star.size / 2);
                    tmp.setPosition(x * sectorWidth + sectorWidth / 2 - tmp.getRadius(), y * sectorWidth + sectorWidth / 2 - tmp.getRadius());
                    tmp.setFillColor(star.color);
                    window.draw(tmp);

                    if (mousePos == sf::Vector2i(coordX, coordY))
                    {
                        sf::CircleShape highlight(tmp.getRadius() + 1);
                        highlight.setPosition(x * sectorWidth + sectorWidth / 2 - tmp.getRadius() - 1, y * sectorWidth + sectorWidth / 2 - tmp.getRadius() - 1);
                        highlight.setFillColor(sf::Color::Transparent);
                        highlight.setOutlineColor(sf::Color::Green);
                        highlight.setOutlineThickness(2);
                        window.draw(highlight);
                    }
                }
            }
        }

        window.draw(coordinates);
        window.display();
    }

    return 0;
}