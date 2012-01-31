#include "geotranslation.h"

int main(int argc, char** argv) {
    double lat, lon, yaw, pitch, roll, distance, angle, dist_x, dist_y;
    double newLat, newLon;
    double res[3];
    double input[3];

    if (argc != 8) {
        printf("Usage: translate3d <latitude> <longitude> <yaw> <pitch> <roll> <distance> <bearing>\n");
        return -1;
    }

    lat = atof(argv[1]);
    lon = atof(argv[2]);
    yaw = atof(argv[3]);
    pitch = atof(argv[4]);
    roll = atof(argv[5]);
    distance = atof(argv[6]);
    angle = atof(argv[7]);

    dist_x = sin(toRad(angle)) * distance;
    dist_y = cos(toRad(angle)) * distance;

    input[0] = dist_x;
    input[1] = dist_y;
    input[2] = 0;

	// yaw is backwards from what you'd expect, so we reverse it
    initialize_rotation_matrix(yaw*-1, pitch, roll);

    rotate_coordinates(res, input);

    printf("New X: %f\n", res[0]);
    printf("New Y: %f\n", res[1]);
    printf("New Z: %f\n", res[2]);

    translateCoord(lat, lon, res[0], res[1], &newLat, &newLon);

    printf("New Coord: %f,%f\n", newLat, newLon);

    return 0;
}
