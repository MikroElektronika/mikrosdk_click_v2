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
** USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file irgrid3.c
 * @brief IR Grid 3 Click Driver.
 */

#include "irgrid3.h"
#include <math.h>

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void write_data_u16 ( irgrid3_t *ctx, uint16_t reg, uint16_t tx_data );
static uint16_t read_data_u16 ( irgrid3_t *ctx, uint16_t reg );
static void read_data_block ( irgrid3_t *ctx, uint16_t start_addr, uint16_t *data_out, uint16_t n_bytes );
static uint8_t check_eeprom_valid ( uint16_t *eeprom_data );
static int check_adjacent_pixels ( uint16_t pix1, uint16_t pix2 );
static void extract_vdd_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static void extract_ptat_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static void extract_gain_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static void extract_tgc_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static void extract_resolution_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static void extract_ks_ta_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static void extract_ks_to_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static void extract_alpha_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static void extract_offset_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static void extract_kta_pixel_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static void extract_kv_pixel_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static void extract_cp_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static void extract_cilc_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data );
static uint8_t extract_deviating_pixels ( irgrid3_t *ctx, uint16_t *eeprom_data );
static float gain_calculation ( irgrid3_t *ctx, uint16_t raw_gain );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void irgrid3_cfg_setup ( irgrid3_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = IRGRID3_SET_DEV_ADDR;
}

err_t irgrid3_init ( irgrid3_t *ctx, irgrid3_cfg_t *cfg ) {
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

    return I2C_MASTER_SUCCESS;
}

void irgrid3_default_cfg ( irgrid3_t *ctx ) {
    static uint16_t eeprom_data[ 832 ];

    // Click default configuration

    irgrid3_read_eeprom( ctx, eeprom_data );
    irgrid3_extract_parameters( ctx, eeprom_data );
    irgrid3_set_refresh_rate( ctx, 0x03 );
    Delay_100ms( );
}

void irgrid3_generic_write ( irgrid3_t *ctx, uint16_t reg, uint8_t *data_buf, uint16_t len )
{
    uint8_t tx_buf[ 1000 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg >> 8;
    tx_buf[ 1 ] = reg & 0x00FF;

    for ( cnt = 2; cnt <= len + 1; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 2 ];
    }

    i2c_master_write( &ctx->i2c, tx_buf, len + 2 );   
}

void irgrid3_generic_read ( irgrid3_t *ctx, uint16_t reg, uint8_t *rx_buf, uint16_t rx_len ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg >> 8;
    tx_buf[ 1 ] = reg & 0x00FF;
    
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, rx_len );
}

void irgrid3_read_eeprom ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    read_data_block( ctx, 0x2400, eeprom_data, 832 );
}

uint8_t irgrid3_extract_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    uint8_t error;

    error = check_eeprom_valid( eeprom_data );

    if ( error == 0 ) {
        extract_vdd_parameters( ctx, eeprom_data);
        extract_ptat_parameters( ctx, eeprom_data );
        extract_gain_parameters( ctx, eeprom_data );
        extract_tgc_parameters( ctx, eeprom_data );
        extract_resolution_parameters( ctx, eeprom_data );
        extract_ks_ta_parameters( ctx, eeprom_data );
        extract_ks_to_parameters( ctx, eeprom_data );
        extract_alpha_parameters( ctx, eeprom_data );
        extract_offset_parameters( ctx, eeprom_data );
        extract_kta_pixel_parameters( ctx, eeprom_data );
        extract_kv_pixel_parameters( ctx, eeprom_data );
        extract_cp_parameters( ctx, eeprom_data );
        extract_cilc_parameters( ctx, eeprom_data );
        error = extract_deviating_pixels( ctx, eeprom_data );
    }
    return error;
}

void irgrid3_set_refresh_rate( irgrid3_t *ctx, uint8_t refresh_rate ) {
    uint16_t ctrl_reg;
    int value;

    value = ( refresh_rate & 0x07 ) << 7;
    read_data_block( ctx, 0x800D, &ctrl_reg, 1 );
    value = ( ctrl_reg & 0xFC7F ) | value;
    write_data_u16 ( ctx, 0x800D, value);
}
uint16_t irgrid3_get_frame_data ( irgrid3_t *ctx, uint16_t *frame_data ) {
    uint16_t drdy = 1;
    uint16_t ctrl_reg;
    uint16_t status_reg;
    uint8_t cnt = 0;

    drdy = 0;

    while ( drdy == 0 ) {
        status_reg = read_data_u16( ctx, 0x8000 );
        drdy = status_reg & 0x0008;
    }

    while ( ( drdy != 0 ) && ( cnt < 5 ) ) {
        write_data_u16 ( ctx, 0x8000, 0x0030);
        read_data_block ( ctx, 0x0400, frame_data, 832 );
        status_reg = read_data_u16 ( ctx, 0x8000 );
        drdy = status_reg & 0x0008;
        cnt = cnt + 1;
    }

    ctrl_reg = read_data_u16( ctx, 0x800D );
    frame_data[ 832 ] = ctrl_reg;
    frame_data[ 833 ] = status_reg & 0x0001;

    return frame_data[ 833 ];
}
void irgrid3_set_resolution ( irgrid3_t *ctx, uint8_t resolution ) {
    uint16_t ctrl_reg;
    uint16_t value;

    value = ( resolution & 0x03 ) << 10;
    ctrl_reg = read_data_u16( ctx, 0x800D );
    value = ( ctrl_reg & 0xF3FF ) | value;
    write_data_u16( ctx, 0x800D, value );
}

uint16_t irgrid3_get_current_res ( irgrid3_t *ctx ) {
    uint16_t ctrl_reg;
    uint16_t resolution_ram;

    ctrl_reg = read_data_u16( ctx, 0x800D );
    resolution_ram = ( ctrl_reg & 0x0C00 ) >> 10;
    return resolution_ram;
}

uint16_t irgrid3_get_refresh_rate( irgrid3_t *ctx ) {
    uint16_t ctrl_reg;
    uint16_t refresh_rate;

    ctrl_reg = read_data_u16 ( ctx, 0x800D );
    refresh_rate = ( ctrl_reg & 0x0380 ) >> 7;

    return refresh_rate;
}

void irgrid3_set_interleaved_mode( irgrid3_t *ctx ) {
    uint16_t ctrl_reg;
    uint16_t value;

    ctrl_reg = read_data_u16( ctx, 0x800D );
    value = ( ctrl_reg & 0xEFFF );
    write_data_u16( ctx, 0x800D, value );
}

void irgrid3_set_chess_mode( irgrid3_t *ctx ) {
   uint16_t ctrl_reg;
   uint16_t value;

    ctrl_reg = read_data_u16( ctx, 0x800D );
    value = ( ctrl_reg | 0x1000 );
    write_data_u16( ctx, 0x800D, value );
}

uint16_t irgrid3_get_current_mode( irgrid3_t *ctx ) {
    uint16_t ctrl_reg;
    uint16_t mode_ram;

    ctrl_reg = read_data_u16( ctx, 0x800D );
    mode_ram = ( ctrl_reg & 0x1000 ) >> 12;
    return mode_ram;
}

void irgrid3_get_pixel_temperature ( irgrid3_t *ctx, float *temp_ambient, float *pixel_temp ) {
    uint16_t cnt;
    float raw_ta = 0;
    static uint16_t frame_data[ 834 ];

    for ( cnt = 0 ; cnt < 2 ; cnt++ ) {
        irgrid3_get_frame_data( ctx, frame_data );
        raw_ta = irgrid3_get_temp_ambient ( ctx, frame_data );
        irgrid3_calculate_temp_obj( ctx, frame_data, raw_ta, pixel_temp );
    }
    *temp_ambient = raw_ta;
}

float irgrid3_get_temp_ambient ( irgrid3_t *ctx, uint16_t *frame_data ) {
    uint16_t raw_ptat_art;
    uint16_t raw_ptat;
    float raw_vdd;
    float raw_ta;

    // VDD parameters

    raw_vdd = irgrid3_get_vdd( ctx, frame_data );

    // PTAT parameters

    raw_ptat = ( float )frame_data[ 800 ];
    if ( raw_ptat > 32767 ) {
        raw_ptat = raw_ptat - 65536;
    }

    // PTAT Art parameters

    raw_ptat_art = frame_data[ 768 ];
    if ( raw_ptat_art > 32767 ) {
        raw_ptat_art = raw_ptat_art - 65536;
    }
    raw_ptat_art = ( raw_ptat / ( raw_ptat * ctx->params.alpha_ptat + raw_ptat_art ) ) * pow( 2, 18 );

    // Temperature ambient

    raw_ta = ( float )( raw_ptat_art / ( 1 + ctx->params.kv_ptat * ( raw_vdd - 3.3 ) ) - ctx->params.v_ptat_25 );
    raw_ta = ( float )(raw_ta / ctx->params.kt_ptat + 25 );

    return raw_ta;
}

uint16_t irgrid3_get_subpage_number( uint16_t *frame_data ) {
    return frame_data[ 833 ];
}

float irgrid3_get_vdd ( irgrid3_t *ctx, uint16_t *frame_data ) {
    volatile float vdd;
    volatile float resolution_correction;
    uint16_t resolution_ram;

    vdd = frame_data[ 810 ];
    if ( vdd > 32767 ) {
        vdd = vdd - 65536;
    }

    resolution_ram = ( frame_data[ 832 ] & 0x0C00 ) >> 10;
    resolution_correction = pow( 2, ( double )ctx->params.resolution_eeprom ) / pow( 2, ( double )resolution_ram );

    vdd = ( resolution_correction * vdd - ctx->params.vdd_25 ) / ctx->params.k_vdd + 3.3;

    return vdd;
}

void irgrid3_calculate_temp_obj ( irgrid3_t *ctx, uint16_t *frame_data, float tr_data, float *px_matrix ) {
    float gain;
    uint16_t sub_page;
    float raw_vdd;
    float raw_ta;
    float raw_ta_4;
    float raw_tr_4;
    float raw_ta_tr;
    float alpha_corr_r[ 4 ];
    float ir_data_cp[ 2 ];
    float ir_data;
    float alpha_compensated;
    uint8_t mode;
    int8_t il_pattern;
    int8_t chess_pattern;
    int8_t pattern;
    int8_t conversion_pattern;
    float raw_sx;
    float raw_to;
    int8_t range;
    int i;
    int px_number;

    sub_page = frame_data[ 833 ];

    raw_vdd = irgrid3_get_vdd( ctx, frame_data );
    raw_ta = irgrid3_get_temp_ambient( ctx, frame_data );
    raw_ta_4 = pow( ( raw_ta + 273.15 ), ( double ) 4 );
    raw_tr_4 = pow( ( tr_data + 273.15 ), ( double ) 4 );
    raw_ta_tr = raw_tr_4 - ( raw_tr_4 - raw_ta_4 ) / 0.95;

    alpha_corr_r[ 0 ] = 1 / ( 1 + ctx->params.ks_to[ 0 ] * 40 );
    alpha_corr_r[ 1 ] = 1 ;
    alpha_corr_r[ 2 ] = ( 1 + ctx->params.ks_to[ 2 ] * ctx->params.ct[ 2 ] );
    alpha_corr_r[ 3 ] = alpha_corr_r[ 2 ] * ( 1 + ctx->params.ks_to[ 3 ] * ( ctx->params.ct[ 3 ] - ctx->params.ct[ 2 ] ) );

    // Gain calculation

    gain = gain_calculation( ctx, frame_data[ 778 ] );

    // Temperature object calculation

    mode = ( frame_data[ 832 ] & 0x1000 ) >> 5;

    ir_data_cp[ 0 ] = frame_data[ 776 ];
    ir_data_cp[ 1 ] = frame_data[ 808 ];

    for ( i = 0; i < 2; i++ ) {
        if ( ir_data_cp[ i ] > 32767 ) {
            ir_data_cp[ i ] = ir_data_cp[ i ] - 65536;
        }
        ir_data_cp[ i ] = ir_data_cp[ i ] * gain;
    }

    ir_data_cp[ 0 ] = ir_data_cp[ 0 ] - ctx->params.cp_offset[ 0 ] * ( 1 + ctx->params.cp_kta * ( raw_ta - 25 ) ) * ( 1 + ctx->params.cp_kv * ( raw_vdd - 3.3 ) );

    if ( mode == ctx->params.calibration_mode_eeprom ) {
        ir_data_cp[ 1 ] = ir_data_cp[ 1 ] - ctx->params.cp_offset[ 1 ] * ( 1 + ctx->params.cp_kta * ( raw_ta - 25 ) ) * ( 1 + ctx->params.cp_kv * ( raw_vdd - 3.3 ) );
    } else {
        ir_data_cp[ 1 ] = ir_data_cp[ 1 ] - ( ctx->params.cp_offset[ 1 ] + ctx->params.il_chess_c[ 0 ] ) * ( 1 + ctx->params.cp_kta * ( raw_ta - 25 ) ) * ( 1 + ctx->params.cp_kv * ( raw_vdd - 3.3 ) );
    }

    for ( px_number = 0; px_number < 768; px_number++ ) {
        il_pattern = px_number / 32 - ( px_number / 64 ) * 2;
        chess_pattern = il_pattern ^ ( px_number - ( px_number / 2 ) * 2 );
        conversion_pattern = ( ( px_number + 2 ) / 4 - ( px_number + 3 ) / 4 + ( px_number + 1 ) / 4 - px_number / 4 ) * ( 1 - 2 * il_pattern );

        if ( mode == 0 ) {
          pattern = il_pattern;
        } else {
          pattern = chess_pattern;
        }

        if ( pattern == frame_data[ 833 ] ) {
            ir_data = frame_data [ px_number ];
            if ( ir_data > 32767 ) {
                ir_data = ir_data - 65536;
            }
            ir_data = ir_data * gain;

            ir_data = ir_data - ctx->params.offset[ px_number ] * ( 1 + ctx->params.kta [ px_number ] * ( raw_ta - 25 ) ) * ( 1 + ctx->params.kv [ px_number ] * ( raw_vdd - 3.3 ) );
            if ( mode != ctx->params.calibration_mode_eeprom ) {
              ir_data = ir_data + ctx->params.il_chess_c[ 2 ] * ( 2 * il_pattern - 1 ) - ctx->params.il_chess_c[ 1 ] * conversion_pattern;
            }

            ir_data = ir_data / 0.95;

            ir_data = ir_data - ctx->params.tgc * ir_data_cp[ sub_page ];

            alpha_compensated = ( ctx->params.alpha[ px_number ] - ctx->params.tgc * ctx->params.cp_alpha[ sub_page ] ) * ( 1 + ctx->params.ks_ta * ( raw_ta - 25 ) );

            raw_sx = pow( alpha_compensated, 3 ) * ( ir_data + alpha_compensated * raw_ta_tr );
            raw_sx = pow( raw_sx, 0.25 ) * ctx->params.ks_to[ 1 ];

            raw_to = pow( ( ir_data / ( alpha_compensated * ( 1 - ctx->params.ks_to[ 1 ] * 273.15 ) + raw_sx ) + raw_ta_tr ), 0.25 ) - 273.15;

            if ( raw_to < ctx->params.ct[ 1 ] ) {
                range = 0;
            } else if ( raw_to < ctx->params.ct[ 2 ] ) {
                range = 1;
            } else if ( raw_to < ctx->params.ct[ 3 ] ) {
                range = 2;
            } else {
                range = 3;
            }

            raw_to = pow( ( ir_data / ( alpha_compensated * alpha_corr_r[ range ] * ( 1 + ctx->params.ks_to[ range ] * ( raw_to - ctx->params.ct[ range ] ) ) ) + raw_ta_tr ), 0.25 ) - 273.15;

            px_matrix[ px_number ] = raw_to;
        }
    }
}

void irgrid3_get_image ( irgrid3_t *ctx, uint16_t *frame_data, float *px_matrix ) {
    float raw_vdd;
    float raw_ta;
    float gain;
    float ir_data_cp[ 2 ];
    float ir_data;
    float alpha_compensated;
    uint8_t mode;
    int8_t il_pattern;
    int8_t chess_pattern;
    int8_t pattern;
    int8_t conversion_pattern;
    uint16_t sub_page;
    int i;
    int px_number;

    sub_page = frame_data[ 833 ];
    raw_vdd = irgrid3_get_vdd( ctx, frame_data );
    raw_ta = irgrid3_get_temp_ambient( ctx, frame_data );

    // Gain calculation

    gain = frame_data[ 778 ];
    if ( gain > 32767 ) {
        gain = gain - 65536;
    }

    gain = ctx->params.gain_eeprom / gain;

    // Image calculation

    mode = ( frame_data[ 832 ] & 0x1000 ) >> 5;

    ir_data_cp[ 0 ] = frame_data[ 776 ];
    ir_data_cp[ 1 ] = frame_data[ 808 ];

    for ( i = 0; i < 2; i++ ) {
        if ( ir_data_cp[ i ] > 32767 ) {
            ir_data_cp[ i ] = ir_data_cp[ i ] - 65536;
        }
        ir_data_cp[ i ] = ir_data_cp[ i ] * gain;
    }
    ir_data_cp[ 0 ] = ir_data_cp[ 0 ] - ctx->params.cp_offset[ 0 ] * ( 1 + ctx->params.cp_kta * ( raw_ta - 25)) * ( 1 + ctx->params.cp_kv * ( raw_vdd - 3.3 ) );

    if ( mode == ctx->params.calibration_mode_eeprom ) {
        ir_data_cp[ 1 ] = ir_data_cp[ 1 ] - ctx->params.cp_offset[ 1 ] * ( 1 + ctx->params.cp_kta * ( raw_ta - 25 ) ) * ( 1 + ctx->params.cp_kv * ( raw_vdd - 3.3 ) );
    } else {
      ir_data_cp[ 1 ] = ir_data_cp[ 1 ] - ( ctx->params.cp_offset[ 1 ] + ctx->params.il_chess_c[ 0 ] ) * ( 1 + ctx->params.cp_kta * ( raw_ta - 25 ) ) * ( 1 + ctx->params.cp_kv * ( raw_vdd - 3.3 ) );
    }

    for ( px_number = 0; px_number < 768; px_number++ ) {
        il_pattern = px_number / 32 - ( px_number / 64 ) * 2;
        chess_pattern = il_pattern ^ ( px_number - ( px_number / 2 ) * 2 );
        conversion_pattern = ( ( px_number + 2 ) / 4 - ( px_number + 3 ) / 4 + ( px_number + 1 ) / 4 - px_number / 4 ) * ( 1 - 2 * il_pattern );

        if ( mode == 0 ) {
            pattern = il_pattern;
        } else {
            pattern = chess_pattern;
        }

        if ( pattern == frame_data[ 833 ] ) {
            ir_data = frame_data[ px_number ];
            if ( ir_data > 32767 ) {
                ir_data = ir_data - 65536;
            }
            ir_data = ir_data * gain;

            ir_data = ir_data - ctx->params.offset[ px_number ] * ( 1 + ctx->params.kta[ px_number ] * ( raw_ta - 25 ) ) * ( 1 + ctx->params.kv[ px_number ] * ( raw_vdd - 3.3 ) );

            if ( mode != ctx->params.calibration_mode_eeprom ) {
                ir_data = ir_data + ctx->params.il_chess_c[ 2 ] * ( 2 * il_pattern - 1 ) - ctx->params.il_chess_c[ 1 ] * conversion_pattern;
            }

            ir_data = ir_data - ctx->params.tgc * ir_data_cp[ sub_page ];

            alpha_compensated = ( ctx->params.alpha[ px_number ] - ctx->params.tgc * ctx->params.cp_alpha[ sub_page ] ) * ( 1 + ctx->params.ks_ta * ( raw_ta - 25 ) );

            px_matrix[ px_number ] = ir_data / alpha_compensated;
        }
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void write_data_u16 ( irgrid3_t *ctx, uint16_t reg, uint16_t tx_data ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = (uint8_t)( tx_data >> 8 );
    tx_buf[ 1 ] = (uint8_t)( tx_data & 0x00FF );

    irgrid3_generic_write( ctx, reg, tx_buf, 2);
}

static uint16_t read_data_u16 ( irgrid3_t *ctx, uint16_t reg ) {
    uint8_t rx_buf[ 2 ];
    uint16_t rx_data = 0;

    irgrid3_generic_read( ctx, reg, rx_buf, 2 );

    rx_data = rx_buf[ 0 ];
    rx_data = rx_data << 8;
    rx_data = rx_data | rx_buf[ 1 ];

    return rx_data;
}

static void read_data_block ( irgrid3_t *ctx, uint16_t start_addr, uint16_t *data_out, uint16_t n_bytes ) {
    uint8_t rx_buf[ 1664 ] = {0};
    uint16_t cnt = 0;
    uint16_t n_mem_addr = 0;
    uint16_t i = 0;

    n_mem_addr = 2 * n_bytes;

    irgrid3_generic_read ( ctx, start_addr, rx_buf, n_mem_addr );

    for ( cnt = 0; cnt < n_bytes; cnt++ ) {
        i = cnt << 1;
        data_out[ cnt ] = rx_buf[ i ];
        data_out[ cnt ] <<= 8;
        data_out[ cnt ] |= rx_buf[ i + 1 ];
    }
}

static uint8_t check_eeprom_valid ( uint16_t *eeprom_data ) {
    uint8_t device_select;

    device_select = eeprom_data[ 10 ] & 0x0040;

    if ( device_select == 0 ) {
        return IRGRID3_EEPROM_OK;
    }
    return IRGRID3_EEPROM_ERROR;
}

static uint8_t check_adjacent_pixels ( uint16_t pix1, uint16_t pix2 ) {
    int pix_pos_dif;

    pix_pos_dif = pix1 - pix2;

    if ( ( pix_pos_dif > -34 ) && ( pix_pos_dif < -30 ) ) {
        return IRGRID3_ADJ_PIXELS_ERROR;
    }
    if ( ( pix_pos_dif > -2 ) && ( pix_pos_dif < 2 ) ) {
        return IRGRID3_ADJ_PIXELS_ERROR;
    }
    if ( ( pix_pos_dif > 30 ) && ( pix_pos_dif < 34 ) ) {
        return IRGRID3_ADJ_PIXELS_ERROR;
    }
    return IRGRID3_ADJ_PIXELS_OK;
}

static void extract_vdd_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    int16_t k_vdd;
    int16_t vdd_25;

    k_vdd = eeprom_data [ 51 ];
    k_vdd = ( eeprom_data[ 51 ] & 0xFF00 ) >> 8;

    if ( k_vdd > 127 ) {
        k_vdd = k_vdd - 256;
    }
    k_vdd = 32 * k_vdd;
    vdd_25 = eeprom_data [ 51 ] & 0x00FF;
    vdd_25 = ( ( vdd_25 - 256 ) << 5 ) - 8192;

    ctx->params.k_vdd = k_vdd;
    ctx->params.vdd_25 = vdd_25;
}

static void extract_ptat_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    float kv_ptat;
    float kt_ptat;
    int16_t v_ptat_25;
    float alpha_ptat;

    kv_ptat = ( eeprom_data[ 50 ] & 0xFC00 ) >> 10;

    if ( kv_ptat > 31 ) {
        kv_ptat = kv_ptat - 64;
    }
    kv_ptat = kv_ptat / 4096;

    kt_ptat = eeprom_data[ 50 ] & 0x03FF;

    if ( kt_ptat > 511 ) {
        kt_ptat = kt_ptat - 1024;
    }
    kt_ptat = kt_ptat / 8;

    v_ptat_25 = eeprom_data[ 49 ];

    alpha_ptat = (eeprom_data[16] & 0xF000) / pow(2, ( double )14) + 8.0f;

    ctx->params.kv_ptat = kv_ptat;
    ctx->params.kt_ptat = kt_ptat;
    ctx->params.v_ptat_25 = v_ptat_25;
    ctx->params.alpha_ptat = alpha_ptat;
}

static void extract_gain_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    int16_t gain_eeprom;

    gain_eeprom = eeprom_data [ 48 ];

    if ( gain_eeprom > 32767 ) {
        gain_eeprom = gain_eeprom - 65536;
    }

    ctx->params.gain_eeprom = gain_eeprom;
}

static void extract_tgc_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    float tgc;

    tgc = eeprom_data[ 60 ] & 0x00FF;

    if ( tgc > 127 ) {
        tgc = tgc - 256;
    }
    tgc = tgc / 32.0;

    ctx->params.tgc = tgc;
}

static void extract_resolution_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    uint8_t resolution_eeprom;

    resolution_eeprom = ( eeprom_data[ 56 ] & 0x3000 ) >> 12;

    ctx->params.resolution_eeprom = resolution_eeprom;
}

static void extract_ks_ta_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    float ks_ta;

    ks_ta = ( eeprom_data[ 60 ] & 0xFF00 ) >> 8;

    if ( ks_ta > 127 ) {
        ks_ta = ks_ta - 256;
    }
    ks_ta = ks_ta / 8192.0;

    ctx->params.ks_ta = ks_ta;
}

static void extract_ks_to_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    volatile int ks_to_scale;
    int8_t step;
    uint8_t cnt;

    step = ( ( eeprom_data[ 63 ] & 0x3000 ) >> 12 ) * 10;

    ctx->params.ct[ 0 ] = -40;
    ctx->params.ct[ 1 ] = 0;
    ctx->params.ct[ 2 ] = ( eeprom_data[ 63 ] & 0x00F0 ) >> 4;
    ctx->params.ct[ 3 ] = ( eeprom_data[ 63 ] & 0x0F00 ) >> 8;

    ctx->params.ct[ 2 ] = ctx->params.ct[ 2 ] * step;
    ctx->params.ct[ 3 ] = ctx->params.ct[ 2 ] + ctx->params.ct[ 3 ] * step;

    ks_to_scale = 15;
    ks_to_scale = 1 << ks_to_scale;

    ctx->params.ks_to[ 0 ] = eeprom_data[ 61 ] & 0x00FF;
    ctx->params.ks_to[ 1 ] = ( eeprom_data[ 61 ] & 0xFF00 ) >> 8;
    ctx->params.ks_to[ 2 ] = eeprom_data[ 62 ] & 0x00FF;
    ctx->params.ks_to[ 3 ] = ( eeprom_data[ 62 ] & 0xFF00 ) >> 8;


    for ( cnt = 0; cnt < 4; cnt++ ) {
        if ( ctx->params.ks_to[ cnt ] > 127 ) {
            ctx->params.ks_to[ cnt ] = ctx->params.ks_to[ cnt ] - 256;
        }
        ctx->params.ks_to[ cnt ] = ctx->params.ks_to[ cnt ] / ks_to_scale;
    }
}

static void extract_alpha_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    int acc_row [ 24 ];
    int acc_column[ 32 ];
    int p = 0;
    int alpha_ref;
    uint8_t alpha_scale;
    uint8_t acc_row_scale;
    uint8_t acc_column_scale;
    uint8_t acc_rem_scale;

    int i;
    int j;

    acc_rem_scale = eeprom_data[ 32 ] & 0x000F;
    acc_column_scale = ( eeprom_data[ 32 ] & 0x00F0 ) >> 4;
    acc_row_scale = ( eeprom_data[ 32 ] & 0x0F00 ) >> 8;
    alpha_scale = ( ( eeprom_data[ 32 ] & 0xF000 ) >> 12 ) + 30;
    alpha_ref = eeprom_data[ 33 ];

    for ( i = 0; i < 6; i++ ) {
        p = i * 4;
        acc_row[ p ] = ( eeprom_data[ 34 + i ] & 0x000F );
        acc_row[ p + 1 ] = ( eeprom_data[ 34 + i ] & 0x00F0 ) >> 4;
        acc_row[ p + 2 ] = ( eeprom_data[ 34 + i ] & 0x0F00 ) >> 8;
        acc_row[ p + 3 ] = ( eeprom_data[ 34 + i ] & 0xF000 ) >> 12;
    }

    for ( i = 0; i < 24; i++ ) {
        if ( acc_row[ i ] > 7 ) {
            acc_row[ i ] = acc_row[ i ] - 16;
        }
    }

    for ( i = 0; i < 8; i++ ) {
        p = i * 4;
        acc_column[ p ] = ( eeprom_data[ 40 + i ] & 0x000F );
        acc_column[ p + 1 ] = ( eeprom_data[ 40 + i ] & 0x00F0 ) >> 4;
        acc_column[ p + 2 ] = ( eeprom_data[ 40 + i ] & 0x0F00 ) >> 8;
        acc_column[ p + 3 ] = ( eeprom_data[ 40 + i ] & 0xF000 ) >> 12;
    }

    for ( i = 0; i < 32; i++ ) {
        if ( acc_column[ i ] > 7 ) {
            acc_column[ i ] = acc_column[ i ] - 16;
        }
    }

    for ( i = 0; i < 24; i++ ) {
        for ( j = 0; j < 32; j++ ) {
            p = 32 * i + j;

            ctx->params.alpha[ p ] = ( eeprom_data[ 64 + p ] & 0x03F0 ) >> 4;
            if ( ctx->params.alpha[ p ] > 31 ) {
                ctx->params.alpha[ p ] = ctx->params.alpha[ p ] - 64;
            }
            ctx->params.alpha[ p ] = ctx->params.alpha[ p ] * ( 1 << acc_rem_scale );
            ctx->params.alpha[ p ] = ( alpha_ref + ( acc_row[ i ] << acc_row_scale ) + ( acc_column[ j ] << acc_column_scale ) + ctx->params.alpha[ p ] );
            ctx->params.alpha[ p ] = ctx->params.alpha[ p ] / pow( 2, ( double )alpha_scale );
        }
    }
}

static void extract_offset_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    int occ_row[ 24 ];
    int occ_column[ 32 ];
    int p = 0;
    int16_t offset_ref;
    uint8_t occ_row_scale;
    uint8_t occ_column_scale;
    uint8_t occ_rem_scale;
    int i;
    int j;


    occ_rem_scale = ( eeprom_data[ 16 ] & 0x000F );
    occ_column_scale = ( eeprom_data[ 16 ] & 0x00F0 ) >> 4;
    occ_row_scale = ( eeprom_data[ 16 ] & 0x0F00 ) >> 8;
    offset_ref = eeprom_data[ 17 ];
    if ( offset_ref > 32767 ) {
        offset_ref = offset_ref - 65536;
    }

    for ( i = 0; i < 6; i++ ) {
        p = i * 4;
        occ_row[ p ] = ( eeprom_data[ 18 + i ] & 0x000F );
        occ_row[ p + 1 ] = ( eeprom_data[ 18 + i ] & 0x00F0 ) >> 4;
        occ_row[ p + 2 ] = ( eeprom_data[ 18 + i ] & 0x0F00 ) >> 8;
        occ_row[ p + 3 ] = ( eeprom_data[ 18 + i ] & 0xF000 ) >> 12;
    }

    for ( i = 0; i < 24; i++ ) {
        if ( occ_row[ i ] > 7 ) {
            occ_row[ i ] = occ_row[ i ] - 16;
        }
    }

    for ( i = 0; i < 8; i++) {
        p = i * 4;
        occ_column[ p ] = ( eeprom_data[ 24 + i ] & 0x000F );
        occ_column[ p + 1 ] = ( eeprom_data[ 24 + i ] & 0x00F0 ) >> 4;
        occ_column[ p + 2 ] = ( eeprom_data[ 24 + i ] & 0x0F00 ) >> 8;
        occ_column[ p + 3 ] = ( eeprom_data[ 24 + i ] & 0xF000 ) >> 12;
    }

    for ( i = 0; i < 32; i++ ) {
        if (occ_column[ i ] > 7) {
            occ_column[ i ] = occ_column[ i ] - 16;
        }
    }

    for ( i = 0; i < 24; i++) {
        for ( j = 0; j < 32; j ++) {
            p = 32 * i + j;
            ctx->params.offset[ p ] = ( eeprom_data[ 64 + p ] & 0xFC00 ) >> 10;

            if ( ctx->params.offset[ p ] > 31 ) {
                ctx->params.offset[ p ] = ctx->params.offset[ p ] - 64;
            }
            ctx->params.offset[ p ] = ctx->params.offset[ p ] * ( 1 << occ_rem_scale );
            ctx->params.offset[ p ] = ( offset_ref + ( occ_row [ i ] << occ_row_scale ) + ( occ_column[ j ] << occ_column_scale ) + ctx->params.offset[ p ] );
        }
    }
}

static void extract_kta_pixel_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    int p = 0;
    int8_t kta_rc[ 4 ];
    int8_t kta_ro_co;
    int8_t kta_ro_ce;
    int8_t kta_re_co;
    int8_t kta_re_ce;
    uint8_t kta_scale_1;
    uint8_t kta_scale_2;
    uint8_t split;

    int i;
    int j;

    kta_ro_co = ( eeprom_data[ 54 ] & 0xFF00 ) >> 8;
    if ( kta_ro_co > 127 ) {
        kta_ro_co = kta_ro_co - 256;
    }
    kta_rc[ 0 ] = kta_ro_co;

    kta_re_co = ( eeprom_data[ 54 ] & 0x00FF );
    if ( kta_re_co > 127 ) {
        kta_re_co = kta_re_co - 256;
    }
    kta_rc[ 2 ] = kta_re_co;

    kta_ro_ce = ( eeprom_data[ 55 ] & 0xFF00 ) >> 8;
    if ( kta_ro_ce > 127 ) {
        kta_ro_ce = kta_ro_ce - 256;
    }
    kta_rc[ 1 ] = kta_ro_ce;

    kta_re_ce = ( eeprom_data[ 55 ] & 0x00FF );
    if ( kta_re_ce > 127 ) {
        kta_re_ce = kta_re_ce - 256;
    }
    kta_rc[ 3 ] = kta_re_ce;

    kta_scale_1 = ( ( eeprom_data[ 56 ] & 0x00F0 ) >> 4 ) + 8;
    kta_scale_2 = ( eeprom_data[ 56 ] & 0x000F );

    for ( i = 0; i < 24; i++ ) {
        for ( j = 0; j < 32; j++ ) {
            p = 32 * i + j;
            split = 2 * ( ( p / 32 ) - ( p / 64 ) * 2 ) + ( p % 2 );
            ctx->params.kta[ p ] = ( eeprom_data[ 64 + p ] & 0x000E ) >> 1;
            if ( ctx->params.kta[ p ] > 3 ) {
                ctx->params.kta[ p ] = ctx->params.kta[ p ] - 8;
            }
            ctx->params.kta[ p ] = ctx->params.kta[ p ] * ( 1 << kta_scale_2 );
            ctx->params.kta[ p ] = kta_rc[ split ] + ctx->params.kta[ p ];
            ctx->params.kta[ p ] = ctx->params.kta[ p ] / pow( 2, ( double )kta_scale_1 );
        }
    }
}

static void extract_kv_pixel_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    int p = 0;
    int8_t kv_t[4];
    int8_t kv_ro_co;
    int8_t kv_ro_ce;
    int8_t kv_re_co;
    int8_t kv_re_ce;
    uint8_t kv_scale;
    uint8_t split;

    int i;
    int j;

    kv_ro_co = ( eeprom_data[ 52 ] & 0xF000 ) >> 12;
    if ( kv_ro_co > 7 ) {
        kv_ro_co = kv_ro_co - 16;
    }
    kv_t[ 0 ] = kv_ro_co;

    kv_re_co = ( eeprom_data[ 52 ] & 0x0F00 ) >> 8;
    if ( kv_re_co > 7 ) {
        kv_re_co = kv_re_co - 16;
    }
    kv_t[ 2 ] = kv_re_co;

    kv_ro_ce = ( eeprom_data[ 52 ] & 0x00F0 ) >> 4;
    if ( kv_ro_ce > 7 ) {
        kv_ro_ce = kv_ro_ce - 16;
    }
    kv_t[ 1 ] = kv_ro_ce;

    kv_re_ce = ( eeprom_data[ 52 ] & 0x000F );
    if ( kv_re_ce > 7 ) {
        kv_re_ce = kv_re_ce - 16;
    }
    kv_t[ 3 ] = kv_re_ce;

    kv_scale = ( eeprom_data[ 56 ] & 0x0F00 ) >> 8;


    for ( i = 0; i < 24; i++ ) {
        for ( j = 0; j < 32; j++ ) {
            p = 32 * i + j;
            split = 2 * ( ( p / 32 ) - ( p / 64 ) * 2 ) + ( p % 2 );
            ctx->params.kv[ p ] = kv_t[ split ];
            ctx->params.kv[ p ] = ctx->params.kv[ p ] / pow(2, ( double )kv_scale);
        }
    }
}

static void extract_cp_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    float alpha_sp[ 2 ];
    int16_t offset_sp[ 2 ];
    float cp_kv;
    float cp_kta;
    uint8_t alpha_scale;
    uint8_t kta_scale_1;
    uint8_t kv_scale;

    alpha_scale = ( ( eeprom_data[ 32 ] & 0xF000 ) >> 12 ) + 27;

    offset_sp[ 0 ] = ( eeprom_data[ 58 ] & 0x03FF );
    if ( offset_sp[ 0 ] > 511 ) {
        offset_sp[ 0 ] = offset_sp[ 0 ] - 1024;
    }

    offset_sp[ 1 ] = ( eeprom_data[ 58 ] & 0xFC00 ) >> 10;
    if ( offset_sp[ 1 ] > 31 ) {
        offset_sp[ 1 ] = offset_sp[ 1 ] - 64;
    }
    offset_sp[ 1 ] = offset_sp[ 1 ] + offset_sp[ 0 ];

    alpha_sp[ 0 ] = ( eeprom_data[ 57 ] & 0x03FF);
    if ( alpha_sp[ 0 ] > 511 ) {
        alpha_sp[ 0 ] = alpha_sp[ 0 ] - 1024;
    }
    alpha_sp[ 0 ] = alpha_sp[ 0 ] / pow( 2, ( double )alpha_scale );

    alpha_sp[ 1 ] = ( eeprom_data[ 57 ] & 0xFC00 ) >> 10;
    if ( alpha_sp[ 1 ] > 31 ) {
        alpha_sp[ 1 ] = alpha_sp[ 1 ] - 64;
    }
    alpha_sp[ 1 ] = ( 1 + alpha_sp[ 1 ] / 128 ) * alpha_sp[ 0 ];

    cp_kta = ( eeprom_data[ 59 ] & 0x00FF );
    if ( cp_kta > 127 ) {
        cp_kta = cp_kta - 256;
    }
    kta_scale_1 = ( ( eeprom_data[ 56 ] & 0x00F0 ) >> 4 ) + 8;
    ctx->params.cp_kta = cp_kta / pow( 2, ( double )kta_scale_1 );

    cp_kv = ( eeprom_data[ 59 ] & 0xFF00 ) >> 8;
    if ( cp_kv > 127 ) {
        cp_kv = cp_kv - 256;
    }
    kv_scale = ( eeprom_data[ 56 ] & 0x0F00 ) >> 8;
    ctx->params.cp_kv = cp_kv / pow( 2, ( double )kv_scale );

    ctx->params.cp_alpha [ 0 ] = alpha_sp[ 0 ];
    ctx->params.cp_alpha [ 1 ] = alpha_sp[ 1 ];
    ctx->params.cp_offset[ 0 ] = offset_sp[ 0 ];
    ctx->params.cp_offset[ 1 ] = offset_sp[ 1 ];
}

static void extract_cilc_parameters ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    float il_chess_c[ 3 ];
    uint8_t calibration_mode_eeprom;

    calibration_mode_eeprom = ( eeprom_data[ 10 ] & 0x0800 ) >> 4;
    calibration_mode_eeprom = calibration_mode_eeprom ^ 0x80;

    il_chess_c[ 0 ] = ( eeprom_data[ 53 ] & 0x003F );
    if ( il_chess_c[ 0 ] > 31 ) {
        il_chess_c[ 0 ] = il_chess_c[ 0 ] - 64;
    }
    il_chess_c[ 0 ] = il_chess_c[ 0 ] / 16.0;

    il_chess_c[ 1 ] = ( eeprom_data[ 53 ] & 0x07C0 ) >> 6;
    if ( il_chess_c[ 1 ] > 15 ) {
        il_chess_c[ 1 ] = il_chess_c[ 1 ] - 32;
    }
    il_chess_c[ 1 ] = il_chess_c[ 1 ] / 2.0;

    il_chess_c[ 2 ] = ( eeprom_data[ 53 ] & 0xF800 ) >> 11;
    if ( il_chess_c[ 2 ] > 15 ) {
        il_chess_c[ 2 ] = il_chess_c[ 2 ] - 32;
    }
    il_chess_c[ 2 ] = il_chess_c[ 2 ] / 8.0;

    ctx->params.calibration_mode_eeprom = calibration_mode_eeprom;
    ctx->params.il_chess_c[ 0 ] = il_chess_c[ 0 ];
    ctx->params.il_chess_c[ 1 ] = il_chess_c[ 1 ];
    ctx->params.il_chess_c[ 2 ] = il_chess_c[ 2 ];
}

static uint8_t extract_deviating_pixels ( irgrid3_t *ctx, uint16_t *eeprom_data ) {
    uint16_t pix_cnt = 0;
    uint16_t broken_pix_cnt = 0;
    uint16_t outlier_pix_cnt = 0;
    uint8_t err = 0;
    int i;

    for ( pix_cnt = 0; pix_cnt < 5; pix_cnt++ ) {
        ctx->params.broken_pixels[ pix_cnt ] = 0xFFFF;
        ctx->params.outlier_pixels[ pix_cnt ] = 0xFFFF;
    }

    pix_cnt = 0;
    while ( ( pix_cnt < 768 ) && ( broken_pix_cnt < 5 ) && ( outlier_pix_cnt < 5 ) ) {
        if ( eeprom_data[ pix_cnt + 64 ] == 0 ) {
            ctx->params.broken_pixels[ broken_pix_cnt ] = pix_cnt;
            broken_pix_cnt = broken_pix_cnt + 1;
        } else if ( ( eeprom_data[ pix_cnt + 64 ] & 0x0001 ) != 0 ) {
            ctx->params.outlier_pixels[ outlier_pix_cnt ] = pix_cnt;
            outlier_pix_cnt = outlier_pix_cnt + 1;
        }
        pix_cnt = pix_cnt + 1;
    }

    if ( broken_pix_cnt > 4 ) {
        err = IRGRID3_BROKEN_PIX_ERROR;
    } else if ( outlier_pix_cnt > 4 ) {
        err = IRGRID3_OUTLIER_PIX_ERROR;
        
    } else if ( ( broken_pix_cnt + outlier_pix_cnt ) > 4 ) {
        err = IRGRID3_2_PIX_ERROR;
    } else {
        for ( pix_cnt = 0; pix_cnt < broken_pix_cnt; pix_cnt++ ) {
            for ( i = pix_cnt + 1; i < broken_pix_cnt; i++ ) {
                err = check_adjacent_pixels( ctx->params.broken_pixels[ pix_cnt ], ctx->params.broken_pixels[ i ] );
                if ( err != 0 ) {
                    return err;
                }
            }
        }

        for ( pix_cnt = 0; pix_cnt < outlier_pix_cnt; pix_cnt++ ) {
            for ( i = pix_cnt + 1; i < outlier_pix_cnt; i++ ) {
                err = check_adjacent_pixels ( ctx->params.outlier_pixels[ pix_cnt ], ctx->params.outlier_pixels[ i ] );
                if ( err != 0 ) {
                    return err;
                }
            }
        }

        for ( pix_cnt = 0; pix_cnt < broken_pix_cnt; pix_cnt++ ) {
            for ( i = 0; i < outlier_pix_cnt; i++ ) {
                err = check_adjacent_pixels( ctx->params.broken_pixels[ pix_cnt ], ctx->params.outlier_pixels[ i ] );
                if ( err != 0 ) {
                    return err;
                }
            }
        }
    }

    return err;
}

static float gain_calculation ( irgrid3_t *ctx, uint16_t raw_gain ) {
    float gain;

    // Gain calculation

    gain = raw_gain;
    if ( gain > 32767 ) {
        gain = gain - 65536;
    }

    return ctx->params.gain_eeprom / gain;
}


// ------------------------------------------------------------------------- END
