#ifndef AED_FLIGHT_COORDINATE_H
#define AED_FLIGHT_COORDINATE_H

class Coordinate {
    private:
        double latitude;
        double longitude;
    public:
        Coordinate();
        Coordinate(double latitude, double longitude);
        double getLatitude() const;
        double getLongitude() const;
};


#endif //AED_FLIGHT_COORDINATE_H
