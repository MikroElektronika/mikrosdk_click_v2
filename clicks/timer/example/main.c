/*!
 * \file 
 * \brief Timer Click example
 * 
 * # Description
 * This application is multifunctional 3-axis digital accelerometer that can also be configured as a 45-degree Tilt sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C,
 * soft reset, sets ETC and EC start ( seconds ), hardwere reset and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Timer Click board.
 * Timer Click communicates with register via I2C by write to register and read from register,
 * display time ( days, hours, minutes and seconds ) which we received reading from the target register address of DS1682 total elapsed time recorder.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "timer.h"

// ------------------------------------------------------------------ VARIABLES

static timer_t timer;
static log_t logger;
static uint8_t time_seconds_new;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    timer_cfg_t cfg;

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

    timer_cfg_setup( &cfg );
    TIMER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    timer_init( &timer, &cfg );
    Delay_ms( 200 );

    log_printf( &logger, "   Driver  Init   \r\n" );
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "    Soft Reset    \r\n" );
    
    timer_soft_reset( &timer );
    Delay_ms( 500 );
    
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "  Set ETC and EC  \r\n" );
    
    timer_set_etc_seconds( &timer, 86390 );
    timer_set_ec_seconds( &timer, 0 );
    
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "  Hardwere Reset  \r\n" );
    
    timer_hw_reset( &timer );
    Delay_ms( 500 );
    
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "        ETC       \r\n" );
    log_printf( &logger, "------------------\r\n" );
    
    time_seconds_new = 0xFF;
}

void application_task ( )
{
    uint8_t time_hours;
    uint8_t time_minutes;
    uint8_t time_seconds;
    uint16_t time_days;

    timer_get_time( &timer, &time_days, &time_hours, &time_minutes, &time_seconds );
   
    if ( time_seconds_new != time_seconds )
    {
        log_printf
        ( 
            &logger, " %d days    %d:%d:%d \r\n", 
            (uint16_t)time_days, 
            (uint16_t)time_hours, 
            (uint16_t)time_minutes, 
            (uint16_t)time_seconds
        );
        log_printf( &logger, "------------------\r\n" );
        time_seconds_new = time_seconds;
    }
    Delay_ms( 1 );
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
