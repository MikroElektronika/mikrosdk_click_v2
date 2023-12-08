/*!
 * \file 
 * \brief Alcohol2 Click example
 * 
 * # Description
 * The demo application gets Alcohol data and logs data to USBUART.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device configuration.
 *  
 * ## Application Task  
 * Gets Alcohol (C2H5OH) data and logs data to USBUART every 500ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "alcohol2.h"

// ------------------------------------------------------------------ VARIABLES

static alcohol2_t alcohol2;
static log_t logger;

static float alcohol_value;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    alcohol2_cfg_t cfg;

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

    alcohol2_cfg_setup( &cfg );
    ALCOHOL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    alcohol2_init( &alcohol2, &cfg );

    alcohol2_write_byte( &alcohol2, ALCOHOL2_MODECN_REG, ALCOHOL2_DEEP_SLEEP_MODE );
    alcohol2_write_byte( &alcohol2, ALCOHOL2_LOCK_REG,   ALCOHOL2_WRITE_MODE );
    alcohol2_write_byte( &alcohol2, ALCOHOL2_TIACN_REG, ALCOHOL2_EXT_TIA_RES | ALCOHOL2_100_OHM_LOAD_RES );
    alcohol2_write_byte( &alcohol2, ALCOHOL2_REFCN_REG, ALCOHOL2_VREF_INT | ALCOHOL2_50_PERCENTS_INT_ZERO | ALCOHOL2_BIAS_POL_NEGATIVE | ALCOHOL2_0_PERCENTS_BIAS );

    log_printf( &logger, "Alcohol 2 is initialized\r\n" );
    Delay_ms( 300 );
}

void application_task ( void )
{
    alcohol_value = alcohol2_read_alcohol( &alcohol2 );
    log_printf( &logger, "Alcohol value : %f \r\n", alcohol_value );
    Delay_ms( 500 );
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
