/*!
 * @file main.c
 * @brief Smart Buck 6 Click example
 *
 * # Description
 * This example demonstrates the use of the Smart Buck 6 Click board. The application changes 
 * the output voltage of all three buck converters (A, B, and C) in a periodic manner and logs 
 * the output current of each. It also monitors the PG (Power Good) pin to detect and log any 
 * fault conditions such as over-temperature, overvoltage, undervoltage, or overcurrent.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Smart Buck 6 Click driver and applies the default configuration.
 *
 * ## Application Task
 * Periodically increases or decreases the output voltage, reads and logs the output current for
 * each buck channel, and checks for any fault conditions indicated via the PG pin and status registers.
 *
 * @note
 * Ensure that a valid power supply and appropriate load are connected to the Click board
 * to observe proper current and fault condition readings.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartbuck6.h"

static smartbuck6_t smartbuck6;
static log_t logger;

/**
 * @brief Smart Buck 6 display status function.
 * @details This function parses and logs all detected status flags from the Smart Buck 6 Click board
 * including over-temperature, power-good, overvoltage, undervoltage, and overcurrent conditions.
 * @param[in] status : Status register structure.
 * See #smartbuck6_status_t object definition for detailed explanation.
 * @return None.
 * @note This function outputs human-readable messages via the logger for each active status flag.
 */
static void smartbuck6_display_status ( smartbuck6_status_t status );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck6_cfg_t smartbuck6_cfg;  /**< Click config object. */

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
    smartbuck6_cfg_setup( &smartbuck6_cfg );
    SMARTBUCK6_MAP_MIKROBUS( smartbuck6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck6_init( &smartbuck6, &smartbuck6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK6_ERROR == smartbuck6_default_cfg ( &smartbuck6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    smartbuck6_status_t status;
    static uint16_t vout = SMARTBUCK6_VOUT_MV_MIN;
    static int16_t vout_step = 200;
    uint16_t current = 0;
    if ( smartbuck6_get_pg_pin ( &smartbuck6 ) )
    {
        log_printf( &logger, "\r\n Fault indication detected via PG pin!\r\n" );
        if ( SMARTBUCK6_OK == smartbuck6_read_status ( &smartbuck6, &status ) )
        {
            smartbuck6_display_status ( status );
        }
        smartbuck6_clear_status( &smartbuck6 );
    }
    if ( SMARTBUCK6_OK == smartbuck6_set_buck_vout ( &smartbuck6, SMARTBUCK6_BUCK_ALL, vout ) )
    {
        log_printf ( &logger, "\r\n All outputs voltage: %u mV\r\n", vout );
        vout += vout_step;
        if ( ( vout > SMARTBUCK6_VOUT_MV_MAX ) || ( vout < SMARTBUCK6_VOUT_MV_MIN ) )
        {
            vout_step = -vout_step;
            vout += vout_step;
            vout += vout_step;
        }
        Delay_ms ( 100 );
        if ( SMARTBUCK6_OK == smartbuck6_read_buck_current ( &smartbuck6, SMARTBUCK6_BUCK_A, &current ) )
        {
            log_printf ( &logger, " Buck A current: %u mA\r\n", current );
        }
        if ( SMARTBUCK6_OK == smartbuck6_read_buck_current ( &smartbuck6, SMARTBUCK6_BUCK_B, &current ) )
        {
            log_printf ( &logger, " Buck B current: %u mA\r\n", current );
        }
        if ( SMARTBUCK6_OK == smartbuck6_read_buck_current ( &smartbuck6, SMARTBUCK6_BUCK_C, &current ) )
        {
            log_printf ( &logger, " Buck C current: %u mA\r\n", current );
        }
    }
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

static void smartbuck6_display_status ( smartbuck6_status_t status )
{
    if ( status.status_0 )
    {
        if ( status.status_0 & SMARTBUCK6_STATUS_0_OVER_TEMP_STATUS )
        {
            log_printf ( &logger, " A critical temperature shutdown has occurred\r\n" );
        }
        if ( status.status_0 & SMARTBUCK6_STATUS_0_BUCK_A_PWR_NOT_GOOD )
        {
            log_printf ( &logger, " Buck A output power is not good\r\n" );
        }
        if ( status.status_0 & SMARTBUCK6_STATUS_0_BUCK_B_PWR_NOT_GOOD )
        {
            log_printf ( &logger, " Buck B output power is not good\r\n" );
        }
        if ( status.status_0 & SMARTBUCK6_STATUS_0_BUCK_C_PWR_NOT_GOOD )
        {
            log_printf ( &logger, " Buck C output power is not good\r\n" );
        }
        if ( status.status_0 & SMARTBUCK6_STATUS_0_VIN_OV )
        {
            log_printf ( &logger, " A VIN OV condition has occurred\r\n" );
        }
    }
    if ( status.status_1 )
    {
        if ( status.status_1 & SMARTBUCK6_STATUS_1_BUCK_A_OV )
        {
            log_printf ( &logger, " A buck A output OV condition has occurred\r\n" );
        }
        if ( status.status_1 & SMARTBUCK6_STATUS_1_BUCK_B_OV )
        {
            log_printf ( &logger, " A buck B output OV condition has occurred\r\n" );
        }
        if ( status.status_1 & SMARTBUCK6_STATUS_1_BUCK_C_OV )
        {
            log_printf ( &logger, " A buck C output OV condition has occurred\r\n" );
        }
        if ( status.status_1 & SMARTBUCK6_STATUS_1_BUCK_A_UV )
        {
            log_printf ( &logger, " A buck A output UV condition has occurred\r\n" );
        }
        if ( status.status_1 & SMARTBUCK6_STATUS_1_BUCK_B_UV )
        {
            log_printf ( &logger, " A buck B output UV condition has occurred\r\n" );
        }
        if ( status.status_1 & SMARTBUCK6_STATUS_1_BUCK_C_UV )
        {
            log_printf ( &logger, " A buck C output UV condition has occurred\r\n" );
        }
    }
    if ( status.oc_status )
    {
        if ( status.oc_status & SMARTBUCK6_OC_STATUS_BUCK_A_OC )
        {
            log_printf ( &logger, " There is an output OC condition on buck A\r\n" );
        }
        if ( status.oc_status & SMARTBUCK6_OC_STATUS_BUCK_B_OC )
        {
            log_printf ( &logger, " There is an output OC condition on buck B\r\n" );
        }
        if ( status.oc_status & SMARTBUCK6_OC_STATUS_BUCK_C_OC )
        {
            log_printf ( &logger, " There is an output OC condition on buck C\r\n" );
        }
    }
}

// ------------------------------------------------------------------------ END
