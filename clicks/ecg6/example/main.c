/*!
 * \file 
 * \brief Ecg6 Click example
 * 
 * # Description
 * ECG 6 Click contain integrated electrocardiogram, pulse oximeter, 
 * heart rate monitor sensor module.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize I2C module and all necessary pins. Checking communication accuracy
 * and running default configuration for measurement.
 * 
 * ## Application Task  
 * Measures an ECG signal or PPG sensor and draws a graph on a SerialPlot
 * 
 * ##Additional Functions :
 * - plot_ecg_data ( ) -  Sends ECG sensor data to SerialPlot
 * - plot_ppg_data ( ) -  Sends PPG sensor data to SerialPlot
 * 
 * 
 * *note:* 
 * When using ECG measurement - PPG measurement must be switched off ...
 * Drawing speeds vary for PPG and ECG sensor.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ecg6.h"

// ------------------------------------------------------------------ VARIABLES

static ecg6_t ecg6;
static log_t logger;

static uint8_t ECG_EXAMPLE = 1;
static uint8_t PPG_EXAMPLE = 0;
static uint8_t DEMO_EXAMPLE;

static uint32_t time_cnt = 0;
static uint8_t device_check;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ecg6_cfg_setup( &cfg );
    ECG6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg6_init( &ecg6, &cfg );
    
    Delay_ms( 1000 );

    device_check = ecg6_check_path_id( &ecg6 );
    if ( device_check != 0 )
    {
       log_printf( &logger, " -- > Device ERROR!!! \r\n" );
       for ( ; ; );
    }
    log_printf( &logger, " -- > Device OK!!! \r\n" );

    if ( DEMO_EXAMPLE == ECG_EXAMPLE )
    {
        ecg6_default_cfg( &ecg6 );
    }
    else
    {
        ecg6_ppg_default_config( &ecg6 );
    }

    log_printf( &logger, " ---- Configuration done ----- \r\n" );
    Delay_ms( 1000 );

    time_cnt = 0;
}

static void plot_ecg_data ( uint32_t ecg_data )
{
    uint8_t tmp;
    uint8_t timer;

    tmp = ecg_data & 0x3FFFFF;
    timer = time_cnt++;
    log_printf( &logger, " %d, \r\n", tmp );
    log_printf( &logger, " %d, \r\n", timer );
    Delay_ms( 3 );
}

static void plot_ppg_data ( uint32_t ir_data, uint32_t red_data )
{
    uint8_t tmp;
    uint8_t tmf;
    uint8_t tmd;

    tmp = ir_data & 0x0007FFFF;
    tmf = red_data & 0x0007FFFF;
    tmd = time_cnt++;

    log_printf( &logger," %d \r\n", tmp );
    log_printf( &logger," %d \r\n", tmf );
    log_printf( &logger," %d \r\n", tmd );
    Delay_ms( 40 );
}

void application_task ( void )
{
    ecg6_element_t sample;
    ecg6_get_sample_data( &ecg6, &sample, 0x00 );
    
    if ( DEMO_EXAMPLE == ECG_EXAMPLE )
    {
        log_printf( &logger, " %u ", sample.element_1 );
        plot_ecg_data( sample.element_1 );
    }
    
    else
    {
        log_printf( &logger, " %u, %u ", sample.element_1, sample.element_2 );
        plot_ppg_data( sample.element_1, sample.element_2 );
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
