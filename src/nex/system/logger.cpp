#include <nex/system/logger.h>

#include <stdio.h>
#include <iostream>
#include <cassert>
#include <time.h>

namespace nx
{


// Get current date/time, format is YYYY-MM-DD.HH:mm:ss.
const std::string currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);

    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format.
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return std::string(buf);
}


Logger::Logger() :
    mLogLevel(LL_DEBUG)
{ }

Logger::~Logger()
{
    // Make sure we close the file handle.
    if (mFileStream.is_open())
    {
        mFileStream.flush();
        mFileStream.close();
    }
}

bool Logger::open(const std::string& path)
{
    mFileStream.open(path.c_str(), std::ios::out | std::ios::app);

    if (!mFileStream.is_open()) {
        std::cout << "failed to open log file: " << path << std::endl;
        return false;
    }

    return true;
}

void Logger::message(const std::string& message)
{
    std::cout << "[" << currentDateTime() << "] "  << message << std::endl;
    if (mFileStream.is_open())
    {
        mFileStream << "[" << currentDateTime() << "] "  << message << std::endl;
    }
}

void Logger::debug(const std::string& debug)
{
    if (mLogLevel >= LL_DEBUG)
    {
        message(std::string(" [DEBUG] ").append(debug));
    }
}

void Logger::info(const std::string& info)
{
    if (mLogLevel >= LL_INFO)
    {
       message(std::string(" [INFO] ").append(info));
    }
}

void Logger::warn(const std::string& warning)
{
    if (mLogLevel >= LL_WARN)
    {
        message(std::string(" [WARN] ").append(warning));
    }
}

void Logger::error(const std::string& error)
{
    if (mLogLevel >= LL_ERROR)
    {
        message(std::string(" [ERROR] ").append(error));
    }
}

void Logger::close()
{
    mFileStream.close();
}

} // namespace nx
