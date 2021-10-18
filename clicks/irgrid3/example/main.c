/*!
 * @file main.c
 * @brief IRGrid3 Click example
 *
 * # Description
 * The demo application displays a reading of ambient temperature and 
 * a 32x24 pixel object temperature matrix.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configures the click and log objects and sets the click default configuration.
 * 
 * ## Application Task  
 * Reads the temperature of all pixels every 500ms 
 * and displays it on USB UART in a form of a 32x24 matrix.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "irgrid3.h"

static irgrid3_t irgrid3;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgrid3_cfg_t irgrid3_cfg;  /**< Click config object. */

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
    log_info( &logger, "---- Application Init ----" );

    // Click initialization.
    irgrid3_cfg_setup( &irgrid3_cfg );
    IRGRID3_MAP_MIKROBUS( irgrid3_cfg, MIKROBUS_1 );
    err_t init_flag = irgrid3_init( &irgrid3, &irgrid3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    irgrid3_default_cfg ( &irgrid3 );
    Delay_ms( 1000 );
    log_info( &logger, "---- Start measurement ----" );
}

void application_task ( void ) {
    float px_matrix[ 768 ];
    float temp_ambient;

    irgrid3_get_pixel_temperature( &irgrid3, &temp_ambient, px_matrix );

    log_printf( &logger, "\r\n>> Pixel temperature matrix 32x24 <<\r\n" );
    for ( uint16_t cnt = 1 ; cnt < 769 ; cnt++) {
        log_printf( &logger, "%.2f", px_matrix[ cnt - 1 ] );
        if ( ( ( cnt % 32 ) == 0 ) ) {
            log_printf( &logger, "\r\n" );
        } else {
            log_printf( &logger, " | " );
        }
    }
    log_printf( &logger, "\r\n** Ambient (sensor) temperature is %.2f Celsius\r\n", temp_ambient );
    Delay_ms( 500 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
