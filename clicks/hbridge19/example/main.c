/*!
 * @file main.c
 * @brief H-Bridge 19 Click example
 *
 * # Description
 * This example demonstrates the use of the H-Bridge 19 Click board by
 * driving the DC motors connected between OUT1A-OUT1B and OUT2A-OUT2B in both directions. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motors connected between OUT1A-OUT1B and OUT2A-OUT2B in both directions
 * in the span of 12 seconds, and logs data on the USB UART where you can track the program flow.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge19.h"

#ifndef MIKROBUS_POSITION_HBRIDGE19
    #define MIKROBUS_POSITION_HBRIDGE19 MIKROBUS_1
#endif

static hbridge19_t hbridge19;
static log_t logger;

/**
 * @brief H-Bridge 19 check fault function.
 * @details This function checks the FAULT pin state and displays on
 * the USB UART whether the error is detected based on the read value.
 * @return None.
 * @note None.
 */
static void hbridge19_check_fault ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge19_cfg_t hbridge19_cfg;  /**< Click config object. */

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
    hbridge19_cfg_setup( &hbridge19_cfg );
    HBRIDGE19_MAP_MIKROBUS( hbridge19_cfg, MIKROBUS_POSITION_HBRIDGE19 );
    if ( I2C_MASTER_ERROR == hbridge19_init( &hbridge19, &hbridge19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE19_ERROR == hbridge19_default_cfg ( &hbridge19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_0, HBRIDGE19_MOTOR_STATE_FORWARD );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_1, HBRIDGE19_MOTOR_STATE_FORWARD );
    log_printf( &logger, "\r\n MOTOR 1: FORWARD\r\n" );
    log_printf( &logger, " MOTOR 2: FORWARD\r\n" );
    hbridge19_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_0, HBRIDGE19_MOTOR_STATE_BRAKE );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_1, HBRIDGE19_MOTOR_STATE_BRAKE );
    log_printf( &logger, "\r\n MOTOR 1: BRAKE\r\n" );
    log_printf( &logger, " MOTOR 2: BRAKE\r\n" );
    hbridge19_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_0, HBRIDGE19_MOTOR_STATE_REVERSE );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_1, HBRIDGE19_MOTOR_STATE_REVERSE );
    log_printf( &logger, "\r\n MOTOR 1: REVERSE\r\n" );
    log_printf( &logger, " MOTOR 2: REVERSE\r\n" );
    hbridge19_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_0, HBRIDGE19_MOTOR_STATE_HI_Z );
    hbridge19_set_motor_state ( &hbridge19, HBRIDGE19_MOTOR_SEL_1, HBRIDGE19_MOTOR_STATE_HI_Z );
    log_printf( &logger, "\r\n MOTOR 1: DISCONNECTED\r\n" );
    log_printf( &logger, " MOTOR 2: DISCONNECTED\r\n" );
    hbridge19_check_fault ( );
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

static void hbridge19_check_fault ( void )
{
    uint8_t fault_flag = 0;
    
    if ( HBRIDGE19_OK == hbridge19_get_fault ( &hbridge19, &fault_flag ) )
    {
        if ( fault_flag )
        {
            log_printf ( &logger, " Fault detected\r\n" );
        }
        else
        {
            log_printf ( &logger, " No fault detected\r\n" );
        }
    }
    else
    {
        log_error ( &logger, " Fault read failed\r\n" );
    }
}

// ------------------------------------------------------------------------ END
