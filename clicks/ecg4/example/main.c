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
 * Initializes the driver, sets the driver handler and enables the click board.
 * 
 * ## Application Task  
 * Reads the received data and parses it on the USB UART if the response buffer is ready.
 * 
 * ## Additional Function
 * - ecg4_process - The general process of collecting data the module sends.
 * - plot_data - Displays raw ECG data.
 * - log_data - Displays the real time BPM heart rate.
 * - process_response - Checks the response and displays raw ECG data or heart rate (BPM).
 * - make_response - Driver handler function which stores data in the response buffer.
 * 
 * @note
 * Use the Serial Plot application for data plotting.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ecg4.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

static ecg4_t ecg4;
static log_t logger;

static uint8_t response[ 256 ];
static uint8_t row_counter;
static uint8_t row_size_cnt;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void ecg4_process ( void )
{
    int32_t rx_size;
    char rx_buff;
    
    rx_size = ecg4_generic_read( &ecg4, &rx_buff, 1 );

    if ( rx_size > 0 )
    { 
        ecg4_uart_isr( &ecg4, rx_buff );
    }
}

void plot_data ( int16_t plot_data )
{
    log_printf( &logger, "%d;\r\n", plot_data );
}

void log_data ( uint8_t code_val, uint8_t data_val )
{
    if ( code_val == ECG4_HEART_RATE_CODE_BYTE )
    {
        log_printf( &logger, "** Real-time Heart Rate : %d BPM **\r\n", ( int16_t ) data_val );
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
        
        if ( response[ idx_cnt ] == ECG4_HEART_RATE_CODE_BYTE )
        {
            log_data( response[ idx_cnt ], response[ idx_cnt + 2 ] );
        }
        
        idx_cnt += ( response[ idx_cnt + 1 ] + 2 );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg4_cfg_t cfg;

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

    ecg4_cfg_setup( &cfg );
    ECG4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg4_init( &ecg4, &cfg );

    ecg4.driver_hdl = make_response;
    Delay_ms ( 500 );

    ecg4_module_reset ( &ecg4 );
    ecg4_enable_ldo_ctrl ( &ecg4, ECG4_ENABLE_LDO_CTRL );

    Delay_ms ( 1000 );
}

void application_task ( void )
{
    ecg4_process(  );
    if ( ecg4_responseReady( &ecg4 ) )
    {
        process_response( );
    }
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
