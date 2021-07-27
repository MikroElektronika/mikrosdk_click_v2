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
 * @file loadcell3.c
 * @brief Load Cell 3 Click Driver.
 */

#include "loadcell3.h"

#define LOADCELL3_SOFT_RESET                     0x02
#define LOADCELL3_P_GAIN_BIT_MASK                0xF8
#define LOADCELL3_T_GAIN_BIT_MASK                0xF8
#define LOADCELL3_TEMP_MODE_BIT_MASK             0xF7
#define LOADCELL3_T_MUX_CTRL_BIT_MASK            0x8F
#define LOADCELL3_ITEMP_CTRL_BIT_MASK            0x8F
#define LOADCELL3_OFFSET_BIT_MASK                0x1F

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Configuration delay.
 * @details Configuration delay for 100 milliseconds.
 */
static void dev_cfg_delay ( void );

/**
 * @brief Measurement delay.
 * @details Measurement delay for 10 milliseconds.
 */
static void dev_measure_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void loadcell3_cfg_setup ( loadcell3_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->an   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LOADCELL3_SET_DEV_ADDR;
}

err_t loadcell3_init ( loadcell3_t *ctx, loadcell3_cfg_t *cfg ) {
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

    digital_in_init( &ctx->an, cfg->an );

    return I2C_MASTER_SUCCESS;
}

err_t loadcell3_default_cfg ( loadcell3_t *ctx ) {
    loadcell3_soft_reset( ctx );
    dev_cfg_delay( );
    
    loadcell3_accesses_digital_interface_control( ctx );
    dev_cfg_delay( );
    
    loadcell3_set_p_gain( ctx, LOADCELL3_SET_GAIN_200 );
    dev_cfg_delay( );
    
    loadcell3_set_t_gain( ctx, LOADCELL3_SET_GAIN_200 );
    dev_cfg_delay( );
    
    loadcell3_set_temp_mode( ctx, LOADCELL3_SET_TSEM_MODE_DIFFERENTIAL );
    dev_cfg_delay( );
    
    loadcell3_set_t_mux_ctrl( ctx, LOADCELL3_SET_T_MUX_CTRL_INT_TEMPE );
    dev_cfg_delay( );
    
    return LOADCELL3_OK;
}

err_t loadcell3_generic_write ( loadcell3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t loadcell3_generic_read ( loadcell3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t loadcell3_generic_eeprom_write ( loadcell3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }
    
    loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_EEPROM_CACHE_CELLS );

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t loadcell3_generic_eeprom_read ( loadcell3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_EEPROM_CACHE_CELLS ); 
        
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t loadcell3_generic_test_page_write ( loadcell3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }
    
    loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_TEST_REG );

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t loadcell3_generic_test_page_read ( loadcell3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_TEST_REG ); 
        
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t loadcell3_set_memory_page_slave_addr ( loadcell3_t *ctx, uint8_t memory_page ) {
    err_t err_flag;
        
    if ( ( memory_page == LOADCELL3_SET_MEMORY_PAGE_TEST_REG ) || ( memory_page == LOADCELL3_SET_MEMORY_PAGE_CONTROL_AND_STATUS_REG ) ||
         ( memory_page == LOADCELL3_SET_MEMORY_PAGE_EEPROM_CACHE_CELLS ) || ( memory_page == LOADCELL3_SET_MEMORY_PAGE_CTRL_AND_STATUS_REG ) ) {
        ctx->slave_address = memory_page;
        err_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );     
    } else {
        err_flag = LOADCELL3_ERROR;
    }
    
    return err_flag;
}

err_t loadcell3_accesses_controller ( loadcell3_t *ctx ) {
    uint8_t tx_buf[ 1 ];
    
    loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_TEST_REG );
   
    tx_buf[ 0 ] = LOADCELL3_SET_IF_SEL_ACCESSES_CONTROLLER;
    loadcell3_generic_write( ctx, LOADCELL3_REG_TEST_MICRO_INTERFACE_CONTROL, tx_buf, 1 );
    
    return LOADCELL3_OK;
}

err_t loadcell3_accesses_digital_interface_control ( loadcell3_t *ctx ) {
    uint8_t tx_buf[ 1 ];
    
    loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_TEST_REG );
    
    tx_buf[ 0 ] = LOADCELL3_SET_IF_SEL_ACCESSES_DIGITAL_INTERFACE;
    loadcell3_generic_write( ctx, LOADCELL3_REG_TEST_MICRO_INTERFACE_CONTROL, tx_buf, 1 );
    
    return LOADCELL3_OK;
}

err_t loadcell3_soft_reset ( loadcell3_t *ctx ) {
    uint8_t tx_buf[ 1 ];
    
    loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_TEST_REG );
   
    tx_buf[ 0 ] = LOADCELL3_SOFT_RESET;
    loadcell3_generic_write( ctx, LOADCELL3_REG_TEST_MICRO_INTERFACE_CONTROL, tx_buf, 1 );
    
    return LOADCELL3_OK;
}

err_t loadcell3_set_p_gain ( loadcell3_t *ctx, uint8_t p_gain ) {
    uint8_t rx_buf;
    err_t err_flag;
    
    if ( p_gain < 8 ) {
        loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_CONTROL_AND_STATUS_REG );
   
        err_flag = loadcell3_generic_read( ctx, LOADCELL3_REG_CTRL_STATUS_P_GAIN_SELECT, &rx_buf, 1 );
        rx_buf &= LOADCELL3_P_GAIN_BIT_MASK;
        rx_buf |= p_gain;
        err_flag |= loadcell3_generic_write( ctx, LOADCELL3_REG_CTRL_STATUS_P_GAIN_SELECT, &rx_buf, 1 );    
    } else {
        err_flag = LOADCELL3_ERROR;    
    }
    
    return err_flag;
}

err_t loadcell3_set_t_gain ( loadcell3_t *ctx, uint8_t t_gain ) {
    uint8_t rx_buf;
    err_t err_flag;
    
    if ( t_gain < 8 ) {
        loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_CONTROL_AND_STATUS_REG );
   
        err_flag = loadcell3_generic_read( ctx, LOADCELL3_REG_CTRL_STATUS_T_GAIN_SELECT, &rx_buf, 1 );
        rx_buf &= LOADCELL3_T_GAIN_BIT_MASK;
        rx_buf |= t_gain;
        err_flag |= loadcell3_generic_write( ctx, LOADCELL3_REG_CTRL_STATUS_T_GAIN_SELECT, &rx_buf, 1 );    
    } else {
        err_flag = LOADCELL3_ERROR;    
    }
    
    return err_flag;
}

err_t loadcell3_set_temp_mode ( loadcell3_t *ctx, uint8_t t_mode ) {
    uint8_t rx_buf;
    err_t err_flag;
    
    if ( ( t_mode == LOADCELL3_SET_TSEM_MODE_SINGLE_ENDED ) || 
         ( t_mode == LOADCELL3_SET_TSEM_MODE_DIFFERENTIAL ) ) {
        loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_CONTROL_AND_STATUS_REG );
   
        err_flag = loadcell3_generic_read( ctx, LOADCELL3_REG_CTRL_STATUS_T_GAIN_SELECT, &rx_buf, 1 );
        rx_buf &= LOADCELL3_TEMP_MODE_BIT_MASK;
        t_mode <<= 3;
        rx_buf |= t_mode;
        err_flag |= loadcell3_generic_write( ctx, LOADCELL3_REG_CTRL_STATUS_T_GAIN_SELECT, &rx_buf, 1 );    
    } else {
        err_flag = LOADCELL3_ERROR;    
    }
    
    return err_flag;
}

err_t loadcell3_set_t_mux_ctrl ( loadcell3_t *ctx, uint8_t t_mux_ctrl ) {
    uint8_t rx_buf;
    err_t err_flag;
    
    if ( ( t_mux_ctrl == LOADCELL3_SET_T_MUX_CTRL_EXT_TEMPE )      || 
         ( t_mux_ctrl == LOADCELL3_SET_T_MUX_CTRL_TEST )           || 
         ( t_mux_ctrl == LOADCELL3_SET_T_MUX_CTRL_INT_TEMPE )      || 
         ( t_mux_ctrl == LOADCELL3_SET_T_MUX_CTRL_BRIDGE_CURRENT ) || 
         ( t_mux_ctrl == LOADCELL3_SET_T_MUX_CTRL_ITEMP ) ) {
        loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_CONTROL_AND_STATUS_REG );
   
        err_flag = loadcell3_generic_read( ctx, LOADCELL3_REG_CTRL_STATUS_T_GAIN_SELECT, &rx_buf, 1 );
        rx_buf &= LOADCELL3_T_MUX_CTRL_BIT_MASK;
        t_mux_ctrl <<= 4;
        rx_buf |= t_mux_ctrl;
        err_flag |= loadcell3_generic_write( ctx, LOADCELL3_REG_CTRL_STATUS_T_GAIN_SELECT, &rx_buf, 1 );    
    } else {
        err_flag = LOADCELL3_ERROR;    
    }
    
    return err_flag;
}

err_t loadcell3_itemp_ctrl ( loadcell3_t *ctx, uint8_t itemp_ctrl ) {
    uint8_t rx_buf;
    err_t err_flag;
    
    if ( itemp_ctrl < 5 ) {
        loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_CONTROL_AND_STATUS_REG );
   
        err_flag = loadcell3_generic_read( ctx, LOADCELL3_REG_CTRL_STATUS_TEMP_CTRL, &rx_buf, 1 );
        rx_buf &= LOADCELL3_ITEMP_CTRL_BIT_MASK;
        itemp_ctrl <<= 4;
        rx_buf |= itemp_ctrl;
        err_flag |= loadcell3_generic_write( ctx, LOADCELL3_REG_CTRL_STATUS_TEMP_CTRL, &rx_buf, 1 );    
    } else {
        err_flag = LOADCELL3_ERROR;    
    }
    
    return err_flag;
}

err_t loadcell3_set_offset ( loadcell3_t *ctx, uint8_t offset_cancel_val, uint8_t offset_cancel_sel ) {
    uint8_t rx_buf;
    err_t err_flag;
    
    if ( ( offset_cancel_val < 16 ) && ( offset_cancel_sel < 2 ) ) {
        loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_CONTROL_AND_STATUS_REG );
   
        err_flag = loadcell3_generic_read( ctx, LOADCELL3_REG_CTRL_STATUS_TEMP_CTRL, &rx_buf, 1 );
        rx_buf &= LOADCELL3_OFFSET_BIT_MASK;
        offset_cancel_sel <<= 4;
        rx_buf |= offset_cancel_sel;
        rx_buf |= offset_cancel_val;
        err_flag |= loadcell3_generic_write( ctx, LOADCELL3_REG_CTRL_STATUS_TEMP_CTRL, &rx_buf, 1 );    
    } else {
        err_flag = LOADCELL3_ERROR;    
    }
    
    return err_flag;
}

int16_t loadcell3_get_p_adc_data ( loadcell3_t *ctx ) {
    uint8_t lsb;
    uint8_t msb;
    int16_t result;
    
    loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_TEST_REG );
    
    loadcell3_generic_read( ctx, LOADCELL3_REG_TEST_PADC_DATA_1, &lsb, 1 );
    loadcell3_generic_read( ctx, LOADCELL3_REG_TEST_PADC_DATA_2, &msb, 1 );
    
    result = msb;
    result <<= 8;
    result |= lsb;
    
    return result;
}

int16_t loadcell3_get_t_adc_data ( loadcell3_t *ctx ) {
    uint8_t lsb;
    uint8_t msb;
    int16_t result;
    
    loadcell3_set_memory_page_slave_addr( ctx, LOADCELL3_SET_MEMORY_PAGE_TEST_REG );
    
    loadcell3_generic_read( ctx, LOADCELL3_REG_TEST_TADC_DATA_1, &lsb, 1 );
    loadcell3_generic_read( ctx, LOADCELL3_REG_TEST_TADC_DATA_2, &msb, 1 );
    
    result = msb;
    result <<= 8;
    result |= lsb;
    
    return result;
}

void loadcell3_tare ( loadcell3_t *ctx, loadcell3_data_t *cell_data ) {
    int16_t results;
    int8_t n_cnt;
    uint32_t sum_val;
    float average_val;

    sum_val = 0;

    for ( n_cnt = 0; n_cnt < 50; n_cnt++ ) {
        results = loadcell3_get_p_adc_data( ctx );
        sum_val += results;
        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= 50.0;

    cell_data->tare = average_val;
    cell_data->tare_ok = LOADCELL3_DATA_OK;
    cell_data->weight_data_100g_ok = LOADCELL3_DATA_NO_DATA;
    cell_data->weight_data_500g_ok = LOADCELL3_DATA_NO_DATA;
    cell_data->weight_data_1000g_ok = LOADCELL3_DATA_NO_DATA;
    cell_data->weight_data_5000g_ok = LOADCELL3_DATA_NO_DATA;
    cell_data->weight_data_10000g_ok = LOADCELL3_DATA_NO_DATA;
}

err_t loadcell3_calibration ( loadcell3_t *ctx, uint16_t cal_val, loadcell3_data_t *cell_data ) {
    uint32_t results;
    uint8_t n_cnt;
    uint32_t sum_val;
    float average_val;
    float tare_val;
    float weight_val;
    err_t err_flag;

    err_flag = LOADCELL3_OK;

    tare_val = cell_data->tare;

    sum_val = 0;

    for ( n_cnt = 0; n_cnt < 50; n_cnt++ ) {
        results = loadcell3_get_p_adc_data( ctx );
        sum_val += results;
        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= 50.0;

    weight_val = average_val - tare_val;

    switch ( cal_val ) {
        case LOADCELL3_WEIGHT_100G : {
            cell_data->weight_coeff_100g = 100.0 / weight_val;
            cell_data->weight_data_100g_ok = LOADCELL3_DATA_OK;
            break;
        }
        case LOADCELL3_WEIGHT_500G : {
            cell_data->weight_coeff_500g = 500.0 / weight_val;
            cell_data->weight_data_500g_ok = LOADCELL3_DATA_OK;
            break;
        }
        case LOADCELL3_WEIGHT_1000G : {
            cell_data->weight_coeff_1000g = 1000.0 / weight_val;
            cell_data->weight_data_1000g_ok = LOADCELL3_DATA_OK;
            break;
        }
        case LOADCELL3_WEIGHT_5000G : {
            cell_data->weight_coeff_5000g = 5000.0 / weight_val;
            cell_data->weight_data_5000g_ok = LOADCELL3_DATA_OK;
            break;
        }
        case LOADCELL3_WEIGHT_10000G : {
            cell_data->weight_coeff_10000g = 10000.0 / weight_val;
            cell_data->weight_data_10000g_ok = LOADCELL3_DATA_OK;
            break;
        }
        default : {
            err_flag = LOADCELL3_ERROR;
            cell_data->weight_data_100g_ok = LOADCELL3_DATA_NO_DATA;
            cell_data->weight_data_500g_ok = LOADCELL3_DATA_NO_DATA;
            cell_data->weight_data_1000g_ok = LOADCELL3_DATA_NO_DATA;
            cell_data->weight_data_5000g_ok = LOADCELL3_DATA_NO_DATA;
            cell_data->weight_data_10000g_ok = LOADCELL3_DATA_NO_DATA;
            break;
        }
    }

    return err_flag;
}

float loadcell3_get_weight ( loadcell3_t *ctx, loadcell3_data_t *cell_data ) {
    uint32_t results;
    uint8_t n_cnt;
    uint32_t sum_val;
    float average_val;
    float tare_val;
    float weight_val;
    uint8_t status;

    status = LOADCELL3_OK;

    tare_val = cell_data->tare;

    sum_val = 0;

    for ( n_cnt = 0; n_cnt < 50; n_cnt++ ) {
        results = loadcell3_get_p_adc_data( ctx );

        sum_val += results;

        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= 50.0;

    weight_val = average_val - tare_val;

    if ( cell_data->weight_data_100g_ok == LOADCELL3_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_100g;
    }
    else if ( cell_data->weight_data_500g_ok == LOADCELL3_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_500g;
    }
    else if ( cell_data->weight_data_1000g_ok == LOADCELL3_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_1000g;
    }
    else if ( cell_data->weight_data_5000g_ok == LOADCELL3_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_5000g;
    }
    else if ( cell_data->weight_data_10000g_ok == LOADCELL3_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_10000g;
    }

    if ( weight_val < 0 ) {
        weight_val = LOADCELL3_WEIGHT_ZERO;
    }

    return weight_val;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_cfg_delay ( void ) {
    Delay_100ms( );
}

static void dev_measure_delay ( void ) {
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END
