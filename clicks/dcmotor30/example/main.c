/*!
 * @file main.c
 * @brief DC Motor 30 Click example
 *
 * # Description
 * This example demonstrates the control of a DC motor using the DC Motor 30 Click board. 
 * It performs motor driving in different modes (forward, brake, reverse, and coast) 
 * and periodically reads the output current and fault status.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click board driver, then sets the default configuration.
 *
 * ## Application Task
 * Drives the motor in different states and monitors the current consumption 
 * and possible fault conditions.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor30.h"

static dcmotor30_t dcmotor30;
static log_t logger;

/**
 * @brief DC Motor 30 check fault function.
 * @details This function checks the FAULT pin and reads the fault status register 
 * from the DC Motor 30 Click board to detect possible fault conditions.
 * It logs detailed fault information such as motor stall, overcurrent, overvoltage, 
 * thermal shutdown, and undervoltage lockout events.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t structure definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void dcmotor30_check_fault ( dcmotor30_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor30_cfg_t dcmotor30_cfg;  /**< Click config object. */

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
    dcmotor30_cfg_setup( &dcmotor30_cfg );
    DCMOTOR30_MAP_MIKROBUS( dcmotor30_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor30_init( &dcmotor30, &dcmotor30_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR30_ERROR == dcmotor30_default_cfg ( &dcmotor30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float current = 0;

    log_printf( &logger, " Motor state : FORWARD\r\n" );
    dcmotor30_drive_motor ( &dcmotor30, DCMOTOR30_MOTOR_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor30_check_fault ( &dcmotor30 );
    if ( DCMOTOR30_OK == dcmotor30_get_out_current ( &dcmotor30, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : BRAKE\r\n" );
    dcmotor30_drive_motor ( &dcmotor30, DCMOTOR30_MOTOR_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor30_check_fault ( &dcmotor30 );
    if ( DCMOTOR30_OK == dcmotor30_get_out_current ( &dcmotor30, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : REVERSE\r\n" );
    dcmotor30_drive_motor ( &dcmotor30, DCMOTOR30_MOTOR_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor30_check_fault ( &dcmotor30 );
    if ( DCMOTOR30_OK == dcmotor30_get_out_current ( &dcmotor30, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : COAST\r\n" );
    dcmotor30_drive_motor ( &dcmotor30, DCMOTOR30_MOTOR_COAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor30_check_fault ( &dcmotor30 );
    if ( DCMOTOR30_OK == dcmotor30_get_out_current ( &dcmotor30, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
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

static void dcmotor30_check_fault ( dcmotor30_t *ctx )
{
    uint8_t fault_status = 0;
    if ( dcmotor30_get_fault_pin ( ctx ) )
    {
        log_printf( &logger, " Fault: Pin Indication\r\n" );
        if ( DCMOTOR30_OK == dcmotor30_read_reg ( ctx, DCMOTOR30_REG_FAULT_STATUS, &fault_status ) )
        {
            if ( fault_status & DCMOTOR30_FAULT_STATUS_STALL )
            {
                log_printf( &logger, " Fault: Motor Stall\r\n" );
            }
            if ( fault_status & DCMOTOR30_FAULT_STATUS_OCP )
            {
                log_printf( &logger, " Fault: Overcurrent Protection (OCP)\r\n" );
            }
            if ( fault_status & DCMOTOR30_FAULT_STATUS_OVP )
            {
                log_printf( &logger, " Fault: Overvoltage Protection (OVP)\r\n" );
            }
            if ( fault_status & DCMOTOR30_FAULT_STATUS_TSD )
            {
                log_printf( &logger, " Fault: Thermal Shutdown (TSD)\r\n" );
            }
            if ( fault_status & DCMOTOR30_FAULT_STATUS_NPOR )
            {
                log_printf( &logger, " Fault: VM Undervoltage Lockout (UVLO)\r\n" );
            }
        }
        dcmotor30_clear_fault ( ctx );
    }
}

// ------------------------------------------------------------------------ END
