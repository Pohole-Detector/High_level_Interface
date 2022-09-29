
#ifndef GPS_FUNC_H
#define GPS_FUNC_H


/*
 * Module Interface for GPS Interface.
 * 
 * Deals with sending out and receiving signals in regards of the vehicle's location for purposes of sending
 * coordinates to better locate potholes and and send to 
 * 
 */
class GPS
    {
    char buffer[ 256 ]; // Place where replies, sending buffer lives -> Mainily for 
public:

    bool enableGPS( const bool onoff ); // true == on, false == off
    int8_t GPSstatus( );
    uint8_t getGPS( const uint8_t arg, char const * const buffer, const uint8_t maxbuff );
    bool getGPS( float const * const lat, float const * const lon, float const * const speed_kph, float const * const heading, float const * const altitude,
                              uint16_t const * const year = NULL, uint8_t const * const month = NULL, uint8_t *day = NULL, uint8_t *hour = NULL, uint8_t *min = NULL, float *sec = NULL);
    
    bool enableNTPTimeSync(boolean onoff, FONAFlashStringPtr ntpserver=0);
    bool getTime(char *buff, uint16_t maxlen);
    }; // end GPS

#endif // end GPS_FUNC_H