/*!
 * \file 
 * \brief Index Counter Click example
 * 
 * # Description
 * This application enables usage of Index counter click board which can be used to measure rotational speed.
 * 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initilaziation of GPIO and write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of the Index Counter click board.
 * This example shows the direction of movement, Rotations Per Minute ( RPM or speed )
 * of the three pairs of rotating poles positioned in the sensor operating range.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * *note:* 
 * Additional Functions :
 *   - void log_display ( float rpm_val ) - The function displays all results
 *     and a float value with a comma with two decimal places.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "indexcounter.h"

// ------------------------------------------------------------------ VARIABLES

static indexcounter_t indexcounter;
static log_t logger;

uint8_t dir_state;
uint8_t speed_state;
uint8_t enable_speed = INDEXCOUNTER_SPEED_ENABLE;
uint8_t n_pole_pairs = 3;
uint32_t time_cnt = 0;
uint32_t pulse_ms;
uint32_t start_timer = 1;
float speed_rpm;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void log_display ( float rpm_val )
{
    uint16_t disp_float;

    disp_float = ( uint16_t ) rpm_val;

    log_printf( &logger, " Direction :" );

    if ( dir_state == 0 )
    {
        log_printf( &logger, " Forward \r\n" );
    }
    else
    {
        log_printf( &logger, " Reverse \r\n" );
    }

    log_printf( &logger, " Speed     : %d.", disp_float );

    disp_float = ( uint16_t ) ( rpm_val * 100 );

    log_printf( &logger, "%d rpm\r\n", disp_float );

    log_printf( &logger, " Time      : %ld  ms \r\n", time_cnt );

    log_printf ( &logger, "-----------------------" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    indexcounter_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    indexcounter_cfg_setup( &cfg );
    INDEXCOUNTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    indexcounter_init( &indexcounter, &cfg );
}

void application_task ( void )
{
    //  Task implementation.

    speed_state = indexcounter_get_speed( &indexcounter );
    dir_state = indexcounter_get_dir( &indexcounter );

    if ( enable_speed && speed_state )
    {
        pulse_ms = time_cnt - start_timer;
        start_timer = time_cnt;
        speed_rpm = INDEXCOUNTER_ONE_MIN_CONV_MS / ( pulse_ms * n_pole_pairs );
        enable_speed = INDEXCOUNTER_SPEED_DISABLE;

        log_display ( speed_rpm );
    }

    if ( ( !enable_speed ) && ( !speed_state ) )
    {
        enable_speed = INDEXCOUNTER_SPEED_ENABLE;
    }

    Delay_1ms();
    time_cnt++;
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
