/*!
 * \file 
 * \brief Ecg4 Click example
 * 
 * # Description
 * This example reads and processes data from ECG 4 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - ecg4_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ecg4.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static ecg4_t ecg4;
static log_t logger;

static uint8_t response[ 256 ];
static uint8_t row_counter;
static uint32_t plot_x;
static uint8_t row_size_cnt;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void ecg4_process ( void )
{
    uint16_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while( process_cnt != 0 )
    {
        rsp_size = ecg4_generic_read( &ecg4, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                ecg4_uart_isr( &ecg4, uart_rx_buffer[ check_buf_cnt ] );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            //Process delay 
            Delay_1ms( );
        }
    }
}

void plot_data ( int16_t plot_data )
{
    char plot_string[ 50 ];
    
    log_printf( &logger, "%d,%ld\r\n", plot_data, plot_x );
    
    if ( plot_data > 4000 )
    {
        //Sound_Play( 520, 25 );
        log_printf( &logger, "Sound_Play( 520, 25 );" );
    }
    
    if ( plot_x == 0xFFFFFFFF )
    {
        plot_x = 0;
    }
    else
    {
        plot_x++;
    }
    
    Delay_ms( 3 );
}

void log_data ( uint8_t code_val, uint8_t data_val )
{
    char log_string[ 20 ];

    if ( code_val == ECG4_SIGNAL_QUALITY_CODE_BYTE )
    {
        log_printf( &logger, "** Signal Quality (0 - sensor off, 200 - sensor on) : %d **\r\n", data_val );
    }
    else if ( code_val == ECG4_HEART_RATE_CODE_BYTE )
    {
        log_printf( &logger, "** Real-time Heart Rate : %d BPM **\r\n", data_val );
    }
}

void make_response ( uint8_t *op_code, uint8_t *row_size, uint8_t *rx_buff, uint8_t *row_cnt )
{
    uint8_t idx_cnt;
    
    if ( *row_cnt == 0 )
    {
        row_size_cnt = 0;
    }
    
    response[ row_size_cnt ] = *op_code;
    response[ row_size_cnt + 1 ] = *row_size;

    for ( idx_cnt = 0; idx_cnt < *row_size; idx_cnt++ )
    {
        response[ row_size_cnt + 2 + idx_cnt ] = rx_buff[ idx_cnt ];
    }
    
    row_size_cnt += ( *row_size + 2 );
    row_counter = *row_cnt;
}

void process_response( )
{
    uint8_t cnt;
    uint8_t idx_cnt;
    int16_t raw_data;
    
    idx_cnt = 0;
    
    for ( cnt = 0; cnt <= row_counter; cnt++ )
    {
        if ( response[ idx_cnt ] == ECG4_RAW_DATA_CODE_BYTE )
        {
            raw_data = response[ idx_cnt + 2 ];
            raw_data <<= 8;
            raw_data |= response[ idx_cnt + 3 ];
            
            plot_data( raw_data );
        }
        
        // if ( ( response[ idx_cnt ] == ECG4_SIGNAL_QUALITY_CODE_BYTE ) || ( response[ idx_cnt ] == ECG4_HEART_RATE_CODE_BYTE ) )
        // {
        //     log_data( response[ idx_cnt ], response[ idx_cnt + 2 ] );
        // }
        
        idx_cnt += (response[ idx_cnt + 1 ] + 2);
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ecg4_cfg_setup( &cfg );
    ECG4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg4_init( &ecg4, &cfg );

    ecg4.driver_hdl = make_response;
    Delay_ms( 300 );

    ecg4_module_reset ( &ecg4 );
    ecg4_enable_ldo_ctrl ( &ecg4, ECG4_ENABLE_LDO_CTRL );

    plot_x = 0;


    Delay_ms( 500 );
}

void application_task ( void )
{
    ecg4_process(  );
    process_response( );
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
