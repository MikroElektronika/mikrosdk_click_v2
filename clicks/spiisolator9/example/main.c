/*!
 * @file main.c
 * @brief SPI Isolator 9 Click example
 *
 * # Description
 * This example demonstrates the use of SPI Isolator 9 Click board by reading the
 * device ID of the connected Accel 22 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads and checks the device ID of the connected Accel 22 Click board, and displays the
 * results on the USB UART approximately once per second.
 *
 * @note
 * Make sure to provide a VCC power supply on the VOUT side.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "spiisolator9.h"

static spiisolator9_t spiisolator9;
static log_t logger;

/**
 * @brief SPI Isolator 9 get accel 22 id function.
 * @details This function reads and checks the device ID of the connected Accel 22 Click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator9_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void spiisolator9_get_accel22_id ( spiisolator9_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spiisolator9_cfg_t spiisolator9_cfg;  /**< Click config object. */

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
    spiisolator9_cfg_setup( &spiisolator9_cfg );
    SPIISOLATOR9_MAP_MIKROBUS( spiisolator9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == spiisolator9_init( &spiisolator9, &spiisolator9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    spiisolator9_get_accel22_id ( &spiisolator9 );
    Delay_ms( 1000 );
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

void spiisolator9_get_accel22_id ( spiisolator9_t *ctx )
{
    #define DEVICE_NAME             "Accel 22 Click"
    #define DEVICE_SPI_READ_REG     0x0B
    #define DEVICE_REG_ID           0x00
    #define DEVICE_ID               0xAD
    uint8_t data_in[ 2 ] = { DEVICE_SPI_READ_REG, DEVICE_REG_ID };
    uint8_t device_id;
    if ( SPIISOLATOR9_OK == spiisolator9_write_then_read ( ctx, data_in, 2, &device_id, 1 ) )
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
