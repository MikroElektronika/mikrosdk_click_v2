/*!
 * @file main.c
 * @brief PMIC 4 Click example
 *
 * # Description
 * This example demonstrates the use of PMIC 4 Click board by monitoring
 * storage voltage, charging paths, and relative load demand.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and I2C driver, verifies the AEM13921 part number,
 * applies the default board APM profile, and displays the device revision.
 *
 * ## Application Task
 * Displays battery voltage, charging/discharging paths, relative load
 * demand, onboard NTC temperature, and protection events.
 * Optional calibrated currents are at STO.
 *
 * @note
 * Set I2C EN = 1 and TH EN = 1. Match VCC SEL to the host logic voltage.
 * Cold-start from SRC1, SRC2, or 5V_IN. MikroBUS 5 V disables harvesting.
 * Limit source current externally and use a battery rated for the 3.00/3.21/4.13 V profile.
 * LOAD is set to 2.5 V. A low on mikroBUS AN indicates LOAD is ready.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pmic4.h"

#ifndef MIKROBUS_POSITION_PMIC4
    #define MIKROBUS_POSITION_PMIC4 MIKROBUS_1
#endif

/**
 * @brief Application monitoring settings.
 * @details Demand is displayed in millions of APM units for readability.
 * It shows relative changes, not absolute power or external load presence.
 * Four temperature flags follow STATUS1 bit order; status bytes are packed
 * together only to track protection transitions.
 */
#define APP_TASK_INTERVAL_MS                1000
#define APP_STATUS_INITIAL                  0xFFFF
#define APP_APM_DISPLAY_SCALE               1000000.0f
#define APP_TEMPERATURE_LIMIT_COUNT         4
#define APP_CHARGE_ACTIVITY_MASK            ( PMIC4_CURRENT_SOURCE_1_VALID | \
                                              PMIC4_CURRENT_SOURCE_2_VALID | \
                                              PMIC4_CURRENT_CHARGER_VALID )

/**
 * @brief Optional customer calibration settings.
 * @details Zero selects activity monitoring. Calibrated alpha factors must
 * match the board and active timings; charger calibration is measured CC mA.
 * Follow #pmic4_current_cfg_t calibration guidance. Alpha uses full apm_value,
 * not the displayed value in millions of units. Net current requires all
 * channels calibrated and valid and excludes other STO consumption.
 * R10 gives only a nominal startup estimate, not charger calibration.
 */
#define APP_CHARGER_RESISTOR_OHM            370.0f
#define APP_CHARGER_NOMINAL_CURRENT_MA      ( PMIC4_CHARGER_CC_FACTOR_MA_OHM / APP_CHARGER_RESISTOR_OHM )
#define APP_SOURCE_1_ALPHA                  0.0f
#define APP_SOURCE_2_ALPHA                  0.0f
#define APP_LOAD_ALPHA                      0.0f
#define APP_CHARGER_CALIBRATED_CURRENT_MA   0.0f
#define APP_BALANCE_DEADBAND_MA             1.0f

static pmic4_t pmic4;    /**< Click context object. */
static log_t logger;     /**< Logger object. */

/** Optional customer calibration; zero selects activity only. */
static pmic4_current_cfg_t current_cfg =
{
    { APP_SOURCE_1_ALPHA, APP_SOURCE_2_ALPHA, APP_LOAD_ALPHA },
    APP_CHARGER_CALIBRATED_CURRENT_MA
};

/**
 * @brief PMIC 4 measurement logging function.
 * @details This function displays transfer paths, relative demand, and protection events.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @param[in] status : Current power and temperature status.
 * @param[in] currents : Fresh APM measurements and optional calibrated currents.
 * @return Nothing.
 * @note APM covers the preceding window; readiness is the current pin state.
 * Net current requires all channels calibrated and valid.
 */
static void pmic4_log_measurements ( pmic4_t *ctx, pmic4_status_t *status, pmic4_currents_t *currents );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pmic4_cfg_t pmic4_cfg;  /**< Click config object. */

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
    pmic4_cfg_setup( &pmic4_cfg );
    PMIC4_MAP_MIKROBUS( pmic4_cfg, MIKROBUS_POSITION_PMIC4 );
    if ( I2C_MASTER_ERROR == pmic4_init( &pmic4, &pmic4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    uint8_t revision;
    err_t error_flag;
    
    // Verify the module before applying the complete default board APM profile.
    error_flag = pmic4_default_cfg( &pmic4 );
    if ( PMIC4_OK != error_flag )
    {
        log_error( &logger, " Default configuration: %ld. Check source power and I2C EN.", error_flag );
        for ( ; ; );
    }

    error_flag = pmic4_configure_apm( &pmic4 );
    if ( PMIC4_OK != error_flag )
    {
        log_error( &logger, " APM configuration: %ld.", error_flag );
        for ( ; ; );
    }

    error_flag = pmic4_read_reg( &pmic4, PMIC4_REG_VERSION, &revision );
    if ( PMIC4_OK != error_flag )
    {
        log_error( &logger, " Device revision read: %ld.", error_flag );
        for ( ; ; );
    }

    log_printf( &logger, " AEM13921 revision: 0x%.2X\r\n", ( uint16_t ) revision );
    log_printf( &logger, " LOAD: 2.5 V | STO limits: 3.00 / 3.21 / 4.13 V\r\n" );
    log_printf( &logger, " Nominal 5 V CC current: %.0f mA (R10 = %.0f ohms; estimate only)\r\n",
                APP_CHARGER_NOMINAL_CURRENT_MA, APP_CHARGER_RESISTOR_OHM );
    log_printf( &logger, " LOAD APM is shown in millions of raw units, not mA.\r\n" );
    log_printf( &logger, " SRCx: disconnect mikroBUS 5 V; limit source current externally.\r\n" );
    log_printf( &logger, " NTC: set TH EN = 1; hardware updates about every 7.45 s.\r\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    pmic4_status_t status;
    pmic4_currents_t currents;
    float ntc_temperature;
    uint16_t flags;
    err_t error_flag;
    err_t ntc_error;

    error_flag = pmic4_get_currents( &pmic4, &current_cfg, &currents );
    if ( PMIC4_OK == error_flag )
    {
        error_flag = pmic4_get_status( &pmic4, &status );
    }
    if ( PMIC4_OK == error_flag )
    {
        pmic4_log_measurements( &pmic4, &status, &currents );
        // Temperature is optional; an unavailable sample must not hide power data.
        ntc_error = pmic4_get_temperature( &pmic4, &ntc_temperature );
        if ( PMIC4_OK == ntc_error )
        {
            log_printf( &logger, "  NTC: %.1f C\r\n", ntc_temperature );
        }
        else if ( PMIC4_ERROR_SAMPLE == ntc_error )
        {
            log_printf( &logger, "  NTC: unavailable; allow first update and check TH EN = 1.\r\n" );
        }
        else
        {
            log_error( &logger, " NTC read error: %ld.", ntc_error );
        }
        if ( pmic4_get_int_pin( &pmic4 ) )
        {
            error_flag = pmic4_get_interrupt_flags( &pmic4, &flags );
        }
    }
    if ( PMIC4_OK != error_flag )
    {
        log_error( &logger, " Communication error: %ld.", error_flag );
    }

    Delay_ms( APP_TASK_INTERVAL_MS );
}

static void pmic4_log_measurements ( pmic4_t *ctx, pmic4_status_t *status, pmic4_currents_t *currents )
{
    static uint16_t previous_status = APP_STATUS_INITIAL;
    static char *channel_name[ PMIC4_CURRENT_CHANNEL_COUNT ] =
    {
        "SRC1", "SRC2", "LOAD", "5V_IN"
    };
    static char *temperature_limit[ APP_TEMPERATURE_LIMIT_COUNT ] =
    {
        "Charge cold", "Charge hot", "Discharge cold", "Discharge hot"
    };
    float balance;
    uint16_t current_status;
    uint8_t channel;
    uint8_t mask;
    uint8_t load_ready = pmic4_get_stl_pin( ctx );
    char *message;

    // Report protection transitions once, independently of load demand.
    current_status = ( ( uint16_t ) status->temperature << PMIC4_REGISTER_BYTE_BITS ) |
                     ( status->power & ( PMIC4_STATUS_OVDIS | PMIC4_STATUS_CHRDY | PMIC4_STATUS_OVCH ) );
    if ( ( APP_STATUS_INITIAL == previous_status ) ||
         ( ( uint8_t ) ( current_status ^ previous_status ) ) )
    {
        if ( status->power & PMIC4_STATUS_OVDIS )
        {
            log_error( &logger, " Battery low; LOAD shutdown pending or active." );
        }
        else if ( status->power & PMIC4_STATUS_OVCH )
        {
            log_info( &logger, " Battery upper limit; charging paused." );
        }
        else if ( !( status->power & PMIC4_STATUS_CHRDY ) )
        {
            log_info( &logger, " Battery below load-ready threshold." );
        }
    }
    if ( ( APP_STATUS_INITIAL == previous_status ) ||
         ( ( current_status ^ previous_status ) >> PMIC4_REGISTER_BYTE_BITS ) )
    {
        for ( channel = 0; channel < APP_TEMPERATURE_LIMIT_COUNT; channel++ )
        {
            if ( status->temperature & ( 1 << channel ) )
            {
                log_error( &logger, " %s temperature limit.", temperature_limit[ channel ] );
            }
        }
        if ( !status->temperature && ( APP_STATUS_INITIAL != previous_status ) )
        {
            log_info( &logger, " Temperature limits cleared." );
        }
    }
    previous_status = current_status;

    log_printf( &logger, "\r\nBattery: %.3f V | ", currents->storage_voltage );
    // The driver validates the sample, not the quality of customer calibration.
    if ( PMIC4_CURRENT_ALL_VALID == currents->valid )
    {
        balance = currents->current[ PMIC4_CURRENT_SOURCE_1 ] +
                  currents->current[ PMIC4_CURRENT_SOURCE_2 ] +
                  currents->current[ PMIC4_CURRENT_CHARGER ] -
                  currents->current[ PMIC4_CURRENT_LOAD ];
        if ( balance > APP_BALANCE_DEADBAND_MA )
        {
            message = "Charging";
        }
        else if ( balance < -APP_BALANCE_DEADBAND_MA )
        {
            message = "Discharging";
        }
        else
        {
            message = "Near balance";
        }
        if ( balance < 0.0f )
        {
            balance = -balance;
        }
        log_printf( &logger, "%s ~%.1f mA at STO", message, balance );
    }
    else if ( currents->errors & PMIC4_APM_CONVERTER_ERROR_MASK )
    {
        log_printf( &logger, "APM unavailable" );
    }
    else if ( currents->activity & APP_CHARGE_ACTIVITY_MASK )
    {
        log_printf( &logger, "Charging path active" );
    }
    else if ( currents->activity & PMIC4_CURRENT_LOAD_VALID )
    {
        log_printf( &logger, "Discharging to LOAD" );
    }
    else
    {
        log_printf( &logger, "No transfer detected" );
    }
    log_printf( &logger, "\r\n" );

    for ( channel = 0; channel < PMIC4_CURRENT_CHANNEL_COUNT; channel++ )
    {
        mask = ( uint8_t ) ( 1 << channel );
        log_printf( &logger, "  %s: ", channel_name[ channel ] );
        if ( PMIC4_CURRENT_LOAD == channel )
        {
            if ( load_ready )
            {
                log_printf( &logger, "ready; " );
            }
            else
            {
                log_printf( &logger, "not ready; " );
            }
        }
        if ( PMIC4_CURRENT_CHARGER == channel )
        {
            if ( !( status->power & PMIC4_STATUS_CHARGER_CONNECTED ) )
            {
                message = "disconnected";
            }
            else if ( currents->activity & mask )
            {
                message = "charging";
            }
            else
            {
                message = "connected, idle";
            }
            log_printf( &logger, "%s", message );
            if ( !( status->power & PMIC4_STATUS_CHARGER_CONNECTED ) && ( currents->activity & mask ) )
            {
                log_printf( &logger, " (charging in previous window)" );
            }
            if ( ( currents->activity & mask ) && ( currents->errors & PMIC4_APM_CHARGER_LIMITED ) )
            {
                log_printf( &logger, " (precharge limited)" );
            }
        }
        else if ( ( channel < PMIC4_CURRENT_LOAD ) && ( status->power & PMIC4_STATUS_CHARGER_CONNECTED ) )
        {
            log_printf( &logger, "disabled by 5 V charger" );
        }
        else if ( currents->errors & ( PMIC4_APM_CHANNEL_ERROR_MASK <<
                                       ( channel * PMIC4_APM_ERROR_BITS_PER_CHANNEL ) ) )
        {
            message = "counter overflow";
            if ( currents->errors & ( PMIC4_APM_SOURCE_1_INVALID <<
                                     ( channel * PMIC4_APM_ERROR_BITS_PER_CHANNEL ) ) )
            {
                if ( channel < PMIC4_CURRENT_LOAD )
                {
                    message = "input above STO";
                }
                else
                {
                    message = "low STO headroom";
                }
            }
            log_printf( &logger, "APM unavailable (%s)", message );
        }
        else if ( PMIC4_CURRENT_LOAD == channel )
        {
            // Nonzero buck activity also occurs without an external load.
            // Display the level to observe demand changes without calibration.
            log_printf( &logger, "APM: %.2f M units", currents->apm_value[ channel ] / APP_APM_DISPLAY_SCALE );
        }
        else if ( currents->activity & mask )
        {
            log_printf( &logger, "charging path active" );
        }
        else
        {
            log_printf( &logger, "idle" );
        }
        if ( currents->valid & mask )
        {
            log_printf( &logger, " (%.1f mA at STO)", currents->current[ channel ] );
        }
        log_printf( &logger, "\r\n" );
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

// ------------------------------------------------------------------------ END
