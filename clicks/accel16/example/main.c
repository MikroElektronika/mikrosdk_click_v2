/*!
 * @file main.c
 * @brief Accel16 Click example
 *
 * # Description
 * This showcases ability of the click board to 
 * read x, y, and z axes data in different resolution,
 * read IC temperature and also have additional functionality
 * to read ADC data. Device also has ability to store data 
 * in internal fifo buffer.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules(SPI, UART) and 
 * additional interrupt pins. Reads device ID's and revision.
 * Then configures device to work in FIFO mode or to read data
 * from the registers, sets 2g resolution, 12.5Hz output data rate,
 * sets interrupt 1 active low, powers on device, and calibrates temperature.
 *
 * ## Application Task
 * Depending of the application mode selects example. 
 *  - If fifo example is selected waits for the interrupt 
 *      to indicate that data is ready  in fifo buffer and 
 *      reads number of fifo entries. Data that should be 
 *      read are X, Y, Z axes and temperature.
 *  - If register example is selected also waits for interrupt
 *      to indicate that data is ready to read. Then reads X, Y, Z
 *      axes, temperature, and ADC data.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel16.h"
#include "conversions.h"

static accel16_t accel16;
static log_t logger;

/**
 * @brief Fifo read data example.
 * @details This function waits for new data in fifo buffer, reads
 * number of fifo enries and reads that amount of fifo bytes multiple by 2.
 * Goes through the buffer and logs data.
 * @return Nothing.
 */
static void accel16_read_fifo_data ( void );

/**
 * @brief Register data read example.
 * @details This function waits for new data indication and reads axes, temperature
 * and ADC data and logs result.
 * @return Nothing.
 */
static void accel16_read_reg_data ( void );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel16_cfg_t accel16_cfg;  /**< Click config object. */

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
    accel16_cfg_setup( &accel16_cfg );
    ACCEL16_MAP_MIKROBUS( accel16_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == accel16_init( &accel16, &accel16_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    accel16.application_type = ACCEL16_APPLICATION_REG;
    
    uint8_t temp_buf[ 4 ] = { 0 };
    
    accel16_multiple_reg_read( &accel16, ACCEL16_REG_DEVID_AD, temp_buf, 4 );
    log_printf( &logger, " > ID0: 0x%.2X\r\n > ID1: 0x%.2X\r\n > ID2: 0x%.2X\r\n > REV: 0x%.2X\r\n", 
                ( uint16_t ) temp_buf[ 0 ], ( uint16_t ) temp_buf[ 1 ], 
                ( uint16_t ) temp_buf[ 2 ], ( uint16_t ) temp_buf[ 3 ] );
    
    if ( ACCEL16_ERROR == accel16_default_cfg ( &accel16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{   
    if ( ACCEL16_APPLICATION_FIFO == accel16.application_type )
    {
        accel16_read_fifo_data( );
    }
    else if ( ACCEL16_APPLICATION_REG == accel16.application_type )
    {
        accel16_read_reg_data( );
    }

    log_printf( &logger, "********************************************************\r\n" );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

static void accel16_read_fifo_data ( void )
{
    uint8_t temp_buf[ 1024 ] = { 0 };
    int16_t temp_data = 0;
    
    while ( accel16_get_interrupt_1( &accel16 ) );
    
    accel16_multiple_reg_read( &accel16, ACCEL16_REG_FIFO_ENTRIES_L, temp_buf, 2 );
    uint16_t fifo_entries = ( ( uint16_t )temp_buf[ 1 ] << 8 ) | temp_buf[ 0 ];
    fifo_entries &= 0x03FF;
    
    accel16_fifo_read( &accel16, temp_buf, fifo_entries * 2 );
    
    for ( uint16_t cnt = 0; cnt < fifo_entries * 2; cnt += 2 )
    {
        temp_data = ( ( uint16_t )temp_buf[ cnt + 1 ] << 8 ) | temp_buf[ cnt ];
        uint8_t fifo_data = ( temp_data >> 14 ) & 0x3;
        temp_data &= 0x3FFF;
        temp_data <<= 2;
        temp_data >>= 2;
        
        switch ( fifo_data )
        {
            case 0x0:
            {
                log_printf( &logger, " > X[g]: %d\r\n", temp_data );
                break;
            }
            case 0x1:
            {
                log_printf( &logger, " > Y[g]: %d\r\n", temp_data );
                break;
            }
            case 0x2:
            {
                log_printf( &logger, " > Z[g]: %d\r\n", temp_data );
                break;
            }
            case 0x3:
            {
                float temperature = ACCEL16_ROOM_TEMPERATURE + 
                                    ( temp_data - ACCEL16_TEMPERATURE_BIAS ) * ACCEL16_TEMPERATURE_RES - 
                                    accel16.room_temp_offset;;
                log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temperature );
                break;
            }
            default:
            {
                log_error( &logger, "Fifo data!" );
                break;
            }
        }
    }
}

static void accel16_read_reg_data ( void )
{
    uint8_t temp_byte = 0;
    float temperature = 0;
    float adc = 0;
    accel16_axes_t axes;
    
    while ( accel16_get_interrupt_1( &accel16 ) );
    
    accel16_get_axes ( &accel16, &axes );
    accel16_get_temperature ( &accel16, &temperature );
    accel16_get_adc ( &accel16, &adc );
    
    log_printf( &logger, " > X[g]: %.2f\r\n", axes.x );
    log_printf( &logger, " > Y[g]: %.2f\r\n", axes.y );
    log_printf( &logger, " > Z[g]: %.2f\r\n", axes.z );
    log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temperature );
    log_printf( &logger, " > ADC[V]: %.2f\r\n", adc );
}

// ------------------------------------------------------------------------ END
