#include "geotranslation.h"

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

void translate2d(double lat, double lon, double distance, double bearing, double* pLat, double* pLon) {
    double lat2, lon2;

    lat = toRad(lat);
    lon = toRad(lon);
    bearing = toRad(bearing);

    lat2 = asin(sin(lat)*cos(distance/RADIUS) + cos(lat)*sin(distance/RADIUS)*cos(bearing));
    lon2 = lon + atan2(sin(bearing)*sin(distance/RADIUS)*cos(lat), cos(distance/RADIUS)-sin(lat)*sin(lat2));

    *pLat = toDeg(lat2);
    *pLon = toDeg(lon2);
}

double complete_rotation_matrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

/**
 *  Calculates a rotation matrix for a given angle about a given axis.
 *  see http://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
 *  for reference
 */
void calc_single_matrix(double result[][3], double theta, double* axis) {
  double cos_theta, sin_theta;

  cos_theta = cos(theta);
  sin_theta = sin(theta);

  result[0][0] = cos_theta + axis[0]*axis[0]*(1 - cos_theta);
  result[1][0] = axis[0]*axis[1]*(1 - cos_theta) + axis[2]*sin_theta;
  result[2][0] = axis[0]*axis[2]*(1 - cos_theta) - axis[1]*sin_theta;

  result[0][1] = axis[1]*axis[0]*(1 - cos_theta) - axis[2]*sin_theta;
  result[1][1] = cos_theta + axis[1]*axis[1]*(1 - cos_theta);
  result[2][1] = axis[1]*axis[2]*(1 - cos_theta) + axis[0]*sin_theta;

  result[0][2] = axis[2]*axis[0]*(1 - cos_theta) + axis[1]*sin_theta;
  result[1][2] = axis[2]*axis[1]*(1 - cos_theta) - axis[0]*sin_theta;
  result[2][2] = cos_theta + axis[2]*axis[2]*(1 - cos_theta);
}

void multiply_matrices(double result[][3], double left_matrix[][3], double right_matrix[][3]) {
  result[0][0] = left_matrix[0][0]*right_matrix[0][0] + left_matrix[0][1]*right_matrix[1][0] + left_matrix[0][2]*right_matrix[2][0];
  result[1][0] = left_matrix[1][0]*right_matrix[0][0] + left_matrix[1][1]*right_matrix[1][0] + left_matrix[1][2]*right_matrix[2][0];
  result[2][0] = left_matrix[2][0]*right_matrix[0][0] + left_matrix[2][1]*right_matrix[1][0] + left_matrix[2][2]*right_matrix[2][0];

  result[0][1] = left_matrix[0][0]*right_matrix[0][1] + left_matrix[0][1]*right_matrix[1][1] + left_matrix[0][2]*right_matrix[2][1];
  result[1][1] = left_matrix[1][0]*right_matrix[0][1] + left_matrix[1][1]*right_matrix[1][1] + left_matrix[1][2]*right_matrix[2][1];
  result[2][1] = left_matrix[2][0]*right_matrix[0][1] + left_matrix[2][1]*right_matrix[1][1] + left_matrix[2][2]*right_matrix[2][1];

  result[0][2] = left_matrix[0][0]*right_matrix[0][2] + left_matrix[0][1]*right_matrix[1][2] + left_matrix[0][2]*right_matrix[2][2];
  result[1][2] = left_matrix[1][0]*right_matrix[0][2] + left_matrix[1][1]*right_matrix[1][2] + left_matrix[1][2]*right_matrix[2][2];
  result[2][2] = left_matrix[2][0]*right_matrix[0][2] + left_matrix[2][1]*right_matrix[1][2] + left_matrix[2][2]*right_matrix[2][2];
}

void copy_matrix(double destination[][3], double source[][3]) {
  destination[0][0] = source[0][0];
  destination[0][1] = source[0][1];
  destination[0][2] = source[0][2];

  destination[1][0] = source[1][0];
  destination[1][1] = source[1][1];
  destination[1][2] = source[1][2];

  destination[2][0] = source[2][0];
  destination[2][1] = source[2][1];
  destination[2][2] = source[2][2];
}

void rotate_coordinates(double* end_points, double* init_points) {
  end_points[0] = complete_rotation_matrix[0][0]*init_points[0] + complete_rotation_matrix[0][1]*init_points[1] + complete_rotation_matrix[0][2]*init_points[2];
  end_points[1] = complete_rotation_matrix[1][0]*init_points[0] + complete_rotation_matrix[1][1]*init_points[1] + complete_rotation_matrix[1][2]*init_points[2];
  end_points[2] = complete_rotation_matrix[2][0]*init_points[0] + complete_rotation_matrix[2][1]*init_points[1] + complete_rotation_matrix[2][2]*init_points[2];
}

void initialize_rotation_matrix(double yaw, double pitch, double roll) {
  double rel_axis[3];
  double abs_axis[3];
  double intermediate[3][3];
  double next_rotation[3][3];

  yaw = toRad(yaw);
  pitch = toRad(pitch);
  roll = toRad(roll);

  // first apply the yaw rotation about the z axis
  abs_axis[0] = 0;
  abs_axis[1] = 0;
  abs_axis[2] = 1;
  calc_single_matrix(next_rotation, yaw, abs_axis);
  copy_matrix(complete_rotation_matrix, next_rotation);

  // then apply the pitch rotation about what used to be the x axis
  rel_axis[0] = 1;
  rel_axis[1] = 0;
  rel_axis[2] = 0;
  rotate_coordinates(abs_axis, rel_axis);               // find out what the axis is now with the rotations we've already done
  calc_single_matrix(next_rotation, pitch, abs_axis);   // calculate the rotation matrix we need to apply next
  copy_matrix(intermediate, complete_rotation_matrix);  // copy the current matrix so we can store the result there
  multiply_matrices(complete_rotation_matrix, next_rotation, intermediate); // apply to next rotation to the complete matrix

  // then apply the roll rotation about what used to be the y axis
  rel_axis[0] = 0;
  rel_axis[1] = 1;
  rel_axis[2] = 0;
  rotate_coordinates(abs_axis, rel_axis);               // find out what the axis is now with the rotations we've already done
  calc_single_matrix(next_rotation, roll, abs_axis);    // calculate the rotation matrix we need to apply next
  copy_matrix(intermediate, complete_rotation_matrix);  // copy the current matrix so we can store the result there
  multiply_matrices(complete_rotation_matrix, next_rotation, intermediate); // apply to next rotation to the complete matrix
}

void translateCoord(double lat, double lon, double dist_x, double dist_y, double* pLat, double* pLon) {
    double bearing = atan(dist_x/dist_y);
    double distance = sqrt(dist_x*dist_x + dist_y*dist_y);

    translate2d(lat, lon, distance, toDeg(bearing), pLat, pLon);
}

