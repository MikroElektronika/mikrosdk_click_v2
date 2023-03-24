/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file charger6.c
 * @brief Charger 6 Click Driver.
 */

#include "charger6.h"

/**
 * @brief Charger 6 system minimum voltage description.
 * @details System minimum voltage 
 * for description of Charger 6 Click driver.
 */
#define CHARGER6_SET_SYS_MIN_VTG_BIT_MASK               0xF1
#define CHARGER6_SET_SYS_MIN_VTG_2600mV                 0x00
#define CHARGER6_SET_SYS_MIN_VTG_2800mV                 0x02
#define CHARGER6_SET_SYS_MIN_VTG_3000mV                 0x04
#define CHARGER6_SET_SYS_MIN_VTG_3200mV                 0x06
#define CHARGER6_SET_SYS_MIN_VTG_3400mV                 0x08
#define CHARGER6_SET_SYS_MIN_VTG_3500mV                 0x0A
#define CHARGER6_SET_SYS_MIN_VTG_3600mV                 0x0C
#define CHARGER6_SET_SYS_MIN_VTG_3700mV                 0x0E

/**
 * @brief Charger 6 fast charge current description.
 * @details Fast charge current 
 * for description of Charger 6 Click driver.
 */
#define CHARGER6_ICHG_BIT_MASK                          0xC0
#define CHARGER6_ICHG_CURRENT_BIT_MASK                  0x3F 
#define CHARGER6_ICHG_DISABLES_CHARGE_0mA               0x00
#define CHARGER6_ICHG_MAX_3000mA                        0x32

/**
 * @brief Charger 6 input current limit description.
 * @details Input current limit 
 * for description of Charger 6 Click driver.
 */
#define CHARGER6_IINDPM_MIN_100mA                       0x00
#define CHARGER6_IINDPM_MAX_3200mA                      0x1F
#define CHARGER6_IINDPM_OFFSET                           100

/**
 * @brief Charger 6 top off timer description.
 * @details Top off timer voltage 
 * for description of Charger 6 Click driver.
 */
#define CHARGER6_TOPOFF_TIMER_BIT_MASK                  0xF9
#define CHARGER6_TOPOFF_TIMER_VAL_DISABLE               0x00
#define CHARGER6_TOPOFF_TIMER_VAL_15_MINUTES            0x01
#define CHARGER6_TOPOFF_TIMER_VAL_30_MINUTES            0x02
#define CHARGER6_TOPOFF_TIMER_VAL_45_MINUTES            0x03

/**
 * @brief Charger 6 precharge and termination current description.
 * @details Precharge and termination current 
 * for description of Charger 6 Click driver.
 */
#define CHARGER6_PRECHARGE_CURRENT_BIT_MASK             0xF0
#define CHARGER6_PRECHARGE_CURRENT_MIN_60mA             0x00
#define CHARGER6_PRECHARGE_CURRENT_MAX_780mA            0xC0
#define CHARGER6_PRECHARGE_CURRENT_OFFSET                 60
#define CHARGER6_TERMINATION_CURRENT_BIT_MASK           0x0F
#define CHARGER6_TERMINATION_CURRENT_MIN_60mA           0x00
#define CHARGER6_TERMINATION_CURRENT_MAX_780mA          0x0C
#define CHARGER6_TERMINATION_CURRENT_OFFSET               60

/**
 * @brief Charger 6 charge voltage description.
 * @details Charge Voltage
 * for description of Charger 6 Click driver.
 */
#define CHARGER6_VREG_BIT_MASK                          0x1F
#define CHARGER6_VREG_MIN_3856mV                        0x00
#define CHARGER6_VREG_MAX_4624mV                        0x1F
#define CHARGER6_VREG_OFFSET                            3856


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief HW LH Reset delay.
 * @details HW LH reset delay for 8000 milliseconds.
 */
static void dev_hw_lh_reset_delay ( void );

/**
 * @brief Reset delay.
 * @details Reset delay for 250 milliseconds.
 */
static void dev_reset_delay ( void );

/**
 * @brief Configuration delay.
 * @details Configuration delay for 10 milliseconds.
 */
static void dev_config_delay ( void );


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void charger6_cfg_setup ( charger6_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->ce   = HAL_PIN_NC;
    cfg->qon = HAL_PIN_NC;
    cfg->psel = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CHARGER6_SET_DEV_ADDR;
}

err_t charger6_init ( charger6_t *ctx, charger6_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->ce, cfg->ce );
    digital_out_init( &ctx->qon, cfg->qon );
    digital_out_init( &ctx->psel, cfg->psel );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t charger6_default_cfg ( charger6_t *ctx ) {   
    uint8_t tx_buf[ 1 ];
    err_t cfg_flag;
    
    charger6_power_source_selection( ctx, CHARGER6_PSEL_SW_MANUAL );
    dev_config_delay( );
    
    tx_buf[ 0 ]  = CHARGER6_R00_EN_HIZ_ENABLE;
    tx_buf[ 0 ] |= ( CHARGER6_R00_IINDPM_1600mA |
                     CHARGER6_R00_IINDPM_400mA  | 
                     CHARGER6_R00_IINDPM_200mA  | 
                     CHARGER6_R00_IINDPM_100mA  );
    cfg_flag = charger6_generic_write( ctx, CHARGER6_REGISTER_00, tx_buf, 1 );
    dev_config_delay( );
    
    tx_buf[ 0 ]  = CHARGER6_R01_PFM_DISABLE;
    tx_buf[ 0 ] |= CHARGER6_R01_WD_RST_NORMAL;
    tx_buf[ 0 ] |= CHARGER6_R01_OTG_DISABLE;
    tx_buf[ 0 ] |= CHARGER6_R01_CHARGE_ENABLE;
    tx_buf[ 0 ] |= CHARGER6_R01_SYS_MIN_3500mV;
    tx_buf[ 0 ] |= CHARGER6_R01_MIN_VBAT_SEL_2800mV;
    cfg_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_01, tx_buf, 1 );
    dev_config_delay( );
    
    tx_buf[ 0 ]  = CHARGER6_R02_BOOST_LIM_1200mA;
    tx_buf[ 0 ] |= CHARGER6_R02_Q1_FULLON_BETTER_EFFICIENCY;
    tx_buf[ 0 ] |= ( CHARGER6_R02_ICHG_1920mA |
                     CHARGER6_R02_ICHG_480mA );
    cfg_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_02, tx_buf, 1 );
    dev_config_delay( );
    
    tx_buf[ 0 ]  = CHARGER6_R03_IPRECHG_240mA;
    tx_buf[ 0 ] |= CHARGER6_R03_ITERM_240mA;
    cfg_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_03, tx_buf, 1 );
    dev_config_delay( );
    
    tx_buf[ 0 ]  = CHARGER6_R04_VREG_256mV;
    tx_buf[ 0 ] |= CHARGER6_R04_TOPOFF_TIMER_DISABLED;
    tx_buf[ 0 ] |= CHARGER6_R04_VRECHG_100mV;
    cfg_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_04, tx_buf, 1 );
    dev_config_delay( );
    
    tx_buf[ 0 ]  = CHARGER6_R05_TERMINATION_ENABLE;
    tx_buf[ 0 ] |= CHARGER6_R05_WATCHDOG_DISABLE;
    tx_buf[ 0 ] |= CHARGER6_R05_TIMER_ENABLE;
    tx_buf[ 0 ] |= CHARGER6_R05_CHG_TIMER_10_HOURS;
    tx_buf[ 0 ] |= CHARGER6_R05_TREG_90_C;
    tx_buf[ 0 ] |= CHARGER6_R05_JEITA_ISET_50;
    cfg_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_05, tx_buf, 1 );
    dev_config_delay( );
    
    tx_buf[ 0 ]  = CHARGER6_R06_OVP_TSH_6500mV;
    tx_buf[ 0 ] |= CHARGER6_R06_BOOSTV_5000mV;
    tx_buf[ 0 ] |= ( CHARGER6_R06_VINDPM_400mV |
                     CHARGER6_R06_VINDPM_200mV );
    cfg_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_06, tx_buf, 1 );
    dev_config_delay( );
    
    tx_buf[ 0 ]  = CHARGER6_R07_FORCE_INPUT_CURRENT_LIMIT;
    tx_buf[ 0 ] |= CHARGER6_R07_TMR2X_ENABLE;
    tx_buf[ 0 ] |= CHARGER6_R07_BATFET_ALLOW_Q4_TURN_ON;
    tx_buf[ 0 ] |= CHARGER6_R07_JEITA_VSET_TO_VREG;
    tx_buf[ 0 ] |= CHARGER6_R07_BATFET_IMMEDIATELY;
    tx_buf[ 0 ] |= CHARGER6_R07_BATFET_RST_ENABLE;
    tx_buf[ 0 ] |= CHARGER6_R07_VDPM_BAT_TRACK_DISABLE;
    cfg_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_07, tx_buf, 1 );
    dev_config_delay( );
    
    tx_buf[ 0 ]  = CHARGER6_R00_EN_HIZ_DISABLE;
    tx_buf[ 0 ] |= ( CHARGER6_R00_IINDPM_1600mA |
                     CHARGER6_R00_IINDPM_400mA  | 
                     CHARGER6_R00_IINDPM_200mA  | 
                     CHARGER6_R00_IINDPM_100mA  );
    cfg_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_00, tx_buf, 1 );
    dev_config_delay( );
    
    return cfg_flag;
}

err_t charger6_generic_write ( charger6_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t charger6_generic_read ( charger6_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void charger6_enable_battery_charging ( charger6_t *ctx ) {
    digital_out_low( &ctx->ce );
}

void charger6_disable_battery_charging ( charger6_t *ctx ) {
    digital_out_high( &ctx->ce );
}

void charger6_power_source_selection ( charger6_t *ctx, uint8_t pwr_sel ) {
    if ( pwr_sel == CHARGER6_PSEL_SW_MANUAL ) {
        digital_out_low( &ctx->psel );   
    } else {
        digital_out_high( &ctx->psel );      
    }
}

err_t charger6_set_input_current_limit ( charger6_t *ctx, uint16_t current_limit ) {
    uint8_t tmp;
    uint8_t rx_tx_buf[ 1 ];
    err_t st_flag;
    
    st_flag = charger6_generic_read( ctx, CHARGER6_REGISTER_00, rx_tx_buf, 1 );
    
    if ( current_limit >= 3200 ) {
        tmp = CHARGER6_IINDPM_MAX_3200mA;    
    } else if ( current_limit <= 100 ) {
        tmp = CHARGER6_IINDPM_MIN_100mA;
    } else {
        tmp -= CHARGER6_IINDPM_OFFSET;
        tmp = ( uint8_t ) ( current_limit / 100 );
    }
    
    rx_tx_buf[ 0 ] |= tmp;
    st_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_00, rx_tx_buf, 1 );
    
    return st_flag; 
}

err_t charger6_set_system_minimum_voltage ( charger6_t *ctx, uint16_t sys_min_voltage ) {
    uint8_t tmp;
    uint8_t rx_tx_buf[ 1 ];
    err_t st_flag;
    
    st_flag = charger6_generic_read( ctx, CHARGER6_REGISTER_01, rx_tx_buf, 1 );
    
    switch ( sys_min_voltage ) {
        case CHARGER6_SYS_MIN_VTG_2600mV : {
            tmp = CHARGER6_SET_SYS_MIN_VTG_2600mV;
            break;
        }
        case CHARGER6_SYS_MIN_VTG_2800mV : {
            tmp = CHARGER6_SET_SYS_MIN_VTG_2800mV;
            break;
        }
        case CHARGER6_SYS_MIN_VTG_3000mV : {
            tmp = CHARGER6_SET_SYS_MIN_VTG_3000mV;
            break;
        }
        case CHARGER6_SYS_MIN_VTG_3200mV : {
            tmp = CHARGER6_SET_SYS_MIN_VTG_3200mV;
            break;
        }
        case CHARGER6_SYS_MIN_VTG_3400mV : {
            tmp = CHARGER6_SET_SYS_MIN_VTG_3400mV;
            break;
        }
        case CHARGER6_SYS_MIN_VTG_3500mV : {
            tmp = CHARGER6_SET_SYS_MIN_VTG_3500mV;
            break;
        }
        case CHARGER6_SYS_MIN_VTG_3600mV : {
            tmp = CHARGER6_SET_SYS_MIN_VTG_3600mV;
            break;
        }
        case CHARGER6_SYS_MIN_VTG_3700mV : {
            tmp = CHARGER6_SET_SYS_MIN_VTG_3700mV;
            break;
        }
        default : {
            tmp = CHARGER6_SET_SYS_MIN_VTG_3500mV;
            break;
        }
    }
    
    rx_tx_buf[ 0 ] &= CHARGER6_SET_SYS_MIN_VTG_BIT_MASK;
    rx_tx_buf[ 0 ] |= tmp;
    st_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_01, rx_tx_buf, 1 );
    
    return st_flag;
}

err_t charger6_get_status ( charger6_t *ctx, charger6_status_t *chg_status ) {
    uint8_t rx_buf[ 4 ];
    err_t st_flag;
    
    st_flag = charger6_generic_read( ctx, CHARGER6_REGISTER_08, rx_buf, 4 );
    
    chg_status->vbus_stat      = rx_buf[ 0 ] & CHARGER6_R08_VBUS_BIT_MASK;
    chg_status->chrg_stat      = rx_buf[ 0 ] & CHARGER6_R08_CHRG_STAT_BIT_MASK;
    chg_status->pg_stat        = rx_buf[ 0 ] & CHARGER6_R08_PG_STAT_BIT_MASK;
    chg_status->therm_stat     = rx_buf[ 0 ] & CHARGER6_R08_THERM_STAT_BIT_MASK;
    chg_status->vsys_stat      = rx_buf[ 0 ] & CHARGER6_R08_VSYS_BIT_MASK;
    
    chg_status->watchdog_fault = rx_buf[ 1 ] & CHARGER6_R09_WATCHDOG_FAULT_BIT_MASK;
    chg_status->boost_fault    = rx_buf[ 1 ] & CHARGER6_R09_BOOST_FAULT_BIT_MASK;
    chg_status->chrg_fault     = rx_buf[ 1 ] & CHARGER6_R09_CHRG_FAULT_BIT_MASK;
    chg_status->bat_fault      = rx_buf[ 1 ] & CHARGER6_R09_BAT_FAULT_BIT_MASK;
    chg_status->ntc_fault      = rx_buf[ 1 ] & CHARGER6_R09_NTC_FAULT_BIT_MASK;
    
    chg_status->vbus_gd        = rx_buf[ 2 ] & CHARGER6_R0A_VBUS_GD_BIT_MASK;
    chg_status->vindpm_stat    = rx_buf[ 2 ] & CHARGER6_R0A_VBUS_GD_VINDPM_BIT_MASK;
    chg_status->iindpm_stat    = rx_buf[ 2 ] & CHARGER6_R0A_VBUS_GD_IINDPM_BIT_MASK;
    chg_status->topoff_active  = rx_buf[ 2 ] & CHARGER6_R0A_TOP_OFF_BIT_MASK;
    chg_status->acov_stat      = rx_buf[ 2 ] & CHARGER6_R0A_ACOV_STAT_BIT_MASK;
    chg_status->vindpm_int     = rx_buf[ 2 ] & CHARGER6_R0A_VINDPM_INT_MASK_MASK;
    chg_status->iindpm_int     = rx_buf[ 2 ] & CHARGER6_R0A_IINDPM_INT_MASK_MASK;
    
    chg_status->dev_id         = rx_buf[ 3 ] & CHARGER6_R0B_DEV_ID_BIT_MASK;
    chg_status->dev_rev        = rx_buf[ 3 ] & CHARGER6_R0B_DEV_REV_BIT_MASK;
    
    return st_flag;
} 

err_t charger6_set_fast_charge_current ( charger6_t *ctx, uint16_t fast_chg_current ) {
    uint8_t tmp;
    uint8_t rx_tx_buf[ 1 ];
    err_t st_flag;
    
    st_flag = charger6_generic_read( ctx, CHARGER6_REGISTER_02, rx_tx_buf, 1 );
    
    if ( fast_chg_current >= 3000 ) {
        tmp = CHARGER6_ICHG_MAX_3000mA;    
    } else if ( fast_chg_current <= 0 ) {
        tmp = CHARGER6_ICHG_DISABLES_CHARGE_0mA;
    } else {
        tmp = ( uint8_t ) ( fast_chg_current / 60 );
    }
    
    rx_tx_buf[ 0 ] &= CHARGER6_ICHG_BIT_MASK;
    rx_tx_buf[ 0 ] |= tmp;
    st_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_02, rx_tx_buf, 1 );
    
    return st_flag;
}

uint16_t charger6_get_fast_charge_current ( charger6_t *ctx ) {
    uint16_t charge_current;
    uint8_t rx_buf[ 1 ];
    
    charger6_generic_read( ctx, CHARGER6_REGISTER_02, rx_buf, 1 );
    
    rx_buf[ 0 ] &= CHARGER6_ICHG_CURRENT_BIT_MASK;
    
    charge_current = ( uint16_t ) ( rx_buf[ 0 ] );
    charge_current *= 60;
    
    return charge_current;
}

err_t charger6_set_precharge_current ( charger6_t *ctx, uint16_t precharge_current ) {
    uint8_t tmp;
    uint8_t rx_tx_buf[ 1 ];
    err_t st_flag;
    
    st_flag = charger6_generic_read( ctx, CHARGER6_REGISTER_03, rx_tx_buf, 1 );
    
    if ( precharge_current >= 720 ) {
        tmp = CHARGER6_PRECHARGE_CURRENT_MAX_780mA;    
    } else if ( precharge_current <= 0 ) {
        tmp = CHARGER6_PRECHARGE_CURRENT_MIN_60mA;
    } else {
        tmp -= CHARGER6_PRECHARGE_CURRENT_OFFSET;
        tmp = ( uint8_t ) ( precharge_current / 60 );
    }
    
    tmp <<= 4;
    rx_tx_buf[ 0 ] &= CHARGER6_PRECHARGE_CURRENT_BIT_MASK;
    rx_tx_buf[ 0 ] |= tmp;
    st_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_03, rx_tx_buf, 1 );
    
    return st_flag;
}

err_t charger6_set_termination_current ( charger6_t *ctx, uint16_t termination_current ) {
    uint8_t tmp;
    uint8_t rx_tx_buf[ 1 ];
    err_t st_flag;
    
    st_flag = charger6_generic_read( ctx, CHARGER6_REGISTER_03, rx_tx_buf, 1 );
    
    if ( termination_current >= 720 ) {
        tmp = CHARGER6_TERMINATION_CURRENT_MAX_780mA;    
    } else if ( termination_current <= 0 ) {
        tmp = CHARGER6_TERMINATION_CURRENT_MIN_60mA;
    } else {
        tmp -= CHARGER6_TERMINATION_CURRENT_OFFSET;
        tmp = ( uint8_t ) ( termination_current / 60 );
    }
    
    rx_tx_buf[ 0 ] &= CHARGER6_TERMINATION_CURRENT_BIT_MASK;
    rx_tx_buf[ 0 ] |= tmp;
    st_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_03, rx_tx_buf, 1 );
    
    return st_flag;
}

err_t charger6_set_charge_voltage ( charger6_t *ctx, uint16_t charge_voltage ) {
    uint8_t tmp;
    uint8_t rx_tx_buf[ 1 ];
    err_t st_flag;
    
    st_flag = charger6_generic_read( ctx, CHARGER6_REGISTER_04, rx_tx_buf, 1 );
    
    if ( charge_voltage >= 4624 ) {
        tmp = CHARGER6_VREG_MAX_4624mV;    
    } else if ( charge_voltage <= 3856 ) {
        tmp = CHARGER6_VREG_MIN_3856mV;
    } else {
        charge_voltage -= CHARGER6_VREG_OFFSET;
        tmp = ( uint8_t ) ( charge_voltage / 32 );
    }
    
    tmp <<= 3;
    rx_tx_buf[ 0 ] &= CHARGER6_VREG_BIT_MASK;
    rx_tx_buf[ 0 ] |= tmp;
    st_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_04, rx_tx_buf, 1 );
    
    return st_flag;
}

err_t charger6_set_top_off_timer ( charger6_t *ctx, uint8_t top_off_time ) {
    uint8_t tmp;
    uint8_t rx_tx_buf[ 1 ];
    err_t st_flag;
    
    st_flag = charger6_generic_read( ctx, CHARGER6_REGISTER_04, rx_tx_buf, 1 );
    
    switch ( top_off_time ) {
        case CHARGER6_TOPOFF_TIMER_DISABLE : {
            tmp = CHARGER6_TOPOFF_TIMER_VAL_DISABLE;
            break;
        }
        case CHARGER6_TOPOFF_TIMER_15_MINUTES : {
            tmp = CHARGER6_TOPOFF_TIMER_VAL_15_MINUTES;
            break;
        }
        case CHARGER6_TOPOFF_TIMER_30_MINUTES : {
            tmp = CHARGER6_TOPOFF_TIMER_VAL_30_MINUTES;
            break;
        }
        case CHARGER6_TOPOFF_TIMER_45_MINUTES : {
            tmp = CHARGER6_TOPOFF_TIMER_VAL_45_MINUTES;
            break;
        }
        default : {
            tmp = CHARGER6_TOPOFF_TIMER_DISABLE;
            break;
        }
    }
    
    tmp <<= 1;
    rx_tx_buf[ 0 ] &= CHARGER6_TOPOFF_TIMER_BIT_MASK;
    rx_tx_buf[ 0 ] |= tmp;
    st_flag |= charger6_generic_write( ctx, CHARGER6_REGISTER_04, rx_tx_buf, 1 );
    
    return st_flag;
}

uint8_t charger6_check_interrupt ( charger6_t *ctx ) {
    return digital_in_read( &ctx->int_pin ); 
}

void charger6_hw_reset ( charger6_t *ctx ) {
    digital_out_low( &ctx->qon );
    dev_hw_lh_reset_delay( );
    digital_out_high( &ctx->qon );
    dev_reset_delay( );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_hw_lh_reset_delay ( void ) {
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
}

static void dev_reset_delay ( void ) {
    Delay_100ms( );
    Delay_100ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
}

static void dev_config_delay ( void ) {
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END
