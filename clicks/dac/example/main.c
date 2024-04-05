/*!
 * \file 
 * \brief Dac Click example
 * 
 * # Description
 * This demo example sends digital signal to the outputs 
 * and converts it to analog.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, SPI communication and LOG.
 * 
 * ## Application Task  
 * Sends different values( form 0 to 4095 with step 1000 ) to output and 
 * prints expected measurement.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dac.h"

// ------------------------------------------------------------------ VARIABLES

static dac_t dac;
static log_t logger;
static uint32_t dac_val;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac_cfg_t cfg;

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

    dac_cfg_setup( &cfg );
    DAC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac_init( &dac, &cfg );
}

void application_task ( void )
{
    //  Task implementation.    
    for ( dac_val = 0; dac_val <= DAC_RESOLUTION; dac_val += DAC_STEP_VALUE )
    {
        dac_set_voltage( &dac, dac_val );
        dac_val *= DAC_CALIB_VAL_1;
        dac_val /= DAC_CALIB_VAL_2;
        log_printf( &logger, " Current DAC Value: %d mV \r\n", dac_val );

        log_printf( &logger, "----------------------------------\r\n" );

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
