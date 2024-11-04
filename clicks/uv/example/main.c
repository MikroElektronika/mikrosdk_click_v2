/*!
 * \file main.c
 * \brief UV Click Driver Example
 *
 * # Description
 * This is a example which demonstrates the use of UV Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configuration of the Click and log objects.
 *
 * ## Application Task
 * Reads the result of AD conversion once per second and calculates
 * the UV index based on that. Results are being sent to the USB UART
 * where you can track their changes.
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uv.h"

// ------------------------------------------------------------------ VARIABLES

static uv_t uv;
static log_t logger;

static float uv_voltage;
static uint8_t uv_index;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void application_callback ( uint8_t *message )
{
    log_printf( &logger, "*** %s ***\r\n", message );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uv_cfg_t cfg;

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
    uv_cfg_setup( &cfg );
    UV_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == uv_init( &uv, &cfg ) )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );
        for ( ; ; );
    }
    uv_set_callback_handler( &uv, application_callback );
    uv_device_enable( &uv );
    Delay_ms ( 1000 );
    uv_voltage = 0;
    uv_index = 0;
    log_info( &logger, "---- Application Init Done ----\r\n" );
}

void application_task ( void )
{
    if ( SPI_MASTER_ERROR != uv_read_adc_voltage( &uv, &uv_voltage ) )
    {
        uv_calc_index( &uv, uv_voltage, &uv_index );

        log_printf( &logger, " UV Index [0-15] : %u\r\n", ( uint16_t ) uv_index );
        log_printf( &logger, " UV ADC Voltage [V] : %.2f\r\n", uv_voltage );
        log_printf( &logger, "------------------------------\r\n" );
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
