/*!
 * @file main.c
 * @brief Tdc Click example
 *
 * # Description
 * This library contains an API for the TDC Click driver.
 * This demo application shows the use of a TDC Click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app set default settings and 
 * the configures the measurement ( set the pulse to 100 us ).
 *
 * ## Application Task
 * This is an example that shows the use of a TDC Click board™.
 * In this example, after the START signal, the app sends 3 STOP signals per 100 microseconds.
 * The application reads and displays the value of Time, Clock count and 
 * Time-of-Flight values of three performed measurements.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "tdc.h"

static tdc_t tdc;
static tdc_t tdc_pulse;
static log_t logger;
static uint16_t pulse_us;
static uint8_t count_stop;
static uint8_t num_stops;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tdc_cfg_t tdc_cfg;  /**< Click config object. */
    tdc_cfg_t tdc_cfg1;
    static uint8_t cal_periods;
    static uint8_t avg_cycles;
    static uint8_t sel_mode;

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

    tdc_cfg_setup( &tdc_cfg );
    TDC_MAP_MIKROBUS( tdc_cfg, MIKROBUS_1 );
    tdc_cfg_setup( &tdc_cfg1 );
    TDC_MAP_MIKROBUS( tdc_cfg1, MIKROBUS_2 );
    err_t init_flag  = tdc_init( &tdc, &tdc_cfg );
    init_flag  |= tdc_init( &tdc_pulse,  &tdc_cfg1 );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    tdc_default_cfg ( &tdc );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
    
    cal_periods = 10;
    avg_cycles = 1;
    num_stops = 3;
    sel_mode = 1;
    pulse_us = 100;
    count_stop = 1;
    tdc_setup_measurement( &tdc, cal_periods, avg_cycles, num_stops, sel_mode );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static uint32_t p_time[ 5 ];
    static uint32_t p_clock_count[ 5 ];
    static uint32_t p_tof[ 5 ];
    
    tdc_start_measurement( &tdc );

    while ( tdc_get_trg( &tdc ) == 0 );
   
    tdc_gen_pulse( &tdc_pulse, pulse_us, num_stops );
   
    while ( tdc_get_interrupt( &tdc ) == 1 );
   
    tdc_get_measurement( &tdc, TDC_MCU_CLOCK_MODE_168_MHZ, count_stop, p_time, p_clock_count, p_tof );
    
    log_printf( &logger, " Time[ 0 ]        = %lu\r\n", p_time[ 0 ] ); 
    log_printf( &logger, " Time[ 1 ]        = %lu\r\n", p_time[ 1 ] ); 
    log_printf( &logger, " Time[ 2 ]        = %lu\r\n", p_time[ 2 ] );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    log_printf( &logger, " Clock count[ 0 ] = %lu\r\n", p_clock_count[ 0 ] );
    log_printf( &logger, " Clock count[ 1 ] = %lu\r\n", p_clock_count[ 1 ] );
    log_printf( &logger, " Clock count[ 2 ] = %lu\r\n", p_clock_count[ 2 ] );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );

    log_printf( &logger, " TOF[ 0 ]         = %u us\r\n", p_tof[ 0 ] ); 
    log_printf( &logger, " TOF[ 1 ]         = %u us\r\n", p_tof[ 1 ] );  
    log_printf( &logger, " TOF[ 2 ]         = %u us\r\n", p_tof[ 2 ] );    
    log_printf( &logger, "---------------------------\r\n" );
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
