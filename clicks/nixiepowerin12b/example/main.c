/*!
 * @file main.c
 * @brief Nixie Power IN-12B Click example
 *
 * # Description
 * This example demonstrates the use of Nixie Power IN-12B Click board by displaying
 * digits from 0 to 9 in sequence and then setting a comma indicator.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Sequentially displays digits 0 through 9 on a IN-12B display, with a 1-second delay
 * between each digit. After displaying all digits, it clears the digits and enables
 * a comma indicator on the display. Each operation is logged on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nixiepowerin12b.h"

static nixiepowerin12b_t nixiepowerin12b;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nixiepowerin12b_cfg_t nixiepowerin12b_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    nixiepowerin12b_cfg_setup( &nixiepowerin12b_cfg );
    NIXIEPOWERIN12B_MAP_MIKROBUS( nixiepowerin12b_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == nixiepowerin12b_init( &nixiepowerin12b, &nixiepowerin12b_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NIXIEPOWERIN12B_ERROR == nixiepowerin12b_default_cfg ( &nixiepowerin12b ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t digit = NIXIEPOWERIN12B_DIGIT_0; digit <= NIXIEPOWERIN12B_DIGIT_9; digit++ )
    {
        if ( NIXIEPOWERIN12B_OK == nixiepowerin12b_set_digit ( &nixiepowerin12b, 
                                                               digit, 
                                                               NIXIEPOWERIN12B_COMMA_CLEAR ) )
        {
            log_printf ( &logger, " Digit %u\r\n", ( uint16_t ) digit );
        }
        Delay_ms ( 1000 );
    }
    if ( NIXIEPOWERIN12B_OK == nixiepowerin12b_set_digit ( &nixiepowerin12b, 
                                                           NIXIEPOWERIN12B_DIGIT_NONE, 
                                                           NIXIEPOWERIN12B_COMMA_SET ) )
    {
        log_printf ( &logger, " Comma\r\n" );
    }
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
