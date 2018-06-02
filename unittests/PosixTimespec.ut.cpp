#include <iostream>
#include <vector>

#include "PosixTimespec.hpp"

int main(int argc, char** argv)
{
    std::vector<timespec> timespecs;

    timespec tp;

    tp.tv_sec = 0;
    tp.tv_nsec = 0;
    timespecs.push_back(tp);

    tp.tv_sec = 1;
    tp.tv_nsec = 1;
    timespecs.push_back(tp);

    tp.tv_sec = 857693847;
    tp.tv_nsec = 736486;
    timespecs.push_back(tp);

    tp.tv_sec = 85769;
    tp.tv_nsec = 566486;
    timespecs.push_back(tp);

    tp.tv_sec = 8576946;
    tp.tv_nsec = 566486999;
    timespecs.push_back(tp);

    tp.tv_sec = 238576946;
    tp.tv_nsec = 999999999;
    timespecs.push_back(tp);

    std::vector<std::pair<unsigned int, unsigned int> > failed_cases;

    for (unsigned int i = 0; i < timespecs.size(); i++)
    {
        PosixTimespec ts1(timespecs[i]);

        for (unsigned int j = 0; j < timespecs.size(); j++)
        {
            PosixTimespec ts2(timespecs[j]);

            // Test addition
            PosixTimespec ts_sum1 = ts1 + ts2;
            PosixTimespec ts_sum2 = ts2 + ts1;
            if (!(ts_sum1 == ts_sum2 && ts_sum2 == ts_sum1))
            {
                failed_cases.push_back(
                    std::pair<unsigned int, unsigned int>(i, j));

                continue;
            }

            // Test equality and inequality
            if (i == j)
            {
                if (!(ts1 == ts2 && ts2 == ts1 &&
                      timespecs[i] == ts2 && ts2 == timespecs[i] &&
                      ts1 == timespecs[j] && timespecs[j] == ts1))
                {
                    failed_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
            else
            {
                if (!(ts1 != ts2 && ts2 != ts1 &&
                      timespecs[i] != ts2 && ts2 != timespecs[i] &&
                      ts1 != timespecs[j] && timespecs[j] != ts1))
                {
                    failed_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
        }
    }

    std::cout << "Failed cases: " << failed_cases.size() << "\n";

    // This unit test passes if no failed cases were recorded; remember that a
    // zero return value means success
    return failed_cases.size() != 0;
}
