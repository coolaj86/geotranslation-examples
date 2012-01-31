#include "geotranslation.h"

int main(int argc, char** argv) {
    double lat, lon, distance, bearing, lat2, lon2;

    if (argc != 5) {
        printf("Usage: translate2d <latitude> <longitude> <distance> <bearing>\n");
        return -1;
    }

    lat = atof(argv[1]);
    lon = atof(argv[2]);
    distance = atof(argv[3]);
    bearing = atof(argv[4]);

    translate2d(lat, lon, distance, bearing, &lat2, &lon2);

    printf("Starting point: %f,%f\n", lat, lon);
    printf("Ending point: %f,%f\n", lat2, lon2);

    return 0;
}
