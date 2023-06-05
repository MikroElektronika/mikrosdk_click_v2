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
 * @note
 * We recommend using the SerialPlot tool for data visualizing.
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
    heartrate3_cfg_t heartrate3_cfg;

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
    heartrate3_cfg_setup( &heartrate3_cfg );
    HEARTRATE3_MAP_MIKROBUS( heartrate3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate3_init( &heartrate3, &heartrate3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "  Heart rate 3 Click  \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    
    if ( HEARTRATE3_ERROR == heartrate3_default_cfg ( &heartrate3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, "     Initialised!     \r\n" );
    log_printf( &logger, "----------------------\r\n" );    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void )
{
    err_t error_flag = HEARTRATE3_OK;
    if ( heartrate3_check_data_ready ( &heartrate3 ) )
    {
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_LED2VAL, &led_2 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_ALED2VAL, &aled_2 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_LED1VAL, &led_1 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_ALED1VAL, &aled_1 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_LED2_ALED2VAL, &led_2_aled_2 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_LED1_ALED1VAL, &led_1_aled_1 );
        if ( HEARTRATE3_OK == error_flag )
        {
            log_printf( &logger, "%lu;%lu;%lu;%lu;%lu;%lu;\r\n", 
                        led_2, aled_2, led_1, aled_1, led_2_aled_2, led_1_aled_1 );
        }
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
