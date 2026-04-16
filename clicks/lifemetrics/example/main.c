/*!
 * @file main.c
 * @brief Life Metrics Click example
 *
 * # Description
 * This example demonstrates the use of the Life Metrics Click board by reading
 * ECG/PPG samples from the AFE FIFO and (optionally) reading accelerometer and
 * temperature measurements. ECG/PPG samples are parsed and logged in a simple
 * format suitable for plotting (e.g. serial plotter).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Life Metrics Click driver, performs default device
 * configuration, reads the external temperature sensor ID, and starts AFE
 * measurements when enabled.
 *
 * ## Application Task
 * Reads and parses AFE FIFO samples (ECG/PPG) and logs them. When enabled, it
 * also reads accelerometer data and temperature values and logs the results.
 *
 * @note
 * We recommend using the SerialPlot tool for data visualizing. 
 * Make sure to set up ECG electrodes properly.
 * Use prefix "E:" in the app for ECG data filtering, and prefix "P:" for PPG filtering.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lifemetrics.h"

#ifndef MIKROBUS_POSITION_LIFEMETRICS
    #define MIKROBUS_POSITION_LIFEMETRICS MIKROBUS_1
#endif

// It is recommended to keep ENABLE_ACCEL_TEMP_LOG disabled on low-speed systems
#define ENABLE_ECG_PPG_LOG      1
#define ENABLE_ACCEL_TEMP_LOG   0

static lifemetrics_t lifemetrics;
static log_t logger;

/**
 * @brief Life Metrics AFE log FIFO function.
 * @details This function logs AFE FIFO results to USB UART parsing ECG and PPG signals.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] fifo_data : FIFO data buffer.
 * @param[in] fifo_data_size : FIFO data size.
 * @return None.
 * @note None.
 */
static void lifemetrics_afe_log_fifo ( uint8_t *fifo_data, uint16_t fifo_data_size );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lifemetrics_cfg_t lifemetrics_cfg;  /**< Click config object. */

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
    lifemetrics_cfg_setup( &lifemetrics_cfg );
    LIFEMETRICS_MAP_MIKROBUS( lifemetrics_cfg, MIKROBUS_POSITION_LIFEMETRICS );
    if ( I2C_MASTER_ERROR == lifemetrics_init( &lifemetrics, &lifemetrics_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIFEMETRICS_ERROR == lifemetrics_default_cfg ( &lifemetrics ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint16_t temp_id[ 3 ] = { 0 };
    if ( LIFEMETRICS_OK == lifemetrics_temp_read_id ( &lifemetrics, temp_id ) )
    {
        log_printf ( &logger, " Temp Sensor ID: 0x%.4X%.4X%.4X\r\n", 
                     temp_id[ 2 ], temp_id[ 1 ], temp_id[ 0 ] );
    }
#if ENABLE_ECG_PPG_LOG
    if ( LIFEMETRICS_OK == lifemetrics_afe_start_meas ( &lifemetrics ) )
    {
        log_printf( &logger, " AFE measurement has started\r\n" );
    }
#endif
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#if ENABLE_ECG_PPG_LOG
    uint8_t fifo_data[ LIFEMETRICS_AFE_FIFO_BUFFER_SIZE ] = { 0 };
    uint16_t fifo_data_size = 0;
    if ( LIFEMETRICS_OK == lifemetrics_afe_read_fifo ( &lifemetrics, fifo_data, &fifo_data_size ) )
    {
        lifemetrics_afe_log_fifo ( fifo_data, fifo_data_size );
    }
#endif
#if ENABLE_ACCEL_TEMP_LOG
    float temperature = 0;
    lifemetrics_accel_data_t meas_data;
    if ( LIFEMETRICS_OK == lifemetrics_accel_get_data ( &lifemetrics, &meas_data ) )
    {
        log_printf( &logger, "Accel X: %.3f g\r\n", meas_data.accel.x );
        log_printf( &logger, "Accel Y: %.3f g\r\n", meas_data.accel.y );
        log_printf( &logger, "Accel Z: %.3f g\r\n", meas_data.accel.z );
        if ( LIFEMETRICS_OK == lifemetrics_temp_read_temp ( &lifemetrics, &temperature ) )
        {
            log_printf ( &logger, "Temperature: %.2f degC\r\n", temperature );
        }
    }
#endif
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

static void lifemetrics_afe_log_fifo ( uint8_t *fifo_data, uint16_t fifo_data_size )
{
    uint32_t adc_data = 0;
    uint8_t data_marker = 0;
    for ( uint16_t cnt = 0; cnt < fifo_data_size; cnt += LIFEMETRICS_AFE_FIFO_SAMPLE_SIZE )
    {
        data_marker = fifo_data[ cnt ] & LIFEMETRICS_AFE_FIFO_DATA_MARKER_MASK;
        adc_data = ( ( uint32_t ) fifo_data[ cnt + 2 ] << 12 ) | 
                   ( ( uint32_t ) fifo_data[ cnt + 1 ] << 4 ) | 
                   ( fifo_data[ cnt ] >> 4 );
        if ( ( 0 == adc_data ) && ( 0 == data_marker ) )
        {
            continue;
        }
        switch ( data_marker )
        {
            case LIFEMETRICS_AFE_FIFO_DATA_MARKER_PPG1_FIRST:
            {
                log_printf ( &logger, "P:%ld\r\n", adc_data );
                break;
            }
            case LIFEMETRICS_AFE_FIFO_DATA_MARKER_ECG_SEQ1_SUB1:
            {
                log_printf ( &logger, "E:%ld\r\n", adc_data );
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

// ------------------------------------------------------------------------ END
