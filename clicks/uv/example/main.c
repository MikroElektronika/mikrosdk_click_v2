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
 * Configuration of the click and log objects.
 *
 * ## Application Task
 * This is a example which demonstrates the use of the UV Click board.
 * This example should read a result of AD conversion and calculate it to UV
 * index level.
 * Results are being sent to the Usart Terminal where you can track their
 * changes.
 * All data logs on usb uart is changed for every 1 second.
 *
 * \author Nemanja Medakovic
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
    if ( uv_init( &uv, &cfg ) == SPI_MASTER_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );

        for ( ; ; );
    }
    uv_set_callback_handler( &uv, application_callback );
    uv_device_enable( &uv );
    Delay_ms( 1000 );
    uv_voltage = 0;
    uv_index = 0;
    log_info( &logger, "---- Application Init Done ----\r\n" );
}

void application_task ( void )
{
    if ( uv_read_adc_voltage( &uv, &uv_voltage ) != SPI_MASTER_ERROR )
    {
        uv_calc_index( &uv, uv_voltage, &uv_index );

        log_printf( &logger, " UV Index [0-15] : %u\r\n", (uint16_t)uv_index );
        log_printf( &logger, " UV ADC Voltage [V] : %.2f\r\n", uv_voltage );
        log_printf( &logger, "------------------------------\r\n" );
    }

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
