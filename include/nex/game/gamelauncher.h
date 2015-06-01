#ifndef GAMELAUNCHER_H_INCLUDE
#define GAMELAUNCHER_H_INCLUDE

#include <nex/game/game.h>

namespace nx
{
    class GameLauncher
    {
    public:
        GameLauncher(Game& game);

        /**
         * @brief Launch the game.
         * @param argc = The argument count.
         * @param argv = The argument values.
         */
        void launch(int argc, char** argv);

    private:

        /**
         * @brief Keeps the game loop alive.
         */
        bool mRunning;

        /**
         * @brief The instance of our current game.
         */
        Game& mGame;

        /**
         * @brief initialize the game launcher and the game.
         * @return true if sucessful.
         */
        bool initialize();

        /**
         * @brief Destroy any loaded content.
         */
        void destroy();

        /**
         * @brief The main game loop.
         */
        void run();
    };
} // namespace nx

#endif // GAMELAUNCHER_H_INCLUDE
