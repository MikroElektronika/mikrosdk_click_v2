/*!
 * @file main.c
 * @brief VCP Monitor 7 Click Example.
 *
 * # Description
 * This example demonstrates the use of VCP Monitor 7 Click board by measuring the
 * differential voltage present between the input terminals of the high common mode
 * difference amplifier.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the differential input voltage and displays the results on the USB UART
 * approximately once per second.
 *
 * @note
 * The input common mode voltage must be at least 4.3V above the board ground for
 * the amplifier to operate in the linear region.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "vcpmonitor7.h"

#ifndef MIKROBUS_POSITION_VCPMONITOR7
    #define MIKROBUS_POSITION_VCPMONITOR7 MIKROBUS_1
#endif

static vcpmonitor7_t vcpmonitor7;   /**< VCP Monitor 7 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vcpmonitor7_cfg_t vcpmonitor7_cfg;  /**< Click config object. */

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
    vcpmonitor7_cfg_setup( &vcpmonitor7_cfg );
    VCPMONITOR7_MAP_MIKROBUS( vcpmonitor7_cfg, MIKROBUS_POSITION_VCPMONITOR7 );
    err_t init_flag = vcpmonitor7_init( &vcpmonitor7, &vcpmonitor7_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float diff_volt = 0;

    if ( VCPMONITOR7_OK == vcpmonitor7_read_diff_voltage ( &vcpmonitor7, &diff_volt ) ) 
    {
        log_printf( &logger, " Differential voltage : %.3f[V]\r\n\n", diff_volt );
    }
    else
    {
        log_printf( &logger, " Differential voltage read error.\r\n\n" );
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
