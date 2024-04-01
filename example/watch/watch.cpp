#include "watch.h"
#include "hsm.h"
#include <chrono>
#include <memory>
#include <optional>


using namespace std::chrono_literals;

Watch::Watch() : Hsm("Watch")
{

    auto timekeeping = std::make_shared<State>("Timekeeping", nullptr, [&] (auto event){timekeepingStd(event);});
    auto time = std::make_shared<State>("Time", timekeeping, [&] (auto ){current_view = "Time";});
    auto date = std::make_shared<State>("Date", timekeeping, [&] (auto){ current_view = "Date";});

    auto setting = std::make_shared<State>("Setting", nullptr, [&] (auto event){settingStd(event);});
    auto hours = std::make_shared<State>("Hours", setting, [] (auto){});
    auto minutes = std::make_shared<State>("Minutes", setting, [] (auto){});
    auto day = std::make_shared<State>("Day", setting, [] (auto){});
    auto month = std::make_shared<State>("Month", setting, [] (auto){});

    auto watchStates = {timekeeping, time, date, setting, hours, minutes, day, month};

    auto watchTransitions = {
        Transition{timekeeping, &TICK, timekeeping, [&] { tick(); }},
        Transition{timekeeping, &CHILD, time, std::nullopt},
        Transition{time, &MODE, date, std::nullopt},
        Transition{date, &MODE, time, std::nullopt},
        Transition{timekeeping, &SET, setting, std::nullopt},
        Transition{setting, &CHILD, hours, std::nullopt},
        Transition{hours, &MODE, hours, [&] { temp_time += 1h; }},
        Transition{hours, &SET, minutes, std::nullopt},
        Transition{minutes, &MODE, minutes, [&] { temp_time += 1min; }},
        Transition{minutes, &SET, day, std::nullopt},
        Transition{day, &MODE, day, [&] { temp_time += 24h; }},
        Transition{day, &SET, month, std::nullopt},
        Transition{month, &MODE, month, [&] { temp_time += 30 * 24h; }},
        Transition{month, &SET, timekeeping, std::nullopt},

    };
    activate(watchStates, watchTransitions);
}


void Watch::some_time_passed()
{
    onEvent(&TICK);
}

void Watch::press_mode()
{
    onEvent(&MODE);
}

void Watch::press_set()
{
    onEvent(&SET);
}

void Watch::tick()
{
    current_time += 1min;
}


void Watch::timekeepingStd(StdEvents event)
{
    if (event == StdEvents::START)
    {
        onEvent(&CHILD);
    }
}

void Watch::settingStd(StdEvents event)
{
    if (event == StdEvents::ENTRY)
    {
        current_view = "Setting";
        temp_time = current_time;
    }
    if (event == StdEvents::START)
    {
        onEvent(&CHILD);
    }
    if (event == StdEvents::EXIT)
    {
        current_time = temp_time;
    }
}
