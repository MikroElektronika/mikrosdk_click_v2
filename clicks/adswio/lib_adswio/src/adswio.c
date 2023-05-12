/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "adswio.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ADSWIO_DUMMY 0

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief CRC8 Calculate function.
 *
 * @param data_in  Data bytes to be included in CRC8 calculation.
 * @param n_bytes  Number of included bytes.
 *
 * @returns Calculated CRC8 byte.
 *
 * @description This function calculates the CRC8 byte using entered data bytes.
 */

static uint8_t adswio_cal_crc8 ( uint8_t *data_in, uint8_t n_bytes );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adswio_cfg_setup ( adswio_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->alt = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

ADSWIO_RETVAL adswio_init ( adswio_t *ctx, adswio_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode        = cfg->spi_mode;
    spi_cfg.speed       = cfg->spi_speed;
    spi_cfg.sck         = cfg->sck;
    spi_cfg.miso        = cfg->miso;
    spi_cfg.mosi        = cfg->mosi;
    
    spi_cfg.default_write_data = ADSWIO_DUMMY;
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ADSWIO_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi,  ADSWIO_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->alt, cfg->alt );
    digital_in_init( &ctx->rdy, cfg->rdy );

    ctx->err_handler = ADSWIO_NULL;

    return ADSWIO_OK;
}

void adswio_default_cfg ( adswio_t *ctx )
{
    ADSWIO_SET_DATA_SAMPLE_EDGE;
    
    adswio_reset( ctx );
    adswio_generic_write( ctx, ADSWIO_REG_CFG_ADC_CHA, ADSWIO_SETUP_ADC_RANGE_0V_TO_10V |
                          ADSWIO_SETUP_ADC_SAMPLE_RATE_4800SPS );

    adswio_enable_ch( ctx, ADSWIO_SETUP_CONV_EN_CHA );

    adswio_set_ch_func( ctx, ADSWIO_SETUP_CONV_EN_CHA, ADSWIO_SETUP_CH_FUNC_VOLT_INPUT );

    adswio_set_conv_mode( ctx, ADSWIO_SETUP_CONV_START_CONT_CONV );
}

void adswio_generic_transfer ( adswio_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
    Delay_1us( );
}

void adswio_reset( adswio_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

uint8_t adswio_status_pin_ready ( adswio_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

uint8_t adswio_status_pin_alert ( adswio_t *ctx )
{
    return digital_in_read( &ctx->alt );
}

void adswio_set_handler ( adswio_t *ctx, adswio_handler_t handler )
{
    ctx->err_handler = handler;
}

void adswio_clear_handler ( adswio_t *ctx )
{
    ctx->err_handler = ADSWIO_NULL;
}
 
adswio_err_t adswio_generic_write ( adswio_t *ctx, uint8_t reg_addr, uint16_t data_in )
{
    uint8_t tx_data[ ADSWIO_FRAME_LENGTH ] = { DUMMY };

    if ( ( reg_addr > 0x2F && reg_addr < 0x3C ) || ( reg_addr == 0x42 ) ||
         ( reg_addr > 0x46 ) )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR REGISTER ADDRESS" );
        }

        return ADSWIO_ERR_REG_ADDR;
    }

    tx_data[ 0 ] = reg_addr;
    tx_data[ 1 ] = data_in >> 8;
    tx_data[ 2 ] = data_in;
    tx_data[ 3 ] = adswio_cal_crc8( tx_data, 3 );

    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    spi_master_write( &ctx->spi, tx_data, ADSWIO_FRAME_LENGTH );
    spi_master_deselect_device( ctx->chip_select ); 
    Delay_1us( );

    return ADSWIO_ERR_STATUS_OK;
}

adswio_err_t adswio_generic_read ( adswio_t *ctx, uint8_t reg_addr, uint16_t *data_out, uint8_t *rd_status )
{
    uint8_t tx_data[ ADSWIO_FRAME_LENGTH ] = { DUMMY };
    uint8_t rx_data[ ADSWIO_FRAME_LENGTH ] = { DUMMY };
    uint16_t ret_val = DUMMY;
    uint8_t crc8 = DUMMY;

    if ( ( reg_addr > 0x2F && reg_addr < 0x3C ) || ( reg_addr == 0x42 ) ||
         ( reg_addr > 0x46 ) )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR REGISTER ADDRESS" );
        }

        return ADSWIO_ERR_REG_ADDR;
    }

    tx_data[ 0 ] = ADSWIO_REG_READ_SELECT;
    tx_data[ 1 ] = ADSWIO_RD_RET_INFO | ADSWIO_RD_AUTO_EN;
    tx_data[ 2 ] = reg_addr;
    tx_data[ 3 ] = adswio_cal_crc8( tx_data, 3 );

    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    spi_master_write( &ctx->spi, tx_data, ADSWIO_FRAME_LENGTH );
    spi_master_deselect_device( ctx->chip_select ); 
    Delay_1us( );

    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    spi_master_read( &ctx->spi, rx_data, ADSWIO_FRAME_LENGTH );
    spi_master_deselect_device( ctx->chip_select ); 
    Delay_1us( );

    if ( ( rx_data[ 0 ] & ADSWIO_MASK_RD_FRAME_RESERVED_BIT ) == 0 )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR READBACK STATUS" );
        }

        return ADSWIO_ERR_RD_STATUS;
    }

    crc8 = adswio_cal_crc8( rx_data, 3 );

    if ( crc8 != rx_data[ 3 ] )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR CRC" );
        }

        return ADSWIO_ERR_CRC;
    }

    if ( data_out != ADSWIO_NULL )
    {
        ret_val = rx_data[ 1 ];
        ret_val <<= 8;
        ret_val |= rx_data[ 2 ];
        *data_out = ret_val;
    }

    if ( rd_status != ADSWIO_NULL )
    {
        *rd_status = rx_data[ 0 ] & ADSWIO_MASK_RD_FRAME_STATUS;
    }

    return ADSWIO_ERR_STATUS_OK;
}

adswio_err_t adswio_generic_multi_read ( adswio_t *ctx, adswio_read_t *rd )
{
    uint8_t cnt;
    uint8_t tx_data[ 13 ] = { DUMMY };
    uint8_t rx_data[ 13 ] = { DUMMY };
    uint16_t ret_val = DUMMY;
    uint8_t crc8 = DUMMY;
    uint8_t rx_idx;
    uint8_t crc_nbytes;

    if ( ( rd->reg_addr > 0x2F && rd->reg_addr < 0x3C ) || ( rd->reg_addr == 0x42 ) ||
         ( rd->reg_addr > 0x46 ) )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR REGISTER ADDRESS" );
        }

        return ADSWIO_ERR_REG_ADDR;
    }

    if ( ( rd->n_words < ADSWIO_MIN_NWORDS ) || ( rd->n_words > ADSWIO_MAX_NWORDS ) )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR READBACK NUMBER OF WORDS" );
        }

        return ADSWIO_ERR_RD_NWORDS;
    }

    if ( ( rd->rd_mode != ADSWIO_RD_AUTO_EN ) &&
         ( rd->rd_mode != ADSWIO_RD_AUTO_DIS ) )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR AUTO READ MODE SETUP" );
        }

        return ADSWIO_ERR_RD_MODE;
    }

    tx_data[ 0 ] = ADSWIO_REG_READ_SELECT;
    tx_data[ 1 ] = rd->rd_mode;
    tx_data[ 2 ] = rd->reg_addr;
    tx_data[ 3 ] = adswio_cal_crc8( tx_data, 3 );

    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    spi_master_write( &ctx->spi, tx_data, ADSWIO_FRAME_LENGTH );
    spi_master_deselect_device( ctx->chip_select ); 
    Delay_1us( );

    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    spi_master_read( &ctx->spi, rx_data, rd->n_words * 3 + 1 );
    spi_master_deselect_device( ctx->chip_select ); 
    Delay_1us( );

    if ( ( rx_data[ 0 ] & ADSWIO_MASK_RD_FRAME_RESERVED_BIT ) == 0 )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR READBACK STATUS" );
        }

        return ADSWIO_ERR_RD_STATUS;
    }

    if ( ( rx_data[ 0 ] & ADSWIO_MASK_RD_FRAME_REG_ADDR ) != rd->reg_addr )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR READBACK STATUS" );
        }

        return ADSWIO_ERR_RD_STATUS;
    }

    if ( rd->data_out != ADSWIO_NULL )
    {
        rx_idx = 0;
        crc_nbytes = 3;

        for ( cnt = 0; cnt < rd->n_words; cnt++ )
        {
            crc8 = adswio_cal_crc8( &rx_data[ rx_idx ], crc_nbytes );

            if ( crc8 != rx_data[ rx_idx + crc_nbytes ] )
            {
                if ( ctx->err_handler != ADSWIO_NULL )
                {
                    ctx->err_handler( "ADSWIO ERROR CRC" );
                }

                return ADSWIO_ERR_CRC;
            }

            if ( crc_nbytes == 3 )
            {
                rx_idx++;
                crc_nbytes = 2;
            }

            ret_val = rx_data[ rx_idx++ ];
            ret_val <<= 8;
            ret_val |= rx_data[ rx_idx ];
            rx_idx += 2;
            *rd->data_out = ret_val;
            rd->data_out++;
        }
    }

    return ADSWIO_ERR_STATUS_OK;
}

adswio_err_t adswio_exe_command ( adswio_t *ctx, uint16_t cmd_key )
{
    if ( ( cmd_key != ADSWIO_CMD_NOP ) &&
         ( cmd_key != ADSWIO_CMD_SW_RST_KEY1 ) &&
         ( cmd_key != ADSWIO_CMD_SW_RST_KEY2 ) &&
         ( cmd_key != ADSWIO_CMD_LDAC_KEY ) &&
         ( cmd_key != ADSWIO_CMD_DAC_CLR_KEY ) )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR COMMAND KEY" );
        }

        return ADSWIO_ERR_CMD_KEY;
    }

    adswio_generic_write( ctx, ADSWIO_REG_CMD_KEY, cmd_key );

    return ADSWIO_ERR_STATUS_OK;
}

void adswio_mask_alert_set ( adswio_t *ctx, uint16_t alert_mask )
{
    adswio_generic_write( ctx, ADSWIO_REG_MASK_ALERT, alert_mask & ADSWIO_MASK_ALERT );
}

adswio_err_t adswio_status_live ( adswio_t *ctx, uint16_t *status, uint16_t status_mask )
{
    uint16_t read_data = DUMMY;
    adswio_err_t error;

    if ( error = adswio_generic_read( ctx, ADSWIO_REG_STATUS_LIVE, &read_data, ADSWIO_NULL ) )
    {
        return error;
    }

    if ( status != ADSWIO_NULL )
    {
        *status = read_data & status_mask;
    }

    return ADSWIO_ERR_STATUS_OK;
}

adswio_err_t adswio_status_data_ready ( adswio_t *ctx, uint8_t *drdy, uint16_t *conv_target )
{
    uint16_t read_data = DUMMY;
    adswio_err_t error;

    if ( error = adswio_status_live( ctx, &read_data, ADSWIO_MASK_STATUS_LIVE_ADC_DRDY |
                                     ADSWIO_MASK_STATUS_LIVE_ADC_CURR_CH ) )
    {
        return error;
    }

    if ( drdy != ADSWIO_NULL )
    {
        if ( read_data & ADSWIO_MASK_STATUS_LIVE_ADC_DRDY )
        {
            *drdy = 1;

            adswio_generic_write( ctx, ADSWIO_REG_STATUS_LIVE, ADSWIO_MASK_STATUS_LIVE_ADC_DRDY );
        }
        else
        {
            *drdy = 0;
        }
    }

    if ( conv_target != ADSWIO_NULL )
    {
        *conv_target = read_data & ADSWIO_MASK_STATUS_LIVE_ADC_CURR_CH;
    }

    return ADSWIO_ERR_STATUS_OK;
}

adswio_err_t adswio_status_alert ( adswio_t *ctx, uint16_t *status, uint16_t status_mask )
{
    uint16_t read_data = DUMMY;
    adswio_err_t error;

    if ( error = adswio_generic_read( ctx, ADSWIO_REG_STATUS_ALERT, &read_data, ADSWIO_NULL ) )
    {
        return error;
    }

    if ( status != ADSWIO_NULL )
    {
        *status = read_data & status_mask;

        if ( read_data & status_mask )
        {
            adswio_generic_write( ctx, ADSWIO_REG_STATUS_ALERT, read_data & status_mask );
        }
    }

    return ADSWIO_ERR_STATUS_OK;
}

adswio_err_t adswio_set_conv_mode ( adswio_t *ctx, uint8_t mode )
{
    uint16_t read_data = DUMMY;
    adswio_err_t error;

    if ( mode > 0x3 )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR CONVERSION MODE" );
        }

        return ADSWIO_ERR_CONV_MODE;
    }

    if ( error = adswio_generic_read( ctx, ADSWIO_REG_ADC_CONV_CTRL, &read_data, ADSWIO_NULL ) )
    {
        return error;
    }

    read_data &= ~ADSWIO_MASK_CONV_MODE;
    read_data |= ( uint16_t ) mode << ADSWIO_OFFSET_CONV_MODE;

    adswio_generic_write( ctx, ADSWIO_REG_ADC_CONV_CTRL, read_data );

    return ADSWIO_ERR_STATUS_OK;
}

adswio_err_t adswio_enable_ch ( adswio_t *ctx, uint8_t channel )
{
    uint16_t read_data = DUMMY;
    adswio_err_t error;

    if ( channel > ADSWIO_SETUP_CONV_EN_ALL_CH )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR CHANNEL SELECTION" );
        }

        return ADSWIO_ERR_EN_CH;
    }

    if ( error = adswio_generic_read( ctx, ADSWIO_REG_ADC_CONV_CTRL, &read_data, ADSWIO_NULL ) )
    {
        return error;
    }

    read_data &= ~( ( uint16_t ) ADSWIO_MASK_CONV_EN << ADSWIO_OFFSET_CONV_EN_CH );
    read_data |= channel << ADSWIO_OFFSET_CONV_EN_CH;

    adswio_generic_write( ctx, ADSWIO_REG_ADC_CONV_CTRL, read_data );

    return ADSWIO_ERR_STATUS_OK;
}

adswio_err_t adswio_enable_diag ( adswio_t *ctx, uint8_t diagnostic )
{
    uint16_t read_data = DUMMY;
    adswio_err_t error;

    if ( diagnostic > ADSWIO_SETUP_CONV_EN_ALL_DIAG )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR DIAGNOSTIC SELECTION" );
        }

        return ADSWIO_ERR_EN_DIAG;
    }

    if ( error = adswio_generic_read( ctx, ADSWIO_REG_ADC_CONV_CTRL, &read_data, ADSWIO_NULL ) )
    {
        return error;
    }

    read_data &= ~( ( uint16_t ) ADSWIO_MASK_CONV_EN << ADSWIO_OFFSET_CONV_EN_DIAG );
    read_data |= diagnostic << ADSWIO_OFFSET_CONV_EN_DIAG;

    adswio_generic_write( ctx, ADSWIO_REG_ADC_CONV_CTRL, read_data );

    return ADSWIO_ERR_STATUS_OK;
}

adswio_err_t adswio_set_ch_func ( adswio_t *ctx, uint8_t channel, uint8_t ch_func )
{
    uint8_t ch_addr;

    if ( ( channel != ADSWIO_SETUP_CONV_EN_CHA ) && ( channel != ADSWIO_SETUP_CONV_EN_CHB ) &&
         ( channel != ADSWIO_SETUP_CONV_EN_CHC ) && ( channel != ADSWIO_SETUP_CONV_EN_CHD ) )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR CHANNEL SELECTION" );
        }

        return ADSWIO_ERR_EN_CH;
    }

    if ( ch_func > 0xA )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR CHANNEL FUNCTION" );
        }

        return ADSWIO_ERR_CH_FUNC;
    }

    ch_addr = channel - ( ( channel >> 2 ) * ( channel >> 2 ) );

    adswio_generic_write( ctx, ch_addr, ch_func );

    return ADSWIO_ERR_STATUS_OK;
}

adswio_err_t adswio_assign_diag ( adswio_t *ctx, uint8_t diagnostic, uint8_t duty )
{
    uint16_t read_data = DUMMY;
    adswio_err_t error;

    if ( ( diagnostic != ADSWIO_SETUP_CONV_EN_DIAG0 ) &&
         ( diagnostic != ADSWIO_SETUP_CONV_EN_DIAG1 ) &&
         ( diagnostic != ADSWIO_SETUP_CONV_EN_DIAG2 ) &&
         ( diagnostic != ADSWIO_SETUP_CONV_EN_DIAG3 ) )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR DIAGNOSTIC SELECTION" );
        }

        return ADSWIO_ERR_EN_DIAG;
    }

    if ( duty > 0xE )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR DIAGNOSTIC ASSIGN" );
        }

        return ADSWIO_ERR_DIAG_ASSIGN;
    }

    if ( error = adswio_generic_read( ctx, ADSWIO_REG_DIAG_ASSIGN, &read_data, ADSWIO_NULL ) )
    {
        return error;
    }

    switch ( diagnostic )
    {
        case ADSWIO_SETUP_CONV_EN_DIAG0 :
        {
            read_data &= ~( ( uint16_t ) ADSWIO_MASK_DIAG_ASSIGN << ADSWIO_OFFSET_ASSIGN_DIAG0 );
            read_data |= ( uint16_t ) duty << ADSWIO_OFFSET_ASSIGN_DIAG0;
        break;
        }
        case ADSWIO_SETUP_CONV_EN_DIAG1 :
        {
            read_data &= ~( ( uint16_t ) ADSWIO_MASK_DIAG_ASSIGN << ADSWIO_OFFSET_ASSIGN_DIAG1 );
            read_data |= ( uint16_t ) duty << ADSWIO_OFFSET_ASSIGN_DIAG1;
        break;
        }
        case ADSWIO_SETUP_CONV_EN_DIAG2 :
        {
            read_data &= ~( ( uint16_t ) ADSWIO_MASK_DIAG_ASSIGN << ADSWIO_OFFSET_ASSIGN_DIAG2 );
            read_data |= ( uint16_t ) duty << ADSWIO_OFFSET_ASSIGN_DIAG2;
        break;
        }
        case ADSWIO_SETUP_CONV_EN_DIAG3 :
        {
            read_data &= ~( ( uint16_t ) ADSWIO_MASK_DIAG_ASSIGN << ADSWIO_OFFSET_ASSIGN_DIAG3 );
            read_data |= ( uint16_t ) duty << ADSWIO_OFFSET_ASSIGN_DIAG3;
        break;
        }
        default :
        {
        break;
        }
    }

    adswio_generic_write( ctx, ADSWIO_REG_DIAG_ASSIGN, read_data );

    return ADSWIO_ERR_STATUS_OK;
}

adswio_err_t adswio_get_conv_results ( adswio_t *ctx, uint8_t channel, uint16_t *data_out )
{
    uint16_t read_data = DUMMY;
    adswio_err_t error;
    uint8_t ch_addr;

    if ( ( channel != ADSWIO_SETUP_CONV_EN_CHA ) && ( channel != ADSWIO_SETUP_CONV_EN_CHB ) &&
         ( channel != ADSWIO_SETUP_CONV_EN_CHC ) && ( channel != ADSWIO_SETUP_CONV_EN_CHD ) )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR CHANNEL SELECTION" );
        }

        return ADSWIO_ERR_EN_CH;
    }

    ch_addr = channel - ( ( channel >> 2 ) * ( channel >> 2 ) );
    ch_addr += ADSWIO_OFFSET_REG_CONV_RES;

    if ( error = adswio_generic_read( ctx, ch_addr, &read_data, ADSWIO_NULL ) )
    {
        return error;
    }

    if ( data_out != ADSWIO_NULL )
    {
        *data_out = read_data;
    }

    return ADSWIO_ERR_STATUS_OK;
}

adswio_err_t adswio_get_diag_results ( adswio_t *ctx, uint8_t diagnostic, uint16_t *data_out )
{
    uint16_t read_data = DUMMY;
    adswio_err_t error;
    uint8_t diag_addr;

    if ( ( diagnostic != ADSWIO_SETUP_CONV_EN_DIAG0 ) &&
         ( diagnostic != ADSWIO_SETUP_CONV_EN_DIAG1 ) &&
         ( diagnostic != ADSWIO_SETUP_CONV_EN_DIAG2 ) &&
         ( diagnostic != ADSWIO_SETUP_CONV_EN_DIAG3 ) )
    {
        if ( ctx->err_handler != ADSWIO_NULL )
        {
            ctx->err_handler( "ADSWIO ERROR DIAGNOSTIC SELECTION" );
        }

        return ADSWIO_ERR_EN_DIAG;
    }

    diag_addr = diagnostic - ( ( diagnostic >> 2 ) * ( diagnostic >> 2 ) );
    diag_addr += ADSWIO_OFFSET_REG_DIAG_RES;

    if ( error = adswio_generic_read( ctx, diag_addr, &read_data, ADSWIO_NULL ) )
    {
        return error;
    }

    if ( data_out != ADSWIO_NULL )
    {
        *data_out = read_data;
    }

    return ADSWIO_ERR_STATUS_OK;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t adswio_cal_crc8 ( uint8_t *data_in, uint8_t n_bytes )
{
    uint32_t crc_code = 0x107;
    uint8_t i = 31;
    uint32_t data_out = 0;
    uint8_t cnt;

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        data_out |= *data_in;
        data_in++;
        data_out <<= 8;
    }

    while ( i >= 8 )
    {
        if ( ( data_out & ( ( uint32_t ) 1 << i ) ) != 0 )
        {
            data_out ^= ( crc_code << ( i - 8 ) );
        }

        i--;
    }

    return ( uint8_t ) data_out;
}


// ------------------------------------------------------------------------- END

