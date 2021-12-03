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
 * @file ecg2.c
 * @brief ECG 2 Click Driver.
 */

#include "ecg2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Hardware reset delay of 1 milliseconds.
 */
void dev_hw_reset_delay ( void );

/**
 * @brief Read 1 uS delay.
 */
void dev_read_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void ecg2_cfg_setup ( ecg2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->pwd = HAL_PIN_NC;
    cfg->drd = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t ecg2_init ( ecg2_t *ctx, ecg2_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }
    
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) {
        return ADC_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->pwd, cfg->pwd );

    digital_in_init( &ctx->drd, cfg->drd );

    digital_out_high( &ctx->rst );
    
    digital_out_high( &ctx->pwd );

    return SPI_MASTER_SUCCESS;
}

err_t ecg2_default_cfg ( ecg2_t *ctx ) 
{
    err_t error_flag = ECG2_OK;
    
    ecg2_write_register( ctx, ECG2_CONFIG1_REG, ECG2_CFG_DATA_SPEED_125 );
    ecg2_write_register( ctx, ECG2_CONFIG2_REG, ECG2_CONFIG2_REG_DEFAULT_VAL);
    ecg2_write_register( ctx, ECG2_CONFIG3_REG, ECG2_CONFIG3_REG_DEFAULT_VAL | 
                                                ECG2_CFG_ENABLE_INT_BUFFER |
                                                ECG2_CFG_RLD_ENABLE );
    ecg2_write_register( ctx, ECG2_LOFF_REG, ECG2_CFG_COMPARATOR_P_70 |
                                             ECG2_CFG_VLEAD_EN |
                                             ECG2_CFG_FLEAD_OFF_DC_OFF ); 
    
    ecg2_right_leg_positive_drive_set( ctx, 0x02 ); 
    ecg2_right_leg_negative_drive_set( ctx, 0x02 ); 
   
    ecg2_lead_off_positive_channel_select( ctx, 0x05 ); 
    ecg2_lead_off_negative_channel_select( ctx, 0x02 ); 
    ecg2_lead_off_current_direction_select( ctx, 0x00 ); 

    ecg2_send_command( ctx, ECG2_STOP_CONVERSION );
    ecg2_send_command( ctx, ECG2_STOP_DATA_CONT_MODE );
    
    ecg2_configure_channel( ctx, ECG2_CH1SET_REG, ECG2_CHANNEL_DISABLE, ECG2_CFG_PGA_GAIN_6, 
                            ECG2_CFG_MUX_NORMAL_ELECTRODE ); 
    ecg2_configure_channel( ctx, ECG2_CH2SET_REG, ECG2_CHANNEL_DISABLE, ECG2_CFG_PGA_GAIN_6, 
                            ECG2_CFG_MUX_NORMAL_ELECTRODE ); 
    ecg2_configure_channel( ctx, ECG2_CH3SET_REG, ECG2_CHANNEL_DISABLE, ECG2_CFG_PGA_GAIN_6, 
                            ECG2_CFG_MUX_NORMAL_ELECTRODE ); 
    ecg2_configure_channel( ctx, ECG2_CH4SET_REG, ECG2_CHANNEL_DISABLE, ECG2_CFG_PGA_GAIN_6, 
                            ECG2_CFG_MUX_NORMAL_ELECTRODE ); 
    
    ecg2_write_register( ctx, ECG2_GPIO_REG, 0x0F ); 
    ecg2_pace_detect_odd_channels_select( ctx, 0x00 ); 
    ecg2_write_register( ctx, ECG2_CONFIG4_REG, 0x02 );

    return error_flag;
}

err_t ecg2_generic_write ( ecg2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t ecg2_generic_read ( ecg2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t ecg2_read_an_pin_value ( ecg2_t *ctx, uint16_t *data_out ) {
    return analog_in_read( &ctx->adc, data_out );
}

err_t ecg2_read_an_pin_voltage ( ecg2_t *ctx, float *data_out ) {
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t ecg2_write_register ( ecg2_t *ctx, uint8_t reg, uint8_t data_in ) {
    uint8_t tx_buf[3];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= ECG2_SPI_CMD_WRITE;
    tx_buf[ 1 ] = DUMMY;
    tx_buf[ 2 ] = data_in;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t ecg2_read_register ( ecg2_t *ctx, uint8_t reg, uint8_t *data_out ) {
    uint8_t tx_buf[2];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= ECG2_SPI_CMD_READ;
    tx_buf[ 1 ] = DUMMY;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    error_flag |= spi_master_read( &ctx->spi, data_out, 1);
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
} 

err_t ecg2_multi_write ( ecg2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 256 ];
    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= ECG2_SPI_CMD_WRITE;
    tx_buf[ 1 ] = len - 1;

    for ( uint8_t cnt = 0; cnt <= len; cnt++) {
        tx_buf[ cnt + 2 ] = data_in[ cnt ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
} 

err_t ecg2_multi_read ( ecg2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= ECG2_SPI_CMD_READ;
    tx_buf[ 1 ] = len - 1;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    error_flag |= spi_master_read( &ctx->spi, data_out, len);
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t ecg2_send_command ( ecg2_t *ctx, uint8_t command ) {
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &command, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

void ecg2_hw_reset ( ecg2_t *ctx ) {
    digital_out_low( &ctx->rst );
    dev_hw_reset_delay( );
    digital_out_high( &ctx->rst );
}

uint8_t ecg2_get_device_id( ecg2_t *ctx ) {
    uint8_t tempbuff;
    
    ecg2_read_register( ctx, ECG2_ID_REG, &tempbuff );
    
    return tempbuff;
}

err_t ecg2_configure_channel ( ecg2_t *ctx, uint8_t channel, uint8_t enable, uint8_t pga_gain, 
                                int8_t channel_input ) {
    uint8_t tempbuff = 0;

    switch ( channel ) {
        case 1: {
            if ( (pga_gain > 7) || ( channel_input > 7 ) ) {
                return ECG2_ERROR;
            }
            
            tempbuff |= pga_gain << 4;
            tempbuff |= channel_input;
            
            if ( ECG2_CHANNEL_ENABLE == enable ) {
                tempbuff |= 1 << 7;
            }  else {
                tempbuff &= ~(1 << 7);
            }

            ecg2_write_register( ctx, ECG2_CH1SET_REG, tempbuff );
            return ECG2_OK;
        }
        case 2: {
            if ( ( channel_input > 15 ) || (pga_gain > 15) ) {
                return ECG2_ERROR;
            }
            if ( ECG2_CHANNEL_ENABLE == enable ) { 
                tempbuff |= 1 << 7;
            } else {
                tempbuff &= ~(1 << 7);
            }
            
            tempbuff |= pga_gain << 4;
            tempbuff |= channel_input;
            ecg2_write_register( ctx, ECG2_CH2SET_REG, tempbuff );
            return ECG2_OK;
        }
        case 3: {
            if  ( ( pga_gain > 15 ) || ( channel_input > 15 ) ) {
                return ECG2_ERROR;
            }
            if ( ECG2_CHANNEL_ENABLE == enable ) {
                tempbuff |= 1 << 7;
            } else { 
                tempbuff &= ~(1 << 7);
            } 
            
            tempbuff |= pga_gain << 4;
            tempbuff |= channel_input;
            ecg2_write_register( ctx, ECG2_CH3SET_REG, tempbuff );
            return ECG2_OK;
        }
        case 4: {
            if ( ( pga_gain > 15 ) || ( channel_input > 15 ) ) {
                return ECG2_ERROR;
            }

           if ( ECG2_CHANNEL_ENABLE == enable ) {
                tempbuff |= 1 << 7;
            } else { 
                tempbuff &= ~(1 << 7);
            } 

            tempbuff |= pga_gain << 4;
            tempbuff |= channel_input;
            ecg2_write_register( ctx, ECG2_CH4SET_REG, tempbuff );
            return ECG2_OK;
        }
        case 5: {
            if ( ( pga_gain > 15 ) || ( channel_input > 15 ) ) {
                return ECG2_ERROR;
            }

            if ( ECG2_CHANNEL_ENABLE == enable ) {
                tempbuff |= 1 << 7;
            } else { 
                tempbuff &= ~(1 << 7);
            } 

            tempbuff |= pga_gain << 4;
            tempbuff |= channel_input;
            ecg2_write_register( ctx, ECG2_CH5SET_REG, tempbuff );
            return ECG2_OK;
        }
        case 6: { 
            if ( ( pga_gain > 15 ) || ( channel_input > 15 ) ) {
                return ECG2_ERROR;
            }

            if ( ECG2_CHANNEL_ENABLE == enable ) {
                tempbuff |= 1 << 7;
            } else { 
                tempbuff &= ~(1 << 7);
            } 

            tempbuff |= pga_gain << 4;
            tempbuff |= channel_input;
            ecg2_write_register( ctx, ECG2_CH6SET_REG, tempbuff );
            return ECG2_OK;
        }
        case 7: { 
            if ( ( pga_gain > 15 ) || ( channel_input > 15 ) ) {
                return ECG2_ERROR;
            }

            if ( ECG2_CHANNEL_ENABLE == enable ) {
                tempbuff |= 1 << 7;
            } else { 
                tempbuff &= ~(1 << 7);
            } 

            tempbuff |= pga_gain << 4;
            tempbuff |= channel_input;
            ecg2_write_register( ctx, ECG2_CH7SET_REG, tempbuff );
            return ECG2_OK;
        }
        case 8: {
            if ( ( pga_gain > 15 ) || ( channel_input > 15 ) ) {
                return ECG2_ERROR;
            }

            if ( ECG2_CHANNEL_ENABLE == enable ) {
                tempbuff |= 1 << 7;
            } else { 
                tempbuff &= ~(1 << 7);
            } 

            tempbuff |= pga_gain << 4;
            tempbuff |= channel_input;
            ecg2_write_register( ctx, ECG2_CH8SET_REG, tempbuff );
            return ECG2_OK;
        }
        default: {
            return ECG2_ERROR;
        }
    }
}

void ecg2_right_leg_positive_drive_set ( ecg2_t *ctx, uint8_t data_in ) {
    ecg2_write_register( ctx, ECG2_RLD_SENSP_REG, data_in );
}

void ecg2_right_leg_negative_drive_set ( ecg2_t *ctx, uint8_t data_in ) {
    ecg2_write_register( ctx, ECG2_RLD_SENSN_REG, data_in );
}

void ecg2_lead_off_positive_channel_select ( ecg2_t *ctx, uint8_t data_in ) {
    ecg2_write_register( ctx, ECG2_LOFF_SENSP_REG, data_in );
}

void ecg2_lead_off_negative_channel_select ( ecg2_t *ctx, uint8_t data_in ) {
    ecg2_write_register( ctx, ECG2_LOFF_SENSN_REG, data_in );
}

void ecg2_lead_off_current_direction_select ( ecg2_t *ctx, uint8_t data_in ) {
    ecg2_write_register( ctx, ECG2_LOFF_FLIP_REG, data_in );
}

err_t ecg2_pace_detect_even_channels_select ( ecg2_t *ctx, uint8_t select) {
    if (select > 3) {
        return ECG2_ERROR;
    } else {
        uint8_t tempbuff = select;
        ecg2_read_register( ctx, ECG2_PACE_REG, &tempbuff );
        tempbuff &= ~(3 << 3);
        tempbuff |= select << 3;
        ecg2_write_register( ctx, ECG2_PACE_REG, tempbuff );
        return ECG2_OK;
    }
}

err_t ecg2_pace_detect_odd_channels_select ( ecg2_t *ctx, uint8_t select ) {
    if (select > 3) {
        return ECG2_ERROR;
    } else {
        uint8_t tempbuff = select;
        ecg2_read_register( ctx, ECG2_PACE_REG, &tempbuff );
        tempbuff &= ~( 3 << 1 );
        tempbuff |= select << 1;
        ecg2_write_register( ctx, ECG2_PACE_REG, tempbuff );
        return ECG2_OK;
    }
}

void ecg2_wilson_center_terminal_configure ( ecg2_t *ctx, uint16_t set ) {
    uint8_t tempbuff[2];
    tempbuff[ 0 ] = ( uint8_t ) set; // lsb
    tempbuff[ 1 ] = ( uint8_t ) (set >> 8); // msb

    ecg2_multi_write( ctx, ECG2_WCT1_REG, tempbuff, 2 );
}

uint8_t ecg2_data_ready ( ecg2_t *ctx ) {
    return digital_in_read( &ctx->drd );
}

err_t ecg2_read_data ( ecg2_t *ctx, uint8_t *data_out, uint8_t len ) {
    while ( ecg2_data_ready( ctx ) ) 
    {
        dev_read_delay( );
    }
    
    err_t error_flag = spi_master_read( &ctx->spi, data_out, len );
    return error_flag;  
}

err_t ecg2_read_channel_data ( ecg2_t *ctx, uint8_t channel, uint16_t *data_out ) {
    uint8_t rx_data[ 20 ];
    uint16_t adc_val;
    
    spi_master_select_device( ctx->chip_select );
    
    err_t error_flag = ecg2_read_data( ctx, rx_data, 20 );
    
    adc_val = rx_data[ channel + 2 ];
    adc_val <<= 8;
    adc_val |= rx_data[ channel + 3 ];
    
    *data_out = adc_val;
    return error_flag;
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void dev_hw_reset_delay ( void ) {
    Delay_1ms( );
}

void dev_read_delay ( void ) {
    Delay_1us( );
}

// ------------------------------------------------------------------------- END
