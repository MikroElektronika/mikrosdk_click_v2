/*!
 * \file 
 * \brief Color10 Click example
 * 
 * # Description
 * Color 10 Click is carrying a sensor for RGB and IR light sensing as well as 
 * the RGB diode incorporated on the board which makes it good color detection 
 * device when its combined with a white LED.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize I2C driver.
 * 
 * ## Application Task  
 * This example senses orange, red, pink, purple, blue, cyan, green or yellow color
 * and IR light and print it via UART terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "color10.h"

// ------------------------------------------------------------------ VARIABLES

static color10_t color10;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void write_color ( void )
{
    float color_val;
    uint8_t color;
    
    color_val = color10_get_color_value( &color10 );
    color = color10_get_color( color_val );
    
    switch ( color )
    {
        case COLOR10_COLOR_ORANGE:
        {
            log_printf( &logger, "ORANGE" );
        break;
        }
    
        case COLOR10_COLOR_RED:
        {
            log_printf( &logger, "RED" );
        break;
        }
    
        case COLOR10_COLOR_PINK:
        {
            log_printf( &logger, "PINK" );
        break;
        }
    
        case COLOR10_COLOR_PURPLE:
        {
            log_printf( &logger, "PURPLE" );
        break;
        }
    
        case COLOR10_COLOR_BLUE:
        {
            log_printf( &logger, "BLUE" );
        break;
        }
    
        case COLOR10_COLOR_CYAN:
        {
            log_printf( &logger, "CYAN" );
        break;
        }
    
        case COLOR10_COLOR_GREEN:
        {
            log_printf( &logger, "GREEN" );
        break;
        }
    
        case COLOR10_COLOR_YELLOW:
        {
            log_printf( &logger, "YELLOW" );
        break;
        }
                
        default:
        {
            log_printf( &logger, "NOT DEFINED" );
        break;
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    color10_cfg_t cfg;
    uint8_t id_data;

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

    color10_cfg_setup( &cfg );
    COLOR10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color10_init( &color10, &cfg );
    Delay_ms( 500 );

    if ( color10_get_id( &color10 ) == COLOR10_DEVICE_ID )
    {
         log_printf( &logger, " -DEVICE ID OK\r\n" );
    }
    else
    {
        log_printf( &logger, " -DEVICE ID ERROR\r\n" );
        for( ; ; );
    }

    color10_config( &color10, COLOR10_CFG_HIGH_DYNAMIC_RANGE_1 |
                    COLOR10_CFG_INTEGRATION_TIME_SETT_50_MS |
                    COLOR10_CFG_AUTO_MODE |
                    COLOR10_CFG_TRIGGER_NO |
                    COLOR10_CFG_POWER_ON |
                    COLOR10_CFG_GAIN_1_X1 |
                    COLOR10_CFG_GAIN_2_X1 );
    log_printf( &logger, "-----Init done------\r\n" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    uint16_t read_data;
    float color_data;

    read_data = color10_generic_read ( &color10, COLOR10_CMD_REG_IR );
    log_printf( &logger, " -IR value: %d\r\n", read_data );
    log_printf( &logger, " -Color: " );
    write_color( void );

    log_printf( &logger, " ********************** \r\n" );
    Delay_ms( 1000 );
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
