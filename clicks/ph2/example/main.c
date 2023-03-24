/*!
 * @file main.c
 * @brief pH 2 Click Example.
 *
 * # Description
 * This library contains API for pH 2 Click driver. 
 * The library initializes and defines the I2C bus drivers or 
 * ADC drivers to read data from pH probe.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs offset calibration, 
 * as well as calibration in pH-neutral substance.

 *
 * ## Application Task
 * This example demonstrates the use of the pH 2 Click board by 
 * reading pH value of the substance where probe is placed.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ph2.h"

static ph2_t ph2;   /**< pH 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ph2_cfg_t ph2_cfg;  /**< Click config object. */

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
    ph2_cfg_setup( &ph2_cfg );
    PH2_MAP_MIKROBUS( ph2_cfg, MIKROBUS_1 );
    err_t init_flag = ph2_init( &ph2, &ph2_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " ================================ \r\n" );
    log_printf( &logger, "     Performing calibration       \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    log_printf( &logger, " Disconect BNC connector, \r\n" );
    log_printf( &logger, "    short-circuit it, \r\n" );
    log_printf( &logger, " adjust offset potentiometer \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    log_printf( &logger, " STAT1 - turn clockwise \r\n" );
    log_printf( &logger, " STAT2 - turn counter-clockwise \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    
    ph2_calibrate_offset( &ph2 );
    
    log_printf( &logger, " Calibration completed \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    
    log_printf( &logger, " Connect probe back \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    Delay_ms( 5000 );
    log_printf( &logger, "  Place probe into pH  \r\n" );
    log_printf( &logger, " neutral substance for \r\n" );
    log_printf( &logger, " mid point calibration \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    Delay_ms( 5000 );
    log_printf( &logger, " Starting calibration  \r\n" );
    log_printf( &logger, " ================================ \r\n" );  
    
    ph2_calibrate( &ph2, 7 );
    
    log_printf( &logger, " Calibration done!  \r\n" );
    log_printf( &logger, " ================================ \r\n" ); 
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ================================ \r\n" ); 
}

void application_task ( void ) 
{
    float pH_val = 0;
    ph2_calculate_ph( &ph2, &pH_val );
    log_printf( &logger, " pH value: %.3f \r\n", pH_val );
    log_printf( &logger, " ================================ \r\n" ); 
    Delay_ms( 1000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
