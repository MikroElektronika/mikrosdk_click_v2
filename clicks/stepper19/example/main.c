/*!
 * @file main.c
 * @brief Stepper 19 Click example
 *
 * # Description
 * This example demonstrates the use of Stepper 19 Click board 
 * by driving the motor in both directions for a desired rotation angle.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The application task represents an example that demonstrates 
 * the use of the Stepper 19 Click board with which the user can sequentially move the motor. 
 * The first part of the sequence executes the clockwise/counterclockwise motor movement 
 * for an angle of 90 degrees with a step speed of 50%, 
 * all the way to the last sequence of the same movement routine 
 * of 360 degree angle with a step speed of 90%. 
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper19.h"


// Bipolar stepper motor, resolution of 200 steps per revolution (1.8 degrees)
#define STEPPER19_STEP_RES_200    200

static stepper19_t stepper19;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper19_cfg_t stepper19_cfg;  /**< Click config object. */

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
    stepper19_cfg_setup( &stepper19_cfg );
    STEPPER19_MAP_MIKROBUS( stepper19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper19_init( &stepper19, &stepper19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER19_ERROR == stepper19_default_cfg ( &stepper19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
}

void application_task ( void ) 
{
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation :  90 degrees\r\n" );
    log_printf( &logger, " Step speed        :  50 %%\r\n" );
    stepper19_set_direction( &stepper19, STEPPER19_DIR_CLOCKWISE );
    if ( STEPPER19_OK == stepper19_rotate_by_angle( &stepper19, 50, 90, STEPPER19_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms( 2000 );
    }
    
    log_printf( &logger, " Counterclockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation :  180 deg\r\n" );
    log_printf( &logger, " Step speed        :  50 %%\r\n" );
    stepper19_set_direction( &stepper19, STEPPER19_DIR_COUNTERCLOCKWISE );
    if ( STEPPER19_OK == stepper19_rotate_by_angle( &stepper19, 50, 180, STEPPER19_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms( 2000 );
    }
    
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 270 deg\r\n" );
    log_printf( &logger, " Step speed        :  90 %% \r\n" );
    stepper19_set_direction( &stepper19, STEPPER19_DIR_CLOCKWISE );
    if ( STEPPER19_OK == stepper19_rotate_by_angle( &stepper19, 90, 270, STEPPER19_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms( 2000 );
    }
    
    log_printf( &logger, " Counterclockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 360 deg\r\n" );
    log_printf( &logger, " Step speed        : 90 %%\r\n" );
    stepper19_set_direction( &stepper19, STEPPER19_DIR_COUNTERCLOCKWISE );
    if ( STEPPER19_OK == stepper19_rotate_by_angle( &stepper19, 90, 360, STEPPER19_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms( 2000 );
    }
    
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 360 deg\r\n" );
    log_printf( &logger, " Step speed        : 90 %% \r\n" );
    stepper19_set_direction( &stepper19, STEPPER19_DIR_CLOCKWISE );
    if ( STEPPER19_OK == stepper19_rotate_by_angle( &stepper19, 90, 360, STEPPER19_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms( 2000 );
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
