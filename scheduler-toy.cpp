#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char** argv)
{
  sched_param scheduler_params;
  scheduler_params.sched_priority = 0;

  int niceness = 0;

  int policy = SCHED_OTHER;

  std::map<int, std::string> policy_names;
  policy_names[SCHED_OTHER] = "SCHED_OTHER";
  policy_names[SCHED_BATCH] = "SCHED_BATCH";
  policy_names[SCHED_IDLE]  = "SCHED_IDLE";
  policy_names[SCHED_RR]    = "SCHED_RR";
  policy_names[SCHED_FIFO]  = "SCHED_FIFO";

  // Parse arguments
  for (int arg = 1; arg < argc; arg++)
  {
    // Argument -p sets static priority
    if (strcmp(argv[arg], "-p") == 0 && arg + 1 < argc)
    {
      arg++;
      scheduler_params.sched_priority = atoi(argv[arg]);
    }
    // Argument -p sets static priority
    else if (strcmp(argv[arg], "-n") == 0 && arg + 1 < argc)
    {
      arg++;
      niceness = atoi(argv[arg]);
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
  getrlimit(RLIMIT_RTPRIO, &rlim);
  std::cout << "RLIMIT_RTPRIO current " << rlim.rlim_cur
            << " max " << rlim.rlim_max << "\n";
  getrlimit(RLIMIT_NICE, &rlim);
  std::cout << "RLIMIT_NICE current " << rlim.rlim_cur
            << " max " << rlim.rlim_max << "\n";
  std::cout << policy_names[policy] << " policy priority min "
            << sched_get_priority_min(policy) << " max "
            << sched_get_priority_max(policy) << "\n";

  std::cout << "Setting scheduling policy " << policy_names[policy]
            << " priority " << scheduler_params.sched_priority << "\n";

  std::cout << "sched_setscheduler returns "
            << sched_setscheduler(0, policy, &scheduler_params) << "\n";

  sched_getparam(0, &scheduler_params);
  std::cout << "Scheduling policy is " << policy_names[sched_getscheduler(0)]
            << " priority " << scheduler_params.sched_priority << "\n";

  std::cout << "Setting nice value " << niceness << "\n";
  std::cout << "setpriority returns " << setpriority(PRIO_PROCESS, 0, niceness)
            << "\n";
  std::cout << "Niceness is " << getpriority(PRIO_PROCESS, 0) << "\n";

  while(1) {}

  return 0;
}
