public class Geotranslation {
    private static final double RADIUS = 6371;

    private static double[][] complete_rotation_matrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    public static double bearingTo(double lat1, double lon1, double lat2, double lon2) {
        double dLon = Math.toRadians(lon2 - lon1);

        lat1 = Math.toRadians(lat1);
        lat2 = Math.toRadians(lat2);

        double y = Math.sin(dLon) * Math.cos(lat2);
        double x = Math.cos(lat1) * Math.sin(lat2) - Math.sin(lat1) * Math.cos(lat2) * Math.cos(dLon);

        double bearing = Math.toDegrees(Math.atan2(y, x));

        if (bearing < 0) {
            bearing += 360;
        }

        return bearing;
    }

    public static double bearingFrom(double lat1, double lon1, double lat2, double lon2) {
        double bearing = bearingTo(lat1, lon1, lat2, lon2);

        bearing += 180;
        if (bearing > 360) {
            bearing -= 360;
        }

        return bearing;
    }

    public static double haversine(double lat1, double lon1, double lat2, double lon2) {
        double dLat = Math.toRadians(lat2 - lat1);
        double dLon = Math.toRadians(lon2 - lon1);

        double a, c, distance;

        lat1 = Math.toRadians(lat1);
        lat2 = Math.toRadians(lat2);

        a = Math.sin(dLat / 2) * Math.sin(dLat / 2) + Math.sin(dLon / 2) * Math.sin(dLon / 2) * Math.cos(lat1) * Math.cos(lat2);
        c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
        distance = RADIUS * c;

        return distance;
    }

    public static LatLong translate2d(double lat, double lon, double distance, double bearing) {
        double lat2, lon2;

        lat = Math.toRadians(lat);
        lon = Math.toRadians(lon);
        bearing = Math.toRadians(bearing);

        lat2 = Math.asin(Math.sin(lat)*Math.cos(distance/RADIUS) + Math.cos(lat)*Math.sin(distance/RADIUS)*Math.cos(bearing));
        lon2 = lon + Math.atan2(Math.sin(bearing)*Math.sin(distance/RADIUS)*Math.cos(lat), Math.cos(distance/RADIUS)-Math.sin(lat)*Math.sin(lat2));

        return new LatLong(Math.toDegrees(lat2), Math.toDegrees(lon2));
    }

    /**
     *    Calculates a rotation matrix for a given angle about a given axis.
     *    see http://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
     *    for reference
     */
    private static double[][] calc_single_matrix(double theta, double[] axis) {
        double[][] result = new double[3][3];

        double cos_theta, sin_theta;

        cos_theta = Math.cos(theta);
        sin_theta = Math.sin(theta);

        result[0][0] = cos_theta + axis[0]*axis[0]*(1 - cos_theta);
        result[1][0] = axis[0]*axis[1]*(1 - cos_theta) + axis[2]*sin_theta;
        result[2][0] = axis[0]*axis[2]*(1 - cos_theta) - axis[1]*sin_theta;

        result[0][1] = axis[1]*axis[0]*(1 - cos_theta) - axis[2]*sin_theta;
        result[1][1] = cos_theta + axis[1]*axis[1]*(1 - cos_theta);
        result[2][1] = axis[1]*axis[2]*(1 - cos_theta) + axis[0]*sin_theta;

        result[0][2] = axis[2]*axis[0]*(1 - cos_theta) + axis[1]*sin_theta;
        result[1][2] = axis[2]*axis[1]*(1 - cos_theta) - axis[0]*sin_theta;
        result[2][2] = cos_theta + axis[2]*axis[2]*(1 - cos_theta);

        return result;
    }

    private static double[][] multiply_matrices(double[][] left_matrix, double[][] right_matrix) {
        double[][] result = new double[3][3];

        result[0][0] = left_matrix[0][0]*right_matrix[0][0] + left_matrix[0][1]*right_matrix[1][0] + left_matrix[0][2]*right_matrix[2][0];
        result[1][0] = left_matrix[1][0]*right_matrix[0][0] + left_matrix[1][1]*right_matrix[1][0] + left_matrix[1][2]*right_matrix[2][0];
        result[2][0] = left_matrix[2][0]*right_matrix[0][0] + left_matrix[2][1]*right_matrix[1][0] + left_matrix[2][2]*right_matrix[2][0];

        result[0][1] = left_matrix[0][0]*right_matrix[0][1] + left_matrix[0][1]*right_matrix[1][1] + left_matrix[0][2]*right_matrix[2][1];
        result[1][1] = left_matrix[1][0]*right_matrix[0][1] + left_matrix[1][1]*right_matrix[1][1] + left_matrix[1][2]*right_matrix[2][1];
        result[2][1] = left_matrix[2][0]*right_matrix[0][1] + left_matrix[2][1]*right_matrix[1][1] + left_matrix[2][2]*right_matrix[2][1];

        result[0][2] = left_matrix[0][0]*right_matrix[0][2] + left_matrix[0][1]*right_matrix[1][2] + left_matrix[0][2]*right_matrix[2][2];
        result[1][2] = left_matrix[1][0]*right_matrix[0][2] + left_matrix[1][1]*right_matrix[1][2] + left_matrix[1][2]*right_matrix[2][2];
        result[2][2] = left_matrix[2][0]*right_matrix[0][2] + left_matrix[2][1]*right_matrix[1][2] + left_matrix[2][2]*right_matrix[2][2];

        return result;
    }

    private static double[][] copy_matrix(double[][] source) {
        double[][] result = new double[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result[i][j] = source[i][j];
            }
        }

        return result;
    }

    public static double[] rotate_coordinates(double[] init_points) {
        double[] end_points = new double[3];

        end_points[0] = complete_rotation_matrix[0][0]*init_points[0] + complete_rotation_matrix[0][1]*init_points[1] + complete_rotation_matrix[0][2]*init_points[2];
        end_points[1] = complete_rotation_matrix[1][0]*init_points[0] + complete_rotation_matrix[1][1]*init_points[1] + complete_rotation_matrix[1][2]*init_points[2];
        end_points[2] = complete_rotation_matrix[2][0]*init_points[0] + complete_rotation_matrix[2][1]*init_points[1] + complete_rotation_matrix[2][2]*init_points[2];

        return end_points;
    }

    public static void initialize_rotation_matrix(double yaw, double pitch, double roll) {
        double[] rel_axis = new double[3];
        double[] abs_axis = new double[3];
        double[][] intermediate = new double[3][3];
        double[][] next_rotation = new double[3][3];

        yaw = Math.toRadians(yaw);
        pitch = Math.toRadians(pitch);
        roll = Math.toRadians(roll);

        // first apply the yaw rotation about the z axis
        abs_axis[0] = 0;
        abs_axis[1] = 0;
        abs_axis[2] = 1;
        next_rotation = calc_single_matrix(yaw, abs_axis);
        complete_rotation_matrix = copy_matrix(next_rotation);

        // then apply the pitch rotation about what used to be the x axis
        rel_axis[0] = 1;
        rel_axis[1] = 0;
        rel_axis[2] = 0;
        abs_axis = rotate_coordinates(rel_axis);                 // find out what the axis is now with the rotations we've already done
        next_rotation = calc_single_matrix(pitch, abs_axis);     // calculate the rotation matrix we need to apply next
        intermediate = copy_matrix(complete_rotation_matrix);    // copy the current matrix so we can store the result there
        complete_rotation_matrix = multiply_matrices(next_rotation, intermediate); // apply to next rotation to the complete matrix

        // then apply the roll rotation about what used to be the y axis
        rel_axis[0] = 0;
        rel_axis[1] = 1;
        rel_axis[2] = 0;
        abs_axis = rotate_coordinates(rel_axis);                 // find out what the axis is now with the rotations we've already done
        next_rotation = calc_single_matrix(roll, abs_axis);    // calculate the rotation matrix we need to apply next
        intermediate = copy_matrix(complete_rotation_matrix);    // copy the current matrix so we can store the result there
        complete_rotation_matrix = multiply_matrices(next_rotation, intermediate); // apply to next rotation to the complete matrix
    }

    public static LatLong translateCoord(double lat, double lon, double dist_x, double dist_y) {
        double bearing = Math.atan(dist_x/dist_y);
        double distance = Math.sqrt(dist_x*dist_x + dist_y*dist_y);

        return translate2d(lat, lon, distance, Math.toDegrees(bearing));
    }
}
