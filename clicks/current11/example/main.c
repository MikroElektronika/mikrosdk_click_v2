/*!
 * @file main.c
 * @brief Current 11 Click Example.
 *
 * # Description
 * This example demonstrates the use of Current 11 Click board by reading and
 * displaying the input current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and calibrates the zero current offset.
 *
 * ## Application Task
 * Reads the input current measurements and displays the results on the USB UART
 * approximately once per second.
 *
 * @note
 * For better accuracy, set the voltage reference by using the @b current11_set_vref function,
 * increase the number of conversions by modifying the @b CURRENT11_NUM_CONVERSIONS macro, 
 * and adjust the @b CURRENT11_COUPLING_FACTOR_G_A value.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "current11.h"

static current11_t current11;   /**< Current 11 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current11_cfg_t current11_cfg;  /**< Click config object. */

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
    current11_cfg_setup( &current11_cfg );
    CURRENT11_MAP_MIKROBUS( current11_cfg, MIKROBUS_1 );
    err_t init_flag = current11_init( &current11, &current11_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " Calibrating zero current offset in 5 seconds...\r\n" );
    log_printf( &logger, " Make sure no current flows through the sensor during the calibration process.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( CURRENT11_ERROR == current11_calibrate_offset ( &current11 ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    log_printf( &logger, " Calibration DONE.\r\n" );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float current = 0;
    if ( CURRENT11_OK == current11_read_current ( &current11, &current ) ) 
    {
        log_printf( &logger, " Current : %.1f A\r\n\n", current );
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
