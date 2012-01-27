#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RADIUS 6371

double toRad(double angle) {
    return angle * M_PI / 180;
}

double toDeg(double angle) {
    return angle * 180 / M_PI;
}

double bearingTo(double lat1, double lon1, double lat2, double lon2) {
    double dLon = toRad(lon2 - lon1);

    lat1 = toRad(lat1);
    lat2 = toRad(lat2);

    double y = sin(dLon) * cos(lat2);
    double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dLon);

    double bearing = toDeg(atan2(y, x));

    if (bearing < 0) {
        bearing += 360;
    }

    return bearing;
}

double bearingFrom(double lat1, double lon1, double lat2, double lon2) {
    double bearing = bearingTo(lat1, lon1, lat2, lon2);

    bearing += 180;
    if (bearing > 360) {
        bearing -= 360;
    }

    return bearing;
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = toRad(lat2 - lat1);
    double dLon = toRad(lon2 - lon1);

    double a, c, distance;

    lat1 = toRad(lat1);
    lat2 = toRad(lat2);

    a = sin(dLat / 2) * sin(dLat / 2) + sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2);
    c = 2 * atan2(sqrt(a), sqrt(1 - a));
    distance = RADIUS * c;

    return distance;
}

int main(int argc, char** argv) {
    double lat1, lon1, lat2, lon2;

    if (argc != 5) {
        printf("Usage: haversine <latitude1> <longitude1> <latitute2> <longitude2>\n");
        return -1;
    }

    // grab the command-line parameters
    lat1 = atof(argv[1]);
    lon1 = atof(argv[2]);
    lat2 = atof(argv[3]);
    lon2 = atof(argv[4]);

    printf("Distance: %f km\n", haversine(lat1, lon1, lat2, lon2));
    printf("Initial bearing: %f°\n", bearingTo(lat1, lon1, lat2, lon2));
    printf("Final bearing: %f°\n", bearingFrom(lat2, lon2, lat1, lon1));

    return 0;
}
