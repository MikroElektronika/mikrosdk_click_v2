/*!
 * \file 
 * \brief HeartRate Click example
 * 
 * # Description
 * This click features an advanced oximeter and heart rate monitoring sensor, 
 * which relies on two integrated LEDs. It is enough to place an index finger on a top 
 * of the sensor to get both of the heart rate and blood oxygen saturation via the I2C interface. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes heartrate driver and click board
 * 
 * ## Application Task  
 * Reading the value from both Ir and Red diode displaying their average values
 * 
 * ## Note
 * <pre>
 * MCU              : STM32F107VCT6
 * Dev. Board       : Fusion for ARM v8
 * </pre>
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "heartrate.h"

// ------------------------------------------------------------------ VARIABLES

static heartrate_t heartrate;
static log_t logger;

static uint16_t counter1 = 0;
static uint8_t  counter2 = 0;
static uint8_t  sample_num;

static uint16_t ir_buff[ 16 ]  = { 0 };
static uint16_t red_buff[ 16 ] = { 0 };
static uint32_t ir_average;
static uint32_t red_average;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    heartrate_cfg_setup( &cfg );
    HEARTRATE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate_init( &heartrate, &cfg );

    heartrate_default_cfg( &heartrate );
    Delay_ms( 100 );
}

void application_task ( void )
{
    if ( heartrate_data_ready( &heartrate ) )      
    {
        sample_num = heartrate_read_ir_red( &heartrate, ir_buff, red_buff );             
        if ( sample_num >= 1 )
        {

            ir_average = 0;
            red_average = 0;
            for ( counter1 = 0; counter1 < sample_num; counter1++ )
            {              
                ir_average += ir_buff[ counter1 ];
                red_average += red_buff[ counter1 ];
            }
                                            
            ir_average  /= sample_num;
            red_average /= sample_num;
            counter2++;
            if ( counter2 > 100 )
            {
                if( red_average > 100 && ir_average > 100 )                
                {       
                    log_printf( &logger, "Average value of Red LED sensor per 100 samples: %u\r\n", red_average );

                    log_printf( &logger, "Average value of IR LED sensor per 100 samples: %u\r\n", ir_average );

                    counter2 = 0; 
                }
                else
                {
                    log_printf( &logger, "Place finger on sensor\r\n" );
                    Delay_ms( 200 );
                }
            }          
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
