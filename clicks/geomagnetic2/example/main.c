/*!
 * @file main.c
 * @brief GeoMagnetic 2 Click example
 *
 * # Description
 * This example demonstrates the use of the GeoMagnetic 2 Click board by
 * reading compensated 3-axis magnetic field data and die temperature from
 * the BMM350 sensor.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the GeoMagnetic 2 driver,
 * then applies the default configuration.
 *
 * ## Application Task
 * Reads the compensated magnetic field data and die temperature from the BMM350 sensor
 * when a data-ready interrupt is received on the INT pin and logs them
 * to the UART terminal.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "geomagnetic2.h"

#ifndef MIKROBUS_POSITION_GEOMAGNETIC2
    #define MIKROBUS_POSITION_GEOMAGNETIC2 MIKROBUS_1
#endif

// Maximum magnetic field threshold
#define GEOMAGNETIC2_FIELD_LIMIT_MAX_UT  2000.0f

// Minimum magnetic field threshold
#define GEOMAGNETIC2_FIELD_LIMIT_MIN_UT -2000.0f

static geomagnetic2_t geomagnetic2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    geomagnetic2_cfg_t geomagnetic2_cfg;  /**< Click config object. */

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
    geomagnetic2_cfg_setup( &geomagnetic2_cfg );
    GEOMAGNETIC2_MAP_MIKROBUS( geomagnetic2_cfg, MIKROBUS_POSITION_GEOMAGNETIC2 );
    if ( I2C_MASTER_ERROR == geomagnetic2_init( &geomagnetic2, &geomagnetic2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GEOMAGNETIC2_ERROR == geomagnetic2_default_cfg ( &geomagnetic2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    /* Enable interrupt */
    geomagnetic2_enable_interrupt( &geomagnetic2, 1 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    geomagnetic2_data_t mag_data;
    uint8_t int_status = 0;

    if ( geomagnetic2_get_int_pin( &geomagnetic2 ) )
    {   
        if ( GEOMAGNETIC2_OK == geomagnetic2_get_int_status( &geomagnetic2, &int_status ) )
        {
            if ( int_status & GEOMAGNETIC2_INT_DRDY_MASK )
            {   
                if ( GEOMAGNETIC2_OK == geomagnetic2_read_data( &geomagnetic2, &mag_data ) )
                {            
                    if ( mag_data.mag_x > GEOMAGNETIC2_FIELD_LIMIT_MAX_UT || mag_data.mag_x < GEOMAGNETIC2_FIELD_LIMIT_MIN_UT ||
                         mag_data.mag_y > GEOMAGNETIC2_FIELD_LIMIT_MAX_UT || mag_data.mag_y < GEOMAGNETIC2_FIELD_LIMIT_MIN_UT ||
                         mag_data.mag_z > GEOMAGNETIC2_FIELD_LIMIT_MAX_UT || mag_data.mag_z < GEOMAGNETIC2_FIELD_LIMIT_MIN_UT )
                    {
                        log_info( &logger, "High field detected -> magnetic reset" );
                        geomagnetic2_magnetic_reset( &geomagnetic2 );
                        return;
                    }

                    log_printf( &logger, "X: %.2f uT\r\n", mag_data.mag_x );
                    log_printf( &logger, "Y: %.2f uT\r\n", mag_data.mag_y );
                    log_printf( &logger, "Z: %.2f uT\r\n", mag_data.mag_z );
                    log_printf( &logger, "T: %.2f degC\r\n", mag_data.temperature );
                    log_printf( &logger, "--------------------\r\n" );
                }
            }
        }
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
