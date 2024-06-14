/*!
 * @file main.c
 * @brief PIR 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of PIR 2 Click boards.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and selects the driver interface.
 *
 * ## Application Task
 * It checks if the sensor has detected movement and displays message on the USB UART.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "pir2.h"

static pir2_t pir2;     /**< PIR 2 Click driver object. */
static log_t logger;    /**< Logger object. */

#define PIR2_VOLTAGE_TRESHOLD       2.5f

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    pir2_cfg_t pir2_cfg;    /**< Click config object. */

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

    pir2_drv_interface_sel( &pir2_cfg, PIR2_DRV_SEL_I2C );

    // Click initialization.
    pir2_cfg_setup( &pir2_cfg );
    PIR2_MAP_MIKROBUS( pir2_cfg, MIKROBUS_1 );
    err_t init_flag = pir2_init( &pir2, &pir2_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    pir2_read_voltage ( &pir2, &voltage );
    if ( voltage > PIR2_VOLTAGE_TRESHOLD )
    {
        log_printf( &logger, " Motion detected \r\n" );
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
