/*!
 * @file main.c
 * @brief BATT-MAN3 Click example
 *
 * # Description
 * This example showcases ability of device to charge battery,
 * and outputs and supply 4 different devices with 3 LDO's and
 * 1 boost channel.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of the communication modules(UART, I2C) and 3 additional
 * input pins(power good, battery ok, and interrupt). Configures device
 * to enable charging, battery voltage monitoring, sets charging termination
 * to 3.7V, charging threshold to 3.1V and dead battery to 2.5V. Enables all
 * 3 LDO's( channel 1 -> 3.3V, channel 2 -> 1.5V, and channel 3 -> 2.5V ). 
 *
 * ## Application Task
 * Reads battery voltage level and logs it. Besides that reads status and logs
 * every change on charging and battery status. If power good flag occurs(PGD 
 * pin goes low) disables LDO's, and reenables them when battery is full(when 
 * battery reaches charging termination voltage).
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "battman3.h"

/**
 * @brief BATT-MAN 3 Click LOG delay.
 * @details Macro that specifies delay between logs of battery voltage.
 */
#define LOG_THRESHOLD_1SEC 10
#define LOG_THRESHOLD_3SEC 30
#define LOG_THRESHOLD_5SEC 50

static battman3_t battman3;
static log_t logger;

/**
 * @brief Parse charge status.
 * @details This function reads charge status 1 and 2 
 * and logs @b CHAGER_STATUS and @b BATTERY_STATUS on change.
 * @return Nothing.
 */
static void battman3_charge_status ( void );

/**
 * @brief Enable/Disable all 3 LDO's.
 * @details This function sets state of all 3 LDO's.
 * @param[in] enable : Enable/Disable.
 * @return Nothing.
 */
static void battman3_ldo( uint8_t enable );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battman3_cfg_t battman3_cfg;  /**< Click config object. */

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
    battman3_cfg_setup( &battman3_cfg );
    BATTMAN3_MAP_MIKROBUS( battman3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battman3_init( &battman3, &battman3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTMAN3_ERROR == battman3_default_cfg ( &battman3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t temp_data = 0;
    
    battman3_reg_read( &battman3, BATTMAN3_REG_MANUFACTURE_AND_MODEL_ID, &temp_data );
    log_printf( &logger, " > ID: 0x%.2X\r\n", ( uint16_t )temp_data );
    battman3_reg_read( &battman3, BATTMAN3_REG_SILICON_REVSION, &temp_data );
    log_printf( &logger, " > REV: 0x%.2X\r\n", ( uint16_t )temp_data );
    
    //Charging voltage termination
    battman3_set_charge_termination_voltage( &battman3, 3.7 );
    //Charging voltage threshold
    battman3_set_charge_voltage_threshold( &battman3, BATTMAN3_VTRK_DEAD_2p5V, 3.1 );
    //LDO 1
    battman3_set_ldo_state( &battman3, BATTMAN3_LDO1, BATTMAN3_ENABLE );
    battman3_set_ldo_vout( &battman3, BATTMAN3_LDO1, BATTMAN3_LDO_3p30V );
    //LDO 2
    battman3_set_ldo_state( &battman3, BATTMAN3_LDO2, BATTMAN3_ENABLE );
    battman3_set_ldo_vout( &battman3, BATTMAN3_LDO2, BATTMAN3_LDO_1p50V );
    //LDO 3
    battman3_set_ldo_state( &battman3, BATTMAN3_LDO3, BATTMAN3_ENABLE );
    battman3_set_ldo_vout( &battman3, BATTMAN3_LDO3, BATTMAN3_LDO_2p50V );
    
    log_info( &logger, " Application Task " );
    Delay_ms( 500 );
}

void application_task ( void ) 
{
    static counter = 0;
    float vbat = 0; 
    
    if ( !battman3_get_power_good( &battman3 ) )
    {
        battman3_ldo( BATTMAN3_DISABLE );
    }
    
    battman3_charge_status( );
    
    if ( counter >= LOG_THRESHOLD_3SEC )
    {
        counter = 0;
        battman3_get_battery_voltage( &battman3, &vbat );
        log_printf( &logger, " > Battery voltage: %.2f\r\n", vbat );  
        log_printf( &logger, "****************************************************\r\n" );
    }
    counter++;
    Delay_ms( 100 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

static void battman3_charge_status ( void )
{
    static uint8_t charge_status1 = 0;
    static uint8_t charge_status2 = 0;
    uint8_t temp_data = 0;
    battman3_reg_read( &battman3, BATTMAN3_REG_CHARGER_STATUS1, &temp_data );
    temp_data &= 0x7;
    if ( charge_status1 != temp_data )
    {
        charge_status1 = temp_data;
        switch ( charge_status1 )
        {
            case BATTMAN3_CHARGE_STATUS1_OFF:
            {
                log_printf( &logger, " > Charge status: off\r\n" );
                break;
            }
            case BATTMAN3_CHARGE_STATUS1_TRICLE_CHARGE:
            {
                log_printf( &logger, " > Charge status: tricle charge\r\n" );
                break;
            }
            case BATTMAN3_CHARGE_STATUS1_FAST_CHARGE_CC:
            {
                log_printf( &logger, " > Charge status: fast charge(CC mode)\r\n" );
                break;
            }
            case BATTMAN3_CHARGE_STATUS1_FAST_CHARGE_CV:
            {
                battman3_ldo( BATTMAN3_ENABLE );/*< Battery is full reenable LDO's*/
                log_printf( &logger, " > Charge status: fast charge(CV mode)\r\n" );
                break;
            }
            case BATTMAN3_CHARGE_STATUS1_CHARGE_COMPLETE:
            {
                log_printf( &logger, " > Charge status: charge complete\r\n" );
                break;
            }
            case BATTMAN3_CHARGE_STATUS1_SUSPEND:
            {
                log_printf( &logger, " > Charge status: suspend\r\n" );
                break;
            }
            case BATTMAN3_CHARGE_STATUS1_TIMER_EXPIRED:
            {
                log_printf( &logger, " > Charge status: ticle, fast or safety charge timer expired\r\n" );
                break;
            }
            case BATTMAN3_CHARGE_STATUS1_BATTERY_DETECTION:
            {
                log_printf( &logger, " > Charge status: battery detection\r\n" );
                break;
            }
            default:
            {
                log_error( &logger, " Status." );
                break;
            }
        }
    }
    battman3_reg_read( &battman3, BATTMAN3_REG_CHARGER_STATUS2, &temp_data );
    temp_data &= 0x07;
    if ( charge_status2 != temp_data )
    {
        charge_status2 = temp_data;
        switch ( charge_status2 )
        {
            case BATTMAN3_CHARGE_STATUS2_BATTERY_MONITOR_OFF:
            {
                log_printf( &logger, " > Battery monitor off\r\n" );
                break;
            }
            case BATTMAN3_CHARGE_STATUS2_NO_BATTERY:
            {
                log_printf( &logger, " > No battery\r\n" );
                break;
            }
            case BATTMAN3_CHARGE_STATUS2_VBSNS_LESSTHEN_VTRK:
            {
                log_printf( &logger, " > Battery voltage less then trickle threshold\r\n" );
                break;
            }
            case BATTMAN3_CHARGE_STATUS2_VBSNS_MIDDLE_VRK_VWEAK:
            {
                log_printf( &logger, " > Battery voltage in middle between tricle and weak threshold\r\n" );
                break;
            }
            case BATTMAN3_CHARGE_STATUS2_VBSNS_MORETHEN_VWEAK:
            {
                log_printf( &logger, " > Battery voltage more then weak threshold\r\n" );
                break;
            }
            default:
            {
                log_error( &logger, " Status." );
                break;
            }
        }
    }
}

static void battman3_ldo( uint8_t enable )
{
    battman3_set_ldo_state( &battman3, BATTMAN3_LDO1, enable );
    battman3_set_ldo_state( &battman3, BATTMAN3_LDO2, enable );
    battman3_set_ldo_state( &battman3, BATTMAN3_LDO3, enable );
}

// ------------------------------------------------------------------------ END
