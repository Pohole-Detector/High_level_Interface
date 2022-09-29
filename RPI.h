
#ifndef RPI_TOP_H
#define RPI_TOP_H
#include <stdint.h> // all uint*_t and int*_t types
#include <stddef.h> //for size_t
#include "Common.h"
#include "GPS.h"

#define DEFAULT_TIMEOUT_MS 100
#define NUM_PIXELS         10000 // Number of pixels in the array 

struct Picture
    {
    char buff[NUM_PIXELS];
    double dist; // distance of perceived 
    };


/*
 * RPI Interface for Interface.
 * 
 * A top level module that deals with image processing (CV), and genearl system intialization of our modules,
 * 
 * This module includes: The camera, IR sensors, 
 * Deals with sending out and receiving signals in regards of the vehicle's location for purposes of sending
 * coordinates to better locate potholes and and send to 
 * 
 */
class RPI
    {
    Bluetooth_Module ble;
    Cellular_Module cell;           // Interact with cellular module and send out signals
    GPS gps_mod;
    // IR sensor -> To be added...

    void task_monitor_for_pothole( ); // Can be embedded in a task (RTOS)

    /*
     * Function does the processing of the picture. 
     * Returns true if based on picture, looks like a pothole.
     */
    bool process_picture( const Picture& ); 
public:
    RPI( );

    RPI( const RPI& ) = delete;
    RPI& operator=( const RPI& ) = delete;

    void start( );

    }; // End RPI

class Cellular_Module
    {
    char buffer[ 256 ]; // Place where replies, sending buffer lives -> Mainily for 

    // Helper functions that may aid in the implementation of the Module
    /*
     * Waits until bytes are available to read in. (Since there can be some latency incurred while sending some signal)
     * Might want to embed into an interrupt so it can be done in parallel (or by some other componenet)
     */
    int available( );
    size_t write( );

    bool HTTP_setup( char const *url );
    void flushInput();
    uint16_t readRaw( const uint16_t b );
    uint8_t readline( const uint16_t timeout = DEFAULT_TIMEOUT_MS, const bool multiline = false );
    uint8_t getReply( const char *send, const uint16_t timeout = DEFAULT_TIMEOUT_MS);
public:
    Cellular_Module( /* Pins possibly required */ );

    // HTTP high level interface (for database possiblity)
    bool HTTP_GET_start( char const *url, uint16_t *status, uint16_t *datalen );
    void HTTP_GET_end( );
    bool HTTP_POST_start( char *url, char const * contenttype, const uint8_t *postdata, uint16_t postdatalen,  uint16_t *status, uint16_t *datalen );
    void HTTP_POST_end( );
    void setUserAgent( char const * useragent );
    };


// For sending to speaker system
/*
 * Module for Bluetooth. Will intialize pins that will be utilized properly
 */
class Bluetooth_Module
    {
    // Likely Will use UARTs to interface.
    UART_t uart_port;

public:
    Bluetooth_Module( const uint16_t baud_rate, const GPIO_t _tx_pin, const GPIO_t _rx_pin );
    Bluetooth_Module( UART_t&& uarts_port );

    void send_port( char const * str );
    // Receive up to a certain len.
    void rec( char * const buff, const uint16_t len );
    };

#endif // end RPI_TOP_H