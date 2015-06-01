#include <nex/game/gamelauncher.h>

namespace nx
{

GameLauncher::GameLauncher(Game& game) :
    mGame(game),
    mRunning(true)
{

}

void GameLauncher::launch(int argc, char** argv)
{

}

bool GameLauncher::initialize()
{
    return mGame.initialize();
}

void GameLauncher::destroy()
{

}

void GameLauncher::run()
{
    while(mRunning)
    {

    }
}

} //namespace nx
