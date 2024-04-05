/*!
 * @file main.c
 * @brief DTMFDecoder Click example
 *
 * # Description
 * This example shows the basic tone capture of
 * DTMF frequencies, decoding and representing
 * them on the UART LOG.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C and UART LOG drivers and powers
 * on the device.
 *
 * ## Application Task
 * Checks the delayed steering for incoming tones
 * and decoding them on the UART LOG. Holding the
 * same key will recognize multiple tone generation,
 * the tone register delay constant can be set to
 * adjust the tolerance.
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "dtmfdecoder.h"

static dtmfdecoder_t dtmfdecoder;
static log_t logger;

static const uint16_t tone_register_delay = 200;

void application_init ( void ) {
    log_cfg_t log_cfg;                  /**< Logger config object. */
    dtmfdecoder_cfg_t dtmfdecoder_cfg;  /**< Click config object. */

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

    dtmfdecoder_cfg_setup( &dtmfdecoder_cfg );
    DTMFDECODER_MAP_MIKROBUS( dtmfdecoder_cfg, MIKROBUS_1 );
    err_t init_flag = dtmfdecoder_init( &dtmfdecoder, &dtmfdecoder_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    dtmfdecoder_default_cfg ( &dtmfdecoder );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    uint8_t result;
    
    if ( dtmfdecoder_delayed_steering_check( &dtmfdecoder ) ) {
        result = dtmfdecoder_tone_read( &dtmfdecoder );
        log_printf( &logger, " Detected key tone:\t%c\r\n", result );
        Delay_ms ( tone_register_delay );
    }
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
