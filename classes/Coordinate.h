#ifndef AED_FLIGHT_COORDINATE_H
#define AED_FLIGHT_COORDINATE_H

class Coordinate {
    private:
        float latitude;
        float longitude;
    public:
        Coordinate();
        Coordinate(float latitude, float longitude);
        float getLatitude() const;
        float getLongitude() const;
};


#endif //AED_FLIGHT_COORDINATE_H
