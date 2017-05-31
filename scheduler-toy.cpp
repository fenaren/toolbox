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
  bool loop = false;

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
    else if (strcmp(argv[arg], "--loop") == 0)
    {
      loop = true;
    }
    else
    {
      std::cout << argv[0] << " [ -p <priority> ] [ -n <niceness> ] "
        "[ --sched-other | --sched-idle | --sched-batch | --sched-rr | "
        "--sched-fifo ] [ --loop ]\n";

      return 1;
    }
  }

  // What is RLIMIT_RTPRIO set to?  RLIMIT_RTPRIO limits the priority that an
  // unprivileged user can assign to a thread/process
  rlimit rlim;
  getrlimit(RLIMIT_RTPRIO, &rlim);
  std::cout << "RLIMIT_RTPRIO current " << rlim.rlim_cur
            << " max " << rlim.rlim_max << "\n";

  // What is RLIMIT_NICE set to?  RLIMIT_NICE limits the niceness that an
  // unprivileged user can assign to a thread/process
  getrlimit(RLIMIT_NICE, &rlim);
  std::cout << "RLIMIT_NICE current " << rlim.rlim_cur
            << " max " << rlim.rlim_max << "\n";

  // What are the minimum and maximum allowable priorities for the given
  // scheduling policy?
  std::cout << policy_names[policy] << " policy priority min "
            << sched_get_priority_min(policy) << " max "
            << sched_get_priority_max(policy) << "\n";

  // We try to set the scheduling policy and priority here
  std::cout << "Setting scheduling policy " << policy_names[policy]
            << " priority " << scheduler_params.sched_priority << "\n";

  // Did we set the scheduling policy and priority ok?
  std::cout << "sched_setscheduler returns "
            << sched_setscheduler(0, policy, &scheduler_params) << "\n";

  // What is the scheduling policy and priority after we tried to set it?
  sched_getparam(0, &scheduler_params);
  std::cout << "Scheduling policy is " << policy_names[sched_getscheduler(0)]
            << " priority " << scheduler_params.sched_priority << "\n";

  // Try to set the given nice value
  std::cout << "Setting nice value " << niceness << "\n";
  std::cout << "setpriority returns " << setpriority(PRIO_PROCESS, 0, niceness)
            << "\n";

  // Report what the current niceness is
  std::cout << "Niceness is " << getpriority(PRIO_PROCESS, 0) << "\n";

  // Loop forever if the user so desires; this can be useful for observing how
  // this process looks in top and ps
  if (loop)
  {
    while(1) {}
  }

  return 0;
}
