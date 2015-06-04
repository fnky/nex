#ifndef EVENT_H_INCLUDE
#define EVENT_H_INCLUDE

#include <nex/system/typedefs.h>

namespace nx
{

enum EventType
{
    NOTHING = 0
};

struct Event
{
    /**
     * @brief Whether or not we have handled the event.
     */
    bool handled;

    /**
     * @brief The type of event that was generated.
     */
    EventType type;


}; // struct Event

} // namespace nx

#endif // EVENT_H_INCLUDE
