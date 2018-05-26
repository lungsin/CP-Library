/*
Converts from rectangular coordinates to latitude/longitude and vice versa. Uses degrees (not radians).
*/

#include <iostream> 
#include <cmath>

using namespace std;

struct LatLong {
    double r, lat, lon;
};

struct rect {
    double x, y, z;
};

LatLong convert (rect &P) {
    LatLong Q;
    Q.r = sqrt(P.x*P.x+P.y*P.y+P.z*P.z);
    Q.lat = 180/M_PI*asin(P.z/Q.r);
    Q.lon = 180/M_PI*acos(P.x/sqrt(P.x*P.x + P.y*P.y));
    
    return Q;
}

rect convert(LatLong &Q) {
    rect P;
    P.x = Q.r*cos(Q.lon*M_PI/180)*cos(Q.lat*M_PI/180); 
    P.y = Q.r*sin(Q.lon*M_PI/180)*cos(Q.lat*M_PI/180); 
    P.z = Q.r*sin(Q.lat*M_PI/180);
    
    return P;
}

int main() {
    if (flag) continue;
    rect A; LatLong B;
    
    A.x = -1.0; A.y = 2.0; A.z = -3.0;
    
    B = convert(A);
    cout << B.r << " " << B.lat << " " << B.lon << endl;
    
    A = convert(B);
    cout << A.x << " " << A.y << " " << A.z << endl;
}

#include <math.h>
#include <cmath> 
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / M_PI);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


