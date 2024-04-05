/*!
 * @file main.c
 * @brief Environment 4 Click example
 *
 * # Description
 * This example demonstrates the use of Environment 4 click board by reading
 * the temperature and humidity data and calculating VOC and NOx indexes.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, and reads and displays the SGP41 sensor unique serial number
 * and performs its build-in self-test. After that performs the SHT41 sensor software reset
 * and reads its unique serial number. Finally, it initializes the sensirion gas index algorithm
 * for VOC and NOx index calculation.
 *
 * ## Application Task
 * Reads the temperature (degC) and the relative humidity (%RH) data from SHT41 sensor with high precision.
 * For the first 10 seconds it executes NOx conditioning and after that it reads the raw signals for VOC and NOx
 * data and processes them with sensirion's gas index algorithm for calculating VOC and NOx indexes.
 * All data will be displayed on the USB UART approximately once per second.
 * 
 * @note
 * Time required for reliably detecting VOC and NOx events on switching ON is typically less than 60 seconds.
 * Refer to the SGP41 sensor datasheet for more timing specifications.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "environment4.h"
#include "sensirion_gas_index_algorithm.h"

static environment4_t environment4;
static log_t logger;

static GasIndexAlgorithmParams voc_params;
static GasIndexAlgorithmParams nox_params;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    environment4_cfg_t environment4_cfg;  /**< Click config object. */

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
    environment4_cfg_setup( &environment4_cfg );
    ENVIRONMENT4_MAP_MIKROBUS( environment4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == environment4_init( &environment4, &environment4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint16_t serial_num_sgp[ 3 ];
    if ( ENVIRONMENT4_OK == environment4_sgp_get_serial_num ( &environment4, serial_num_sgp ) )
    {
        log_printf ( &logger, " SGP Serial number: 0x%.4X%.4X%.4X\r\n", 
                     serial_num_sgp[ 0 ], serial_num_sgp[ 1 ], serial_num_sgp[ 2 ] );
    }
    
    uint8_t test_result_sgp;
    if ( ENVIRONMENT4_OK == environment4_sgp_exe_self_test ( &environment4, &test_result_sgp ) )
    {
        log_printf ( &logger, " SGP Self test result: " );
        if ( ENVIRONMENT4_SGP_SELF_TEST_OK == test_result_sgp )
        {
            log_printf ( &logger, "OK\r\n" );
        }
        else
        {
            if ( ENVIRONMENT4_SGP_SELF_TEST_VOC_PIXEL == test_result_sgp )
            {
                log_printf ( &logger, "VOC pixel fail; " );
            }
            if ( ENVIRONMENT4_SGP_SELF_TEST_NOX_PIXEL == test_result_sgp )
            {
                log_printf ( &logger, "NOx pixel fail; " );
            }
            log_printf ( &logger, "\r\n" );
        }
    }
    
    if ( ENVIRONMENT4_OK == environment4_sht_soft_reset ( &environment4 ) )
    {
        log_printf ( &logger, " SHT Software reset\r\n" );
        Delay_1sec ( );
    }
    
    uint32_t serial_num_sht;
    if ( ENVIRONMENT4_OK == environment4_sht_read_serial_num ( &environment4, &serial_num_sht ) )
    {
        log_printf ( &logger, " SHT Serial number: 0x%.8LX\r\n", serial_num_sht );
    }
    
    log_printf ( &logger, " Initialize Gas Index algorithm for VOC and NOx\r\n" );
    GasIndexAlgorithm_init ( &voc_params, GasIndexAlgorithm_ALGORITHM_TYPE_VOC );
    GasIndexAlgorithm_init ( &nox_params, GasIndexAlgorithm_ALGORITHM_TYPE_NOX );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature, humidity;
    uint16_t comp_rh, comp_t, sraw_voc, sraw_nox;
    int32_t voc_index, nox_index;
    static uint8_t conditioning_num = 10;
    Delay_ms ( 1000 );
    if ( ENVIRONMENT4_OK == environment4_sht_read_meas_hp ( &environment4, &temperature, &humidity ) )
    {
        log_printf ( &logger, "\r\n Temperature: %.2f degC\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n", humidity );
        
        comp_rh = ( uint16_t ) ( humidity * ENVIRONMENT4_SHT_DATA_RESOLUTION / 
                                 ( ENVIRONMENT4_SHT_ABS_MAX_HUM - ENVIRONMENT4_SHT_ABS_MIN_HUM ) );
        comp_t = ( uint16_t ) ( ( temperature - ENVIRONMENT4_SHT_ABS_MIN_TEMP ) * ENVIRONMENT4_SHT_DATA_RESOLUTION / 
                                ( ENVIRONMENT4_SHT_ABS_MAX_TEMP - ENVIRONMENT4_SHT_ABS_MIN_TEMP ) );
        if ( conditioning_num ) 
        {
            if ( ENVIRONMENT4_OK == environment4_sgp_exe_conditioning ( &environment4, comp_rh, comp_t, &sraw_voc ) )
            {
                conditioning_num--;
            }
        } 
        else 
        {
            if ( ENVIRONMENT4_OK == environment4_sgp_meas_raw_signals ( &environment4, comp_rh, comp_t, &sraw_voc, &sraw_nox ) )
            {
                GasIndexAlgorithm_process( &voc_params, ( int32_t ) sraw_voc, &voc_index );
                GasIndexAlgorithm_process( &nox_params, ( int32_t ) sraw_nox, &nox_index );
                log_printf ( &logger, " VOC Index: %ld\r\n", voc_index );
                log_printf ( &logger, " NOx Index: %ld\r\n", nox_index );
            }
        }
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
