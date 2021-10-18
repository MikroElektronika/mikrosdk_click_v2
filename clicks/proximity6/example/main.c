/*!
 * \file 
 * \brief Proximity6 Click example
 * 
 * # Description
 * This application can detect the proximity of an object via sensor and can show the results
 * of proximity as a graphic view, or show the position of the object.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Sets the registers in default state and configures the device to work in
 * proper operating mode (Proximity Mode). 
 * ## Application Task  
 * Example can show the data register values as graphic view in desired resolution.
 * Also can determine from which side the object (body) affects on the sensor and logs results on USB UART.
 * Results will be shown only when one or more data registers are updated with the new value (sensor detects the change).
 * 
 * Additional Functions :
 * - void proximity6_logGraphicRes() - Function loggs on USB UART results from the data proximity registers as graphic view.
 * - void proximity6_logPositionRes() - Function loggs on USB UART the position of the object which affects of the sensor.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity6.h"

// ------------------------------------------------------------------ VARIABLES

static proximity6_t proximity6;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void proximity6_log_graphic_res ( proximity6_t *ctx )
{
    uint8_t count1;
    uint8_t count2;
    uint8_t axis_data[ 4 ];

    proximity6_display_data( ctx, &axis_data[ 0 ], PROXIMITY6_RESOLUTION_300 );

    for ( count1 = 0; count1 < 4; count1++ )
    {
        if ( axis_data[ count1 ] == 0 )
        {
            log_printf( &logger, "MIN\r\n" );
        }
        else
        {
            for ( count2 = 0; count2 <= axis_data[ count1 ]; count2++ )
            {
                if ( count2 < axis_data[ count1 ] )
                {
                    log_printf( &logger, "|" );
                }
                else
                {
                    log_printf( &logger, "|\r\n" );
                }
            }
        }
    }
    log_printf( &logger, "\r\n" );
}

void proximity6_log_position_res ( proximity6_t *ctx )
{
    uint8_t check_pos;

    proximity6_get_position( ctx, &check_pos );

    switch ( check_pos )
    {
        case PROXIMITY6_RIGHT_POS :
        {
            log_printf( &logger, "Right\r\n" );
            break;
        }
        case PROXIMITY6_LEFT_POS :
        {
            log_printf( &logger, "Left\r\n" );
            break;
        }
        case PROXIMITY6_BOTTOM_POS :
        {
            log_printf( &logger, "Bottom\r\n" );
            break;
        }
        case PROXIMITY6_UP_POS :
        {
            log_printf( &logger, "Up\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
    Delay_ms( 200 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity6_cfg_t cfg;

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

    proximity6_cfg_setup( &cfg );
    PROXIMITY6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity6_init( &proximity6, &cfg );

    Delay_ms( 300 );
    
    proximity6_default_cfg( &proximity6 );
    proximity6_load_settings( &proximity6 );
    proximity6_set_mode( &proximity6, PROXIMITY6_PROXIMITY_MODE );

    log_printf( &logger, "Proximity 6 is initialized\r\n\r\n" );
    Delay_ms( 300 );
}

void application_task ( void )
{
    //  Task implementation.
    
    proximity6_log_position_res( &proximity6 );
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
