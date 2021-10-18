/*!
 * \file 
 * \brief HeartRate3 Click example
 * 
 * # Description
 * The demo application shows reflected red, green and ir values.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes click driver, resets the device, applies default settings
 * and makes an initial log.
 * 
 * ## Application Task  
 * This example demonstrates the use of Heart rate 3 board. It is set in default
 * mode, and reads reflected red, green and ir values and displays the results 
 * on USART terminal.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "heartrate3.h"

// ------------------------------------------------------------------ VARIABLES

static heartrate3_t heartrate3;
static log_t logger;

static uint32_t led_2;
static uint32_t aled_2;
static uint32_t led_1;
static uint32_t aled_1;
static uint32_t led_2_aled_2;
static uint32_t led_1_aled_1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate3_cfg_t cfg;

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

    heartrate3_cfg_setup( &cfg );
    HEARTRATE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate3_init( &heartrate3, &cfg );
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "  Heart rate 3 Click  \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    
    heartrate3_rst_state ( &heartrate3, HEARTRATE3_PIN_STATE_LOW );
    Delay_us( 100 );
    
    heartrate3_rst_state ( &heartrate3, HEARTRATE3_PIN_STATE_HIGH );
    Delay_ms( 1000 );
    
    heartrate3_default_cfg ( &heartrate3 );
    Delay_ms( 100 );
    
    log_printf( &logger, "     Initialised!     \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms(100);
}

void application_task ( void )
{
    led_2 = heartrate3_read_u32( &heartrate3, HEARTRATE3_LED2VAL );
    aled_2 = heartrate3_read_u32( &heartrate3, HEARTRATE3_ALED2VAL );
    led_1 = heartrate3_read_u32( &heartrate3, HEARTRATE3_LED1VAL );
    aled_1 = heartrate3_read_u32( &heartrate3, HEARTRATE3_ALED1VAL );
    led_2_aled_2 = heartrate3_read_u32( &heartrate3, HEARTRATE3_LED2_ALED2VAL );
    led_1_aled_1 = heartrate3_read_u32( &heartrate3, HEARTRATE3_LED1_ALED1VAL );
    
    log_printf( &logger, "%.0f,%.0f,%.0f,%.0f,%.0f,%.0f \r\n", (float)led_2, (float)aled_2, 
                (float)led_1, (float)aled_1, (float)led_2_aled_2, (float)led_1_aled_1 );
    Delay_ms(3);
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
