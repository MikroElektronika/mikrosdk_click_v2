/*!
 * @file main.c
 * @brief SPIIsolator6 Click example
 *
 * # Description
 * This example demonstrates the use of SPI Isolator 6 click board by reading the
 * device ID of the connected Accel 22 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads and checks the device ID of the connected Accel 22 click board, and displays the
 * results on the USB UART approximately once per second.
 *
 * @note
 * Make sure to provide VCC power supply on VCC-EXT pin.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "spiisolator6.h"

static spiisolator6_t spiisolator6;
static log_t logger;

/**
 * @brief SPI Isolator 6 get accel 22 device id function.
 * @details This function reads and checks the device ID of the connected Accel 22 click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void spiisolator6_get_accel22_device_id ( spiisolator6_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spiisolator6_cfg_t spiisolator6_cfg;  /**< Click config object. */

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
    spiisolator6_cfg_setup( &spiisolator6_cfg );
    SPIISOLATOR6_MAP_MIKROBUS( spiisolator6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == spiisolator6_init( &spiisolator6, &spiisolator6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    spiisolator6_get_accel22_device_id ( &spiisolator6 );
    Delay_ms( 1000 );
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

void spiisolator6_get_accel22_device_id ( spiisolator6_t *ctx )
{
    #define DEVICE_NAME             "Accel 22 click"
    #define DEVICE_SPI_READ_REG     0x0B
    #define DEVICE_REG_ID           0x00
    #define DEVICE_ID               0xAD
    uint8_t data_in[ 2 ] = { DEVICE_SPI_READ_REG, DEVICE_REG_ID };
    uint8_t device_id;
    if ( SPIISOLATOR6_OK == spiisolator6_generic_read ( ctx, data_in, 2, &device_id, 1 ) )
    {
        log_printf( &logger, "\r\n %s\r\n", ( char * ) DEVICE_NAME );
        if ( DEVICE_ID == device_id )
        {
            log_printf ( &logger, " Device ID: 0x%.2X\r\n", ( uint16_t ) device_id );
        }
        else
        {
            log_error( &logger, " Wrong Device ID: 0x%.2X", ( uint16_t ) device_id );
        }
    }
}

// ------------------------------------------------------------------------ END
