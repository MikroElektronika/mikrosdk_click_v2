/*!
 * @file main.c
 * @brief Accel4 Click example
 *
 * # Description
 * This example is a showcase of the ability of the device
 * to read 3 axis data in varity of 3 resolutions, ability 
 * to configure 2 interrput pins for user needs etc..
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializion of communication modules (I2C/SPI, UART) and 
 * additional interrupt pins. Reading status register in loop
 * until power up bit is set to 1. Then reads device ID and checks
 * if it's valid, and in the end configures device to get interrupt 
 * on new data received, set device in active mode and sets currently 
 * configured resolution to context object.
 *
 * ## Application Task
 * Reads data of all 3 axes whenever interrupt is received and logs it.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel4.h"

static accel4_t accel4;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel4_cfg_t accel4_cfg;  /**< Click config object. */

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
    accel4_cfg_setup( &accel4_cfg );
    ACCEL4_MAP_MIKROBUS( accel4_cfg, MIKROBUS_1 );
    err_t init_flag  = accel4_init( &accel4, &accel4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint8_t temp_data = 0;
    
    // Wait for the powerup status
    do {
        accel4_generic_read( &accel4, ACCEL4_REG_INT_STATUS, &temp_data, 1 );
        Delay_ms( 1 );
    }while ( ( temp_data & 1 ) != 1 );
    
    //Read device ID
    accel4_generic_read( &accel4, ACCEL4_REG_WHO_AM_I, &temp_data, 1 );
    log_printf( &logger, " > WHO AM I: 0x%.2X\r\n", ( uint16_t )temp_data );
    if ( ACCEL4_DEVICE_ID != temp_data )
    {
        log_error( &logger, " ID" );
        for( ; ; );
    }
    
    accel4_default_cfg ( &accel4 );
    
    Delay_ms( 1000 );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( accel4_get_int1( &accel4 ) )
    {
        accel4_axes_t axes;
        accel4_get_axes_data( &accel4, &axes );
        
        log_printf( &logger, " > X: %.2f\r\n", axes.x );
        log_printf( &logger, " > Y: %.2f\r\n", axes.y );
        log_printf( &logger, " > Z: %.2f\r\n", axes.z );
        log_printf( &logger, "*****************************************\r\n" );
        Delay_ms( 300 );
    }
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

// ------------------------------------------------------------------------ END
