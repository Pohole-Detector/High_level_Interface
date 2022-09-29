

#ifndef CAMERA_H
#define CAMERA_H

#include <stddef.h> // for size_t
#include "Common.h"


class Oak_D_Camera
    {
    char * const pictures;
    GPIO_t done_pin; // Potential pin used for interrupts.
    // Any Hardware Modules and GPIO pins to help communicate with device.
public:
    Oak_D_Camera( /*Pins and Modules*/ );

    // Potentially to request the camera to take a picture
    void take_picture( ); // Can be embedded in a task to continously do so.

    // Pass in a buffer that will receive a picture 
    // (probably copied from an internal buffer)
    void receive_picture( const char *buff, const size_t size, const bool blocking );

    }; // end Oak_D_Camera
#endif
