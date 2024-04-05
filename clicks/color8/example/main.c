/*!
 * \file 
 * \brief Color8 Click example
 * 
 * # Description
 * This demo app reads RED, GREEEN, BLUE, IR data and return detect color.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device device configuration for start measurement.
 * 
 * ## Application Task  
 * Reads RED, GREEEN, BLUE and IR data. 
 * Converts data to HSL value and return detect color.
 * For a successful color test, place a click near the color of the monitor and detect the color on the screen.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "color8.h"

// ------------------------------------------------------------------ VARIABLES

static color8_t color8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    color8_cfg_t cfg;

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

    color8_cfg_setup( &cfg );
    COLOR8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color8_init( &color8, &cfg );

    color8_write_byte( &color8, COLOR8_REG_SYSTEM_CONTROL, COLOR8_SS_SW_RESET_IS_DONE | COLOR8_SS_INT_PIN_IS_ACTIVE );
    color8_write_byte( &color8, COLOR8_REG_MODE_CONTROL_1, COLOR8_MC1_IR_DATA_GAIN_X1 |
                                                       COLOR8_MC1_RGB_DATA_GAIN_X1 |
                                                       COLOR8_MC1_MEASURE_MODE_35ms );
     
    color8_write_byte( &color8, COLOR8_REG_MODE_CONTROL_2, COLOR8_MC2_MEASUREMENT_IS_ACTIVE );
    log_printf( &logger, "---- Start measurement ----\r\n");
}

void application_task ( void )
{
    uint16_t red_data;
    uint16_t green_data;
    uint16_t blue_data;
    uint16_t ir_data;
    uint8_t is_color;
    float color_value;
    
    red_data = color8_read_data( &color8, COLOR8_REG_RED_DATA );
    log_printf( &logger, " RED data : %d \r\n", red_data );

    green_data = color8_read_data( &color8, COLOR8_REG_GREEN_DATA );
    log_printf( &logger, " GREEN data : %d \r\n", green_data );

    blue_data = color8_read_data( &color8, COLOR8_REG_BLUE_DATA );
    log_printf( &logger, " BLUE data : %d \r\n", blue_data );

    ir_data = color8_read_data( &color8, COLOR8_REG_IR_DATA );
    log_printf( &logger, " IR data : %d \r\n", ir_data );

    color_value = color8_get_color_value( &color8 );
    log_printf( &logger, " HSL color value : %f \r\n", color_value );

    is_color = color8_get_color( &color8, color_value );
    
    switch( is_color )
    {
        case 1:
        {
            log_printf( &logger, "--- Color: ORANGE \r\n" );
            break;
        }
        case 2:
        {
            log_printf( &logger, "--- Color: RED \r\n" );
            break;
        }
        case 3:
        {
            log_printf( &logger, "--- Color: PINK \r\n" );
            break;
        }
        case 4:
        {
            log_printf( &logger, "--- Color: PURPLE \r\n" );
            break;
        }
        case 5:
        {
            log_printf( &logger, "--- Color: BLUE \r\n" );
            break;
        }
        case 6:
        {
            log_printf( &logger, "--- Color: CYAN \r\n" );
            break;
        }
        case 7:
        {
            log_printf( &logger, "--- Color: GREEN \r\n" );
            break;
        }
        case 8:
        {
            log_printf( &logger, "--- Color: YELLOW \r\n" );
            break;
        }
        default:
        {
            break;
        }
    }
    Delay_ms ( 1000 );
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
