public class Haversine {
    public static void main(String[] args) {
        if (args.length != 4) {
            System.out.println("Usage: example <latitude1> <longitude1> <latitute2> <longitude2>");
            return;
        }

        double lat1 = Double.parseDouble(args[0]);
        double lon1 = Double.parseDouble(args[1]);
        double lat2 = Double.parseDouble(args[2]);
        double lon2 = Double.parseDouble(args[3]);

        System.out.println("Distance: " + Geotranslation.haversine(lat1, lon1, lat2, lon2) + " km");
        System.out.println("Initial bearing: " + Geotranslation.bearingTo(lat1, lon1, lat2, lon2) + "°");
        System.out.println("Final bearing: " + Geotranslation.bearingFrom(lat2, lon2, lat1, lon1) + "°");
    }
}
