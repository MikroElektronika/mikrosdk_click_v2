/*!
 * @file main.c
 * @brief Oximeter5 Click example
 *
 * # Description
 * This library contains API for Oximeter 5 Click driver.
 * The demo application reads and calculate 
 * SpO2 oxygen saturation data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and log UART.
 * After driver initialization the app set 
 * driver interface setup and  default settings,
 * buffer length of 100 stores 4 seconds of samples running at 25sps
 * read the first 100 samples, and determine the signal range.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Oximeter 5 Click board™.
 * In this example, display the IR and RED ADC data, 
 * and the SpO2 oxygen saturation data [ 0% - 100% ].
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @note
 * A measurement time of at least 10 seconds is required 
 * for the SpO2 oxygen saturation data to be valid.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "oximeter5.h"

static oximeter5_t oximeter5;
static log_t logger;
static uint32_t aun_ir_buffer[ 100 ];
static uint32_t aun_red_buffer[ 100 ];
static uint32_t un_min, un_max, un_prev_data, un_brightness;
static float f_temp;
static uint8_t n_spo2;
  
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    oximeter5_cfg_t oximeter5_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    oximeter5_cfg_setup( &oximeter5_cfg );
    OXIMETER5_MAP_MIKROBUS( oximeter5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == oximeter5_init( &oximeter5, &oximeter5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    if ( OXIMETER5_ERROR == oximeter5_default_cfg ( &oximeter5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms( 100 ); 
    
    un_brightness = 0;
    un_min = 0x3FFFF;
    un_max = 0;
  
    for ( uint8_t n_cnt = 0; n_cnt < 100; n_cnt++ )
    {
        while ( oximeter5_check_interrupt( &oximeter5 ) == OXIMETER5_INTERRUPT_ACTIVE );
        
        oximeter5_read_sensor_data( &oximeter5, &aun_red_buffer[ n_cnt ], &aun_ir_buffer[ n_cnt ] );
    
        if ( un_min > aun_red_buffer[ n_cnt ] )
        {
            un_min = aun_red_buffer[ n_cnt ];
        }
    
        if ( un_max < aun_red_buffer[ n_cnt ] )
        {
            un_max = aun_red_buffer[ n_cnt ];
        }
    }

    oximeter5_get_oxygen_saturation( &aun_ir_buffer[ 0 ], 100, &aun_red_buffer[ 0 ], &n_spo2 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 ); 
}

void application_task ( void ) 
{
    for ( uint8_t n_cnt = 25; n_cnt < 100; n_cnt++ )
    {
        aun_red_buffer[ n_cnt - 25 ] = aun_red_buffer[ n_cnt ];
        aun_ir_buffer[ n_cnt - 25 ] = aun_ir_buffer[ n_cnt ];

        if ( un_min > aun_red_buffer[ n_cnt ] )
        {
            un_min = aun_red_buffer[ n_cnt ];
        }
      
        if ( un_max < aun_red_buffer[ n_cnt ] )
        {
            un_max=aun_red_buffer[n_cnt];
        }
    }

    for ( uint8_t n_cnt = 75; n_cnt < 100; n_cnt++ )
    {
        un_prev_data = aun_red_buffer[ n_cnt - 1 ];
        while ( oximeter5_check_interrupt( &oximeter5 ) == OXIMETER5_INTERRUPT_ACTIVE ); 

        oximeter5_read_sensor_data( &oximeter5, &aun_red_buffer[ n_cnt ], &aun_ir_buffer[ n_cnt ] );

        if ( aun_red_buffer[ n_cnt ] > un_prev_data )
        {
            f_temp = aun_red_buffer[ n_cnt ]-un_prev_data;
            f_temp /= ( un_max - un_min );
            f_temp *= MAX_BRIGHTNESS;
            f_temp = un_brightness - f_temp;
        
            if ( f_temp < 0 )
            {
                un_brightness = 0;
            }
            else
            {
                un_brightness = ( uint32_t ) f_temp;
            }
        }
        else
        {
            f_temp = un_prev_data - aun_red_buffer[ n_cnt ];
            f_temp /= ( un_max - un_min );
            f_temp *= MAX_BRIGHTNESS;
            un_brightness += ( uint32_t ) f_temp;
            
            if ( un_brightness > MAX_BRIGHTNESS )
            {
                un_brightness = MAX_BRIGHTNESS;
            }
        }
      
        if ( ( OXIMETER5_OK == oximeter5_get_oxygen_saturation( &aun_ir_buffer[ 0 ], 100, &aun_red_buffer[ 0 ], &n_spo2 ) ) )
        {
            if ( aun_ir_buffer[n_cnt] > 10000  ) 
            {
                log_printf( &logger, "\tIR    : %lu \r\n", aun_ir_buffer[ n_cnt ] );
                log_printf( &logger, "\tRED   : %lu \r\n", aun_red_buffer[ n_cnt ] ); 
                log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
                log_printf( &logger, "\tSPO2  : %d %%\r\n", ( uint16_t ) n_spo2 );
                log_printf( &logger, "-----------------------------\r\n" );
                Delay_ms( 100 );       
            }
            else
            {
                Delay_ms( 10 );      
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
