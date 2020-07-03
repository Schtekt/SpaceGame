#include "Game.h"
#include <random>
#include <time.h>
int main()
{
    srand(time(NULL));
    Game game;
    game.Run();
    return 0;
}