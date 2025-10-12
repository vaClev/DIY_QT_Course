#ifndef TRAFFICLIGHTCOLORS_H
#define TRAFFICLIGHTCOLORS_H

enum class TrafficLightColors
{
    Red = 0,
    Yellow = 1,
    Green = 2,
    YellowAfterGreen = 3,
    Count = 4
};

TrafficLightColors GetNextColor(const TrafficLightColors & current);
#endif // TRAFFICLIGHTCOLORS_H
