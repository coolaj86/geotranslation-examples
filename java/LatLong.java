public class LatLong {
    private double lat;
    private double lon;

    public LatLong(double lat, double lon) {
        this.lat = lat;
        this.lon = lon;
    }

    public double getLatitude() {
        return this.lat;
    }

    public double getLongitude() {
        return this.lon;
    }

    public void setLatitude(double lat) {
        this.lat = lat;
    }

    public void setLongitude(double lon) {
        this.lon = lon;
    }
}
