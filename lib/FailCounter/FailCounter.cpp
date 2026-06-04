#include "FailCounter.h"
#include "Logger.h"
#include "config.h"

void FailCounter::reset()
{
    failCount = 0;

    Logger::info("[FAIL] Counter Reset");
}

void FailCounter::increase()
{
    failCount++;

    Logger::warn(
        "[FAIL] Count = " +
        String(failCount)
    );
}

int FailCounter::getCount() const
{
    return failCount;
}

bool FailCounter::isLimitReached() const
{
    return failCount >= MAX_AUTH_FAIL_COUNT;
}