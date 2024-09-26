/*!
 * @file main.c
 * @brief DAC 18 Click example
 *
 * # Description
 * This example demonstrates the use of the DAC 18 click board 
 * by configuring the waveform signals from a function generator on the OUT0 
 * and voltage level on the OUT1.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, the app executes a default configuration (configuration mode).
 *
 * ## Application Task
 * The demo application operated in standalone mode and displayed the voltage level on OUT1.
 * The GP0, GP1, and GP2 switches on the DAC 18 click board 
 * are used to change the output voltage level and waveform signals.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * ## Additional Function
 * - static void dac18_display_out_status ( uint8_t status )
 *
 * @note
 * Set GP0, GP1, and GP2 switches to position "1" for the configuration modes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dac18.h"

static dac18_t dac18;
static log_t logger;

static uint8_t gpi_status = 0;
static uint8_t new_gpi_status = 7;

/**
 * @brief DAC 18 display output states.
 * @details This function displays OUT0 and OUT1 status.
 * @note None.
 */
static void dac18_display_out_status ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac18_cfg_t dac18_cfg;  /**< Click config object. */

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
    dac18_cfg_setup( &dac18_cfg );
    DAC18_MAP_MIKROBUS( dac18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dac18_init( &dac18, &dac18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC18_ERROR == dac18_default_cfg ( &dac18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " Use the GP0, GP1 and GP2 switch to change the outputs\r\n\n" );
}

void application_task ( void ) 
{
    dac18_get_gpi_status( &dac18, &gpi_status );
    if ( gpi_status != new_gpi_status )
    {
        new_gpi_status = gpi_status;
        dac18_display_out_status( );
    }
    Delay_ms ( 100 );
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

static void dac18_display_out_status ( void )
{
    switch ( gpi_status )
    {
        case 0: case 4:
        {
            log_printf( &logger, " OUT0 Duty-cycle: 80 [%%]\r\n" );
            log_printf( &logger, " OUT1 Voltage: 0.75 [V]\r\n\n" );
            break;
        }
        case 1: case 5:
        {
            log_printf( &logger, " OUT0 Duty-cycle: 20 [%%]\r\n" );
            log_printf( &logger, " OUT1 Voltage: 2.00 [V]\r\n\n" );
            break;
        }
        case 2: case 6:
        {
            log_printf( &logger, " OUT0 Duty-cycle: 60 [%%]\r\n" );
            log_printf( &logger, " OUT1 Voltage: 1.16 [V]\r\n\n" );
            break;
        }
        case 3: case 7:
        {
            log_printf( &logger, " OUT0 Duty-cycle: 40 [%%]\r\n" );
            log_printf( &logger, " OUT1 Voltage: 1.58 [V]\r\n\n" );
            break;
        }
        default:
        {
            log_printf( &logger, " Unknown\r\n" );
        }
    }
}

// ------------------------------------------------------------------------ END
