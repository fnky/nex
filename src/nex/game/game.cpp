#include <nex/game/game.h>

namespace nx
{

Game::Game(const String &title, const int32 updatesPerSecond) :
    mTitle(title),
    mUpdatesPerSecond(updatesPerSecond)
{

}

Game::~Game()
{

}

bool Game::initialize()
{
    return true;
}

void Game::destroy()
{

}

void Game::update()
{

}

void Game::render(const float deltaTime)
{

}

} //namespace nx
