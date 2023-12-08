/*!
 * \file 
 * \brief Accel14 Click example
 * 
 * # Description
 * This application measures accelermeter data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * SPI, check device ID, sets default configuration, also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Accel 14 Click board.
 * Measured and display Acceleration data for X-axis, Y-axis and Z-axis.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes for every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accel14.h"

// ------------------------------------------------------------------ VARIABLES

static accel14_t accel14;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel14_cfg_t cfg;

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

    accel14_cfg_setup( &cfg );
    ACCEL14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel14_init( &accel14, &cfg );

    Delay_ms( 100 );

    log_printf( &logger, "   Driver init done   \r\n" );
    log_printf( &logger, "--------------------- \r\n" );
    log_printf( &logger, " Communication check  \r\n" );

    if ( accel14_check_communication( &accel14 ) == ACCEL14_CHECK_ID_SUCCESS )
    {
        log_printf( &logger, "       SUCCESS        \r\n" );
        log_printf( &logger, "--------------------- \r\n" );
    }
    else
    {
        log_printf( &logger, "        ERROR         \r\n" );
        log_printf( &logger, "   Reset the device   \r\n" );
        log_printf( &logger, "--------------------- \r\n" );
        for ( ; ; );
    }

    log_printf( &logger, " Set default config.  \r\n" );
    log_printf( &logger, "--------------------- \r\n" );
    accel14_default_cfg( &accel14 );
    Delay_ms( 100 );

    log_printf( &logger, "  Acceleration data:  \r\n" );
    log_printf( &logger, "--------------------- \r\n" );
}

void application_task ( void )
{
    accel14_accel_t accel_data;
    uint8_t data_ready_flag;

    data_ready_flag = accel14_check_accel_data_ready( &accel14 );
    Delay_ms( 10 );

    if ( data_ready_flag == ACCEL14_NEW_DATA_AVAILABLE )
    {
        accel14_get_data ( &accel14, &accel_data );

        log_printf( &logger, "  Accel X : %d \r\n", accel_data.x );
        log_printf( &logger, "  Accel Y : %d \r\n", accel_data.y );
        log_printf( &logger, "  Accel Z : %d \r\n", accel_data.z );
        log_printf( &logger, "--------------------- \r\n" );
        Delay_ms( 1000 );
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
