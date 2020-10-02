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

#include "barometer3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define BAROMETER3_DUMMY  0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void barometer3_i2c_write ( barometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void barometer3_i2c_read ( barometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void barometer3_spi_write ( barometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void barometer3_spi_read ( barometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

void dev_get_twos_comp ( int32_t *raw, uint8_t length );

uint32_t dev_busy_delay ( uint16_t mr, uint16_t osr );

void dev_failsafe_delay ( );
// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void barometer3_cfg_setup ( barometer3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x00;
    cfg->sel = BAROMETER3_MASTER_I2C;
    
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

BAROMETER3_RETVAL barometer3_init ( barometer3_t *ctx, barometer3_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == BAROMETER3_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return BAROMETER3_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = barometer3_i2c_read;
        ctx->write_f = barometer3_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;

        spi_cfg.default_write_data = BAROMETER3_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;
    
        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return BAROMETER3_INIT_ERROR;
        }
        
        spi_master_set_default_write_data( &ctx->spi, BAROMETER3_DUMMY );
        spi_master_set_speed( &ctx->spi, cfg->spi_speed );
        spi_master_set_mode( &ctx->spi, cfg->spi_mode );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        
        ctx->read_f = barometer3_spi_read;
        ctx->write_f = barometer3_spi_write;
    }

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    spi_master_deselect_device( ctx->chip_select ); 

    return BAROMETER3_OK;
}

void barometer3_generic_write ( barometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void barometer3_generic_read ( barometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t barometer3_read_byte ( barometer3_t *ctx, uint8_t reg_adr )
{
    uint8_t tx_buf[ 2 ];
    uint8_t result;
    uint8_t rx_buf[ 2 ];

    tx_buf[ 0 ] = reg_adr;

    if ( ctx->communication_interface == I2C_COMMUNICATION )
    {
        barometer3_i2c_read( ctx, reg_adr, &result, 1 );
    }
    else
    {
        tx_buf[ 0 ] |= BAROMETER3_READ_BIT_MASK;
        
        barometer3_spi_read( ctx, tx_buf[ 0 ], rx_buf, 1 );
        
        result = rx_buf[ 1 ];
    }

    return result;
}

void  barometer3_read_coeffs ( barometer3_t *ctx )
{
    uint8_t buf[ 18 ];
    int32_t tmp_coef;

    barometer3_generic_read ( ctx, BAROMETER3_COEF_C0, buf, 18 );

    tmp_coef = ( ( uint32_t )buf[ 0 ] << 4 ) | ( ( ( uint32_t )buf[ 1 ] >> 4 ) & 0x0F );
    dev_get_twos_comp( &tmp_coef, 12 );
    tmp_coef /= 2;
    ctx->coef_c0_half = tmp_coef;

    tmp_coef = ( ( ( uint32_t )buf[ 1 ] & 0x0F ) << 8 ) | ( uint32_t )buf[ 2 ];
    dev_get_twos_comp( &tmp_coef, 12 );
    ctx->coef_c1 = tmp_coef;

    tmp_coef = ( ( uint32_t )buf[ 3 ] << 12 ) | ( ( uint32_t )buf[ 4 ] << 4 ) 
               | ( ( ( uint32_t )buf[ 5 ] >> 4 ) & 0x0F );
    dev_get_twos_comp( &tmp_coef, 20 );
    ctx->coef_c00 = tmp_coef;

    tmp_coef = ( ( ( uint32_t )buf[ 5 ] & 0x0F ) << 16 ) 
               | ( ( uint32_t )buf[ 6 ] << 8 ) | ( uint32_t )buf[ 7 ];
    dev_get_twos_comp( &tmp_coef, 20 );
    ctx->coef_c10 = tmp_coef;

    tmp_coef = ( ( uint32_t )buf[ 8 ] << 8 ) | ( uint32_t )buf[ 9 ];
    dev_get_twos_comp( &tmp_coef, 16 );
    ctx->coef_c01 = tmp_coef;

    tmp_coef = ( ( uint32_t )buf[ 10 ] << 8 ) | ( uint32_t )buf[ 11 ];
    dev_get_twos_comp( &tmp_coef, 16 );
    ctx->coef_c11 = tmp_coef;

    tmp_coef = ( ( uint32_t )buf[ 12 ] << 8 ) | ( uint32_t )buf[ 13 ];
    dev_get_twos_comp( &tmp_coef, 16 );
    ctx->coef_c20 = tmp_coef;

    tmp_coef = ( ( uint32_t )buf[ 14 ] << 8 ) | ( uint32_t )buf[ 15 ];
    dev_get_twos_comp( &tmp_coef, 16 );
    ctx->coef_c21 = tmp_coef;

    tmp_coef = ( ( uint32_t )buf[ 16 ] << 8 ) | ( uint32_t )buf[ 17 ];
    dev_get_twos_comp( &tmp_coef, 16 );
    ctx->coef_c30 = tmp_coef;
}

void barometer3_set_op_mode ( barometer3_t *ctx, uint8_t op_mode )
{
    barometer3_generic_write( ctx, BAROMETER3_MEAS_CFG, &op_mode, 1 );
    ctx->cfg_op_mode = op_mode;
}

void barometer3_flush_fifo ( barometer3_t *ctx )
{
    uint8_t buf = BAROMETER3_FIFO_FLUSH;
    barometer3_generic_write( ctx, BAROMETER3_RESET, &buf, 1 );
}

void barometer3_disable_fifo ( barometer3_t *ctx )
{
    uint8_t buf;
    barometer3_flush_fifo( ctx );
    barometer3_generic_read( ctx, BAROMETER3_CFG_REG, &buf, 1 );
    buf &= ~BAROMETER3_FIFO_EN;
    barometer3_generic_write( ctx, BAROMETER3_CFG_REG, &buf, 1 );
}

void barometer3_standby ( barometer3_t *ctx )
{
    barometer3_set_op_mode( ctx, BAROMETER3_MEAS_CTRL_IDLE );

    barometer3_disable_fifo( ctx );
    ctx->cfg_op_mode = BAROMETER3_MEAS_CTRL_IDLE;
}

void barometer3_cfg_temp ( barometer3_t *ctx, uint8_t temp_mr, uint8_t temp_osr )
{
    uint8_t buf = 0;
    uint8_t sensor = 0;

    temp_mr &= 0x70;
    temp_osr &= 0x07;
    sensor = ctx->cfg_temp_sens;
    sensor &= 0x80;
    buf = temp_mr | temp_osr | sensor;

    barometer3_generic_write ( ctx, BAROMETER3_TMP_CFG, &buf, 1 );

    if ( temp_osr > BAROMETER3_TMP_PRC_8 )
    {
        buf |= BAROMETER3_T_SHIFT;
        barometer3_generic_write( ctx, BAROMETER3_CFG_REG, &buf, 1 );
    }
    else
    {
        buf &= ~BAROMETER3_T_SHIFT;
        barometer3_generic_write( ctx, BAROMETER3_CFG_REG, &buf, 1 );
    }

    ctx->cfg_temp_mr = temp_mr;
    ctx->cfg_temp_osr = temp_osr;
}

void  barometer3_cfg_pres ( barometer3_t *ctx, uint8_t prs_mr, uint8_t prs_osr )
{
    uint8_t buf = 0;

    prs_mr &= 0x70;
    prs_osr &= 0x07;
    buf = prs_mr | prs_osr;

    barometer3_generic_write ( ctx, BAROMETER3_PRS_CFG, &buf, 1 );

    if ( prs_osr > BAROMETER3_PM_PRC_8 )
    {
        buf |= BAROMETER3_P_SHIFT;
        barometer3_generic_write( ctx, BAROMETER3_CFG_REG, &buf, 1 );
    }
    else
    {
        buf &= ~BAROMETER3_P_SHIFT;
        barometer3_generic_write( ctx, BAROMETER3_CFG_REG, &buf, 1 );
    }

    ctx->cfg_prs_mr = prs_mr;
    ctx->cfg_prs_osr = prs_osr;
}

uint8_t barometer3_st_meas_temp_once ( barometer3_t *ctx, uint8_t temp_osr )
{
    if ( temp_osr != ctx->cfg_temp_osr )
    {
        barometer3_cfg_temp( ctx, ctx->cfg_temp_mr, temp_osr );
    }

    barometer3_set_op_mode( ctx, BAROMETER3_MEAS_CTRL_CMD_TM );

    return BAROMETER3_SUCCESS;
}

uint8_t barometer3_st_meas_pres_once ( barometer3_t *ctx, uint8_t prs_osr )
{
    if ( prs_osr != ctx->cfg_prs_osr )
    {
        barometer3_cfg_pres( ctx, ctx->cfg_prs_mr, prs_osr );
    }

    barometer3_set_op_mode( ctx, BAROMETER3_MEAS_CTRL_CMD_PM );

    return BAROMETER3_SUCCESS;
}

void  barometer3_get_raw_res ( barometer3_t *ctx, uint8_t reg_adr, int32_t *raw )
{
    uint8_t buf[ 3 ];
    int32_t raw_tmp;

    barometer3_generic_read( ctx, reg_adr, buf, 3 );

    raw_tmp = buf[ 0 ];
    raw_tmp <<= 8;
    raw_tmp |= buf[ 1 ];
    raw_tmp <<= 8;
    raw_tmp |= buf[ 2 ];

    dev_get_twos_comp( &raw_tmp, 24 );
    *raw = raw_tmp;
}

float barometer3_calc_temp ( barometer3_t *ctx, int32_t raw )
{
    uint32_t tmp_scl_fct = 0;
    float temp = 0.0;

    switch ( ctx->cfg_temp_osr )
    {
        case BAROMETER3_TMP_PRC_1:
        {
            tmp_scl_fct = BAROMETER3_SCALE_FCTR_OSR_1;
        }
        case BAROMETER3_TMP_PRC_2:
        {
            tmp_scl_fct = BAROMETER3_SCALE_FCTR_OSR_2;
        }
        case BAROMETER3_TMP_PRC_4:
        {
            tmp_scl_fct = BAROMETER3_SCALE_FCTR_OSR_4;
        }
        case BAROMETER3_TMP_PRC_8:
        {
            tmp_scl_fct = BAROMETER3_SCALE_FCTR_OSR_8;
        }
        case BAROMETER3_TMP_PRC_16:
        {
            tmp_scl_fct = BAROMETER3_SCALE_FCTR_OSR_16;
        }
        case BAROMETER3_TMP_PRC_32:
        {
            tmp_scl_fct = BAROMETER3_SCALE_FCTR_OSR_32;
        }
        case BAROMETER3_TMP_PRC_64:
        {
            tmp_scl_fct = BAROMETER3_SCALE_FCTR_OSR_64;
        }
        case BAROMETER3_TMP_PRC_128:
        {
            tmp_scl_fct = BAROMETER3_SCALE_FCTR_OSR_128;
        }
        default:
        {
            break;
        }
    }

    temp = ( float ) ( ( ( float ) raw ) / ( ( float ) tmp_scl_fct ) );

    ctx->coef_temp_scal = temp;

    temp = ctx->coef_c0_half + ctx->coef_c1 * temp;

    return temp;
}

float barometer3_calc_pres ( barometer3_t *ctx, int32_t raw )
{
    uint32_t prs_scl_fct;
    float prs = 0.0;

    switch ( ctx->cfg_temp_osr )
    {
        case BAROMETER3_PM_PRC_1:
        {
            prs_scl_fct = BAROMETER3_SCALE_FCTR_OSR_1;
        }
        case BAROMETER3_PM_PRC_2:
        {
            prs_scl_fct = BAROMETER3_SCALE_FCTR_OSR_2;
        }
        case BAROMETER3_PM_PRC_4:
        {
            prs_scl_fct = BAROMETER3_SCALE_FCTR_OSR_4;
        }
        case BAROMETER3_PM_PRC_8:
        {
            prs_scl_fct = BAROMETER3_SCALE_FCTR_OSR_8;
        }
        case BAROMETER3_PM_PRC_16:
        {
            prs_scl_fct = BAROMETER3_SCALE_FCTR_OSR_16;
        }
        case BAROMETER3_PM_PRC_32:
        {
            prs_scl_fct = BAROMETER3_SCALE_FCTR_OSR_32;
        }
        case BAROMETER3_PM_PRC_64:
        {
            prs_scl_fct = BAROMETER3_SCALE_FCTR_OSR_64;
        }
        case BAROMETER3_PM_PRC_128:
        {
            prs_scl_fct = BAROMETER3_SCALE_FCTR_OSR_128;
        }
        default:
        {
            break;
        }
    }
    
    prs = ( float ) ( ( ( float ) raw ) / ( ( float ) prs_scl_fct ) );

    prs = ctx->coef_c00 + prs * ( ctx->coef_c10 + prs * ( ctx->coef_c20 + prs * ctx->coef_c30 ) )
    + ctx->coef_temp_scal * ( ctx->coef_c01 + prs * ( ctx->coef_c11 + prs * ctx->coef_c21 ) );

    return prs;
}

uint8_t barometer3_get_single_res ( barometer3_t *ctx, float *result )
{
    uint8_t rdy = 0;
    int32_t raw_val = 0;
    uint8_t old_mode = 0;

    switch ( ctx->cfg_op_mode )
    {
        case BAROMETER3_MEAS_CTRL_CMD_TM:
        {
            barometer3_generic_read ( ctx, BAROMETER3_MEAS_CFG, &rdy, 1 );
            rdy &= BAROMETER3_TMP_RDY;
            break;
        }
        case BAROMETER3_MEAS_CTRL_CMD_PM:
        {
            barometer3_generic_read ( ctx, BAROMETER3_MEAS_CFG, &rdy, 1 );
            rdy &= BAROMETER3_PRS_RDY;
            break;
        }
        default:
        {
            return BAROMETER3_BUSY;
        }
    }

    if ( rdy == 0 )
    {
        return BAROMETER3_FAIL;
    }
    else
    {
        old_mode = ctx->cfg_op_mode;
        ctx->cfg_op_mode = BAROMETER3_MEAS_CTRL_IDLE;

        switch ( old_mode )
        {
            case BAROMETER3_MEAS_CTRL_CMD_TM:
            {
                barometer3_get_raw_res( ctx, BAROMETER3_TMP_B2, &raw_val );
                *result = barometer3_calc_temp( ctx, raw_val );
                return BAROMETER3_SUCCESS;
            }
            case BAROMETER3_MEAS_CTRL_CMD_PM:
            {
                barometer3_get_raw_res( ctx, BAROMETER3_PSR_B2, &raw_val );
                *result = barometer3_calc_pres( ctx, raw_val );
                return BAROMETER3_SUCCESS;
            }
            default:
            {
                return BAROMETER3_FAIL;
            }
        }
    }
    return BAROMETER3_FAIL;
}

uint8_t barometer3_meas_temp_once ( barometer3_t *ctx, float *result, uint8_t temp_osr )
{
    uint8_t ret = 0;

    ret = barometer3_st_meas_temp_once( ctx, temp_osr );

    if ( ret != 0 )
    {
        barometer3_standby( ctx );
        return ret;
    }
    
    dev_busy_delay( ctx->cfg_temp_mr, ctx->cfg_temp_osr );
    dev_failsafe_delay( );
    
    ret = barometer3_get_single_res( ctx, result );
    if (ret != 0 )
    {
        barometer3_standby( ctx );
        return ret;
    }
    barometer3_standby( ctx );
    return BAROMETER3_SUCCESS;
}

uint8_t barometer3_meas_prs_once ( barometer3_t *ctx, float *result, uint8_t prs_osr )
{
    uint8_t ret;

    ret = barometer3_st_meas_pres_once( ctx, prs_osr );
    if ( ret != BAROMETER3_SUCCESS )
    {
        return ret;
    }

    dev_busy_delay( ctx->cfg_prs_mr, ctx->cfg_prs_osr );
    dev_failsafe_delay( );

    ret = barometer3_get_single_res( ctx, result );
    if ( ret != BAROMETER3_SUCCESS )
    {
        barometer3_standby( ctx );
        return ret;
    }
    barometer3_standby( ctx );
    
    return BAROMETER3_SUCCESS;
}

void barometer3_def_cfg ( barometer3_t *ctx )
{
    uint8_t sensor;
    float trash;

    barometer3_generic_read( ctx, BAROMETER3_COEF_SRCE, &sensor, 1 );
    sensor &= BAROMETER3_TMP_COEF_SRCE;
    ctx->cfg_temp_sens = sensor;

    barometer3_read_coeffs( ctx );

    barometer3_standby( ctx );

    barometer3_cfg_temp( ctx, BAROMETER3_TMP_RATE_1, BAROMETER3_TMP_PRC_8 );
    barometer3_cfg_pres( ctx, BAROMETER3_PM_RATE_1, BAROMETER3_PM_PRC_8 );

    barometer3_meas_temp_once( ctx, &trash, BAROMETER3_TMP_PRC_128 );

    barometer3_standby( ctx );

    barometer3_meas_temp_once( ctx, &trash, BAROMETER3_TMP_PRC_128 );
    barometer3_standby( ctx );
}

uint8_t barometer3_get_fifo_val ( barometer3_t *ctx, int32_t *value )
{
    uint8_t buf[ 3 ];
    int32_t tmp;

    barometer3_generic_read ( ctx, BAROMETER3_PSR_B2, buf, 3 );

    tmp = buf[ 0 ];
    tmp <<= 8;
    tmp |= buf[ 1 ];
    tmp <<= 8;
    tmp |= buf[ 2 ];

    dev_get_twos_comp( &tmp, 24 );
    *value = tmp;

    return ( buf[ 2 ] & 0x01 );
}

uint8_t barometer3_get_cont_res ( barometer3_t *ctx, float *temp_buf, float *prs_buf )
{
    int32_t raw_result = 0;
    float result = 0.0;
    uint8_t type = 0;
    uint8_t temp_cnt = 3;
    uint8_t prs_cnt = 0;

    if ( ( ctx->cfg_op_mode & 0x04 ) == 0 )
    {
        return BAROMETER3_BUSY;
    }

    while ( ( barometer3_read_byte( ctx, BAROMETER3_FIFO_STS ) & 
              BAROMETER3_FIFO_EMPTY ) == 0 )
    {
        type = barometer3_get_fifo_val( ctx, &raw_result );
        switch ( type )
        {
            case 0:
            {
                if ( temp_cnt < BAROMETER3_FIFO_SIZE )
                {
                    result = barometer3_calc_temp( ctx, raw_result );
                    temp_buf[ temp_cnt++ ] = result;
                }
                break;
            }
            case 1:
            {
                if ( prs_cnt < BAROMETER3_FIFO_SIZE )
                {
                    result = barometer3_calc_pres( ctx, raw_result );
                    prs_buf[ prs_cnt++ ] = result;
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
    return BAROMETER3_SUCCESS;
}

uint8_t barometer3_check_int ( barometer3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void barometer3_i2c_write ( barometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }

    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
}

static void barometer3_i2c_read ( barometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void barometer3_spi_write ( barometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );   
}

static void barometer3_spi_read ( barometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );  

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt + 1];
    }
}

void dev_get_twos_comp ( int32_t *raw, uint8_t length )
{
    if ( *raw & ( ( uint32_t )1 << ( length - 1 ) ) )
    {
        *raw -= (uint32_t)1 << length;
    }
}

uint32_t dev_busy_delay ( uint16_t mr, uint16_t osr )
{
    uint32_t del_time;
    uint32_t del_cnt;
    
    del_time = ( ( ( uint32_t )20 << mr ) + ( ( uint32_t )16 << ( osr + mr ) ) ) / 10;
    for ( del_cnt = 0; del_cnt < del_time; del_cnt++ )
    {
        Delay_1ms( );
    }
    return del_time;
}

void dev_failsafe_delay ( )
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END

