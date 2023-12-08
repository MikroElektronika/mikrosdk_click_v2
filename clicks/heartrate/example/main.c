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
 * Initializes heartrate driver and set the click board default configuration.
 * 
 * ## Application Task  
 * Reading values from both Ir and Red diode and displaying their average values on the USB UART.
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

static uint16_t  counter = 500;
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
        if ( sample_num > 0 )
        {
            ir_average = 0;
            red_average = 0;
            for ( uint8_t cnt = 0; cnt < sample_num; cnt++ )
            {              
                ir_average += ir_buff[ cnt ];
                red_average += red_buff[ cnt ];
            }                 
            ir_average  /= sample_num;
            red_average /= sample_num;
            counter++;
            if( red_average > 100 && ir_average > 100 )                
            {       
                log_printf( &logger, "%lu;%lu;\r\n", red_average, ir_average );
                counter = 500;
            }
            else
            {
                if ( counter > 500 ) 
                {
                    log_printf( &logger, "Please place your index finger on the sensor.\r\n" );
                    counter = 0;
                }
            }   
        }
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
