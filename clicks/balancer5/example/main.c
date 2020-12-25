/*!
 * \file 
 * \brief Balancer5 Click example
 * 
 * # Description
 * This example demonstrates basic Balancer 5 Click functionalities.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Click and Driver, Checks Device ID, starts charging,
 * reads charge status registers and configures ADC.
 * 
 * ## Application Task  
 * Reads ADC values from registers and logs it.
 * 
 * ## Additional function
 * void charger_status_1_handler ( uint8_t cs1_data );
 * void charger_status_2_handler ( uint8_t cs2_data );
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "balancer5.h"

// ------------------------------------------------------------------ VARIABLES

static balancer5_t balancer5;
static log_t logger;

static uint8_t temp_data;
static uint16_t temp_uint_data;
static float temp_float_data;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void charger_status_1_handler ( uint8_t cs1_data )
{
    uint8_t charge = 0;

    log_printf( &logger, "* CHARGER STATUS 1 :\r\n" );
    if ( ( cs1_data & BALANCER5_CS1_IINDPM_IN_REGULATION ) == BALANCER5_CS1_IINDPM_IN_REGULATION )
    {
        log_printf( &logger, "    - IINDPM_IN_REGULATION" );
    }
    else
    {
        log_printf( &logger, "    - IINDPM_NORMAL" );
    }

    if ( ( cs1_data & BALANCER5_CS1_VINDPM_IN_REGULATION ) == BALANCER5_CS1_VINDPM_IN_REGULATION )
    {
        log_printf( &logger, "    - VINDPM_IN_REGULATION" );
    }
    else
    {
        log_printf( &logger, "    - VINDPM_NORMAL" );
    }

    if ( ( cs1_data & BALANCER5_CS1_IC_IN_THERMAL_REGULATION ) == BALANCER5_CS1_IC_IN_THERMAL_REGULATION )
    {
        log_printf( &logger, "    - IC_IN_THERMAL_REGULATION" );
    }
    else
    {
        log_printf( &logger, "    - IC_NORMAL" );
    }

    if ( ( cs1_data & BALANCER5_CS1_WD_TIMER_EXPIRED ) == BALANCER5_CS1_WD_TIMER_EXPIRED )
    {
        log_printf( &logger, "    - WD_TIMER_EXPIRED" );
    }
    else
    {
        log_printf( &logger, "    - WD_NORMAL" );
    }

    if ( ( cs1_data & BALANCER5_CS1_TRICKLE_CHARGE ) == BALANCER5_CS1_TRICKLE_CHARGE )
    {
        charge++;
        log_printf( &logger, "    - TRICKLE_CHARGE" );
    }
    if ( ( cs1_data & BALANCER5_CS1_PRE_CHARGE ) == BALANCER5_CS1_PRE_CHARGE )
    {
        charge++;
        log_printf( &logger, "    - PRE_CHARGE" );
    }
    if ( ( cs1_data & BALANCER5_CS1_FAST_CHARGE ) == BALANCER5_CS1_FAST_CHARGE )
    {
        charge++;
        log_printf( &logger, "    - FAST_CHARGE" );
    }
    if ( ( cs1_data & BALANCER5_CS1_TAPER_CHARGE ) == BALANCER5_CS1_TAPER_CHARGE )
    {
        charge++;
        log_printf( &logger, "    - TAPER_CHARGE" );
    }
    if ( ( cs1_data & BALANCER5_CS1_TOP_OFF_TIMER_CHARGE ) == BALANCER5_CS1_TOP_OFF_TIMER_CHARGE )
    {
        charge++;
        log_printf( &logger, "    - TOP_OFF_TIMER_CHARG" );
    }
    if ( ( cs1_data & BALANCER5_CS1_CHARGE_TERMINATION ) == BALANCER5_CS1_CHARGE_TERMINATION )
    {
        charge++;
        log_printf( &logger, "    - CHARGE_TERMINATION" );
    }
    if ( charge == 0 )
    {
        log_printf( &logger, "    - NOT_CHARGING" );
    }
}

void charger_status_2_handler ( uint8_t cs2_data )
{
    uint8_t power_in = 0;

    log_printf( &logger, "\r\n* CHARGER STATUS 2 :\r\n" );

    if ( ( cs2_data & BALANCER5_CS2_MAX_INPUT ) == BALANCER5_CS2_MAX_INPUT )
    {
        log_printf( &logger, "    - MAX_INPUT" );
    }
    else if ( ( cs2_data & BALANCER5_CS2_ICO_OPTIMIZATION_IN_PROGRESS ) == BALANCER5_CS2_ICO_OPTIMIZATION_IN_PROGRESS )
    {
        log_printf( &logger, "    - ICO_OPTIMIZATION_IN_PROGRESS" );
    }
    else
    {
        log_printf( &logger, "    - ICO_DISABLED" );
    }

    if ( ( cs2_data & BALANCER5_CS2_POWER_GOOD ) == BALANCER5_CS2_POWER_GOOD )
    {
        log_printf( &logger, "    - POWER_GOOD" );
    }
    else
    {
        log_printf( &logger, "    - POWER_NOT_GOOD" );
    }

    if ( ( cs2_data & BALANCER5_CS2_NON_STANDARD_ADAPTER ) == BALANCER5_CS2_NON_STANDARD_ADAPTER )
    {
        power_in++;
        log_printf( &logger, "    - NON_STANDARD_ADAPTER" );
    }
    if ( ( cs2_data & BALANCER5_CS2_UNKNOWN_ADAPTER ) == BALANCER5_CS2_UNKNOWN_ADAPTER )
    {
        power_in++;
        log_printf( &logger, "    - UNKNOWN_ADAPTER" );
    }
    if ( ( cs2_data & BALANCER5_CS2_POORSRC ) == BALANCER5_CS2_POORSRC )
    {
        power_in++;
        log_printf( &logger, "    - POORSRC" );
    }
    if ( ( cs2_data & BALANCER5_CS2_ADAPTER ) == BALANCER5_CS2_ADAPTER )
    {
        power_in++;
        log_printf( &logger, "    - ADAPTER" );
    }
    if ( ( cs2_data & BALANCER5_CS2_USB_CDP ) == BALANCER5_CS2_USB_CDP )
    {
        power_in++;
        log_printf( &logger, "    - CS2_USB_CDP" );
    }
    if ( ( cs2_data & BALANCER5_CS2_USB_HOST_SDP ) == BALANCER5_CS2_USB_HOST_SDP )
    {
        power_in++;
        log_printf( &logger, "    - USB_HOST_SDP" );
    }
    if ( power_in == 0 )
    {
        log_printf( &logger, "    - NO_INPUT" );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    balancer5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    balancer5_cfg_setup( &cfg );
    BALANCER5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    balancer5_init( &balancer5, &cfg );

    //  Device ID sanity check

    temp_data = balancer5_check_id( &balancer5 );

    if ( temp_data == BALANCER5_ERROR_ID )
    {
        log_info( &logger, "ID ERROR!!!" );
        for ( ; ; );
    }
    
    log_info( &logger, "***** ID OK *****" );

    //  Switch charger on

    balancer5_charge( &balancer5, BALANCER5_CHARGE_ON );

    //  Send configuration info to logger

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_CHARGER_STATUS_1 );
    charger_status_1_handler( temp_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_CHARGER_STATUS_2 );
    charger_status_2_handler( temp_data );

    //  Set default configuration

    balancer5_default_cfg ( &balancer5 );
   
}

void application_task ( void )
{
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_IBUS_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_IBUS_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- IBUS: %umA\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_ICHG_ADC1 ); 
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_ICHG_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- ICHG: %umA\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VBAT_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VBAT_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- VBAT: %umV\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VBUS_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VBUS_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- VBUS: %umV\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VCELLTOP_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VCELLTOP_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- VCELLTOP: %umV\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VCELLBOT_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VCELLBOT_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- VCELLBOT: %umV\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_TS_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_TS_ADC0 );
    temp_uint_data |= temp_data;
    temp_float_data = temp_uint_data;
    temp_float_data *= 0.098;
    log_printf( &logger, "- TS: %.2f%%\r\n", temp_float_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_TDIE_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_TDIE_ADC0 );
    temp_uint_data |= temp_data;
    temp_float_data = temp_uint_data;
    temp_float_data *= 0.5;
    log_printf( &logger, "- TDIE: %.2f degC\r\n", temp_float_data );
    log_printf( &logger, "____________________\r\n" );
    
    Delay_ms( 5000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
