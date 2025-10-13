/*!
 * @file main.c
 * @brief 2-Wire SPI ISO Click example
 *
 * # Description
 * This example demonstrates the use of a 2-Wire SPI ISO Click board by showing
 * the communication between the two Click boards (Slave and Master). That is performed by
 * sending commands to a 2-Wire SPI ISO Click (Slave) to read the device ID of a Accel 22
 * Click board connected to the 2-Wire SPI ISO Click (Master).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads and checks the device ID of a Accel 22 Click board connected to the 2-Wire SPI ISO
 * (Master) Click, and displays the results on the USB UART approximately once per second.
 *
 * @note
 * The communication topology is as follows:
 * MCU <-> 2-Wire SPI ISO Click (Slave) <-> 2-Wire SPI ISO Click (Master) <-> Accel 22 Click
 * The Master/Slave selection is done via on-board SMD jumpers.
 * The Master Click board must be powered up with a 3V3 and 5V power supply externally.
 * Also the DIS must be pulled down on Master Click board to enable the device.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c2wirespiiso.h"

static c2wirespiiso_t c2wirespiiso;
static log_t logger;

/**
 * @brief 2-Wire SPI ISO get Accel 22 ID function.
 * @details This function reads and checks the device ID of the Accel 22 Click board which
 * is connected to 2-Wire SPI ISO (master) Click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void c2wirespiiso_get_accel22_id ( c2wirespiiso_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c2wirespiiso_cfg_t c2wirespiiso_cfg;  /**< Click config object. */

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
    c2wirespiiso_cfg_setup( &c2wirespiiso_cfg );
    C2WIRESPIISO_MAP_MIKROBUS( c2wirespiiso_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c2wirespiiso_init( &c2wirespiiso, &c2wirespiiso_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    c2wirespiiso_default_cfg ( &c2wirespiiso );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    c2wirespiiso_get_accel22_id ( &c2wirespiiso );
    Delay_ms ( 1000 );
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

void c2wirespiiso_get_accel22_id ( c2wirespiiso_t *ctx )
{
    #define TIMEOUT_MS          1000
    #define DEVICE_NAME         "Accel 22 Click"
    #define DEVICE_SPI_READ_REG 0x0B
    #define DEVICE_REG_ID       0x00
    #define DEVICE_ID           0xAD
    uint8_t data_buf[ 3 ] = { DEVICE_SPI_READ_REG, DEVICE_REG_ID, 0 };
    uint16_t timeout_cnt = 0;

    // Send SPI read reg command + reg address + 1 dummy byte as data request
    c2wirespiiso_write ( ctx, data_buf, 3 );
    // Wait for RX buffer not empty indication
    while ( !c2wirespiiso_get_bne_pin ( ctx ) )
    {
        if ( ++timeout_cnt > TIMEOUT_MS )
        {
            log_error( &logger, "Timeout! Make sure the DIS pin is pulled down on master Click board." );
            return;
        }
        Delay_1ms ( );
    }
    // Read 3 bytes, 2 dummy bytes + response data byte
    c2wirespiiso_read ( ctx, data_buf, 3 );

    log_printf( &logger, "\r\n %s\r\n", ( char * ) DEVICE_NAME );
    if ( DEVICE_ID == data_buf[ 2 ] )
    {
        log_printf ( &logger, " Device ID: 0x%.2X\r\n", ( uint16_t ) data_buf[ 2 ] );
    }
    else
    {
        log_error( &logger, "Wrong ID read: 0x%.2X", ( uint16_t ) data_buf[ 2 ] );
    }
}

// ------------------------------------------------------------------------ END
