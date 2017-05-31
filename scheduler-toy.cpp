#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char** argv)
{
  sched_param scheduler_params;
  scheduler_params.sched_priority = 0;

  int policy = SCHED_OTHER;

  // Parse arguments
  for (int arg = 1; arg < argc; arg++)
  {
    // Argument -p sets static priority
    if (strcmp(argv[arg], "-p") == 0 && arg + 1 < argc)
    {
      arg++;
      scheduler_params.sched_priority = atoi(argv[arg]);
    }
    // Argument --sched-other sets SCHED_OTHER scheduling policy
    else if (strcmp(argv[arg], "--sched-other") == 0)
    {
      policy = SCHED_OTHER;
    }
    // Argument --sched-batch sets SCHED_BATCH scheduling policy
    else if (strcmp(argv[arg], "--sched-batch") == 0)
    {
      policy = SCHED_BATCH;
    }
    // Argument --sched-idle sets SCHED_IDLE scheduling policy
    else if (strcmp(argv[arg], "--sched-idle") == 0)
    {
      policy = SCHED_IDLE;
    }
    // Argument --sched-rr sets SCHED_RR scheduling policy
    else if (strcmp(argv[arg], "--sched-rr") == 0)
    {
      policy = SCHED_RR;
    }
    // Argument --sched-fifo sets SCHED_FIFO scheduling policy
    else if (strcmp(argv[arg], "--sched-fifo") == 0)
    {
      policy = SCHED_FIFO;
    }
  }

  rlimit rlim;
  std::cout << "getrlimit returns " << getrlimit(RLIMIT_RTPRIO, &rlim) << "\n";
  std::cout << "RLIMIT_RTPRIO current " << rlim.rlim_cur
            << " max " << rlim.rlim_max << "\n";
  std::cout << "getrlimit returns " << getrlimit(RLIMIT_NICE, &rlim) << "\n";
  std::cout << "RLIMIT_NICE current " << rlim.rlim_cur
            << " max " << rlim.rlim_max << "\n";

  std::cout << "Setting scheduling policy " << policy << " priority "
            << scheduler_params.sched_priority << "\n";

  std::cout << "sched_setscheduler returns "
            << sched_setscheduler(0, policy, &scheduler_params) << "\n";

  std::cout << "Scheduling policy is " << sched_getscheduler(0) << " priority "
            << getpriority(PRIO_PROCESS, 0) << "\n";

  while(1) {}

  return 0;
}
