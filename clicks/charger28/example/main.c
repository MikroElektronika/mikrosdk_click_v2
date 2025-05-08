/*!
 * @file main.c
 * @brief Charger 28 Click example
 *
 * # Description
 * This example demonstrates the use of the Charger 28 Click board by monitoring various parameters
 * of the charging system, such as input voltage (VBUS), battery voltage (VBAT), system voltage (VSYS),
 * charging current (IBAT), and chip temperature (TDIE). Additionally, it reads and interprets the
 * charger status and fault registers to provide detailed status and error feedback during operation.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the driver and performs the default configuration of the Charger 28 Click by disabling
 * charging, resetting registers, disabling the TS pin, configuring the ADC, and re-enabling charging.
 *
 * ## Application Task
 * Periodically retrieves and logs charging parameters such as input voltage, battery voltage,
 * system voltage, charging current, and temperature. The application also reads the status and 
 * fault registers to determine the current charging state and logs the information for debugging 
 * or monitoring purposes.
 *
 * @note
 * The application is designed to continuously monitor the charging system, providing real-time 
 * feedback on its operation. The detailed charge status parsing includes states such as "Not Charging", 
 * "Trickle Charge", "Fast Charge", and "Charge Done", among others, to help track the charging process.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "charger28.h"

static charger28_t charger28;
static log_t logger;

/**
 * @brief Charger 28 parse charge status function.
 * @details This function parses the given charge status value and logs the corresponding charge state.
 * @param[in] status : Charge status byte.
 * The status byte contains the charge status information as per the device Charger status 1 register.
 * @return None.
 * @note This function logs the charge status details using the logger object.
 */
static void charger28_parse_charge_status ( uint8_t status );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger28_cfg_t charger28_cfg;  /**< Click config object. */

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
    charger28_cfg_setup( &charger28_cfg );
    CHARGER28_MAP_MIKROBUS( charger28_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger28_init( &charger28, &charger28_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER28_ERROR == charger28_default_cfg ( &charger28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float ibus = 0, vbat = 0, vsys = 0, adcin = 0, tdie = 0;
    uint8_t status_0 = 0, status_1 = 0, fault = 0;
    uint16_t vbus = 0, vpmid = 0;
    int16_t ibat = 0;

    if ( CHARGER28_OK == charger28_get_vbus ( &charger28, &vbus ) )
    {
        log_printf ( &logger, "\r\n VBUS: %u mV\r\n", vbus );
    }

    if ( CHARGER28_OK == charger28_get_ibus ( &charger28, &ibus ) )
    {
        log_printf ( &logger, " IBUS: %.1f mA\r\n", ibus );
    }

    if ( CHARGER28_OK == charger28_get_vbat ( &charger28, &vbat ) )
    {
        log_printf ( &logger, " VBAT: %.2f mV\r\n", vbat );
    }

    if ( CHARGER28_OK == charger28_get_ibat ( &charger28, &ibat ) )
    {
        log_printf ( &logger, " IBAT: %d mA\r\n", ibat );
    }

    if ( CHARGER28_OK == charger28_get_vsys ( &charger28, &vsys ) )
    {
        log_printf ( &logger, " VSYS: %.2f mV\r\n", vsys );
    }

    if ( CHARGER28_OK == charger28_get_vpmid ( &charger28, &vpmid ) )
    {
        log_printf ( &logger, " VPMID: %u mV\r\n", vpmid );
    }

    if ( CHARGER28_OK == charger28_get_adcin ( &charger28, &adcin ) )
    {
        log_printf ( &logger, " ADCIN: %.2f mV\r\n", adcin );
    }

    if ( CHARGER28_OK == charger28_get_tdie ( &charger28, &tdie ) )
    {
        log_printf ( &logger, " TDIE: %.1f degC\r\n", tdie );
    }

    if ( CHARGER28_OK == charger28_read_reg_byte ( &charger28, CHARGER28_REG_CHARGER_STATUS_0, &status_0 ) )
    {
        log_printf ( &logger, " Status 0: 0x%.2X\r\n", ( uint16_t ) status_0 );
    }
    
    if ( CHARGER28_OK == charger28_read_reg_byte ( &charger28, CHARGER28_REG_CHARGER_STATUS_1, &status_1 ) )
    {
        log_printf ( &logger, " Status 1: 0x%.2X\r\n", ( uint16_t ) status_1 );
        charger28_parse_charge_status ( status_1 );
    }

    if ( CHARGER28_OK == charger28_read_reg_byte ( &charger28, CHARGER28_REG_FAULT_STATUS, &fault ) )
    {
        log_printf ( &logger, " Fault: 0x%.2X\r\n", ( uint16_t ) fault );
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

static void charger28_parse_charge_status ( uint8_t status )
{
    log_printf ( &logger, " Charge Status: " );
    switch ( CHARGER28_CHARGER_STATUS_1_CHG_STAT_MASK & status )
    {
        case CHARGER28_CHARGER_STATUS_1_CHG_STAT_NOT_CHARGING:
        {
            log_printf ( &logger, "Not Charging\r\n" );
            break;
        }
        case CHARGER28_CHARGER_STATUS_1_CHG_STAT_TRICKLE_CHARGE:
        {
            log_printf ( &logger, "Trickle Charge (VBAT < VBAT_SHORTZ)\r\n" );
            break;
        }
        case CHARGER28_CHARGER_STATUS_1_CHG_STAT_PRE_CHARGE:
        {
            log_printf ( &logger, "Pre-charge (VBAT_SHORTZ < VBAT < VBAT_LOWV)\r\n" );
            break;
        }
        case CHARGER28_CHARGER_STATUS_1_CHG_STAT_FAST_CHARGE:
        {
            log_printf ( &logger, "Fast Charge (CC mode)\r\n" );
            break;
        }
        case CHARGER28_CHARGER_STATUS_1_CHG_STAT_TAPER_CHARGE:
        {
            log_printf ( &logger, "Taper Charge (CV mode)\r\n" );
            break;
        }
        case CHARGER28_CHARGER_STATUS_1_CHG_STAT_TO_TIMER_ACT_CH:
        {
            log_printf ( &logger, "Top-off Timer Active Charging\r\n" );
            break;
        }
        case CHARGER28_CHARGER_STATUS_1_CHG_STAT_CHARGE_DONE:
        {
            log_printf ( &logger, "Charge Termination Done\r\n" );
            break;
        }
        default:
        {
            log_printf ( &logger, "Unknown\r\n" );
            break;
        }
    }
}

// ------------------------------------------------------------------------ END
