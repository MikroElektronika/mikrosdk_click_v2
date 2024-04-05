/*!
 * @file main.c
 * @brief Silent Step 2 Click example
 *
 * # Description
 * This example demonstrates the use of Silent Step 2 Click board™ 
 * by driving the motor in both directions for a desired rotation angle.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C and SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The application task represents an example that demonstrates 
 * the use of the Silent Step 2 Click board™ with which the user can sequentially move the motor. 
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
#include "silentstep2.h"

static silentstep2_t silentstep2;
static log_t logger;

// Bipolar stepper motor, resolution of 200 steps per revolution (1.8 degrees)
#define SILENTSTEP2_STEP_RES_200    200

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    silentstep2_cfg_t silentstep2_cfg;  /**< Click config object. */

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
    silentstep2_cfg_setup( &silentstep2_cfg );
    SILENTSTEP2_MAP_MIKROBUS( silentstep2_cfg, MIKROBUS_1 );
    err_t init_flag = silentstep2_init( &silentstep2, &silentstep2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SILENTSTEP2_ERROR == silentstep2_default_cfg ( &silentstep2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation :  90 degrees\r\n" );
    log_printf( &logger, " Step speed        :  50 %%\r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_CLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 50, 90, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Counterclockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation :  180 deg\r\n" );
    log_printf( &logger, " Step speed        :  50 %%\r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_COUNTERCLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 50, 180, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 270 deg\r\n" );
    log_printf( &logger, " Step speed        :  50 %% \r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_CLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 50, 270, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Counterclockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 360 deg\r\n" );
    log_printf( &logger, " Step speed        : 90 %%\r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_COUNTERCLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 90, 360, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 360 deg\r\n" );
    log_printf( &logger, " Step speed        : 90 %% \r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_CLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 90, 360, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
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
