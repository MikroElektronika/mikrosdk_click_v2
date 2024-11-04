/*!
 * @file main.c
 * @brief H-Bridge 14 Click example
 *
 * # Description
 * This example demonstrates the use of the H-Bridge 14 board by driving the 
 * motor in both directions with braking and coasting in between.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motor in both directions with coasting and braking in between, every sate is lasting 5 seconds.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge14.h"

static hbridge14_t hbridge14;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge14_cfg_t hbridge14_cfg;  /**< Click config object. */

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
    hbridge14_cfg_setup( &hbridge14_cfg );
    HBRIDGE14_MAP_MIKROBUS( hbridge14_cfg, MIKROBUS_1 );
    err_t init_flag = hbridge14_init( &hbridge14, &hbridge14_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE14_ERROR == hbridge14_default_cfg ( &hbridge14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t fault_status = 0;

    hbridge14_drive_motor( &hbridge14, HBRIDGE14_DRIVE_MOTOR_CW );
    log_printf( &logger, " Driving motor Clockwise \r\n" );
    hbridge14_register_read( &hbridge14, HBRIDGE14_REG_FAULT_STATUS, &fault_status );
    log_printf( &logger, " Fault status : 0x%.2X \r\n", ( uint16_t ) fault_status );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    hbridge14_drive_motor( &hbridge14, HBRIDGE14_DRIVE_MOTOR_BRAKE );
    log_printf( &logger, " Brake is on \r\n" );
    hbridge14_register_read( &hbridge14, HBRIDGE14_REG_FAULT_STATUS, &fault_status );
    log_printf( &logger, " Fault status : 0x%.2X \r\n", ( uint16_t ) fault_status );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    hbridge14_drive_motor( &hbridge14, HBRIDGE14_DRIVE_MOTOR_CCW );
    log_printf( &logger, " Driving motor counter-clockwise \r\n" );
    hbridge14_register_read( &hbridge14, HBRIDGE14_REG_FAULT_STATUS, &fault_status );
    log_printf( &logger, " Fault status : 0x%.2X \r\n", ( uint16_t ) fault_status );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    hbridge14_drive_motor( &hbridge14, HBRIDGE14_DRIVE_MOTOR_COASTING );
    log_printf( &logger, " Driving motor Coasting \r\n" );
    hbridge14_register_read( &hbridge14, HBRIDGE14_REG_FAULT_STATUS, &fault_status );
    log_printf( &logger, " Fault status : 0x%.2X \r\n", ( uint16_t ) fault_status );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

// ------------------------------------------------------------------------ END
