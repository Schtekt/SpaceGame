#ifndef STAR_H
#define STAR_H
namespace sf
{
    class Color;
}
class Star
{
private:
    bool m_exists = false;
    float m_size = .0f;
    sf::Color* m_pColor;
public:
    Star(int x, int y, int minSize, int maxSize);

    bool Exists();
    float Size();
    sf::Color Color();
};

#endif