#ifndef TIME_OF_DAY_H
#define TIME_OF_DAY_H

enum class TimeOfDay {
    MORNING,
    AFTERNOON,
    EVENING
};

TimeOfDay getTimeOfDay(int hour);

#endif