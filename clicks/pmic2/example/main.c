/*!
 * @file main.c
 * @brief PMIC 2 Click example
 *
 * # Description
 * This example demonstrates the use of the PMIC 2 Click board. The board is designed to efficiently 
 * harvest energy from high-impedance sources such as solar panels. The demo reads and logs 
 * status flags and battery health indicators, including over-voltage, under-voltage, 
 * output current protection, and chip status. It also measures and logs the battery charging 
 * current in microamperes.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the PMIC 2 Click driver and applies the default configuration.
 *
 * ## Application Task
 * Periodically checks and logs status flags, battery OK signal, and charging current.
 *
 * @note
 * Ensure a valid energy harvesting source and energy storage element (e.g. supercap or battery) 
 * are connected to the board for proper operation.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pmic2.h"

static pmic2_t pmic2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pmic2_cfg_t pmic2_cfg;  /**< Click config object. */

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
    pmic2_cfg_setup( &pmic2_cfg );
    PMIC2_MAP_MIKROBUS( pmic2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pmic2_init( &pmic2, &pmic2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PMIC2_ERROR == pmic2_default_cfg ( &pmic2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t flags = 0;
    float current = 0;

    if ( PMIC2_OK == pmic2_read_reg ( &pmic2, PMIC2_REG_FLAGS, &flags ) )
    {
        if ( flags & PMIC2_FLAGS_OVP_OUT_MASK )
        {
            log_printf ( &logger, " OVP_OUT flag: VBAT is above OVP threshold\r\n" );
        }
        if ( flags & PMIC2_FLAGS_LVD_OUT_MASK )
        {
            log_printf ( &logger, " LVD_OUT flag: VBAT is below LVD threshold\r\n" );
        }
        if ( flags & PMIC2_FLAGS_SDF_MASK )
        {
            log_printf ( &logger, " SDF flag: Low battery harvesting current measured\r\n" );
        }
        if ( flags & PMIC2_FLAGS_OCF_MASK )
        {
            log_printf ( &logger, " OCF flag: IBAT is above OCP level\r\n" );
        }
        if ( !( flags & PMIC2_FLAGS_CHIP_OK_MASK ) )
        {
            log_printf ( &logger, " Chip_NOK flag: cold start not done\r\n" );
        }
    }

    if ( !pmic2_get_bok_pin ( &pmic2 ) )
    {
        log_printf ( &logger, " Battery status: NOK\r\n" );
    }

    if ( PMIC2_OK == pmic2_get_charge_current ( &pmic2, &current ) )
    {
        log_printf ( &logger, " Charge current: %.1f uA\r\n\n", current );
    }

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
