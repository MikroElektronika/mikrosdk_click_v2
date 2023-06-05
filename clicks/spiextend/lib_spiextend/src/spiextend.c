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
 * @file spiextend.c
 * @brief SPI Extend Click Driver.
 */

#include "spiextend.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 
/**
 * @brief SPI Extend start spi transfer function.
 * @details This function starts spi transfer.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] sel_slave : Select slave.
 * @return Nothing.
 */
static void dev_start_spi_transfer ( spiextend_t *ctx, uint8_t sel_slave );

/**
 * @brief SPI Extend stop spi transfer function.
 * @details This function stops spi transfer function.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] sel_slave : Select slave.
 * @return Nothing.
 */
static void dev_stop_spi_transfer ( spiextend_t *ctx, uint8_t sel_slave );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void spiextend_cfg_setup ( spiextend_cfg_t *cfg )  {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->ss3  = HAL_PIN_NC;
    cfg->ss2  = HAL_PIN_NC;
    cfg->ssc  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t spiextend_init ( spiextend_t *ctx, spiextend_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->ss3, cfg->ss3 );
    digital_out_init( &ctx->ss2, cfg->ss2 );
    digital_out_init( &ctx->ssc, cfg->ssc );
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t spiextend_default_cfg ( spiextend_t *ctx ) {
    spi_master_deselect_device( ctx->chip_select );
    digital_out_high( &ctx->ss3 );
    digital_out_high( &ctx->ss2 );
    digital_out_high( &ctx->ssc );
    
    return SPIEXTEND_OK;
}

err_t spiextend_generic_write ( spiextend_t *ctx, uint8_t reg, uint8_t data_in ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] <<= 1;
    tx_buf[ 0 ] |= SPIEXTEND_SPI_WRITE;
    tx_buf[ 1 ] = data_in;

    digital_out_low( &ctx->ssc );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    digital_out_high( &ctx->ssc );

    return error_flag;
}

err_t spiextend_generic_read ( spiextend_t *ctx, uint8_t reg, uint8_t *data_out ) {
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] <<= 1;
    tx_buf[ 0 ] |= SPIEXTEND_SPI_READ;
    tx_buf[ 1 ] = DUMMY;
    
    digital_out_low( &ctx->ssc );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_out, 1 );
    digital_out_high( &ctx->ssc );

    return error_flag;
}

void spiextend_get_config ( spiextend_t *ctx, spiextend_config_data_t *config_data ) {
    uint8_t config_val;

    spiextend_generic_read( ctx, SPIEXTEND_REG_CONFIG, &config_val );

    config_data->rem_ss1_pha =   config_val & 0x01;
    config_data->rem_ss1_pol = ( config_val & 0x02 ) >> 1;
    config_data->rem_ss2_pha = ( config_val & 0x04 ) >> 2;
    config_data->rem_ss2_pol = ( config_val & 0x08 ) >> 3;
    config_data->rem_ss1_pha = ( config_val & 0x10 ) >> 4;
    config_data->rem_ss1_pol = ( config_val & 0x20 ) >> 5;
}

void spiextend_set_config ( spiextend_t *ctx, spiextend_config_data_t config_data ) {
    uint8_t config_val;

    config_val =  config_data.rem_ss1_pha & 0x01;
    config_val |= config_data.rem_ss1_pol & 0x02;
    config_val |= config_data.rem_ss2_pha & 0x04;
    config_val |= config_data.rem_ss2_pol & 0x08;
    config_val |= config_data.rem_ss1_pha & 0x10;
    config_val |= config_data.rem_ss1_pol & 0x20;
    
    spiextend_generic_write( ctx, SPIEXTEND_REG_CONFIG, config_val );
}

void spiextend_get_status ( spiextend_t *ctx, spiextend_status_data_t *status_data ) {
    uint8_t status_val;

    spiextend_generic_read( ctx, SPIEXTEND_REG_STATUS, &status_val);

    status_data->nlink     =   status_val & 0x01;
    status_data->nint      = ( status_val & 0x02 ) >> 1;
    status_data->rmt_nint  = ( status_val & 0x04 ) >> 2;
    status_data->speed_idx = ( status_val & 0xF0 ) >> 4;
}

void spiextend_get_event ( spiextend_t *ctx, spiextend_event_data_t *event_data ) {
    uint8_t event_val;

    spiextend_generic_read( ctx, SPIEXTEND_REG_EVENT, &event_val );

    event_data->e_link_good =   event_val & 0x01;
    event_data->e_link_lost = ( event_val & 0x02 ) >> 1;
    event_data->e_fault     = ( event_val & 0x04 ) >> 2;
}

void spiextend_clear_event ( spiextend_t *ctx ) {
    spiextend_generic_write( ctx, SPIEXTEND_REG_EVENT, SPIEXTEND_CMD_CLEAR_EVENT );
}

void spiextend_enable_int ( spiextend_t *ctx, spiextend_event_data_t event_data ) {
    uint8_t event_val;

    spiextend_generic_read( ctx, SPIEXTEND_REG_INT_EN, &event_val );
    
    event_val |= event_data.e_link_good;
    event_val |= event_data.e_link_lost << 1;
    event_val |= event_data.e_fault << 2;

    spiextend_generic_write( ctx, SPIEXTEND_REG_INT_EN, event_val );
}

void spiextend_get_fault ( spiextend_t *ctx, spiextend_fault_data_t *fault_data ) {
    uint8_t fault_val;

    spiextend_generic_read( ctx, SPIEXTEND_REG_FAULT, &fault_val );

    fault_data->spi_write_fault = fault_val & 0x01;
    fault_data->link_fault = ( fault_val & 0x02 ) >> 1;
    fault_data->rmt_spi_fault = ( fault_val & 0x04 ) >> 2;
    fault_data->tx_buf_overflow = ( fault_val & 0x08 ) >> 3;
    fault_data->tx_buf_underflow = ( fault_val & 0x10 ) >> 4;
}

uint8_t spiextend_get_word_length ( spiextend_t *ctx ) {
    uint8_t word_length;

    spiextend_generic_read( ctx, SPIEXTEND_REG_WORD_LENGTH, &word_length );

    return word_length;
}

void spiextend_set_word_length ( spiextend_t *ctx, uint8_t word_length ) {
    word_length %= 32;
    
    if ( word_length < 8 ) {
        word_length = 8;
    }
    
    spiextend_generic_write( ctx, SPIEXTEND_REG_WORD_LENGTH, word_length );
}

uint8_t spiextend_get_scratch (  spiextend_t *ctx ) {
    uint8_t rx_buf;

    spiextend_generic_read( ctx, SPIEXTEND_REG_SCRATCH, &rx_buf );

    return rx_buf;
}

void spiextend_set_scratch ( spiextend_t *ctx, uint8_t scratch ) {
    spiextend_generic_write( ctx, SPIEXTEND_REG_SCRATCH, scratch );
}

void spiextend_set_ss1 ( spiextend_t *ctx, uint8_t en_cs ) {
    if ( en_cs == SPIEXTEND_PIN_STATE_LOW ) {
        spi_master_select_device( ctx->chip_select );
    } else {
        spi_master_deselect_device( ctx->chip_select );
    }
}

void spiextend_set_ss2 ( spiextend_t *ctx, uint8_t en_rst ) {
    if ( en_rst == SPIEXTEND_PIN_STATE_LOW ) {
        digital_out_low( &ctx->ss2 );
    } else {
        digital_out_high( &ctx->ss2 );
    }
}

void spiextend_set_ss3 ( spiextend_t *ctx, uint8_t en_an ) {
    if ( en_an == SPIEXTEND_PIN_STATE_LOW ) {
        digital_out_low( &ctx->ss3 );
    } else {
        digital_out_high( &ctx->ss3 );
    }
}
 
uint8_t spiextend_check_int ( spiextend_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

void spiextend_rmt_spi_write ( spiextend_t *ctx, uint8_t *p_tx_data, uint16_t n_bytes ) {
    spi_master_write( &ctx->spi, p_tx_data, n_bytes );
}

void spiextend_rmt_spi_read ( spiextend_t *ctx, uint8_t *p_rx_data, uint16_t n_bytes ) {
    spi_master_read( &ctx->spi, p_rx_data, n_bytes );
}

void spiextend_rmt_write ( spiextend_t *ctx, uint8_t reg, uint8_t tx_data, uint8_t sel_slave ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data;
    
    dev_start_spi_transfer ( ctx, sel_slave );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    dev_stop_spi_transfer ( ctx, sel_slave );
}

uint8_t spiextend_rmt_read ( spiextend_t *ctx, uint8_t reg, uint8_t sel_slave ) {
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 1 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = DUMMY;

    dev_start_spi_transfer( ctx, sel_slave );
    spi_master_write_then_read( &ctx->spi, tx_buf, 2, rx_buf, 1 );
    dev_stop_spi_transfer( ctx, sel_slave );

    return rx_buf[ 0 ];
}

void spiextend_rmt_multi_write ( spiextend_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint16_t n_bytes, uint8_t sel_slave ) {
    
    uint16_t n_cnt;
    uint8_t tx_buf[ 10000 ];

    tx_buf[ 0 ] = reg;

    for ( n_cnt = 0; n_cnt < n_bytes; n_cnt++ ) {
       
        tx_buf[ n_cnt + 1 ] = p_tx_data[ n_cnt ];
    }

    
    dev_start_spi_transfer( ctx, sel_slave );
    spi_master_write( &ctx->spi, tx_buf, n_bytes + 1);
    dev_stop_spi_transfer( ctx, sel_slave );
}

void spiextend_rmt_multi_read ( spiextend_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes, uint8_t sel_slave ) {
   
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = DUMMY;

    dev_start_spi_transfer( ctx, sel_slave );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, p_rx_data, n_bytes );
    dev_stop_spi_transfer( ctx, sel_slave );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_start_spi_transfer ( spiextend_t *ctx, uint8_t sel_slave ) {
   
    switch ( sel_slave ) {
        case 1: {
            spi_master_select_device( ctx->chip_select );
            break;
        }
        case 2: {
            digital_out_low( &ctx->ss2 );
            break;
        }
        case 3: {
            digital_out_low( &ctx->ss3 );
            break;
        }
        default: {
            spi_master_select_device( ctx->chip_select );
            break;
        }
    }
}

static void dev_stop_spi_transfer ( spiextend_t *ctx, uint8_t sel_slave ) {
    
    switch ( sel_slave ) {
       case 1: {
            spi_master_deselect_device( ctx->chip_select );
            break;
        }
        case 2: {
            digital_out_high( &ctx->ss2 );
            break;
        }
        case 3: {
            digital_out_high( &ctx->ss3 );
            break;
        }
        default: {
            spi_master_deselect_device( ctx->chip_select );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END

