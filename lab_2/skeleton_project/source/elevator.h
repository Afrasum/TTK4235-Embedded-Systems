#include <iostream>
#include <vector>


typedef struct {

    bool stopped;
    int dir;
    bool door;
    int floor;
    int floor_stops[4];
    bool sensor;
    std::vector<bool> vil_opp;
    std::vector<bool> vil_ned;


} elevator;





