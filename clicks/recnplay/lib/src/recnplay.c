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

#include "recnplay.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define RECNPLAY_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void recnplay_cfg_setup ( recnplay_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rdy = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000;
}

RECNPLAY_RETVAL recnplay_init ( recnplay_t *ctx, recnplay_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = RECNPLAY_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return RECNPLAY_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, RECNPLAY_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->rdy, cfg->rdy );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

	digital_out_low( &ctx->rst );

    return RECNPLAY_OK;
}

void recnplay_generic_transfer ( recnplay_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

RECNPLAY_RETVAL recplay_play_vp( recnplay_t *ctx, uint16_t index )
{
	uint8_t temp_data[ 3 ];
	uint8_t ret_val[ 3 ];

	temp_data[ 0 ] = RECPLAY_PLAY_VP;
	temp_data[ 1 ] = index >> 8;
	temp_data[ 2 ] = index;

	recnplay_generic_transfer( ctx, temp_data, 3, ret_val, 3 );

	return ret_val[ 2 ];
}

RECNPLAY_RETVAL recplay_play_vp_rn( recnplay_t *ctx, uint8_t value_rn )
{
    uint8_t temp_data[ 2 ];
    uint8_t ret_val[ 2 ];

    temp_data[ 0 ] = RECPLAY_PLAY_VP_RN;
    temp_data[ 1 ] = value_rn;

    recnplay_generic_transfer( ctx, temp_data, 2, ret_val, 2 );
    
    return ret_val[ 1 ];
}

RECNPLAY_RETVAL recplay_execute_vm ( recnplay_t* ctx, uint16_t index )
{
	uint8_t temp_data[ 3 ];
	uint8_t ret_val[ 3 ];

	temp_data[ 0 ] = RECPLAY_EXE_VM;
	temp_data[ 1 ] = index >> 8;
	temp_data[ 2 ] = index;

	recnplay_generic_transfer( ctx, temp_data, 3, ret_val, 3 );

	return ret_val[ 2 ];
}

RECNPLAY_RETVAL recplay_record_msg ( recnplay_t* ctx )
{
	uint8_t temp_data = RECPLAY_REC_MSG;
	uint8_t ret_val;

	recnplay_generic_transfer( ctx, &temp_data, 1, &ret_val, 1 );

	return ret_val;
}

RECNPLAY_RETVAL recplay_record_msg_addr ( recnplay_t* ctx, uint32_t mem_addr )
{
	uint8_t temp_data[ 4 ];
	uint8_t ret_val[ 4 ];

	temp_data[ 0 ] = RECPLAY_REC_MSG_ADDR;
	temp_data[ 1 ] = mem_addr >> 16;
	temp_data[ 2 ] = mem_addr >> 8;
	temp_data[ 3 ] = mem_addr;

	recnplay_generic_transfer( ctx, temp_data, 4, ret_val, 4 );

	return ret_val[ 3 ];
}

RECNPLAY_RETVAL recplay_play_msg ( recnplay_t* ctx, uint32_t mem_addr, uint16_t sector_offset )
{
	uint8_t temp_data[ 6 ];
	uint8_t ret_val[ 6 ];

	temp_data[ 0 ] = RECPLAY_PLAY_MSG;
	temp_data[ 1 ] = mem_addr >> 16;
	temp_data[ 2 ] = mem_addr >> 8;
	temp_data[ 3 ] = mem_addr;
	temp_data[ 4 ] = sector_offset >> 8;
	temp_data[ 5 ] = sector_offset;

	recnplay_generic_transfer( ctx, temp_data, 6, ret_val, 6 );

	return ret_val[ 5 ];
}

RECNPLAY_RETVAL recplay_play_silence ( recnplay_t* ctx, uint8_t silence_length )
{
	uint8_t temp_data[ 2 ];
	uint8_t ret_val[ 2 ];

	temp_data[ 0 ] = RECPLAY_PLAY_SIL;
	temp_data[ 1 ] = silence_length;

	recnplay_generic_transfer( ctx, temp_data, 2, ret_val, 2 );

	return ret_val[ 1 ];
}

RECNPLAY_RETVAL recplay_stop ( recnplay_t* ctx )
{
	uint8_t temp_data = RECPLAY_STOP;
	uint8_t ret_val;

	recnplay_generic_transfer( ctx, &temp_data, 1, &ret_val, 1 );

	return ret_val;
}

RECNPLAY_RETVAL recplay_erase_msg ( recnplay_t* ctx, uint32_t mem_addr )
{
	uint8_t temp_data[ 4 ];
	uint8_t ret_val[ 4 ];

	temp_data[ 0 ] = RECPLAY_ERASE_MSG;
	temp_data[ 1 ] = mem_addr >> 16;
	temp_data[ 2 ] = mem_addr >> 8;
	temp_data[ 3 ] = mem_addr;

	recnplay_generic_transfer( ctx, temp_data, 4, ret_val, 4 );

	return ret_val[ 3 ];
}

RECNPLAY_RETVAL recplay_spi_write_pcm ( recnplay_t* ctx, uint16_t* data_pcm, uint8_t num_pcm )
{
	uint8_t temp_data[ 256 ];
	uint8_t ret_val[ 256 ];
	uint8_t cnt;
	uint8_t index;
	uint8_t n_pcm = num_pcm;

	if ( n_pcm > 127 )
	{
		n_pcm = 127;
	}

	temp_data[ 0 ] = RECPLAY_SPI_PCM_WRITE;
	index = 0;

	for ( cnt = 1; cnt <= n_pcm; cnt += 2 )
	{ 
		temp_data[ cnt ] = data_pcm[ index ];
		temp_data[ cnt + 1 ] = data_pcm[ index ] >> 8;
		index++;
	}
	n_pcm = ( n_pcm * 2 ) + 1;

	recnplay_generic_transfer( ctx, temp_data, n_pcm, ret_val, n_pcm );

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_spi_read_pcm ( recnplay_t* ctx, uint16_t* data_pcm, uint8_t num_pcm )
{
	uint8_t temp_data[ 256 ] = { 0 };
	uint8_t ret_val[ 256 ];
	uint8_t cnt;
	uint8_t index;
	uint8_t n_pcm = num_pcm;

	if ( n_pcm > 127 )
	{
		n_pcm = 127;
	}

	temp_data[ 0 ] = RECPLAY_SPI_PCM_READ;
	index = 0;

	recnplay_generic_transfer( ctx, temp_data, n_pcm * 2 + 1, ret_val, n_pcm * 2 + 1 );

	for ( cnt = 1; cnt <= n_pcm; cnt += 2 )
	{
		data_pcm[ index ] = ret_val[ cnt + 1 ];
		data_pcm[ index ] <<= 8;
		data_pcm[ index ] |= ret_val[ cnt ];
		index++;	  
	}

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_spi_send_cmprsd_data ( recnplay_t* ctx, uint8_t* cmprsd_data, uint8_t n_data )
{
	uint8_t temp_data[ 256 ];
	uint8_t ret_val[ 256 ];
	uint8_t cnt;
	uint8_t num_data = n_data;

	if ( num_data > 255 )
	{
		num_data = 255;
	}

	temp_data[ 0 ] = RECPLAY_SPI_SND_DEC;

	for ( cnt = 1; cnt <= num_data; cnt++ )
	{
		temp_data[ cnt ] = cmprsd_data[ cnt - 1 ];
	}
	num_data += 1;

	recnplay_generic_transfer( ctx, temp_data, num_data, ret_val, num_data );

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_spi_receive_enc_data ( recnplay_t* ctx, uint8_t* encoded_data, uint8_t n_data )
{
	uint8_t temp_data[ 256 ] = { RECNPLAY_DUMMY };
	uint8_t ret_val[ 256 ];
	uint8_t cnt;
	uint8_t num_data = n_data;

	if ( num_data > 255 )
	{
		num_data = 255;
	}

	temp_data[ 0 ] = RECPLAY_SPI_RCV_ENC;

	recnplay_generic_transfer( ctx, temp_data, num_data + 1, ret_val, num_data + 1 );

	for ( cnt = 1; cnt <= num_data; cnt++ )
	{
		encoded_data[ cnt - 1 ] = ret_val[ cnt ];
	}

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_read_status ( recnplay_t* ctx, uint8_t* interr_status )
{
	uint8_t temp_data[ 2 ] = { RECNPLAY_DUMMY };
	uint8_t ret_val[ 2 ];

	temp_data[ 0 ] = RECPLAY_READ_STATUS;

	recnplay_generic_transfer( ctx, temp_data, 2, ret_val, 2 );

	*interr_status = ret_val[ 1 ];

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_read_interr ( recnplay_t* ctx, uint8_t* interr_status )
{
	uint8_t temp_data[ 2 ] = { RECNPLAY_DUMMY };
	uint8_t ret_val[ 2 ];

	temp_data[ 0 ] = RECPLAY_READ_INT;

	recnplay_generic_transfer( ctx, temp_data, 2, ret_val, 2 );

	*interr_status = ret_val[ 1 ];

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_read_msg_addr ( recnplay_t* ctx, uint32_t* msg_addr, uint16_t* msg_length )
{
	uint8_t temp_data[ 6 ] = { RECNPLAY_DUMMY };
	uint8_t ret_val[ 6 ];

	temp_data[ 0 ] = RECPLAY_READ_MSG_ADDR;

	recnplay_generic_transfer( ctx, temp_data, 6, ret_val, 6 );

	*msg_addr = ret_val[ 1 ];
	*msg_addr <<= 8;
	*msg_addr |= ret_val[ 2 ];
	*msg_addr <<= 8;
	*msg_addr |= ret_val[ 3 ];

	*msg_length = ret_val[ 4 ];
	*msg_length <<= 8;
	*msg_length |= ret_val[ 5 ];

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_read_msg_length ( recnplay_t* ctx, uint16_t* msg_length )
{
	uint8_t temp_data[ 3 ] = { RECNPLAY_DUMMY };
	uint8_t ret_val[ 3 ];

	temp_data[ 0 ] = RECPLAY_READ_MSG_LEN;

	recnplay_generic_transfer( ctx, temp_data, 3, ret_val, 3 );

	*msg_length = ret_val[ 1 ];
	*msg_length <<= 8;
	*msg_length |= ret_val[ 2 ];

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_read_id ( recnplay_t* ctx, recnplay_dev_id_t* dev_id_data )
{
	uint8_t temp_data[ 5 ] = { RECNPLAY_DUMMY };
	uint8_t ret_val[ 5 ];

	temp_data[ 0 ] = RECPLAY_READ_ID;

	recnplay_generic_transfer( ctx, temp_data, 5, ret_val, 5 );

	dev_id_data->part_id = ret_val[ 1 ];
	dev_id_data->man_id = ret_val[ 2 ];
	dev_id_data->mem_type = ret_val[ 3 ];
	dev_id_data->dev_id = ret_val[ 4 ];

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_dig_read ( recnplay_t* ctx, uint32_t mem_addr, uint8_t* data_out, uint8_t n_data)
{
	uint8_t temp_data[ 256 ] = { 0 };
	uint8_t ret_val[ 256 ];
	uint8_t cnt;
	uint8_t num_data = n_data;

	if ( num_data > 252 )
	{
		num_data = 252;
	}

	temp_data[ 0 ] = RECPLAY_DIG_READ;
	temp_data[ 1 ] = mem_addr >> 16;
	temp_data[ 2 ] = mem_addr >> 8;
	temp_data[ 3 ] = mem_addr;

	recnplay_generic_transfer( ctx, temp_data, num_data + 4, ret_val, num_data + 4 );

	for ( cnt = 4; cnt < num_data + 4; cnt++ )
	{
		data_out[ cnt - 4 ] = ret_val[ cnt ];
	}

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_dig_write ( recnplay_t* ctx, uint32_t mem_addr, uint8_t* data_in, uint8_t n_data )
{
	uint8_t temp_data[ 256 ] = { 0 };
	uint8_t ret_val[ 256 ];
	uint8_t cnt;
	uint8_t num_data = n_data;

	if ( num_data > 252 )
	{
		num_data = 252;
	}

	temp_data[ 0 ] = RECPLAY_DIG_WRITE;
	temp_data[ 1 ] = mem_addr >> 16;
	temp_data[ 2 ] = mem_addr >> 8;
	temp_data[ 3 ] = mem_addr;

	for ( cnt = 4; cnt < num_data + 4; cnt++ ) 
	{
		temp_data[ cnt ] = data_in[ cnt - 4 ];
	}

	recnplay_generic_transfer( ctx, temp_data, num_data + 4, ret_val, num_data + 4 );

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_erase_mem ( recnplay_t* ctx, uint32_t start_addr, uint32_t end_addr )
{
	uint8_t temp_data[ 7 ];
	uint8_t ret_val[ 7 ];

	temp_data[ 0 ] = RECPLAY_ERASE_MEM;
	temp_data[ 1 ] = start_addr >> 16;
	temp_data[ 2 ] = start_addr >> 8;
	temp_data[ 3 ] = start_addr;
	temp_data[ 4 ] = end_addr >> 16;
	temp_data[ 5 ] = end_addr >> 8;
	temp_data[ 6 ] = end_addr;

	recnplay_generic_transfer( ctx, temp_data, 7, ret_val, 7 );

	return ret_val[ 6 ];
}

RECNPLAY_RETVAL recplay_erase_chip ( recnplay_t* ctx )
{
	uint8_t temp_data[ 2 ];
	uint8_t ret_val[ 2 ];

	temp_data[ 0 ] = RECPLAY_CHIP_ERASE;
	temp_data[ 1 ] = 0x01;

	recnplay_generic_transfer( ctx, temp_data, 2, ret_val, 2 );

	return ret_val[ 1 ];
}

RECNPLAY_RETVAL recplay_pwr_up ( recnplay_t* ctx )
{
	uint8_t temp_data[ 2 ] = { RECNPLAY_DUMMY };
	uint8_t ret_val[ 2 ];

	temp_data[ 0 ] = RECPLAY_PWR_UP;


	recnplay_generic_transfer( ctx, temp_data, 2, ret_val, 2 );

	return ret_val[ 1 ];
}

RECNPLAY_RETVAL recplay_pwr_down ( recnplay_t* ctx ) 
{
	uint8_t temp_data[ 2 ] = { RECNPLAY_DUMMY };
	uint8_t ret_val[ 2 ];

	temp_data[ 0 ] = RECPLAY_PWR_DOWN;

	recnplay_generic_transfer( ctx, temp_data, 2, ret_val, 2 );

	return ret_val[ 1 ];
}

RECNPLAY_RETVAL recplay_set_clk_cnfg ( recnplay_t* ctx, uint8_t clk_cnfg )
{
	uint8_t temp_data[ 2 ];
	uint8_t ret_val[ 2 ];

	temp_data[ 0 ] = RECPLAY_SET_CLK_CFG;
	temp_data[ 1 ] = clk_cnfg;

	recnplay_generic_transfer( ctx, temp_data, 2, ret_val, 2 );

	return ret_val[ 1 ];
}

RECNPLAY_RETVAL recplay_read_clk_cnfg ( recnplay_t* ctx, uint8_t* clk_cnfg )
{
	uint8_t temp_data[ 2 ] = { RECNPLAY_DUMMY };
	uint8_t ret_val[ 2 ];

	temp_data[ 0 ] = RECPLAY_READ_CLK_CFG;

	recnplay_generic_transfer( ctx, temp_data, 2, ret_val, 2 );

	*clk_cnfg = ret_val[ 1 ];

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_write_cnfg_reg ( recnplay_t* ctx, uint8_t reg_addr, uint8_t* cnfg_data, uint8_t n_data )
{
	uint8_t temp_data[ 50 ] = { 0 };
	uint8_t ret_val[ 50 ];
	uint8_t cnt;
	uint8_t r_addr = reg_addr;
	uint8_t num_data = n_data;

	if ( r_addr > 0x2F )
	{
		r_addr = 0x2F;
	}
	if ( num_data > ( 48 - r_addr ) )
	{
		num_data = 48 - r_addr;
	}

	temp_data[ 0 ] = RECPLAY_WRITE_CFG_REG;
	temp_data[ 1 ] = r_addr;

	for ( cnt = 2; cnt < num_data + 2; cnt++ )
	{
		temp_data[ cnt ] = cnfg_data[ cnt - 2 ];
	}

	recnplay_generic_transfer( ctx, temp_data, num_data + 2, ret_val, num_data + 2 );

	return ret_val[ 0 ];
}

RECNPLAY_RETVAL recplay_read_cnfg_reg ( recnplay_t* ctx, uint8_t reg_addr, uint8_t* cnfg_data, uint8_t n_data )
{
	uint8_t temp_data[ 50 ] = { RECNPLAY_DUMMY };
	uint8_t ret_val[ 50 ];
	uint8_t cnt;
	uint8_t r_addr = reg_addr;
	uint8_t num_data = n_data;

	if ( r_addr > 0x2F )
	{
		r_addr = 0x2F;
	}
	if ( num_data > ( 48 - r_addr ) )
	{
		num_data = 48 - r_addr;
	}

	temp_data[ 0 ] = RECPLAY_READ_CFG_REG;
	temp_data[ 1 ] = r_addr;

	recnplay_generic_transfer( ctx, temp_data, num_data + 2, ret_val, num_data + 2 );

	for ( cnt = 2; cnt < num_data + 2; cnt++ )
	{
		cnfg_data[ cnt - 2 ] = ret_val[ cnt ];
	}

	return ret_val[ 0 ];
}

uint8_t recplay_check_rdy ( recnplay_t* ctx )
{
	if ( digital_in_read( &ctx->rdy ) )
	{
		return RECPLAY_SPI_RDY_PIN;
	}
	else
	{
		return RECPLAY_SPI_BSY_PIN;
	}
}

uint8_t recplay_check_int ( recnplay_t* ctx )
{
	if ( digital_in_read( &ctx->int_pin ) )
	{
		return RECPLAY_INT_NO_GEN_PIN;
	}
	else
	{
		return RECPLAY_INT_GEN_PIN;
	}
}

void recplay_reset ( recnplay_t* ctx )
{
	digital_out_high( &ctx->rst );
	Delay_ms( 100 );
	digital_out_low( &ctx->rst );
	Delay_ms( 1000 );
}

// ------------------------------------------------------------------------- END

