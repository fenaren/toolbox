#if !defined LOG_HPP
#define LOG_HPP

#include <iostream>

/* A general purpose text-based logging utility.
 */
class Log
{
  public:

    // Log constructor; initializes output_stream
    Log(std::ostream& output_stream     = std::cout,
        bool          flush_after_write = false);

    // Log destructor; does nothing
    ~Log();

    // Sets the output stream to write log messages to
    void setOutputStream(std::ostream& output_stream);

    // Returns the output stream to write log messages to
    std::ostream& getOutputStream() const;

    // Writes a standard log message
    void write(const std::string& message);

    // Writes a warning log message
    void writeWarning(const std::string& message);

    // Writes an error log message
    void writeError(const std::string& message);

    // Flushes the current output stream
    void flush();

    // Causes log timestamps to be generated in GMT
    void useGreenwichMeanTime();

    // Causes log timestamps to be generated in local time
    void useLocalTime();

    // Should the log flush the output stream after every write?
    void flushAfterWrite(bool flush_after_write);

  private:

    // Enumerates the different supported time formats
    enum TimeFormat
    {
      GMT,
      LOCAL
    };

    // Generates a timestamp to prepend to log messages
    void generateTimestamp(std::string& timestamp) const;

    // The output stream to write log messages to
    std::ostream* output_stream;

    // The time format log timestamps are currently generated in
    TimeFormat current_time_format;

    // Whether or not the log flushes the output stream after every write
    bool flush_after_write;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    Log(const Log&);
    Log& operator=(const Log&);
};

inline void Log::setOutputStream(std::ostream& output_stream)
{
  this->output_stream = &output_stream;
}

inline std::ostream& Log::getOutputStream() const
{
  return *output_stream;
}

inline void Log::useGreenwichMeanTime()
{
  current_time_format = GMT;
}

inline void Log::useLocalTime()
{
  current_time_format = LOCAL;
}

inline void Log::flushAfterWrite(bool flush_after_write)
{
  this->flush_after_write = flush_after_write;
}

#endif
