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
 * @file temphum16.c
 * @brief Temp&Hum 16 Click Driver.
 */

#include "temphum16.h"

// ------------------------------------------------------------- PRIVATE MACROS 

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                             0x00

/**
 * @brief Auto-increment and SPI serial interface SPI R/W bit.
 * @details Definition of auto-increment and SPI serial interface READ/WRITE bit.
 */
#define I2C_AUTO_INCREMENT_RW_BIT         0x80
#define SPI_WRITE_BIT                     0x7F
#define SPI_READ_BIT                      0x80

/**
 * @brief Configuration bit masks.
 * @details Definition of configuration bit masks.
 */
#define CONTINUOUS_MODE_BIT_MASK          0x80
#define BDU_CONTINUOUS_UPDATE_BIT_MASK    0xFB
#define ODR_BIT_MASK                      0x03
#define HEATER_BIT_MASK                   0x02
#define DATA_READY_INTERRUPT_BIT_MASK     0x04

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Temp&Hum 16 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t temphum16_i2c_write ( temphum16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Temp&Hum 16 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t temphum16_i2c_read ( temphum16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Temp&Hum 16 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t temphum16_spi_write ( temphum16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Temp&Hum 16 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t temphum16_spi_read ( temphum16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Temp&Hum 16 read the raw humidity output function.
 * @details This function reads the raw humidity output 
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @return raw humidity output data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static uint16_t temphum16_get_h_t_out ( temphum16_t *ctx );

/**
 * @brief Temp&Hum 16 read the h0_rh calibration function.
 * @details This function reads the h0_rh calibration output data
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @return h0_rh calibration data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static uint16_t temphum16_get_h0_rh ( temphum16_t *ctx );

/**
 * @brief Temp&Hum 16 read the h1_rh calibration function.
 * @details This function reads the h1_rh calibration output data
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @return h1_rh calibration data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static uint16_t temphum16_get_h1_rh ( temphum16_t *ctx );

/**
 * @brief Temp&Hum 16 read the h0_t0_out calibration function.
 * @details This function reads the h0_t0_out calibration output data
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @return h0_t0_out calibration data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static uint16_t temphum16_get_h0_t0_out ( temphum16_t *ctx );

/**
 * @brief Temp&Hum 16 read the h1_t0_out calibration function.
 * @details This function reads the h1_t0_out calibration output data
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @return h1_t0_out calibration data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static uint16_t temphum16_get_h1_t0_out ( temphum16_t *ctx );

/**
 * @brief Temp&Hum 16 read the t0_out calibration function.
 * @details This function reads the t0_out calibration data
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @return t0_out calibration output data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static uint16_t temphum16_get_t0_out ( temphum16_t *ctx );

/**
 * @brief Temp&Hum 16 read the t1_out calibration function.
 * @details This function reads the t1_out calibration data
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @return t1_out calibration output data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static uint16_t temphum16_get_t1_out ( temphum16_t *ctx );

/**
 * @brief Temp&Hum 16 read the raw temperature output function.
 * @details This function reads the raw temperature output data
 * of the Humidity sensor with integrated Temperature sensor WSEN-HIDS 
 * on the Temp&Hum 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #temphum16_t object definition for detailed explanation.
 * @return Temperature output data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static uint16_t temphum16_get_t_out ( temphum16_t *ctx );

/**
 * @brief Temp&Hum 16 reset delay function.
 * @details Reset delay for 100 milliseconds.
 * @return Nothing.
 * 
 * @note None.
 */
static void dev_cfg_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum16_cfg_setup ( temphum16_cfg_t *cfg ) {
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM16_SET_DEV_ADDR;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = TEMPHUM16_DRV_SEL_I2C;
}

void temphum16_drv_interface_selection ( temphum16_cfg_t *cfg, temphum16_drv_t drv_sel ) {
    cfg->drv_sel = drv_sel;
}

err_t temphum16_init ( temphum16_t *ctx, temphum16_cfg_t *cfg ) {
    ctx->drv_sel = cfg->drv_sel;

    if ( ctx->drv_sel == TEMPHUM16_DRV_SEL_I2C ) {
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

        ctx->read_f  = temphum16_i2c_read;
        ctx->write_f = temphum16_i2c_write;
    } else {
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

        ctx->read_f  = temphum16_spi_read;
        ctx->write_f = temphum16_spi_write;
    }

    digital_in_init( &ctx->rdy, cfg->rdy );

    return TEMPHUM16_OK;
}

err_t temphum16_default_cfg ( temphum16_t *ctx ) {
    temphum16_power_mode( ctx, TEMPHUM16_PWR_MODE_CONTINUOUS );
    dev_cfg_delay( );
      
    temphum16_bdu_mode( ctx, TEMPHUM16_BDU_NOT_UPDAT_UNTIL_READ );
    dev_cfg_delay( );
      
    temphum16_set_odr( ctx, TEMPHUM16_ODR_1_Hz );
    dev_cfg_delay( );

    temphum16_enable_data_ready_interrupt( ctx );
    dev_cfg_delay( );
    
    return TEMPHUM16_OK;
}

err_t temphum16_generic_write ( temphum16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t temphum16_generic_read ( temphum16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t temphum16_get_device_id ( temphum16_t *ctx, uint8_t *device_id ) {
    err_t err_flag = temphum16_generic_read( ctx, TEMPHUM16_REG_DEVICE_ID, device_id, 1 );
    return err_flag;
}

err_t temphum16_power_mode ( temphum16_t *ctx, uint8_t pwr_mode ) {
    uint8_t buf[ 1 ];
    
    err_t err_flag = temphum16_generic_read( ctx, TEMPHUM16_REG_CTRL_1, buf, 1 );
    
    if ( pwr_mode == TEMPHUM16_PWR_MODE_POWER_DOWN ) {
        buf[ 0 ] &= ~CONTINUOUS_MODE_BIT_MASK;    
    } else if ( pwr_mode == TEMPHUM16_PWR_MODE_CONTINUOUS ) {
        buf[ 0 ] |= CONTINUOUS_MODE_BIT_MASK;    
    } else {
        err_flag = TEMPHUM16_ERROR;    
    }
    
    err_flag = temphum16_generic_write( ctx, TEMPHUM16_REG_CTRL_1, buf, 1 );
    
    return err_flag;
}

err_t temphum16_bdu_mode ( temphum16_t *ctx, uint8_t bdu_mode ) {
    uint8_t buf[ 1 ];
    
    err_t err_flag = temphum16_generic_read( ctx, TEMPHUM16_REG_CTRL_1, buf, 1 );
    
    if ( bdu_mode == TEMPHUM16_BDU_CONTINUOUS_UPDATE ) {
        buf[ 0 ] &= BDU_CONTINUOUS_UPDATE_BIT_MASK;    
    } else if ( bdu_mode == TEMPHUM16_BDU_NOT_UPDAT_UNTIL_READ ) {
        buf[ 0 ] |= ~BDU_CONTINUOUS_UPDATE_BIT_MASK;    
    }
    
    err_flag = temphum16_generic_write( ctx, TEMPHUM16_REG_CTRL_1, buf, 1 );
    
    return err_flag;
}

err_t temphum16_set_odr ( temphum16_t *ctx, uint8_t odr ) {
    uint8_t buf[ 1 ];
    
    err_t err_flag = temphum16_generic_read( ctx, TEMPHUM16_REG_CTRL_1, buf, 1 );
    
    odr &= ODR_BIT_MASK;
    buf[ 0 ] |= odr; 
    
    err_flag = temphum16_generic_write( ctx, TEMPHUM16_REG_CTRL_1, buf, 1 );
    
    return err_flag;
}

err_t temphum16_heater ( temphum16_t *ctx, uint8_t heater_mode ) {
    uint8_t buf[ 1 ];
    
    err_t err_flag = temphum16_generic_read( ctx, TEMPHUM16_REG_CTRL_2, buf, 1 );
    
    if ( heater_mode == TEMPHUM16_HEATER_DISABLE ) {
        buf[ 0 ] &= ~HEATER_BIT_MASK;    
    } else if ( heater_mode == TEMPHUM16_HEATER_ENABLE ) {
        buf[ 0 ] |= HEATER_BIT_MASK;    
    }
    
    err_flag = temphum16_generic_write( ctx, TEMPHUM16_REG_CTRL_2, buf, 1 );
    
    return err_flag;
}

err_t temphum16_enable_data_ready_interrupt ( temphum16_t *ctx ) {
    uint8_t tx_buf[ 1 ];
    
    tx_buf[ 0 ] = DATA_READY_INTERRUPT_BIT_MASK;
    
    err_t err_flag = temphum16_generic_write( ctx, TEMPHUM16_REG_CTRL_3, tx_buf, 1 );
    
    return err_flag;
}

err_t temphum16_get_status ( temphum16_t *ctx, uint8_t *status ) {
    err_t err_flag = temphum16_generic_read( ctx, TEMPHUM16_REG_CTRL_2, status, 1 );
    
    return err_flag;
}

uint8_t temphum16_check_ready ( temphum16_t *ctx ) {
    return digital_in_read( &ctx->rdy );
}

err_t temphum16_get_humidity ( temphum16_t *ctx, float *humidity ) {
    int16_t h0_t0_out;
    int16_t h1_t0_out;
    int16_t h_t_out;
    uint16_t h0_rh;
    uint16_t h1_rh;
    float h_temp;
    float hum;
   
    h_temp = 0.0;
    hum = 0.0;

    h_t_out = temphum16_get_h_t_out( ctx );
    h0_rh = temphum16_get_h0_rh( ctx );
    h0_rh >>=  1;
    h1_rh = temphum16_get_h1_rh( ctx );
    h1_rh >>= 1;
    
    hum = ( float ) ( h1_rh - h0_rh );
    h0_t0_out = ( int16_t ) temphum16_get_h0_t0_out( ctx );
    h1_t0_out = ( int16_t ) temphum16_get_h1_t0_out( ctx );
    
    h_temp = ( float ) h_t_out;
    h_temp -= ( float ) h0_t0_out;
    h_temp *= hum;
    h_temp /= ( float ) ( h1_t0_out - h0_t0_out );
    hum = ( float ) h0_rh;
    
    *humidity = hum + h_temp;

    return TEMPHUM16_OK;
}

err_t temphum16_get_temperature ( temphum16_t *ctx, float *temperature ) {
    int16_t t0_out;
    int16_t t1_out;
    int16_t t_out;
    uint16_t t0_degc_x8_u16;
    uint16_t t1_degc_x8_u16;
    int16_t t0_degc, t1_degc;
    uint8_t rx_buf;
    uint8_t tmp; 
    float t_temp;
    float deg;
    
    t_temp = 0.0;
    deg = 0.0;
    
    temphum16_generic_read( ctx, TEMPHUM16_REG_T0_T1_DEGC_H2, &tmp, 1 );
    temphum16_generic_read( ctx, TEMPHUM16_REG_T0_DEGC_X8, &rx_buf, 1 );
    
    t0_degc_x8_u16 = ( ( ( uint16_t ) ( tmp & 0x03 ) ) << 8 ) | ( ( uint16_t ) rx_buf );
    t0_degc = ( int16_t ) ( t0_degc_x8_u16 >> 3 );
    
    temphum16_generic_read( ctx, TEMPHUM16_REG_T1_DEGC_X8, &rx_buf, 1 );
    
    t1_degc_x8_u16 = ( ( ( uint16_t ) ( tmp & 0x0C ) ) << 6 ) | ( ( uint16_t ) rx_buf );
    t1_degc = ( int16_t ) ( t1_degc_x8_u16 >> 3 );
    t0_out = ( int16_t ) temphum16_get_t0_out( ctx );
    t1_out = ( int16_t ) temphum16_get_t1_out( ctx );
    t_out = ( int16_t ) temphum16_get_t_out( ctx );
    deg = ( float ) ( t1_degc - t0_degc );
    t_temp = ( float )( ( t_out - t0_out ) * deg) / ( float ) (t1_out - t0_out);
    deg = ( float ) t0_degc ;
    
    *temperature = deg + t_temp;
    
    return TEMPHUM16_OK;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static err_t temphum16_i2c_write ( temphum16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    if ( len > 1 ) {
        tx_buf[ 0 ] |= I2C_AUTO_INCREMENT_RW_BIT;   
    }

    for ( cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t temphum16_i2c_read ( temphum16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    if ( len > 1 ) {
        reg |= I2C_AUTO_INCREMENT_RW_BIT;   
    }
    
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t temphum16_spi_write ( temphum16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] &= SPI_WRITE_BIT;
    for ( cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );
Delay_1ms( );
    return error_flag;
}

static err_t temphum16_spi_read ( temphum16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    reg |= SPI_READ_BIT; 
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
Delay_10ms( );
    return error_flag;
}

static uint16_t temphum16_get_h_t_out ( temphum16_t *ctx ) {
    uint8_t rx_buf[ 2 ];
    uint16_t h_t_out = 0;
    
    temphum16_generic_read( ctx, TEMPHUM16_REG_H_OUT_H, rx_buf, 1 );

    h_t_out = rx_buf[ 0 ];
    h_t_out <<= 8;
    
    temphum16_generic_read( ctx, TEMPHUM16_REG_H_OUT_L, rx_buf, 1 );
    h_t_out |= rx_buf[ 0 ];

   return h_t_out;
}

static uint16_t temphum16_get_h0_rh ( temphum16_t *ctx ) {
    uint16_t h0_rh = 0;
    uint8_t rx_buf[ 1 ];
    
    temphum16_generic_read( ctx, TEMPHUM16_REG_H0_RH_X2, rx_buf, 1 );
    
    h0_rh = ( uint16_t ) rx_buf[ 0 ];
    
    return h0_rh;
}

static uint16_t temphum16_get_h1_rh ( temphum16_t *ctx ) {
    uint16_t h1_rh = 0;
    uint8_t rx_buf[ 1 ];

    temphum16_generic_read( ctx, TEMPHUM16_REG_H1_RH_X2, rx_buf, 1 );
    
    h1_rh = ( uint16_t ) rx_buf[ 0 ];

    return h1_rh;
}

static uint16_t temphum16_get_h0_t0_out ( temphum16_t *ctx ) {
    uint8_t rx_buf[ 2 ];
    uint16_t h0_t0_out = 0;
    
    temphum16_generic_read( ctx, TEMPHUM16_REG_H0_T0_OUT_H, rx_buf, 1 );

    h0_t0_out = rx_buf[ 0 ];
    h0_t0_out <<= 8;
    
    temphum16_generic_read( ctx, TEMPHUM16_REG_H0_T0_OUT_L, rx_buf, 1 );
    h0_t0_out |= rx_buf[ 0 ];

    return h0_t0_out;
}

static uint16_t temphum16_get_h1_t0_out ( temphum16_t *ctx ) {
    uint8_t rx_buf[ 2 ];
    uint16_t h1_t0_out = 0;
    
    temphum16_generic_read( ctx, TEMPHUM16_REG_H1_T0_OUT_H, rx_buf, 1 );

    h1_t0_out = rx_buf[ 0 ];
    h1_t0_out <<= 8;
    
    temphum16_generic_read( ctx, TEMPHUM16_REG_H1_T0_OUT_L, rx_buf, 1 );
    h1_t0_out |= rx_buf[ 0 ];
    
    return h1_t0_out;
}

static uint16_t temphum16_get_t0_out ( temphum16_t *ctx ) {
    uint8_t buffer;
    uint16_t t0_out = 0;
    
    temphum16_generic_read( ctx, TEMPHUM16_REG_T0_OUT_H, &buffer, 1 );

    t0_out = ((uint16_t)buffer) << 8;

    temphum16_generic_read( ctx, TEMPHUM16_REG_T0_OUT_L, &buffer, 1 );

    t0_out |= buffer;

    return t0_out;
}

static uint16_t temphum16_get_t1_out ( temphum16_t *ctx ) {
    uint8_t buffer;
    uint16_t t1_out = 0;
    
    temphum16_generic_read( ctx, TEMPHUM16_REG_T1_OUT_H, &buffer, 1 );
    t1_out = ((uint16_t)buffer) << 8;

    temphum16_generic_read( ctx, TEMPHUM16_REG_T1_OUT_L, &buffer, 1 );
    t1_out |= buffer;

    return t1_out;
}

static uint16_t temphum16_get_t_out ( temphum16_t *ctx )
{
    uint8_t buffer;
    uint16_t t_out = 0;
    
    temphum16_generic_read( ctx, TEMPHUM16_REG_T_OUT_H, &buffer, 1 );

    t_out = ( uint16_t ) buffer << 8;

    temphum16_generic_read( ctx, TEMPHUM16_REG_T_OUT_L, &buffer, 1 );

    t_out |= buffer;

    return t_out;
}

static void dev_cfg_delay( void ) {
    Delay_100ms( );
}

// ------------------------------------------------------------------------ END
