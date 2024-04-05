/*!
 * \file main.c
 * \brief Fan 2 Click example
 *
 * # Description
 * This example demonstrates the use of Fan 2 Click board.
 * It demonstrates sensor measurements and fan control.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and executes a default configuration for Fan 2 click.
 * Also initializes UART logger for results logging.
 *
 * ## Application Task
 * Increments the fan speed from half speed to maximum, and on each step measures
 * the current fan speed in RPM and the remote temperature in Celsius.
 * Fan speed will be incremented/decremented each second for 10 percents.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fan2.h"

// ------------------------------------------------------------------ VARIABLES

static fan2_t fan2;
static log_t logger;
static float fan2_speed;
static uint16_t fan2_curr_speed;
static float fan2_temp;
static uint8_t flag;

static char deg_cels[ 3 ] = { 176, 'C', 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    fan2_cfg_t fan2_cfg;
    log_cfg_t log_cfg;

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
    fan2_cfg_setup( &fan2_cfg );
    FAN2_MAP_MIKROBUS( fan2_cfg, MIKROBUS_1 );
    fan2_init( &fan2, &fan2_cfg );
    
    fan2_default_cfg( &fan2 );
    fan2_speed = FAN2_HALF_SPEED_PER;
    Delay_ms ( 1000 );

    log_printf( &logger, "* * *  Fan 2 initialization done  * * *\r\n" );
    log_printf( &logger, "***************************************\r\n" );
    flag = 0;
}

void application_task( void )
{
    fan2_direct_speed_control( &fan2, fan2_speed );

    Delay_ms ( 1000 );
    fan2_read_tacho( &fan2, FAN2_REG_TACH1_CNT, &fan2_curr_speed );
    
    fan2_read_temp( &fan2, FAN2_REG_REMOTE_TEMP_READ, &fan2_temp );

    log_printf( &logger, "* Fan 2 set speed : %.2f %%\r\n", fan2_speed );
    log_printf( &logger, "* Fan 2 current speed : %u RPM\r\n", fan2_curr_speed );
    log_printf( &logger, "* Fan 2 remote temperature : %.2f %s\r\n", fan2_temp, deg_cels );
    log_printf( &logger, "***************************************\r\n" );
    
    if ( flag == 0 ) {
        if ( fan2_speed < FAN2_MAX_SPEED_PER)
            fan2_speed += 10;
        else
            flag = 1;
    }
    
    if ( flag == 1 ) {
        if ( fan2_speed > FAN2_MIN_SPEED_PER)
            fan2_speed -= 10;
        else {
            fan2_speed = FAN2_HALF_SPEED_PER;
            flag = 0;
        }
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
