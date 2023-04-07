/*!
 * @file main.c
 * @brief H-Bridge 11 Click example
 *
 * # Description
 * This example demonstrates the use of the H-Bridge 11 click board by
 * driving the DC motors connected between OUT0-OUT1 and OUT2-OUT3 in both directions. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Drives the motors connected between OUT0-OUT1 and OUT2-OUT3 in both directions
 * in the span of 12 seconds, and logs data on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge11.h"

static hbridge11_t hbridge11;
static log_t logger;

/**
 * @brief H-Bridge 11 check fault function.
 * @details This function checks the fault pin state then reads the fault flags
 * and displays on the USB UART.
 * @return None.
 * @note None.
 */
static void hbridge11_check_fault ( void );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge11_cfg_t hbridge11_cfg;  /**< Click config object. */

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
    hbridge11_cfg_setup( &hbridge11_cfg );
    HBRIDGE11_MAP_MIKROBUS( hbridge11_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridge11_init( &hbridge11, &hbridge11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE11_ERROR == hbridge11_default_cfg ( &hbridge11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_0, HBRIDGE11_MOTOR_STATE_FORWARD );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_1, HBRIDGE11_MOTOR_STATE_FORWARD );
    log_printf( &logger, "\r\n MOTOR 0: FORWARD\r\n" );
    log_printf( &logger, " MOTOR 1: FORWARD\r\n" );
    hbridge11_check_fault ( );
    Delay_ms ( 3000 );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_0, HBRIDGE11_MOTOR_STATE_BRAKE );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_1, HBRIDGE11_MOTOR_STATE_BRAKE );
    log_printf( &logger, "\r\n MOTOR 0: BRAKE\r\n" );
    log_printf( &logger, " MOTOR 1: BRAKE\r\n" );
    hbridge11_check_fault ( );
    Delay_ms ( 3000 );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_0, HBRIDGE11_MOTOR_STATE_REVERSE );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_1, HBRIDGE11_MOTOR_STATE_REVERSE );
    log_printf( &logger, "\r\n MOTOR 0: REVERSE\r\n" );
    log_printf( &logger, " MOTOR 1: REVERSE\r\n" );
    hbridge11_check_fault ( );
    Delay_ms ( 3000 );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_0, HBRIDGE11_MOTOR_STATE_HI_Z );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_1, HBRIDGE11_MOTOR_STATE_HI_Z );
    log_printf( &logger, "\r\n MOTOR 0: DISCONNECTED\r\n" );
    log_printf( &logger, " MOTOR 1: DISCONNECTED\r\n" );
    hbridge11_check_fault ( );
    Delay_ms ( 3000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

static void hbridge11_check_fault ( void )
{
    uint8_t fault_flags = 0;
    if ( !hbridge11_get_fault_pin ( &hbridge11 ) )
    {
        if ( HBRIDGE11_OK == hbridge11_read_flags ( &hbridge11, &fault_flags ) )
        {
            log_printf ( &logger, " Fault flags: 0x%.2X\r\n", ( uint16_t ) fault_flags );
        }
    }
}

// ------------------------------------------------------------------------ END
