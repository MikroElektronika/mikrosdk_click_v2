/*!
 * @file main.c
 * @brief PMIC Click example
 *
 * # Description
 * This example demonstrates the use of PMIC click board by enabling battery charging and
 * displaying the charging status.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which enables charging.
 *
 * ## Application Task
 * Reads and displays the VBAT, VBUS, and VSYS voltage and the battery charging status on the USB UART
 * approximately once per second.
 *
 * @note
 * A charged battery or a USB at VBUS must be connected to communicate with the click board.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pmic.h"

static pmic_t pmic;
static log_t logger;

/**
 * @brief PMIC display charger status function.
 * @details This function reads and parses the battery charger status register.
 * @param[in] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void pmic_display_charger_status ( pmic_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pmic_cfg_t pmic_cfg;  /**< Click config object. */

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
    pmic_cfg_setup( &pmic_cfg );
    PMIC_MAP_MIKROBUS( pmic_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pmic_init( &pmic, &pmic_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PMIC_ERROR == pmic_default_cfg ( &pmic ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t vbat = 0, vbus = 0, vsys = 0;
    if ( PMIC_OK == pmic_get_vbat ( &pmic, &vbat ) )
    {
        log_printf( &logger, " VBAT : %u mV\r\n", vbat );
    }
    if ( PMIC_OK == pmic_get_vbus ( &pmic, &vbus ) )
    {
        log_printf( &logger, " VBUS : %u mV\r\n", vbus );
    }
    if ( PMIC_OK == pmic_get_vsys ( &pmic, &vsys ) )
    {
        log_printf( &logger, " VSYS : %u mV\r\n\n", vsys );
    }
    pmic_display_charger_status ( &pmic );
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

void pmic_display_charger_status ( pmic_t *ctx )
{
    uint8_t charge_status = 0;
    if ( PMIC_OK == pmic_reg_read_byte ( &pmic, PMIC_REG_BCHARGER_BCHGCHARGESTATUS, &charge_status ) )
    {
        log_printf( &logger, " --- Battery Charge status ---\r\n" );
        if ( charge_status & PMIC_CHARGE_STATUS_BATTERYDETECTED )
        {
            log_printf( &logger, " Battery is connected\r\n" );
        }
        if ( charge_status & PMIC_CHARGE_STATUS_COMPLETED )
        {
            log_printf( &logger, " Charging completed (Battery Full)\r\n" );
        }
        if ( charge_status & PMIC_CHARGE_STATUS_TRICKLECHARGE )
        {
            log_printf( &logger, " Trickle charge\r\n" );
        }
        if ( charge_status & PMIC_CHARGE_STATUS_CONSTANTCURRENT )
        {
            log_printf( &logger, " Constant Current charging\r\n" );
        }
        if ( charge_status & PMIC_CHARGE_STATUS_CONSTANTVOLTAGE )
        {
            log_printf( &logger, " Constant Voltage charging\r\n" );
        }
        if ( charge_status & PMIC_CHARGE_STATUS_RECHARGE )
        {
            log_printf( &logger, " Battery re-charge is needed\r\n" );
        }
        if ( charge_status & PMIC_CHARGE_STATUS_DIETEMPHIGHCHGPAUSED )
        {
            log_printf( &logger, " Charging stopped due Die Temp high.\r\n" );
        }
        if ( charge_status & PMIC_CHARGE_STATUS_SUPPLEMENTACTIVE )
        {
            log_printf( &logger, " Supplement Mode Active\r\n" );
        }
        log_printf( &logger, " -----------------------------\r\n" );
    }
}
// ------------------------------------------------------------------------ END
