/*!
 * @file main.c
 * @brief DC Motor 24 Click example
 *
 * # Description
 * This example demonstrates the use of the DC Motor 24 Click board by driving the 
 * motor in both directions at different speeds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Controls the motor speed by changing the PWM duty cycle every 500ms.
 * The duty cycle ranges from 0% to 100%. At the minimal speed, the motor switches direction.
 * It also reads and parses the diagnostics word register. Each step will be logged on
 * the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor24.h"

static dcmotor24_t dcmotor24;
static log_t logger;

/**
 * @brief DC Motor 24 display diag function.
 * @details This function parses and displays a diagnostics word on the USB UART.
 * @param[in] diag : Diagnostics word to parse and display.
 * @return None.
 * @note None.
 */
static void dcmotor24_display_diag ( uint16_t diag );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor24_cfg_t dcmotor24_cfg;  /**< Click config object. */

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
    dcmotor24_cfg_setup( &dcmotor24_cfg );
    DCMOTOR24_MAP_MIKROBUS( dcmotor24_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dcmotor24_init( &dcmotor24, &dcmotor24_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR24_ERROR == dcmotor24_default_cfg ( &dcmotor24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static int8_t duty_pct = 10;
    static int8_t duty_step = 10;
    uint16_t diag;
    if ( DCMOTOR24_OK == dcmotor24_set_duty_cycle ( &dcmotor24, ( float ) duty_pct / 100 ) )
    {
        log_printf( &logger, "\r\n Duty: %u%%\r\n", ( uint16_t ) duty_pct );
    }
    if ( DCMOTOR24_OK == dcmotor24_read_diag ( &dcmotor24, &diag ) )
    {
        dcmotor24_display_diag ( diag );
    }
    Delay_ms( 500 );
    if ( ( 100 == duty_pct ) || ( 0 == duty_pct ) ) 
    {
        duty_step = -duty_step;
        if ( 0 == duty_pct )
        {
            log_printf( &logger, "\r\n Switch direction\r\n" );
            dcmotor24_switch_direction ( &dcmotor24 );
            Delay_ms ( 500 );
        }
    }
    duty_pct += duty_step;
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

static void dcmotor24_display_diag ( uint16_t diag )
{
    log_printf( &logger, " --- Diagnostics ---\r\n" );
    if ( diag & DCMOTOR24_DIA_OL_OFF )
    {
        log_printf( &logger, " * Open Load in OFF condition\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_OL_ON )
    {
        log_printf( &logger, " * Open Load in ON condition\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_VS_UV )
    {
        log_printf( &logger, " * Vs undervoltage\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_VDD_OV )
    {
        log_printf( &logger, " * Vdd overvoltage\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_ILIM )
    {
        log_printf( &logger, " * Current Limitation reached\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_TWARN )
    {
        log_printf( &logger, " * Temperature warning\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_TSD )
    {
        log_printf( &logger, " * Over-temperature Shutdown\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_ACT )
    {
        log_printf( &logger, " * Bridge enable\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_OC_LS1 )
    {
        log_printf( &logger, " * Over-Current on Low Side 1\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_OC_LS2 )
    {
        log_printf( &logger, " * Over-Current on Low Side 2\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_OC_HS1 )
    {
        log_printf( &logger, " * Over-Current on High Side 1\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_OC_HS2 )
    {
        log_printf( &logger, " * Over-Current on High Side 2\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_SGND_OFF )
    {
        log_printf( &logger, " * Short to GND in OFF condition\r\n" );
    }
    if ( diag & DCMOTOR24_DIA_SBAT_OFF )
    {
        log_printf( &logger, " * Short to Battery in OFF condition\r\n" );
    }
}

// ------------------------------------------------------------------------ END
