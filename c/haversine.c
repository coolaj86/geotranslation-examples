#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "geotranslation.h"

int main(int argc, char** argv) {
    double lat1, lon1, lat2, lon2;
    double distance;

    if (argc != 5) {
        printf("Usage: haversine <latitude1> <longitude1> <latitute2> <longitude2>\n");
        return -1;
    }

    // grab the command-line parameters
    lat1 = atof(argv[1]);
    lon1 = atof(argv[2]);
    lat2 = atof(argv[3]);
    lon2 = atof(argv[4]);

    distance = haversine(lat1, lon1, lat2, lon2);

    printf("Distance: %f km\n", distance);
    printf("Initial bearing: %f°\n", bearingTo(lat1, lon1, lat2, lon2));
    printf("Final bearing: %f°\n", bearingFrom(lat2, lon2, lat1, lon1));

    return 0;
}
