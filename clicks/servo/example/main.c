/*!
 * \file 
 * \brief Servo Click example
 * 
 * # Description
 * This app shows how the servo motor can be controled by the click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * The servo motor at CH1 rotate in clockwise and counter clockwise directions.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "servo.h"

// ------------------------------------------------------------------ VARIABLES

static servo_t servo;
static log_t logger;
static int16_t cnt;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    servo_cfg_t cfg;

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

    servo_cfg_setup( &cfg );
    SERVO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    servo_init( &servo, &cfg );
    
    servo_default_cfg( &servo );
}

void application_task ( void )
{
    log_printf( &logger, "<<< Counter clockwise >>>\r\n" );
    Delay_1sec( );
    
    for ( cnt = servo.min_pos; cnt <= servo.max_pos; cnt++ )
    {
        servo_set_position( &servo, SERVO_MOTOR_1, cnt );
        log_printf( &logger, "Position : %u \r\n", ( uint16_t ) cnt );
        Delay_10ms( );
    }
    
    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, "<<< Clockwise >>>\r\n" );
    Delay_1sec( );
    
    for ( cnt = servo.max_pos; cnt >= servo.min_pos; cnt-- )
    {
        servo_set_position( &servo, SERVO_MOTOR_1, cnt );
        log_printf( &logger, "Position : %u \r\n", ( uint16_t ) cnt );
        Delay_10ms( );
    }
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
