// General-purpose timestamp-based log utility
// Leigh Garbs

#include "Log.hpp"

#include <ctime>
#include <ostream>
#include <sstream>
#include <string>
#include <sys/time.h>

//==============================================================================
// Log constructor; initializes output_stream
//==============================================================================
Log::Log(std::ostream& output_stream) :
  output_stream(&output_stream),
  current_time_format(GMT),
  flush_after_write(false)
{
}

//==============================================================================
// Log destructor; does nothing
//==============================================================================
Log::~Log()
{
}

//==============================================================================
// Writes a standard log message
//==============================================================================
void Log::write(const std::string& message)
{
  // Generate a timestamp
  std::string timestamp;
  generateTimestamp(timestamp);

  // Write the log message
  *output_stream << timestamp + " " + message + "\n";

  if (flush_after_write)
  {
    flush();
  }
}

//==============================================================================
// Writes a warning log message
//==============================================================================
void Log::writeWarning(const std::string& message)
{
  // Generate a timestamp
  std::string timestamp;
  generateTimestamp(timestamp);

  // Write the log message
  *output_stream << timestamp + " WARNING - " + message + "\n";

  if (flush_after_write)
  {
    flush();
  }
}

//==============================================================================
// Writes an error log message
//==============================================================================
void Log::writeError(const std::string& message)
{
  // Generate a timestamp
  std::string timestamp;
  generateTimestamp(timestamp);

  // Write the log message
  *output_stream << timestamp + " ERROR - " + message + "\n";

  if (flush_after_write)
  {
    flush();
  }
}

//==============================================================================
// Flushes the current output stream
//==============================================================================
void Log::flush()
{
  output_stream->flush();
}

//==============================================================================
// Generates a timestamp to prepend to a log message
//==============================================================================
void Log::generateTimestamp(std::string& timestamp)
{
  // Get numeric timestamp
  timeval ts;
  if (gettimeofday(&ts, 0) == -1)
  {
    // Could not generate timestamp
    timestamp = "[???]";
    return;
  }

  // Convert ts into string timestamp
  tm* ts_local;
  if (current_time_format == LOCAL)
  {
    ts_local = localtime(&ts.tv_sec);
  }
  else
  {
    ts_local = gmtime(&ts.tv_sec);
  }

  // Format ts_local
  unsigned int max_ts_len = 30;
  char ts_local_temp[max_ts_len];
  strftime(ts_local_temp, max_ts_len, "%a %b %d %Y %X:", ts_local);

  // Save into string timestamp
  timestamp = "[";
  timestamp += ts_local_temp;

  // Add microseconds
  std::ostringstream out_stream;
  out_stream.width(6);
  out_stream.fill('0');
  out_stream << ts.tv_usec;
  timestamp += out_stream.str();

  // Add timezone
  strftime(ts_local_temp, max_ts_len, " %Z", ts_local);
  timestamp += ts_local_temp;
  timestamp += "]";
}
