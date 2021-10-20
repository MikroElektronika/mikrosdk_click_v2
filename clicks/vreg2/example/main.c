/*!
 * \file 
 * \brief Vreg2 Click example
 * 
 * # Description
 * This application enables voltage regulation.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the GPIO driver and configures the PWM 
 * peripheral for controlling VREG2 voltage output.
 * 
 * ## Application Task  
 * Based on the data received from the uart the voltage output will be increased or decreased.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "vreg2.h"

// ------------------------------------------------------------------ VARIABLES

static vreg2_t vreg2;
static log_t logger;

static float duty_cycle = 0.5;
static uint8_t ctrl_flag = 0;
static uint8_t ctrl_pre_flag = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    vreg2_cfg_t cfg;

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

    vreg2_cfg_setup( &cfg );
    vreg2_init( &vreg2, &cfg );

    vreg2_set_duty_cycle( &vreg2, duty_cycle );
    vreg2_pwm_start( &vreg2 );
}

void application_task ( void )
{
    //  Task implementation.

    switch ( ctrl_flag )
    {
        case 0:
        {
            duty_cycle = 0.2;
            log_printf( &logger, "Volatage set to : %d %%\r\n", duty_cycle );
            ctrl_pre_flag = ctrl_flag;
            ctrl_flag = 1;
            break;
        }

        case 1:
        {
            duty_cycle = 0.5;
            log_printf( &logger, "Volatage set to : %d %%\r\n", duty_cycle );

            if ( ctrl_pre_flag == 0 )
            {
                ctrl_pre_flag = ctrl_flag;
                ctrl_flag = 2;
            }
            else if ( ctrl_pre_flag == 2 )
            {
                ctrl_pre_flag = ctrl_flag;
                ctrl_flag = 0;
            }
            break;
        }
        case 2:
        {
            duty_cycle = 0.7;
            log_printf( &logger, "Volatage set to : %d %%\r\n", duty_cycle );

            if ( ctrl_pre_flag == 1 )
            {
                ctrl_pre_flag = ctrl_flag;
                ctrl_flag = 3;
            }
            else if ( ctrl_pre_flag == 3 )
            {
                ctrl_pre_flag = ctrl_flag;
                ctrl_flag = 1;
            }
            break;
        }
        case 3:
        {
            duty_cycle = 0.95;
            log_printf( &logger, "Volatage set to : %d %%\r\n", duty_cycle );
            ctrl_pre_flag = ctrl_flag;
            ctrl_flag = 2;
            break;

        }
        default:
        {
            log_printf( &logger, "Something broke\r\n");
        }
    }

    vreg2_set_duty_cycle( &vreg2, duty_cycle );
    Delay_ms( 1500 );
    Delay_100ms();
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
