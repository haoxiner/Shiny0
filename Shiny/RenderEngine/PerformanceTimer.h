//
// Created by haoxin on 17/2/12.
//

#ifndef SHINY_PERFORMANCETIMER_H
#define SHINY_PERFORMANCETIMER_H

#include "shiny.h"
#include <cstdint>

SHINY_NAMESPACE_BEGIN

class PerformanceTimer {
public:
    PerformanceTimer();
    ~PerformanceTimer() = default;
    void Reset();
    void Tick();
    float GetDeltaTime() const { return deltaTime_; };
private:
    uint64_t lastTime_ = 0;
    uint64_t currentTime_ = 0;
    double invFrequency_ = 0;
    float deltaTime_ = 0;
};

SHINY_NAMESPACE_END

#endif //SHINY_PERFORMANCETIMER_H
