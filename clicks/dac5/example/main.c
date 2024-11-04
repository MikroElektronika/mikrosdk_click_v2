/*!
 * \file 
 * \brief Dac5 Click example
 * 
 * # Description
 *
 * This demo example sends digital signal to one of the outputs and converts it to analog
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver init, tests communication and configures device for measuring
 *
 * ## Application Task
 * Sets the channel H with different values and logs the expected output on USB UART
 *
 * ## NOTE
 * In order to improve the accuracy, measure the voltage on the Click board VrefIN SEL jumper and set it as VREF below.
 * 
 * \author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dac5.h"

// ------------------------------------------------------------------ VARIABLES

static dac5_t dac5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac5_cfg_t cfg;

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

    dac5_cfg_setup( &cfg );
    DAC5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac5_init( &dac5, &cfg );

    if ( dac5_get_device_id( &dac5 ) != DAC5_DEVICE_ID )
    {
        log_printf( &logger, "ERROR - DEVICE IS NOT READY\r\n" );
        log_printf( &logger, "Please check the onboard jumpers position.\r\n" );
        for ( ; ; );
    }

    dac5_config( &dac5, DAC5_CONFIG_GLOBAL_ENABLED );
    log_printf( &logger, "The Click board is configured.\r\n" );

    Delay_ms ( 100 );
}

void application_task ( void )
{
    for ( uint16_t cnt = DAC5_MIN_DATA; cnt < DAC5_MAX_DATA; cnt += 500 )
    {
        if ( dac5_send_data( &dac5, DAC5_REG_DAC_H_DATA, cnt ) == DAC5_ERROR )
        {
            log_printf( &logger, "ERROR SENDING DATA\r\n" );
        }
        else
        {
            log_printf( &logger, "Expected output on channel H:\t %d mV\r\n", ( uint16_t )( ( ( float ) cnt / DAC5_MAX_DATA ) * dac5.vref ) );
        }
        log_printf( &logger,"------------------------------------\r\n" );
        Delay_ms ( 1000 );
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
