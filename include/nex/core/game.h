#ifndef GAME_H_INCLUDE
#define GAME_H_INCLUDE

#include <nex/system/string.h>

namespace nx
{
    class Game
    {
    public:
        /**
         * @brief Construct an instance of the game class.
         * @param title = title of the game (also for the window if any)
         * @param updatesPerSecond = rate to update the game at.
         */
        Game(const nx::String& title, const int32 updatesPerSecond);

        /**
         * @brief initialize the game launcher and the game.
         * @return true if sucessful.
         */
        virtual bool initialize();

        /**
         * @brief Destroy any loaded content.
         */
        virtual void destroy();

        /**
         * @brief Called at the specified update per second.
         */
        virtual void update();

        /**
         * @brief Called at faster rate than the update. may be locked to vsync.
         * @param deltaTime = delta time for interpolation.
         */
        virtual void render(const float deltaTime);

    private:

        /**
         * @brief mUpdatesPerSecond = Rate the game is updated at.
         */
        int32 mUpdatesPerSecond;

        /**
         * @brief mTitle = Title of the game (and window if any)
         */
        nx::String mTitle;
    };
} // namespace nx

#endif // GAME_H_INCLUDE
