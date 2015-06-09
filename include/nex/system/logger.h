#ifndef LOGGER_H_INCLUDE
#define LOGGER_H_INCLUDE

#include <string>
#include <fstream>

namespace nx
{

enum LogLevel
{
    LL_DEBUG = 3,
    LL_INFO = 2,
    LL_WARN = 1,
    LL_ERROR = 0
};

class Logger
{
public:

    /**
     * @brief Default constructor for the logger.
     */
    Logger();

    /**
      * @brief Default destructor for the logger.
      */
    ~Logger();

    /**
     * @brief Open the file stream to which the logger will start writing after this call.
     * @param path = The file to write our log data to.
     * @return true if we opened the file correctly.
     */
    bool open(const std::string& path);

    /**
     * @brief Closes the loggers file stream.
     */
    void close();

    /**
     * @brief Write a message to the log.
     * @param message = The message to write.
     */
    void message(const std::string& message);

    /**
     * @brief Write a debug message to the log.
     * @param debug = The debug message.
     */
    void debug(const std::string& debug);

    /**
     * @brief Write an info message to the log.
     * @param info = The info message.
     */
    void info(const std::string& info);

    /**
     * @brief Write a warning message to the log.
     * @param warning = the warning message.
     */
    void warn(const std::string& warning);

    /**
     * @brief Write an error message to the log.
     * @param error = the error message.
     */
    void error(const std::string& error);

    /**
     * @brief Get the loggers current log level.
     * @return log level.
     */
    LogLevel getLogLevel() const { return mLogLevel; }

    /**
     * @brief Set the loggers current log level.
     * @param level = log level.
     */
    void setLogLevel(LogLevel level) { mLogLevel = level; }

private:
    LogLevel mLogLevel;
    std::ofstream mFileStream;
};

} // namespace nx

#endif // LOGGER_H_INCLUDE
