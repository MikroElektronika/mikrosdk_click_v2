/*!
 * @file main.c
 * @brief 6DOFIMU13 Click example
 *
 * # Description
 * This example demonstrates the use of 6DOF IMU 13 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, and sets the device default configuration.
 *
 * ## Application Task
 * Measures acceleration and magnetometer data and displays the results on the USB UART every second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c6dofimu13.h"

static c6dofimu13_t c6dofimu13;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu13_cfg_t c6dofimu13_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );

    log_info( &logger, " Application Init " );

    // Click initialization.

    c6dofimu13_cfg_setup( &c6dofimu13_cfg );
    C6DOFIMU13_MAP_MIKROBUS( c6dofimu13_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu13_init( &c6dofimu13, &c6dofimu13_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    c6dofimu13_default_cfg ( &c6dofimu13 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float acc_x, acc_y, acc_z;
    float mag_x, mag_y, mag_z;

    c6dofimu13_accel_get_data( &c6dofimu13, &acc_x, &acc_y, &acc_z );
    c6dofimu13_mag_get_data( &c6dofimu13, &mag_x, &mag_y, &mag_z );

    log_printf( &logger, " Accel X: %.3f g\t Mag X: %.2f uT\r\n", acc_x, mag_x );
    log_printf( &logger, " Accel Y: %.3f g\t Mag Y: %.2f uT\r\n", acc_y, mag_y );
    log_printf( &logger, " Accel Z: %.3f g\t Mag Z: %.2f uT\r\n", acc_z, mag_z );
    log_printf( &logger, "----------------------------------\r\n");

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
