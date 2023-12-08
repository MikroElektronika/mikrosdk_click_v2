/*!
 * \file 
 * \brief Uv3 Click example
 * 
 * # Description
 * Converts solar UV light intensity to digital data 
 * and measure UV radiation under long time solar UV exposure.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C, enable sensor and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of UV 3 Click board.
 * UV 3 Click communicates with register via I2C by write to register and read from register,
 * measurement UV data, calculate UV radiation level and write log.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 2 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uv3.h"

// ------------------------------------------------------------------ VARIABLES

static uv3_t uv3;
static log_t logger;

static uint16_t uv_data;
static uint8_t risk_lvl;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uv3_cfg_t cfg;

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

    uv3_cfg_setup( &cfg );
    UV3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uv3_init( &uv3, &cfg );
    uv3_default_cfg ( &uv3 );
}

void application_task ( void )
{
    uv_data = uv3_read_measurements( &uv3 );
    
    Delay_ms( 200 );

    risk_lvl = uv3_risk_level( uv_data );

    log_printf( &logger, "UV value  : %d\r\n ", uv_data );

    log_printf( &logger, "Radiation lvl : " );

    if ( risk_lvl == UV3_RAD_LOW )
    {
        log_printf( &logger, "Low\r\n " );
    }

    if ( risk_lvl == UV3_RAD_MODERATE )
    {
        log_printf( &logger, "Moderate\r\n " );
    }

    if ( risk_lvl == UV3_RAD_HIGH )
    {
        log_printf( &logger, "High\r\n " );
    }

    if ( risk_lvl == UV3_RAD_VERY_HIGH )
    {
        log_printf( &logger, "Very High\r\n " );
    }

    if ( risk_lvl == UV3_RAD_EXTREME )
    {
        log_printf( &logger, "Extreme\r\n " );
    }

    Delay_ms( 2000 );
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
