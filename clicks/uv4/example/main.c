/*!
 * \file 
 * \brief UV4 Click example
 * 
 * # Description
 * This application reads configured measurements from selected channels, and
 * then logs them.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, performs reset command, enables
 * channels 0, 1 and 4 and configures channel 0 as 24-bit witch measures WHITE light,
 * channel 1 as 24-bit witch measures Small IR light, and channel 4 as 16-bit witch
 * measures UV light.
 * 
 * ## Application Task  
 * Reads all configured measurements from selected channels
 * and logs results on USB UART. Repeats operation every 500ms.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uv4.h"

// ------------------------------------------------------------------ VARIABLES

static uv4_t uv4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uv4_cfg_t cfg;

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

    uv4_cfg_setup( &cfg );
    UV4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uv4_init( &uv4, &cfg );
    uv4_default_cfg( &uv4 );
}

void application_task ( void )
{
    uint8_t cnt;
    uint8_t pom = 1;
    uint32_t data_r[ 6 ];
    
    uv4_read_measurements( &uv4, &data_r[ 0 ] );
    
    for ( cnt = 0; cnt < 6; cnt++ )
    {
        if ( uv4.config_byte & pom )
        {
            switch ( uv4.optical_data[ cnt ] )
            {
                case UV4_OPT_FUNC_SMALL_IR:
                {
                    log_printf( &logger, "Small IR: " );
                    break;
                }
                case UV4_OPT_FUNC_MEDIUM_IR:
                {
                    log_printf( &logger, "Medium IR: " );
                    break;
                }
                case UV4_OPT_FUNC_LARGE_IR:
                {
                    log_printf( &logger, "Large IR: " );
                    break;
                }
                case UV4_OPT_FUNC_WHITE:
                {
                    log_printf( &logger, "White : " );
                    break;
                }
                case UV4_OPT_FUNC_LARGE_WHITE:
                {
                    log_printf( &logger, "Large White: " );
                    break;
                }
                case UV4_OPT_FUNC_UV:
                {
                    log_printf( &logger, "UV: " );
                    break;
                }
                case UV4_OPT_FUNC_UV_DEEP:
                {
                    log_printf( &logger, "UV-Deep: " );
                    break;
                }
                default:
                {
                    break;
                }
            }
            log_printf( &logger, "%d\r\n", data_r[ cnt ] );
        }
        pom <<= 1;
    }
    Delay_ms ( 500 );
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
