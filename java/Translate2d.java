public class Translate2d {
    public static void main(String[] args) {
        if (args.length != 4) {
            System.out.println("Usage: translate2d <latitude> <longitude> <distance> <bearing>");
            return;
        }

        double lat = Double.parseDouble(args[0]);
        double lon = Double.parseDouble(args[1]);
        double distance = Double.parseDouble(args[2]);
        double bearing = Double.parseDouble(args[3]);

        LatLong ll = Geotranslation.translate2d(lat, lon, distance, bearing);

        System.out.println(String.format("Starting point: %f,%f", lat, lon));
        System.out.println(String.format("Ending point: %f,%f", ll.getLatitude(), ll.getLongitude()));
    }
}
