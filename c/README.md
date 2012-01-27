This example will:

- compute the distance between two GPS coordinates
- compute the initial bearing when going from one coordinate to another
- compute the final bearing when going from one coordinate to another

This example uses coordinates using latitude/longitude, as opposed to MGRS or UTM.

All algorithms come from [Movable Type Scripts](http://www.movable-type.co.uk/scripts/latlong.html).

### About the code ###

In the example, there are three functions:

- haversine- compute the distance between two points using the haversine formula
- bearingTo- compute the initial bearing when going from a point to another
- bearingFrom- compute the final bearing when going from a point to another

`bearingTo` and `bearingFrom` give the starting and ending bearing respectively. Since the earth is not flat, a person cannot move straight from one point to another, but instead follows an arc.

### Command-line usage ###

The example code takes exactly four arguments: lat1, lon1, lat2, lon2

- lat1- latitude of first point
- lon1- longitude of first point
- lat2- latitude of second point
- lon2- longitude of second point

When computations have finished, it will output something like this:

> Distance: 124 km
> 
> Initial bearing: 48°
> 
> Final bearing: 50°

The values used internally are floats, so the values output will also be floats. Integers are used above for clarity.
