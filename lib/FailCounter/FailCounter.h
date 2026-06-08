#ifndef FAIL_COUNTER_H
#define FAIL_COUNTER_H

#include "config.h"

class FailCounter
{
public:

    void reset();

    void increase();

    int getCount() const;

    bool isLimitReached() const;

    void setMaxFailCount(int value);

    int getMaxFailCount() const;

private:

    int failCount = 0;

    int maxFailCount = MAX_AUTH_FAIL_COUNT;
};

#endif