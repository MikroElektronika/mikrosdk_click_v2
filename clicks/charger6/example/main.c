/*!
 * @file main.c
 * @brief Charger6 Click example
 *
 * # Description
 * This library contains API for the Charger 6 Click driver.
 * The library contains drivers to enable/disable battery charging, 
 * set current limit, set system min voltage, set fast charge current,
 * set charge voltage, etc.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and set default configuration:
 * input current limit set to 500 mA, system minimum voltage to 3500 mV,
 * fast charge current set to 360 mA, charge voltage to 4112 mV and
 * enable battery charging.  
 *
 * ## Application Task
 * This example monitors the operation of the Charger 6 Click and all its charging states. 
 * The user can observe information such as charging status, selected mode, 
 * charging current value, and the momentary value of the supply voltage relative to the battery voltage.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "charger6.h"

static charger6_t charger6;
static log_t logger;

charger6_status_t chg_status;
static uint16_t charge_current;

void display_chrg_status ( void ) {
    log_printf( &logger, " Charging   :" );
    switch ( chg_status.chrg_stat ) {
        case CHARGER6_R08_CHRG_STAT_NOT_CHARGING : {
            log_printf( &logger, " Not Charging\r\n" );
            break;
        }
        case CHARGER6_R08_CHRG_STAT_PRE_CHARGE : {
            log_printf( &logger, " Pre-charge\r\n" );
            break;
        }
        case CHARGER6_R08_CHRG_STAT_FAST_CHARGING : {
            log_printf( &logger, " Fast Charging\r\n" );
            charge_current = charger6_get_fast_charge_current( &charger6 );
            log_printf( &logger, " Chg Current: %u mA\r\n", charge_current );
            break;
        }
        case CHARGER6_R08_CHRG_STAT_CHARGE_TERMINATION : {
            log_printf( &logger, " Charge Termination\r\n" );
            break;
        }
        default : {
            log_printf( &logger, " Unknown\r\n" );
            break;
        }
    }
}

void display_power_good_status ( void ) {
    log_printf( &logger, " Power      :" );
    switch ( chg_status.pg_stat ) {
        case CHARGER6_R08_PG_STAT_POWER_NOT_GOOD : {
            log_printf( &logger, " Power Not Good\r\n" );
            break;
        }
        case CHARGER6_R08_PG_STAT_POWER_GOOD : {
            log_printf( &logger, " Power Good\r\n" );
            break;
        }
        default : {
            log_printf( &logger, " Unknown\r\n" );
            break;
        }
    }
}

void display_vsys_status ( void ) {
    log_printf( &logger, " Vsys       :" );
    switch ( chg_status.vsys_stat ) {
        case CHARGER6_R08_VSYS_STAT_NOT : {
            log_printf( &logger, " BAT > Vsys Min\r\n" );
            break;
        }
        case CHARGER6_R08_VSYS_STAT_VSYSM : {
            log_printf( &logger, " BAT < Vsys Min\r\n" );
            break;
        }
        default : {
            log_printf( &logger, " Unknown\r\n" );
            break;
        }
    }
}


void display_bat_status ( void ) {
    log_printf( &logger, " Battery    :" );
    switch ( chg_status.bat_fault ) {
        case CHARGER6_R09_BAT_FAULT_NORMAL : {
            log_printf( &logger, " Normal\r\n" );
            break;
        }
        case CHARGER6_R08_VSYS_STAT_VSYSM : {
            log_printf( &logger, " Overvoltage\r\n" );
            break;
        }
        default : {
            log_printf( &logger, " Unknown\r\n" );
            break;
        }
    }
}

void display_chrg_fault_status ( void ) {
    log_printf( &logger, " Chrg fault :" );
    switch ( chg_status.chrg_fault ) {
        case CHARGER6_R09_CHRG_FAULT_NORMAL : {
            log_printf( &logger, " Normal\r\n" );
            break;
        }
        case CHARGER6_R09_CHRG_FAULT_INPUT_FAULT : {
            log_printf( &logger, " Input fault\r\n" );
            break;
        }
        case CHARGER6_R09_CHRG_FAULT_THERMAL_SHUTDOWN : {
            log_printf( &logger, " Thermal shutdown\r\n" );
            break;
        }
        case CHARGER6_R09_CHRG_FAULT_CHG_SAFETY_TIMER_EXP : {
            log_printf( &logger, " Charge Safety Timer Expiration\r\n" );
            break;
        }
        default : {
            log_printf( &logger, " Unknown\r\n" );
            break;
        }
    }
}

void application_init ( void ) {
    log_cfg_t log_cfg;            /**< Logger config object. */
    charger6_cfg_t charger6_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    charger6_cfg_setup( &charger6_cfg );
    CHARGER6_MAP_MIKROBUS( charger6_cfg, MIKROBUS_1 );
    err_t init_flag = charger6_init( &charger6, &charger6_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    charger6_default_cfg ( &charger6 );
    log_info( &logger, " Application Task " );
    Delay_ms( 1000 );

    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, " Set Current Limit   :  500 mA \r\n" );
    charger6_set_input_current_limit( &charger6, 500 );
    Delay_ms( 100 );
    
    log_printf( &logger, " Set Sys Min Voltage : 3500 mV \r\n" );
    charger6_set_system_minimum_voltage( &charger6, 3500 );
    Delay_ms( 100 );
    
    log_printf( &logger, " Set Fast Chg Current:  360 mA \r\n" );
    charger6_set_fast_charge_current( &charger6, 360 );
    Delay_ms( 100 );
    
    log_printf( &logger, " Set Charge Voltage  : 4112 mV \r\n" );
    charger6_set_charge_voltage( &charger6, 4112 );
    Delay_ms( 100 );
    
    log_printf( &logger, " >> Enable Battery Charging << \r\n" );
    charger6_enable_battery_charging( &charger6 );
    Delay_ms( 1000 );
    
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "       >>>   Status   <<<      \r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
}

void application_task ( void ) {
    charger6_get_status( &charger6, &chg_status );
    Delay_ms( 100 );
    
    display_power_good_status( );
    Delay_ms( 100 );
    
    display_chrg_status( );
    Delay_ms( 100 );
    
    display_bat_status( );
    Delay_ms( 100 );
    
    display_chrg_fault_status( );
    Delay_ms( 100 );
    
    display_vsys_status( );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms( 2000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
