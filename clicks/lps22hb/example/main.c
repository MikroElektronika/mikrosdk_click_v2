/*!
 * \file 
 * \brief Lps22hb Click example
 * 
 * # Description
 * The demo application measures temperature and pressure.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes Click driver, resets the device, applies default settings
 * and makes an initial log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of LPS22HB Click board. By 
 * measuring temperature and pressure. The results are being sent to the USART 
 * terminal where you can track their changes.
 *  
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lps22hb.h"

// ------------------------------------------------------------------ VARIABLES

static lps22hb_t lps22hb;
static log_t logger;

static float pressure;
static float temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lps22hb_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    lps22hb_cfg_setup( &cfg );
    LPS22HB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lps22hb_init( &lps22hb, &cfg );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "        LPS22HB Click\r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 1000 );
    
    lps22hb_default_cfg ( &lps22hb, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, "  - Initialization  done -\r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    pressure = lps22hb_get_pressure( &lps22hb );
    temperature = lps22hb_get_temp( &lps22hb );
    
    log_printf( &logger, " Pressure    : %.2f mBar\r\n", pressure );
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    
    log_printf( &logger, "----------------------------\r\n" );

    Delay_ms ( 1000 );
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
