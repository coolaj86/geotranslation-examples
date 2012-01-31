#ifndef __GEOTRANSLATION_H__
#define __GEOTRANSLATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define RADIUS 6371

void translate2d(double lat, double lon, double distance, double bearing, double* pLat, double* pLon);

void calc_single_matrix(double result[][3], double theta, double* axis);
void multiply_matrices(double result[][3], double left_matrix[][3], double right_matrix[][3]);
void copy_matrix(double destination[][3], double source[][3]);
void rotate_coordinates(double* end_points, double* init_points);
void initialize_rotation_matrix(double yaw, double pitch, double roll);
void translateCoord(double lat, double lon, double dist_x, double dist_y, double* pLat, double* pLon);

double toRad(double angle);
double toDeg(double angle);

double bearingTo(double lat1, double lon1, double lat2, double lon2);
double bearingFrom(double lat1, double lon1, double lat2, double lon2);

double haversine(double lat1, double lon1, double lat2, double lon2);

#endif
