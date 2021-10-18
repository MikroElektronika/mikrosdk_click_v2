/*!
 * \file 
 * \brief diffpressure Click example
 * 
 * # Description
 * This application is temperature compensated and calibrated pressure sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device. Start sending log via UART.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Diff Pressure click board.
 *             The example is display
 *             values of ADC module (MPC3551) 22-bit register and
 *             value of difference pressure [ Pa ] via UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "diffpressure.h"

// ------------------------------------------------------------------ VARIABLES

static diffpressure_t diffpressure;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    diffpressure_cfg_t cfg;

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

    //  Click initialization.

    diffpressure_cfg_setup( &cfg );
    DIFFPRESSURE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uint8_t err_flag = diffpressure_init( &diffpressure, &cfg );
    
    if ( DIFFPRESSURE_INIT_ERROR == err_flag )
    {
        log_info( &logger, "---- Error Init ----" );
        for ( ; ; );
    }
    Delay_ms( 100 );
}

void application_task ( void )
{
    int32_t difference = 0;
    int32_t adc_value = 0;
    uint8_t status;

    adc_value = diffpressure_read_data( &diffpressure );
    difference = diffpressure_get_kpa_difference( &diffpressure, adc_value );
    status = diffpressure_status_check( &diffpressure, adc_value );

    if ( status == DIFFPRESSURE_OK )
    {
        log_printf( &logger, "ADC Value:  %ld\r\n", adc_value );

        log_printf( &logger, "Difference: %ld", difference );
        
        log_printf( &logger, "  [Pa] \r\n" );

        Delay_ms( 3000 );
    }

    if ( status == DIFFPRESSURE_OVH )
    {
        log_printf( &logger, "Overflow happened" );
        Delay_100ms( );
    }

    if ( status == DIFFPRESSURE_OVL )
    {
        log_printf( &logger, "Underflow happened" );
        Delay_100ms( );
    }

    log_printf( &logger, "" );
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
