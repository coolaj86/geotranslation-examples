public class Translate3d {
    public static void main(String[] args) {
        double lat, lon, yaw, pitch, roll, distance, angle, dist_x, dist_y;
        double[] input = new double[3];

        if (args.length != 7) {
            System.out.println("Usage: translate3d <latitude> <longitude> <yaw> <pitch> <roll> <distance> <bearing>");
            return;
        }

        lat = Double.parseDouble(args[0]);
        lon = Double.parseDouble(args[1]);
        yaw = Double.parseDouble(args[2]);
        pitch = Double.parseDouble(args[3]);
        roll = Double.parseDouble(args[4]);
        distance = Double.parseDouble(args[5]);
        angle = Double.parseDouble(args[6]);

        dist_x = Math.sin(Math.toRadians(angle)) * distance;
        dist_y = Math.cos(Math.toRadians(angle)) * distance;

        input[0] = dist_x;
        input[1] = dist_y;
        input[2] = 0;

        // yaw is backwards from what you'd expect, so we reverse it
        Geotranslation.initialize_rotation_matrix(yaw * -1, pitch, roll);

        double[] res = Geotranslation.rotate_coordinates(input);

        System.out.println(String.format("New X: %f", res[0]));
        System.out.println(String.format("New Y: %f", res[1]));
        System.out.println(String.format("New Z: %f", res[2]));

        LatLong ll = Geotranslation.translateCoord(lat, lon, res[0], res[1]);

        System.out.println(String.format("New Coord: %f,%f", ll.getLatitude(), ll.getLongitude()));
    }
}
