/*!
 * @file main.c
 * @brief DCMotor16 Click example
 *
 * # Description
 * This example shows the capabilities of the DC Motor 16 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver init.
 *
 * ## Application Task
 * Start motor example with change in motor direction and speed.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor16.h"

static dcmotor16_t dcmotor16;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor16_cfg_t dcmotor16_cfg;  /**< Click config object. */

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

    dcmotor16_cfg_setup( &dcmotor16_cfg );
    DCMOTOR16_MAP_MIKROBUS( dcmotor16_cfg, MIKROBUS_1 );
    err_t init_flag  = dcmotor16_init( &dcmotor16, &dcmotor16_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    uint16_t cnt;
    
    log_printf( &logger, ">> Motor start with direction [FORWARD] <<\r\n" );
    dcmotor16_set_direction( &dcmotor16, DCMOTOR16_DIR_FORWARD );
    for( cnt = 0; cnt <= 0x0100; cnt+= 25 ) {
        dcmotor16_ctrl_vref( &dcmotor16, cnt );
        Delay_ms ( 250 );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">> Motor stop \r\n" );
    dcmotor16_stop( &dcmotor16 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">> Motor start with direction [BACKWARD] <<\r\n" );
    dcmotor16_set_direction( &dcmotor16, DCMOTOR16_DIR_BACKWARD );
    for( cnt = 0; cnt <= 0x0100; cnt+= 25 ) {
        dcmotor16_ctrl_vref( &dcmotor16, cnt );
        Delay_ms ( 250 );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">> Motor stop \r\n" );
    dcmotor16_stop( &dcmotor16 );
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
