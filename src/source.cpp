#include "Game.h"
#include <random>
#include <time.h>
#include <crtdbg.h>
int main()
{
    #ifdef DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif // DEBUG

    srand(time(NULL));
    Game game;
    game.Run();
    return 0;
}