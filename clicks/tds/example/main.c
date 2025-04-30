/*!
 * @file main.c
 * @brief TDS Click Example.
 *
 * # Description
 * This example demonstrates the usage of the TDS Click board, which measures the Total 
 * Dissolved Solids (TDS) in water. The application initializes the TDS Click board, 
 * establishes communication, and continuously reads the TDS value in parts per million (ppm).
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and configures the TDS Click board. It sets up communication 
 * using either ADC or I2C, verifies proper initialization, and prepares the device 
 * for measurement.
 *
 * ## Application Task
 * Continuously reads the TDS value from the sensor and logs it in ppm (parts per million).
 *
 * @note
 * Ensure a proper TDS probe is attached to the Click board for accurate measurements.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "tds.h"

static tds_t tds;       /**< TDS Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tds_cfg_t tds_cfg;  /**< Click config object. */

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
    tds_cfg_setup( &tds_cfg );
    TDS_MAP_MIKROBUS( tds_cfg, MIKROBUS_1 );
    err_t init_flag = tds_init( &tds, &tds_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float tds_ppm = 0;
    if ( TDS_OK == tds_read_ppm ( &tds, &tds_ppm ) ) 
    {
        log_printf( &logger, " TDS Value : %.1f ppm\r\n\n", tds_ppm );
        Delay_ms ( 1000 );
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
