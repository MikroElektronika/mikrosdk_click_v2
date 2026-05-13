/*!
 * @file main.c
 * @brief IR Sense 7 Click example
 *
 * # Description
 * This example demonstrates the use of the IR Sense 7 Click board for
 * measuring ambient and object temperature using an infrared sensor.
 * The application reads sensor data from RAM and calculates temperature values.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and IR Sense 7 Click driver, applies the default
 * configuration, and reads device identification and EEPROM data.
 *
 * ## Application Task
 * Periodically reads sensor data and calculates ambient and object
 * temperatures, then logs the results to the serial terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "irsense7.h"

#ifndef MIKROBUS_POSITION_IRSENSE7
    #define MIKROBUS_POSITION_IRSENSE7 MIKROBUS_1
#endif

static irsense7_t irsense7;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irsense7_cfg_t irsense7_cfg;  /**< Click config object. */

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
    irsense7_cfg_setup( &irsense7_cfg );
    IRSENSE7_MAP_MIKROBUS( irsense7_cfg, MIKROBUS_POSITION_IRSENSE7 );
    if ( I2C_MASTER_ERROR == irsense7_init( &irsense7, &irsense7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRSENSE7_ERROR == irsense7_default_cfg ( &irsense7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Unique ID: 0x%.4X%.4X%.4X\r\n", 
                irsense7.ee_data[ IRSENSE7_IDX_ID2 ], 
                irsense7.ee_data[ IRSENSE7_IDX_ID1 ], 
                irsense7.ee_data[ IRSENSE7_IDX_ID0 ] );
    log_printf( &logger, " Product Code: 0x%.4X\r\n", 
                irsense7.ee_data[ IRSENSE7_IDX_EE_PRODUCT_CODE ] );
    log_printf( &logger, " EEPROM Version: 0x%.4X\r\n", 
                irsense7.ee_data[ IRSENSE7_IDX_EE_VERSION ] );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( IRSENSE7_OK == irsense7_read_ram ( &irsense7 ) )
    {
        log_printf ( &logger, " Ambient temp: %.2f\r\n", irsense7_calculate_amb_temp ( &irsense7 ) );
        log_printf ( &logger, " Object temp: %.2f\r\n\n", irsense7_calculate_obj_temp ( &irsense7 ) );
    }
    Delay_ms ( 500 );
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
