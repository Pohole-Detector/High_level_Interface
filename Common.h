

#ifndef COMMON_COMP_H
#define COMMON_COMP_H

#include <stdint.h>

/*
 * These are a Library of Functions used to raise the level of abstraction for common used constructs (pins)
 * The idea here is to isolate these into abstract Versions such that it limits the need to change certain functions
 * (i.e. what functions are used pins interact with GPIO pins). That way if we decide to use a different MCU
 * like porting from Arduino to RPI, all we have to change are the implementation of the functions (so the .c or .cpp files).
 * That way less time is spent changing our code to be compatiable with different platforms.
 */

enum class GPIO_MODE
    {
    GPIO_INPUT,
    GPIO_OUTPUT,
    GPIO_ALT_FUNC,
    GPIO_ANALOG   // reset mode
    };

enum class GPIO_PULLx
    {
    GPIO_PIN_PULL_NON, 
    GPIO_PIN_PULL_UP, 
    GPIO_PIN_PULL_DOWN
    };

enum class GPIO_STATE_t
    {
    LOW,
    HIGH
    };

class GPIO_t
    {
    GPIO_MODE pin_mode;
    char        port;  // Might be not needed 
    GPIO_STATE_t state : 1; // Used to hold that state (and read it faster perhaps)
                       // (This might not be needed since there should be a register and functions that handles the reading.)
    uint8_t  pin_num;
public:

    /*
     * Initialize GPIO pin (with specific state and pin number)
     */
    GPIO_t ( const uint8_t _pin_num, const GPIO_MODE mode, const GPIO_PULLx def_state );
    /*
     * Reconfigure / initialize GPIO pin. This allows to possibly reconfigure pin to be something else
     * (which shouldn't really be necessary but possible)
     */
    void config_gpio( const uint8_t _pin_num, const GPIO_MODE mode, const GPIO_PULLx def_state  );
    GPIO_MODE read_gpio_mode( );
    void write_gpio( const uint8_t state );
    GPIO_STATE_t read_gpio( const uint8_t state );
    };

/*
 * Class for UARTS module.
 * 
 */
class UART_t
    {
    uint32_t baud_rate;
    GPIO_t tx_pin, rx_pin;
    char buff[ 1024 ]; // Potential Buffer for 
public:
    UART_t( const uint32_t _baud_rate, const GPIO_t _tx_pin, const GPIO_t _rx_pin );
    UART_t( UART_t&& uarts );

    // Prohibit Copy mechanisms (doesn't make sense)
    UART_t( const UART_t& uarts ) = delete;
    UART_t& operator=(const UART_t& uarts ) = delete;

    void set_baud_rate( const uint32_t _baud_rate );
    void putchar( const char c );
    void put_chars( char const *cstr );

    // Reads up to len bytes (and writes to cstr)
    uint32_t read_bytes(  char const *cstr, const uint16_t len );
    };
#endif