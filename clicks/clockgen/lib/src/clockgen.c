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

#include "clockgen.h"


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t get_param_shift_num ( uint8_t clk_pll );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void clockgen_cfg_setup ( clockgen_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = CLOCKGEN_SLAVE_ADDRESS;
}

CLOCKGEN_RETVAL clockgen_init ( clockgen_t *ctx, clockgen_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return CLOCKGEN_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    
    return CLOCKGEN_OK;
}

void clockgen_default_cfg ( clockgen_t *ctx )
{
    uint8_t tx_val;
    
    // Turn off
    clockgen_enable_clk( ctx, CLOCKGEN_DISABLE_ALL_CLK );
    clockgen_ctrl_clk( ctx, CLOCKGEN_CLOCK_0, 0x80 );
    clockgen_ctrl_clk( ctx, CLOCKGEN_CLOCK_1, 0x80 );
    clockgen_ctrl_clk( ctx, CLOCKGEN_CLOCK_2, 0x80 );
    clockgen_ctrl_clk( ctx, CLOCKGEN_CLOCK_3, 0x80 );
    clockgen_ctrl_clk( ctx, CLOCKGEN_CLOCK_4, 0x80 );
    clockgen_ctrl_clk( ctx, CLOCKGEN_CLOCK_5, 0x80 );
    clockgen_ctrl_clk( ctx, CLOCKGEN_CLOCK_6, 0x80 );
    clockgen_ctrl_clk( ctx, CLOCKGEN_CLOCK_7, 0x80 );
    
    tx_val = 0x0C;
    clockgen_generic_write( ctx, CLOCKGEN_REG_PLL_IN_SRC, &tx_val, 1 );

    tx_val = 0;
    clockgen_generic_write( ctx, CLOCKGEN_REG_VCXO_PARAM_B7_0, &tx_val, 1 );
    clockgen_generic_write( ctx, CLOCKGEN_REG_VCXO_PARAM_B15_8, &tx_val, 1 );
    clockgen_generic_write( ctx, CLOCKGEN_REG_VCXO_PARAM_B21_16, &tx_val, 1 );

    tx_val = CLOCKGEN_RESET_PLLA | CLOCKGEN_RESET_PLLB;
    clockgen_generic_write( ctx, CLOCKGEN_REG_PLL_RST, &tx_val, 1 );

    clockgen_set_clk_pll( ctx, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA );
    clockgen_enable_clk( ctx, CLOCKGEN_CLOCK_0 );
}

void clockgen_generic_write ( clockgen_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void clockgen_generic_read ( clockgen_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void clockgen_enable_clk ( clockgen_t *ctx, uint8_t clk_num )
{
    uint8_t temp_ctrl;
    uint8_t tx_val;
    
    
    if ( clk_num < 8 )
    {
        clockgen_generic_read( ctx, CLOCKGEN_REG_OUTPUT_ENABLE_CTRL, &temp_ctrl, 1 );
        
        tx_val = temp_ctrl & ( 0xFF ^ ( 1 << clk_num ) );
        clockgen_generic_write( ctx, CLOCKGEN_REG_OUTPUT_ENABLE_CTRL, &tx_val, 1 );
                                
        clockgen_ctrl_clk( ctx, clk_num, 0x4F );
    }
    else
    {
        tx_val = 0xFF;
        clockgen_generic_write( ctx, CLOCKGEN_REG_OUTPUT_ENABLE_CTRL, &tx_val, 1 );
    }
}

void clockgen_ctrl_clk ( clockgen_t *ctx, uint8_t clk_num, uint8_t ctrl_data )
{    
    clockgen_generic_write( ctx, ( CLOCKGEN_REG_CLK0_CTRL + clk_num ), &ctrl_data, 1 );
}

void clockgen_set_disable_state ( clockgen_t *ctx, uint8_t clk_num, uint8_t disable_state )
{
    uint8_t tx_val;
    uint8_t tx_val2;

    disable_state &= 0x3;
    tx_val = disable_state << ( CLOCKGEN_DISIABLE_STATE_SHIFT * clk_num );
    tx_val2 = disable_state << ( CLOCKGEN_DISIABLE_STATE_SHIFT * ( clk_num - 4 ) );

    switch ( clk_num )
    {
        case CLOCKGEN_CLOCK_0:
        {
            clockgen_generic_write( ctx, CLOCKGEN_REG_CLK3_0_DIS_STATE, &tx_val, 1 );
            return;
        }
        case CLOCKGEN_CLOCK_1:
        {
            clockgen_generic_write( ctx, CLOCKGEN_REG_CLK3_0_DIS_STATE, &tx_val, 1 );
            return;
        }
        case CLOCKGEN_CLOCK_2:
        {
            clockgen_generic_write( ctx, CLOCKGEN_REG_CLK3_0_DIS_STATE, &tx_val, 1 );
            return;
        }
        case CLOCKGEN_CLOCK_3:
        {
            clockgen_generic_write( ctx, CLOCKGEN_REG_CLK3_0_DIS_STATE, &tx_val, 1 );
            return;
        }
        case CLOCKGEN_CLOCK_4:
        {
            clockgen_generic_write( ctx, CLOCKGEN_REG_CLK3_0_DIS_STATE, &tx_val2, 1 );
            return;
        }
        case CLOCKGEN_CLOCK_5:
        {
            clockgen_generic_write( ctx, CLOCKGEN_REG_CLK3_0_DIS_STATE, &tx_val2, 1 );
            return;
        }
        case CLOCKGEN_CLOCK_6:
        {
            clockgen_generic_write( ctx, CLOCKGEN_REG_CLK3_0_DIS_STATE, &tx_val2, 1 );
            return;
        }
        case CLOCKGEN_CLOCK_7:
        {
            clockgen_generic_write( ctx, CLOCKGEN_REG_CLK3_0_DIS_STATE, &tx_val2, 1 );
            return;
        }
        default:
        {
            return;
        }
    }
}

void clockgen_set_clk_pll ( clockgen_t *ctx, uint8_t clk_num, uint8_t pll_sel )
{
    uint8_t temp_ctrl;

    if ( ( pll_sel != CLOCKGEN_PLLA ) || ( pll_sel != CLOCKGEN_PLLB ) )
    {
        return;
    }

    clockgen_generic_read( ctx, ( CLOCKGEN_CLK_CTRL + clk_num ), &temp_ctrl, 1 );

    temp_ctrl &= pll_sel;
    clockgen_generic_write( ctx, ( CLOCKGEN_CLK_CTRL + clk_num ), &temp_ctrl, 1 );
}

void clockgen_set_params ( clockgen_t *ctx, uint8_t clk_pll_num, clockgen_params_t *param_group )
{
    uint8_t start_adr;
    uint8_t param_buf[ CLOCKGEN_PARAMS_MACRO ];

    start_adr = get_param_shift_num( clk_pll_num );

    start_adr = CLOCKGEN_REG_MULTI_NA_PARAM3_B15_8 + ( CLOCKGEN_PARAMS_MACRO * start_adr );

    param_buf[ 0 ] = ( param_group->p3 >> 8 ) & 0xFF;
    param_buf[ 1 ] = param_group->p3 & 0xFF;
    param_buf[ 2 ] = ( param_group->div_val << 4 ) | ( param_group->div4 << 2 ) | ( ( param_group->p1 >> 16 ) & 0x3 );
    param_buf[ 3 ] = ( param_group->p1 >> 8 ) & 0xFF;
    param_buf[ 4 ] = param_group->p1 & 0xFF;
    param_buf[ 5 ] = ( ( ( param_group->p3 >> 16 ) & 0xF ) << 4 ) | ( ( param_group->p2 >> 16 ) & 0xF );
    param_buf[ 6 ] = ( param_group->p2 >> 8 ) & 0xFF;
    param_buf[ 7 ] = param_group->p2 & 0xFF;

    clockgen_generic_write( ctx, start_adr, param_buf, CLOCKGEN_PARAMS_MACRO );
}

void clockgen_get_params ( clockgen_t *ctx, uint8_t clk_pll_num, clockgen_params_t *param_group )
{
    uint8_t start_adr;
    uint8_t param_buf[ CLOCKGEN_PARAMS_MACRO ];

    start_adr = get_param_shift_num( clk_pll_num );

    start_adr = CLOCKGEN_REG_MULTI_NA_PARAM3_B15_8 + ( CLOCKGEN_PARAMS_MACRO * start_adr );

    clockgen_generic_read( ctx, start_adr, param_buf, CLOCKGEN_PARAMS_MACRO );

    param_group->p1 = ( uint32_t )( param_buf[ 2 ] & 0x3 ) << 16;
    param_group->p1 |= ( uint32_t ) param_buf[ 3 ] << 8;
    param_group->p1 |= ( uint32_t ) param_buf[ 4 ];
    param_group->p2 = ( uint32_t )( param_buf[ 5 ] & 0xF ) << 16;
    param_group->p2 |= ( uint32_t ) param_buf[ 6 ] << 8;
    param_group->p2 |= ( uint32_t ) param_buf[ 7 ];
    param_group->p3 = ( uint32_t ) ( ( param_buf[ 5 ] >> 4 ) & 0xF ) << 16;
    param_group->p3 |= ( uint32_t ) param_buf[ 0 ] << 8;
    param_group->p3 |= ( uint32_t ) param_buf[ 1 ];
    param_group->div_val = ( param_buf[ 2 ] >> 4 ) & 0x7;
    param_group->div4 = ( param_buf[ 2 ] >> 2 ) & 0x3;
}

void clockgen_set_frequency ( clockgen_t *ctx, uint8_t clk_num, uint8_t pll_num, uint32_t freq )
{
    static uint32_t divider;
    static uint32_t div_val;
    static uint32_t frequency;
    
    frequency = freq * 1000000;
    div_val = CLOCKGEN_XTAL * 36 / frequency;
    divider = 25 * div_val / 100;
    divider += div_val;
    
    ctx->denom = 1;
    clockgen_setup_pll( ctx, pll_num, 36, 0 );

    ctx->factor = CLOCKGEN_PARAM_DIV_1;
    clockgen_setup_multisyinth( ctx, clk_num, divider, 0 );
}

void clockgen_setup_pll ( clockgen_t *ctx, uint8_t pll, uint8_t mult, uint32_t num )
{
    uint8_t tx_val;
    
    clockgen_params_t param_group;

    tx_val =  CLOCKGEN_RESET_PLLA | CLOCKGEN_RESET_PLLB; 
    clockgen_generic_write( ctx, CLOCKGEN_REG_PLL_RST, &tx_val, 1 );
    
    if ( num == 0 )
    {
        param_group.p1 = 128 * mult - 512;
        param_group.p2 = num;
        param_group.p3 = ctx->denom;
    }
    else
    {
        param_group.p1 = ( uint32_t )( 128 * mult + ( 128 * ( ( float ) num / ( float ) ctx->denom ) ) - 512 );
        param_group.p2 = ( uint32_t )( 128 * num - ctx->denom * ( 128 * ( ( float ) num / ( float ) ctx->denom ) ) );
        param_group.p3 = ctx->denom;
    }

    clockgen_set_params( ctx, pll, &param_group );
}

void clockgen_setup_multisyinth ( clockgen_t *ctx, uint8_t clk_num, uint32_t divider, uint32_t num )
{
    clockgen_params_t param_group;

    param_group.div4 = 0;
    if ( ctx->factor == 4 )
    {
        param_group.div4 = CLOCKGEN_PARAM_DIV_4_EN;
        param_group.p1 = 0;
        param_group.p2 = 0;
        param_group.p3 = 1;
    }
    else if ( num == 0 )
    {
        param_group.p1 = 128 * divider - 512;
        param_group.p2 = 0;
        param_group.p3 = 1;
    }
    else
    {
        param_group.p1 = ( uint32_t )( 128 * divider + ( 128 * ( ( float ) num / ( float ) ctx->denom ) ) - 512 );
        param_group.p2 = ( uint32_t )( 128 * num - ctx->denom * ( 128 * ( ( float ) num / ( float ) ctx->denom ) ) );
        param_group.p3 = ctx->denom;
    }
    param_group.div_val = ctx->factor;


    clockgen_set_params( ctx, clk_num, &param_group );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t get_param_shift_num ( uint8_t clk_pll )
{
    switch ( clk_pll )
    {
        case CLOCKGEN_PLLA:
        {
            return 0;
        }
        case CLOCKGEN_PLLB:
        {
            return 1;
        }
        case CLOCKGEN_CLOCK_0:
        {
            return 2;
        }
        case CLOCKGEN_CLOCK_1:
        {
            return 3;
        }
        case CLOCKGEN_CLOCK_2:
        {
            return 4;
        }
        case CLOCKGEN_CLOCK_3:
        {
            return 5;
        }
        case CLOCKGEN_CLOCK_4:
        {
            return 6;
        }
        case CLOCKGEN_CLOCK_5:
        {
            return 7;
        }
        case CLOCKGEN_CLOCK_6:
        {
            return 8;
        }
        case CLOCKGEN_CLOCK_7:
        {
            return 9;
        }
        default:
        {
            return 0xFF;
        }
    }
}

// ------------------------------------------------------------------------- END

