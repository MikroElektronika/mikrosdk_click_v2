/*!
 * \file 
 * \brief LedFlash2 Click example
 * 
 * # Description
 * This app demonstrate flash and torch mode on LED light.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device and sets the Click into "OFF" mode.
 * 
 * ## Application Task  
 * This function will demonstrate how to use the flash mode,
 * and the torch mode, with different power settings. 
 * It will then turn the Click off.
 * 
 * ## NOTE 
 * LED lights can be very bright, even on lowest power settings.
 * Avoid looking directly into the light when Click is in operation.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ledflash2.h"

// ------------------------------------------------------------------ VARIABLES

static ledflash2_t ledflash2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ledflash2_cfg_t cfg;

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

    ledflash2_cfg_setup( &cfg );
    LEDFLASH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ledflash2_init( &ledflash2, &cfg );

    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_OFF, 0, 0 );
    log_printf( &logger, "Initialized...\r\n" );
}

void application_task ( void )
{ 
    Delay_ms ( 1000 );
    log_printf( &logger, "Do not look directly into the led lights.\r\n" );
    log_printf( &logger, "Triggering flash in 5...\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "4...\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "3...\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "2...\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "1...\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "Cheese!\r\n" );

    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_FLASH, LEDFLASH2_CUR_50, LEDFLASH2_FTMR_312 );
    Delay_ms ( 350 );
    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_OFF, 0, 0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Switching to the torch mode in a moment...\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_TORCH, LEDFLASH2_CUR_100, 0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "Dimming the torch light...\r\n" );
    
    for ( uint8_t cnt = LEDFLASH2_CUR_100; cnt <= LEDFLASH2_CUR_18; cnt++ )
    {
        ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_TORCH, cnt, 0 );
        Delay_ms ( 500 );
    }
    Delay_ms ( 1000 );
    log_printf( &logger, "Switching off...\r\n" );
    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_OFF, 0, 0 );
    log_printf( &logger, "------------------------------------------------\r\n" );
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
