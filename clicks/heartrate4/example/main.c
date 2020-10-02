/*!
 * \file 
 * \brief HeartRate4 Click example
 * 
 * # Description
 * This click has an integrated pulse oximetry and heart-rate monitor module. It includes 
 * internal LEDs, photodetectors, optical elements, and low-noise electronics with ambient 
 * light rejection. Since oxygen-saturated blood absorbs more infrared light than red light, 
 * and unsaturated blood absorbs more red light than infrared light, the SpO2 readings 
 * are calculated by the comparison of the amount of these two types of light.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, applies default settings, and makes an initial log.
 * 
 * ## Application Task  
 * This example demonstrates the use of Heart rate 4 board. It is set in heart rate mode, 
 * and reads reflected red values and displays the results on USART terminal.
 * 
 * *note:* 
 * <pre>
 *  MCU              : STM32F107VCT6
 *  Dev. Board       : Fusion for ARM v8
 * </pre>
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "heartrate4.h"

// ------------------------------------------------------------------ VARIABLES

static heartrate4_t heartrate4;
static log_t logger;

static uint32_t red_samp = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    heartrate4_cfg_setup( &cfg );
    HEARTRATE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate4_init( &heartrate4, &cfg );

    Delay_ms( 100 );
    heartrate4_default_cfg( &heartrate4 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    if ( heartrate4_get_intrrupt( &heartrate4, 1 ) & 0x40 )
    {
        red_samp = heartrate4_get_red_val( &heartrate4 );
        if ( red_samp > 0 && red_samp < 32000 )
        {
            log_printf( &logger, "Place Finger On Sensor\r\n" );
            Delay_ms( 1000 );
        }
        else if ( red_samp != 0 )
        {
            log_printf( &logger, "%u\r\n", red_samp );
        }
//         log_printf( &logger, "------------------------------\r\n" );
//         Delay_ms( 1000 );
    }
    else
    {
        Delay_ms( 1 );
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
