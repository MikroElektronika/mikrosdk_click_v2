/*!
 * \file 
 * \brief Ecg3 Click example
 * 
 * # Description
 * This click is made for ECG and HR, 
 * equipped with an ultra-low power, single channel, integrated biopotential AFE, 
 * with the ECG and R-to-R detection functionality. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI interface and performs the all necessary configuration 
 * for device to work properly.
 * 
 * ## Application Task  
 * Reads ECG Data every 8ms and sends this data to the serial plotter.
 * 
 * *note:* 
 * Additional Functions :
 *  - void plot_ecg() - Sends ECG Data to the serial plotter.
 *  - void log_rtor() - Sends Heart Rate and R - R Data to the uart terminal.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ecg3.h"

// ------------------------------------------------------------------ VARIABLES

static ecg3_t ecg3;
static log_t logger;

static uint32_t ecg_data;
static uint16_t rr_data;
static uint16_t hr_data;
static uint32_t meas_time_cnt = 0;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void plot_ecg ( )
{
    if ( ecg_data > 50000 )
    {
        log_printf( &logger,"    %lu,       %lu\r\n", ecg_data, meas_time_cnt );
        
        if ( meas_time_cnt == 0xFFFFFFFF )
        {
            meas_time_cnt = 0;
        }
        else
        {
            meas_time_cnt++;
        }
    }
    Delay_ms ( 8 );
}

void log_rtor ( )
{
    if ( ( rr_data != 0 ) && ( hr_data != 65535 ) )
    {
        log_printf( &logger,"R - R Interval : %u ms\r\n", rr_data );
        log_printf( &logger,"Heart Rate :  %u BPM\r\n", hr_data );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg3_cfg_t cfg;

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

    ecg3_cfg_setup( &cfg );
    ECG3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg3_init( &ecg3, &cfg );

    ecg3_sw_reset( &ecg3 );
    ecg3_fifo_reset( &ecg3 );
    Delay_ms ( 100 );

    ecg3_default_cfg ( &ecg3 );
    Delay_ms ( 300 );
}

void application_task ( void )
{
    ecg3_get_ecg( &ecg3, &ecg_data );

    plot_ecg( );
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
