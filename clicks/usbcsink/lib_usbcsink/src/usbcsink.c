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
 * @file usbcsink.c
 * @brief USB-C Sink Click Driver.
 */

#include "usbcsink.h"

static uint8_t sector[ 5 ][ 8 ] = {
{ 0x00, 0x00, 0xB0, 0xAA, 0x00, 0x45, 0x00, 0x00 },
{ 0x10, 0x40, 0x9C, 0x1C, 0xFF, 0x01, 0x3C, 0xDF },
{ 0x02, 0x40, 0x0F, 0x00, 0x32, 0x00, 0xFC, 0xF1 },
{ 0x00, 0x19, 0x56, 0xAF, 0xF5, 0x35, 0x5F, 0x00 },
{ 0x00, 0x3C, 0x90, 0x21, 0x43, 0x00, 0x40, 0xFB }};

static uint8_t rd_sec = 0;

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Device reset delay function.
**/
static void dev_device_reset_delay ( void );

/**
 * @brief Enable write delay function.
**/
static void dev_enable_wr_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void usbcsink_cfg_setup ( usbcsink_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->po3   = HAL_PIN_NC;
    cfg->po2   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = USBCSINK_SLAVE_ADR_0;
}

err_t usbcsink_init ( usbcsink_t *ctx, usbcsink_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->po2, cfg->po2 );
    digital_in_init( &ctx->po3, cfg->po3 );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t usbcsink_generic_write ( usbcsink_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t usbcsink_generic_read ( usbcsink_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void usbcsink_hw_reset ( usbcsink_t *ctx ) {
    digital_out_low( &ctx->rst );
    dev_device_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_device_reset_delay( );
    digital_out_low( &ctx->rst );
}

uint8_t usbcsink_get_pdo2 ( usbcsink_t *ctx ) {
    return digital_in_read( &ctx->po2 );
}

uint8_t usbcsink_get_pdo3 ( usbcsink_t *ctx ) {
    return digital_in_read( &ctx->po3 );
}

uint8_t usbcsink_get_interrupt ( usbcsink_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}


void usbcsink_write_byte ( usbcsink_t *ctx, uint8_t reg, uint8_t tx_data ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data;

    i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

uint8_t usbcsink_read_byte ( usbcsink_t *ctx, uint8_t reg ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];

    tx_buf[ 0 ] = reg;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 1 );
    
    return rx_buf[ 0 ];
}

uint8_t usbcsink_dev_chk ( usbcsink_t *ctx ) {
    rd_sec = 0;

    if( rd_sec == 0 ) {
        usbcsink_load_data( ctx );
        rd_sec = 1;
    }
    return 1;
}

err_t usbcsink_cust_wr_sec ( usbcsink_t *ctx, uint8_t sec_num,  uint8_t *sec_data ) {
    uint8_t buf[ 8 ];
    uint8_t n_cnt;

    for ( n_cnt = 0; n_cnt < 8; n_cnt++ ) {
        buf[ n_cnt ] = sec_data[ n_cnt ];
    }

    if (  usbcsink_generic_write( ctx, USBCSINK_REG_RW_BUF, buf, 8 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    buf[ 0 ] = USBCSINK_FTP_CUST_PWR | USBCSINK_FTP_CUST_RST_N;
    if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    buf[ 0 ] = ( USBCSINK_WRITE_PL & USBCSINK_FTP_CUST_OPCODE );
    if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_1, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    buf[ 0 ] = USBCSINK_FTP_CUST_PWR   |
               USBCSINK_FTP_CUST_RST_N |
               USBCSINK_FTP_CUST_REQ;
    if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 ) != USBCSINK_OK )
    {
        return USBCSINK_ERROR;
    }

    do {
        usbcsink_generic_read( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 );
    } while( buf[ 0 ] & USBCSINK_FTP_CUST_REQ );

    buf[ 0 ] = ( USBCSINK_PROG_SEC & USBCSINK_FTP_CUST_OPCODE );
    if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_1, buf, 1 ) != USBCSINK_OK )
    {
        return USBCSINK_ERROR;
    }

    buf[ 0 ] = ( sec_num & USBCSINK_FTP_CUST_SECT ) |
                           USBCSINK_FTP_CUST_PWR    |
                           USBCSINK_FTP_CUST_RST_N  |
                           USBCSINK_FTP_CUST_REQ;
    if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    do {
        usbcsink_generic_read( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 );
    } while( buf[ 0 ] & USBCSINK_FTP_CUST_REQ );

    return USBCSINK_OK;
}

err_t usbcsink_cust_ent_wr_mode ( usbcsink_t *ctx, uint8_t er_sec ) {
    uint8_t buf[ 2 ];

    buf[ 0 ] = USBCSINK_FTP_CUST_PWD;
    if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CUST_PWD_REG, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    buf[ 0 ] = 0;
    if ( usbcsink_generic_write( ctx, USBCSINK_REG_RW_BUF, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    {
        buf[ 0 ] = 0;
        if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 ) != USBCSINK_OK ) {
            return USBCSINK_ERROR;
        }

        buf[ 0 ] = USBCSINK_FTP_CUST_PWR | USBCSINK_FTP_CUST_RST_N;
        if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 ) != USBCSINK_OK ) {
            return USBCSINK_ERROR;
        }
    }


    buf[ 0 ] = ( ( er_sec << 3 ) & USBCSINK_FTP_CUST_SER ) | 
                 ( USBCSINK_WRITE_SER & USBCSINK_FTP_CUST_OPCODE );
    if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_1, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    buf[ 0 ] = USBCSINK_FTP_CUST_PWR   |
               USBCSINK_FTP_CUST_RST_N | 
               USBCSINK_FTP_CUST_REQ ;
    if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    do {
        dev_enable_wr_delay ( );
        usbcsink_generic_read( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 );
    } while( buf[ 0 ] & USBCSINK_FTP_CUST_REQ );

    buf[ 0 ] = USBCSINK_SOFT_PROG_SEC & USBCSINK_FTP_CUST_OPCODE ;
    if (    usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_1, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    buf[ 0 ] = USBCSINK_FTP_CUST_PWR   |
               USBCSINK_FTP_CUST_RST_N | 
               USBCSINK_FTP_CUST_REQ ;
    if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    do {
        usbcsink_generic_read( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 );
    } while( buf[ 0 ] & USBCSINK_FTP_CUST_REQ );

    buf[ 0 ] = USBCSINK_ERASE_SEC & USBCSINK_FTP_CUST_OPCODE ;
    if (    usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_1, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    buf[ 0 ] = USBCSINK_FTP_CUST_PWR   |
               USBCSINK_FTP_CUST_RST_N | 
               USBCSINK_FTP_CUST_REQ ;
    if (    usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    do {
        usbcsink_generic_read( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 );
    } while( buf[ 0 ] & USBCSINK_FTP_CUST_REQ );

    return USBCSINK_OK;
}

err_t usbcsink_cust_ext_test_mode ( usbcsink_t *ctx ) {
    uint8_t buf[ 2 ];

    buf[ 0 ] = USBCSINK_FTP_CUST_RST_N;
    buf[ 1 ] = 0x00;
    
    if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    buf[ 0 ] = 0x00;
    if ( usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CUST_PWD_REG, buf, 1 ) != USBCSINK_OK ) {
        return USBCSINK_ERROR;
    }

    return USBCSINK_OK ;
}

void usbcsink_load_data ( usbcsink_t *ctx ) {
    uint8_t buf[ 8 ];
    uint8_t n_cnt_i;
    uint8_t n_cnt_j;
    rd_sec = 1;

    buf[ 0 ] = USBCSINK_FTP_CUST_PWD;
    usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CUST_PWD_REG, buf, 1 );

    buf[ 0 ] = 0;
    usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 );

    buf[ 0 ] = USBCSINK_FTP_CUST_PWR | 
               USBCSINK_FTP_CUST_RST_N;
    usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 );

    for( n_cnt_i = 0; n_cnt_i < 5; n_cnt_i++ ) {
        buf[ 0 ] = USBCSINK_FTP_CUST_PWR | 
                   USBCSINK_FTP_CUST_RST_N;
        usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 );

        buf[ 0 ] = ( USBCSINK_READ & USBCSINK_FTP_CUST_OPCODE );
        usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_1, buf, 1 );

        buf[ 0 ] = ( n_cnt_i & USBCSINK_FTP_CUST_SECT ) |
                               USBCSINK_FTP_CUST_PWR    | 
                               USBCSINK_FTP_CUST_RST_N  | 
                               USBCSINK_FTP_CUST_REQ;
        usbcsink_generic_write( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 );

        do {
            usbcsink_generic_read( ctx, USBCSINK_REG_FTP_CTL_0, buf, 1 );
        } while( buf[ 0 ] & USBCSINK_FTP_CUST_REQ );

        for ( n_cnt_j = 0; n_cnt_j < 8; n_cnt_j++ ) {
            buf[ n_cnt_j ] = sector[ n_cnt_i ][ n_cnt_j ];
        }
        
        usbcsink_generic_read( ctx, USBCSINK_REG_RW_BUF, buf, 8 );
    }

    usbcsink_cust_ext_test_mode( ctx );
}

void usbcsink_upload_new_data ( usbcsink_t *ctx, uint8_t def_vals ) {
    uint8_t buf[ 8 ];
    uint8_t n_cnt;
    
    if( def_vals == 0 ) {
        usbcsink_cust_ent_wr_mode( ctx, USBCSINK_SEC_0 | 
                                        USBCSINK_SEC_1 | 
                                        USBCSINK_SEC_2 | 
                                        USBCSINK_SEC_3 | 
                                        USBCSINK_SEC_4 );
        
        for ( n_cnt = 0; n_cnt < 8; n_cnt++ ) {
            buf[ n_cnt ] = sector[ 0 ][ n_cnt ];
        }
        
        usbcsink_cust_wr_sec( ctx, 0, buf );
        
        for ( n_cnt = 0; n_cnt < 8; n_cnt++ ) {
            buf[ n_cnt ] = sector[ 1 ][ n_cnt ];
        }
        usbcsink_cust_wr_sec( ctx, 1, buf );
        
        for ( n_cnt = 0; n_cnt < 8; n_cnt++ ) {
            buf[ n_cnt ] = sector[ 2 ][ n_cnt ];
        }
        usbcsink_cust_wr_sec( ctx, 2, buf );
        
        for ( n_cnt = 0; n_cnt < 8; n_cnt++ ) {
            buf[ n_cnt ] = sector[ 3 ][ n_cnt ];
        }
        usbcsink_cust_wr_sec( ctx, 3, buf );
        
        for ( n_cnt = 0; n_cnt < 8; n_cnt++ ) {
            buf[ n_cnt ] = sector[ 4 ][ n_cnt ];
        }
        usbcsink_cust_wr_sec( ctx, 4, buf );
        usbcsink_cust_ext_test_mode( ctx );
    } else {
        uint8_t def_sec[ 5 ][ 8 ] =
        {
            { 0x00, 0x00, 0xB0, 0xAA, 0x00, 0x45, 0x00, 0x00 },
            { 0x10, 0x40, 0x9C, 0x1C, 0xFF, 0x01, 0x3C, 0xDF },
            { 0x02, 0x40, 0x0F, 0x00, 0x32, 0x00, 0xFC, 0xF1 },
            { 0x00, 0x19, 0x56, 0xAF, 0xF5, 0x35, 0x5F, 0x00 },
            { 0x00, 0x4B, 0x90, 0x21, 0x43, 0x00, 0x40, 0xFB }
        };

        usbcsink_cust_ent_wr_mode( ctx, USBCSINK_SEC_0 | 
                                        USBCSINK_SEC_1 | 
                                        USBCSINK_SEC_2 | 
                                        USBCSINK_SEC_3 | 
                                        USBCSINK_SEC_4 );
        
        for ( n_cnt = 0; n_cnt < 8; n_cnt++ ) {
            buf[ n_cnt ] = def_sec[ 0 ][ n_cnt ];
        }
        usbcsink_cust_wr_sec( ctx, 0, buf );
        
        for ( n_cnt = 0; n_cnt < 8; n_cnt++ ) {
            buf[ n_cnt ] = def_sec[ 1 ][ n_cnt ];
        }
        usbcsink_cust_wr_sec( ctx, 1, buf );
        
        for ( n_cnt = 0; n_cnt < 8; n_cnt++ ) {
            buf[ n_cnt ] = def_sec[ 2 ][ n_cnt ];
        }
        usbcsink_cust_wr_sec( ctx, 2, buf );
        
        for ( n_cnt = 0; n_cnt < 8; n_cnt++ ) {
            buf[ n_cnt ] = def_sec[ 3 ][ n_cnt ];
        }
        usbcsink_cust_wr_sec( ctx, 3, buf );
        
        for ( n_cnt = 0; n_cnt < 8; n_cnt++ ) {
            buf[ n_cnt ] = def_sec[ 4 ][ n_cnt ];
        }
        usbcsink_cust_wr_sec( ctx, 4, buf );
        usbcsink_cust_ext_test_mode( ctx );
    }
}

void usbcsink_set_voltage ( uint8_t pdo_numb, float volt ) {
    uint16_t set_volt;

    if( volt < 5 ) {
        volt = 5;
    } else if( volt > 20 ) {
        volt = 20;
    }

    if( pdo_numb == 2 ) {
        sector[ 4 ][ 1 ] = ( volt / 0.2 );
    } else {
        set_volt = ( volt / 0.05 );
        sector[ 4 ][ 2 ] = ( 0xFF & set_volt );
        sector[ 4 ][ 3 ] &= 0xFC;
        sector[ 4 ][ 3 ] |= ( set_volt >> 8 );
    }
}

float usbcsink_get_voltage ( uint8_t pdo_numb ) {
    float voltage;
    
    if ( pdo_numb == 1 ) {
        voltage = 5.0;
    } else if ( pdo_numb == 2 ) {
        voltage = sector[ 4 ][ 1 ];
        voltage *= 0.2;
    } else {
        voltage = ( float ) ( ( ( sector[ 4 ][ 3 ] & 0x03 ) << 8 ) );
        voltage += ( float ) sector[ 4 ][ 2 ];
        voltage *= 0.05;
    }
    
    return voltage;
}

void usbcsink_set_current ( uint8_t pdo_numb,  float curr ) {
    if ( curr < 0.5 ) {
        curr = 0;
    } else if ( curr <= 3 ) {
        curr = ( ( 4 * curr ) - 1 );
    } else {
        curr = ( ( 2 * curr ) + 5 );
    }

    if( pdo_numb == 1 ) {
        sector[ 3 ][ 2 ] &= 0x0F;
        sector[ 3 ][ 2 ] |= ( ( uint8_t )curr << 4 );
    } else if ( pdo_numb == 2 ) {
        sector[ 3 ][ 4 ] &= 0xF0;
        sector[ 3 ][ 4 ] |= ( uint8_t ) curr;
    } else {
        sector[ 3 ][ 5 ] &= 0x0F;
        sector[ 3 ][ 5 ] |= ( ( uint8_t )curr << 4 );
    }
}

float usbcsink_get_current ( uint8_t pdo_numb ) {
    uint8_t digi_val;
    float current;

    if ( pdo_numb == 1 ) {
        digi_val = ( sector[ 3 ][ 2 ] & 0xF0 ) >> 4;

        if( digi_val == 0 ) {
            current = 0.0;
        } else if( digi_val < 11 ) {
            current = ( digi_val * 0.25 + 0.25 );
        } else {
            current = ( digi_val * 0.50 - 2.50 );
        }
    } else if ( pdo_numb == 2 ) {
        digi_val = ( sector[ 3 ][ 4 ] & 0x0F );

        if ( digi_val == 0 ) {
            current = 0.0;
        } else if ( digi_val < 11 ) {
            current = ( digi_val * 0.25 + 0.25 );
        } else {
            current = ( digi_val * 0.50 - 2.50 );
        }
    } else {
        digi_val = ( sector[ 3 ][ 5 ] & 0xF0 ) >> 4;

        if ( digi_val == 0 ) {
            current = 0.0;
        } else if ( digi_val < 11 ) {
            current = ( digi_val * 0.25 + 0.25 );
        } else {
            current = ( digi_val * 0.50 - 2.50 );
        }
    }
    
    return current;
}

void usbcsink_set_lo_volt_limit ( uint8_t pdo_numb, uint8_t value ) {
    if ( value < 5 ) {
        value = 5;
    } else if ( value > 20 ) {
        value = 20;
    } 
    
    if ( pdo_numb == 2 ) {
        sector[ 3 ][ 4 ] &= 0x0F;
        sector[ 3 ][ 4 ] |= ( ( value - 5 ) << 4 );
    } else if ( pdo_numb == 3 ) {
        sector[ 3 ][ 6 ] &= 0xF0;
        sector[ 3 ][ 6 ] |= ( value - 5 );
    }
}

uint8_t usbcsink_get_lo_volt_limit ( uint8_t pdo_numb ) {
    uint8_t lo_volt_limit;

    if ( pdo_numb == 1 ) {
        lo_volt_limit = 0;
    } else if ( pdo_numb == 2 ) {
        lo_volt_limit = ( ( sector[ 3 ][ 4 ] >> 4 ) + 5 );
    } else {
        lo_volt_limit = ( ( sector[ 3 ][ 6 ] & 0x0F ) + 5 );
    }

    return lo_volt_limit;
}

void usbcsink_set_up_volt_limit ( uint8_t pdo_numb,  uint8_t value ) {
    if ( value < 5 ) {
        value = 5;
    } else if ( value > 20 ) {
        value = 20;
    }

    if ( pdo_numb == 1 ) {
        sector[ 3 ][ 3 ] &= 0x0F;
        sector[ 3 ][ 3 ] |= value - 5;
        sector[ 3 ][ 3 ] <<= 4;
    } else if ( pdo_numb == 2 ) {
        sector[ 3 ][ 5 ] &= 0xF0;
        sector[ 3 ][ 5 ] |= value - 5;
    } else if ( pdo_numb == 3 ) {
        sector[ 3 ][ 6 ] &= 0x0F;
        sector[ 3 ][ 6 ] |= value - 5;
        sector[ 3 ][ 6 ] <<= 4;
    }
}

uint8_t usbcsink_get_up_volt_limit ( uint8_t pdo_numb ) {
    uint8_t up_volt_limit;
    
    if ( pdo_numb == 1 ) {
        up_volt_limit = ( ( sector[ 3 ][ 3 ] >> 4 ) + 5 );
    } else if ( pdo_numb == 2 ) {
        up_volt_limit = ( ( sector[ 3 ][ 5 ] & 0x0F ) + 5 );
    } else {
        up_volt_limit = ( ( sector[ 3 ][ 6 ] >> 4 ) + 5 );
    }
    
    return up_volt_limit;
}

void usbcsink_set_flx_curr ( float value ) {
    uint16_t flex_val;

    if ( value > 5 ) {
        value = 5;
    } else if ( value < 0 ) {
        value = 0;
    }

    flex_val = value * 100;

    sector[ 4 ][ 3 ] &= 0x03;
    sector[ 4 ][ 3 ] |= flex_val & 0x3F;
    sector[ 4 ][ 3 ] <<= 2;

    sector[ 4 ][ 4 ] &= 0xF0;
    sector[ 4 ][ 4 ] |= flex_val & 0x03C0;
    sector[ 4 ][ 4 ] >>= 6;
}

float usbcsink_get_flx_curr ( void ) {
    uint16_t digi_val;
    float flx_curr;
    
    digi_val = ( sector[ 4 ][ 4 ] & 0x0F ) << 6;
    digi_val += ( sector[ 4 ][ 3 ] & 0xFC ) >> 2;
    
    flx_curr = ( float ) digi_val;
    flx_curr /= 100.0;

    return flx_curr;
}

void usbcsink_set_pdo_num ( uint8_t pdo_numb ) {
    if( pdo_numb > 3 ) {
        pdo_numb = 3;
    }

    sector[ 3 ][ 2 ] &= 0xF9;
    sector[ 3 ][ 2 ] |= ( pdo_numb << 1 );
}

uint8_t usbcsink_get_pdo_num ( void ) {
    uint8_t pdo_num;
    
    pdo_num = sector[ 3 ][ 2 ] & 0x06;
    pdo_num >>= 1;
    
    return pdo_num;
}

void usbcsink_set_ext_pow ( uint8_t value ) {
    if ( value != 0 ) {
        value = 1;
    }

    sector[ 3 ][ 2 ] &= 0xF7;
    sector[ 3 ][ 2 ] |= ( ( value ) << 3 );

}

uint8_t usbcsink_get_ext_pow ( void ) {
    uint8_t ext_pow;

    ext_pow = sector[ 3 ][ 2 ] & 0x08;
    ext_pow >>= 3;
    
    return ext_pow;
}

void usbcsink_set_usb_com_capa ( uint8_t value ) {
    if ( value != 0 ) {
        value = 1;
    }

    sector[ 3 ][ 2 ] &= 0xFE;
    sector[ 3 ][ 2 ] |= value;
}

uint8_t usbcsink_get_usb_com_cap ( void ) {
    uint8_t usb_com_cap;

    usb_com_cap = sector[ 3 ][ 2 ] & 0x01;
    
    return usb_com_cap;
}

void usbcsink_set_cfg_ok_gpio ( uint8_t value ) {
    if ( value < 2 ) {
        value = 0;
    } else if ( value > 3 ) {
        value = 3;
    }

    sector[ 4 ][ 4 ] &= 0x9F;
    sector[ 4 ][ 4 ] |= ( value << 5 );
}

uint8_t usbcsink_get_cfg_ok_gpio ( void ) {
    uint8_t cfg_ok_gpio;
    
    cfg_ok_gpio = sector[ 4 ][ 4 ] & 0x60;
    cfg_ok_gpio >>= 5;
    
    return cfg_ok_gpio;
}

void usbcsink_set_gpio_ctl ( uint8_t value ) {
    if ( value > 3 ) {
        value = 3;
    }

    sector[ 1 ][ 0 ] &= 0xCF;
    sector[ 1 ][ 0 ] |= ( value << 4 );
}

uint8_t usbcsink_get_gpio_ctl ( void ) {
    uint8_t gpio_ctl;

    gpio_ctl = sector[ 1 ][ 0 ] & 0x30;
    gpio_ctl >>= 4;
    
    return gpio_ctl;
}

void usbcsink_set_pow_above_5v_only ( uint8_t value ) {
    if( value != 0 ) {
        value = 1;
    }

    sector[ 4 ][ 6 ] &= 0xF7;
    sector[ 4 ][ 6 ] |= ( value << 3 );
}

uint8_t usbcsink_get_pow_above_5v_only ( void ) {
    uint8_t pow_val;

    pow_val = sector[ 4 ][ 6 ] & 0x08;
    pow_val >>= 3;
    
    return pow_val;
}

void usbcsink_set_req_src_current ( uint8_t value ) {
    if( value != 0 ) {
        value = 1;
    }

    sector[ 4 ][ 6 ] &= 0xEF;
    sector[ 4 ][ 6 ] |= ( value << 4 );
}

uint8_t usbcsink_get_req_src_curr ( void ) {
    uint8_t req_src_curr;

    req_src_curr = sector[ 4 ][ 6 ] & 0x10;
    req_src_curr >>= 4;
    
    return req_src_curr;
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_device_reset_delay ( void ) {
    Delay_100ms( );
}

static void dev_enable_wr_delay ( void ) {
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
