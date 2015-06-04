#ifndef NONCOPYABLE_H_INCLUDE
#define NONCOPYABLE_H_INCLUDE

namespace nx
{

class NonCopyable
{
protected:

    /**
     * @brief Default constructor to prevent the generation of the default constructor.
     */
    NonCopyable() {}

private:

    /**
     * @brief By making the copy constructor private, the compiler will trigger an error if anyone outside tries to use it.
     */
    NonCopyable(const NonCopyable&);

    /**
     * @brief By making the assignment operator private, the compiler will trigger an error if anyone outside tries to use it.
     */
    NonCopyable& operator =(const NonCopyable&);
};

} //namespace nx

#endif // NONCOPYABLE_H_INCLUDE
