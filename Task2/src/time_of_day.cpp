#include "time_of_day.h"

TimeOfDay getTimeOfDay(int hour) {
    if (hour >= 8 && hour < 12) return TimeOfDay::MORNING;
    if (hour >= 12 && hour < 18) return TimeOfDay::AFTERNOON;
    return TimeOfDay::EVENING;
}