#ifndef FAIL_COUNTER_H
#define FAIL_COUNTER_H

class FailCounter
{
public:

    void reset();

    void increase();

    int getCount() const;

    bool isLimitReached() const;

private:

    int failCount = 0;
};

#endif