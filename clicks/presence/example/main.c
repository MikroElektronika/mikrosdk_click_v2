/*!
 * \file 
 * \brief Presence Click example
 * 
 * # Description
 * This application enables usage of sensor for motion and presence sensing
 * and measuring of object's and ambient temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and performs the click default configuration.
 * 
 * ## Application Task  
 * Checks whether a new event (motion, presence or over-temperature) is detected. 
 * If there's no event detected it reads the ambient and object temperature and displays
 * the results on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "presence.h"

// ------------------------------------------------------------------ VARIABLES

static presence_t presence;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    presence_cfg_t cfg;

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
    presence_cfg_setup( &cfg );
    PRESENCE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    presence_init( &presence, &cfg );

    if ( PRESENCE_ERROR == presence_default_cfg ( &presence ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t int_status = 0;
    uint8_t tp_presence = 0;
    uint8_t tp_motion = 0;
    float t_amb = 0;
    float t_obj = 0;
    
    if ( PRESENCE_OK == presence_generic_read( &presence, PRESENCE_REG_INTERRUPT_STATUS, &int_status, 1 ) )
    {
        if ( int_status & PRESENCE_INT_MASK1_PRESENCE )
        {
            if ( PRESENCE_OK == presence_generic_read( &presence, PRESENCE_REG_TP_PRESENCE, &tp_presence, 1 ) )
            {
                log_info( &logger, "Presence detected! Level: %u", ( uint16_t ) tp_presence );
            }
        }
        else if ( int_status & PRESENCE_INT_MASK1_MOTION )
        {
            if ( PRESENCE_OK == presence_generic_read( &presence, PRESENCE_REG_TP_MOTION, &tp_motion, 1 ) )
            {
                log_info( &logger, "Motion detected! Level: %u", ( uint16_t ) tp_motion );
            }
        }
        else if ( int_status & PRESENCE_INT_MASK1_TP_OT )
        {
            log_info( &logger, "Temp threshold exceeded!" );
        }
        else
        {
            if ( PRESENCE_OK == presence_ambient_temperature( &presence, &t_amb ) )
            {
                log_printf( &logger, "Ambient temperature: %.2f degC\r\n", t_amb );
            }
            if ( PRESENCE_OK == presence_object_temperature( &presence, &t_obj ) )
            {
                log_printf( &logger, "Object temperature: %.2f degC\r\n\n", t_obj );
            }
        }
    }
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
