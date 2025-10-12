#include "trafficlightcolors.h"

TrafficLightColors GetNextColor(const TrafficLightColors & current)
{
    int next = static_cast<int>(current) + 1;
    TrafficLightColors nextColor = static_cast<TrafficLightColors>(next);

    return nextColor == TrafficLightColors::Count
               ? TrafficLightColors::Red
               : nextColor;
}
