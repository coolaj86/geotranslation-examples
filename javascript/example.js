(function () {
    'use strict';

    var RADIUS = 6371;

    function toRad(angle) {
        return angle * Math.PI / 180;
    }

    function toDeg(angle) {
        return angle * 180 / Math.PI;
    }

    function bearingTo(lat1, lon1, lat2, lon2) {
        var dLon = toRad(lon2 - lon1),
            x, y, bearing;

        lat1 = toRad(lat1);
        lat2 = toRad(lat2);

        y = Math.sin(dLon) * Math.cos(lat2);
        x = Math.cos(lat1) * Math.sin(lat2) - Math.sin(lat1) * Math.cos(lat2) * Math.cos(dLon);

        bearing = toDeg(Math.atan2(y, x));

        if (bearing < 0) {
            bearing += 360;
        }

        return bearing;
    }

    function bearingFrom(lat1, lon1, lat2, lon2) {
        var bearing = bearingTo(lat1, lon1, lat2, lon2);

        bearing += 180;
        if (bearing > 360) {
            bearing -= 360;
        }

        return bearing;
    }

    function haversine(lat1, lon1, lat2, lon2) {
        var dLat = toRad(lat2 - lat1),
            dLon = toRad(lon2 - lon1),
            a, c, distance;

        lat1 = toRad(lat1);
        lat2 = toRad(lat2);

        a = Math.sin(dLat / 2) * Math.sin(dLat / 2) + Math.sin(dLon / 2) * Math.sin(dLon / 2) * Math.cos(lat1) * Math.cos(lat2);
        c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
        distance = RADIUS * c;

        return distance;
    }

    function main(args) {
        // grab the command-line parameters
        var lat1 = parseFloat(args[0]),
            lon1 = parseFloat(args[1]),
            lat2 = parseFloat(args[2]),
            lon2 = parseFloat(args[3]);

        console.log("Distance: " + haversine(lat1, lon1, lat2, lon2) + " km");
        console.log("Initial bearing: " + bearingTo(lat1, lon1, lat2, lon2) + "°");
        console.log("Final bearing: " + bearingFrom(lat2, lon2, lat1, lon1) + "°");
    }

    if (process.argv.length !== 6) {
        console.log("Usage: haversine <latitude1> <longitude1> <latitute2> <longitude2>");
        return;
    }

    main(process.argv.slice(2));
}());
