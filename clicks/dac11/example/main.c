/*!
 * @file main.c
 * @brief DAC11 Click example
 *
 * # Description
 * This example demonstrates the use of DAC 11 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and executes the Click default configuration which sets the WRM mode and
 * disables all outputs.
 *
 * ## Application Task
 * Changes the output voltage of all channels every 2 seconds and logs the voltage value on the USB UART.
 * It will go through the entire voltage range taking into account the number of steps which is defined below.
 *
 * @note
 * Measure the voltage at VCC_SEL jumper and adjust the reference voltage value below for better accuracy.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dac11.h"

#define REFERENCE_VOLTAGE  3.3 // The reference voltage defined by the VCC_SEL on-board jumper. 
#define NUMBER_OF_STEPS    20  // The number of steps by which we will divide the entire voltage range. 

static dac11_t dac11;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    dac11_cfg_t dac11_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    dac11_cfg_setup( &dac11_cfg );
    DAC11_MAP_MIKROBUS( dac11_cfg, MIKROBUS_1 );
    err_t init_flag  = dac11_init( &dac11, &dac11_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    dac11_default_cfg ( &dac11 );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float step = REFERENCE_VOLTAGE / NUMBER_OF_STEPS;
    float output_voltage = step;
    uint8_t cnt = 0;
    while ( cnt < NUMBER_OF_STEPS )
    {
        dac11_set_all_ch_voltage ( &dac11, REFERENCE_VOLTAGE, output_voltage );
        log_printf( &logger, " All channels output voltage set to %.2f V\r\n", output_voltage );
        
        output_voltage += step;
        cnt++;
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
