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

#include "osd.h"
#include "resources.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define OSD_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void osd_cfg_setup ( osd_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->los = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->hsy = HAL_PIN_NC;
    cfg->vsy = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t osd_init  ( osd_t *ctx, osd_cfg_t *cfg )
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, OSD_DUMMY ) ) 
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

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    // Output pins 
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins
    digital_in_init( &ctx->los, cfg->los );
    digital_in_init( &ctx->hsy, cfg->hsy );
    digital_in_init( &ctx->vsy, cfg->vsy );

    return OSD_OK;
}

void osd_default_cfg  ( osd_t *ctx )
{
    uint8_t r_buffer;
    
    osd_write_byte( ctx, OSD_VM0_REG, 0x4C );
    r_buffer  = osd_read_byte( ctx, OSD_OSDBL_REG );
    r_buffer &= 0xEF;
    osd_write_byte( ctx, OSD_OSDBL_REG, r_buffer );
    osd_write_byte( ctx, OSD_DMM_REG, 0x04 );
    osd_write_byte( ctx, OSD_HOS_REG, 0x26 );
}

void osd_write_byte  ( osd_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 2 ];
    
    w_buffer[ 0 ] = reg_address;
    w_buffer[ 0 ] &= OSD_WRITE_CMD;
    w_buffer[ 1 ] = write_data;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, w_buffer, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

uint8_t osd_read_byte ( osd_t *ctx, uint8_t reg_address )
{
    uint8_t w_buffer[ 1 ];
    uint8_t r_buffer[ 1 ];

    w_buffer[ 0 ] = reg_address;
    w_buffer[ 0 ] |= OSD_READ_CMD;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, w_buffer, 1, r_buffer, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return r_buffer[ 0 ];
}

void osd_hw_reset ( osd_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_10ms();
    digital_out_high ( &ctx->rst );
    Delay_10ms();
}

void osd_enable ( osd_t *ctx )
{
    uint8_t tmp;

    tmp  = osd_read_byte( ctx, OSD_VM0_REG );
    tmp |= 0x08;
    osd_write_byte( ctx, OSD_VM0_REG, tmp );
}

void osd_disable ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_VM0_REG );
    tmp &= 0xF7;
    osd_write_byte( ctx, OSD_VM0_REG, tmp );
}


void osd_write_character ( osd_t *ctx, uint8_t line_pos, uint8_t row_pos, uint8_t symbol )
{
    uint8_t position;
    uint16_t tmp;
    
    tmp = line_pos * 30 + row_pos;
    
    if ( tmp < 256 )
    {
        osd_write_byte( ctx, OSD_DMAH_REG, 0x00 );
        Delay_1ms();
    }
    else
    {
        osd_write_byte( ctx, OSD_DMAH_REG, 0x01 );
        Delay_1ms();
    }
    
    position = ( uint8_t ) tmp;

    osd_write_byte( ctx, 0x06, position );
    osd_write_byte( ctx, 0x07, osd_chr[ symbol ] );
}

void osd_insert_custom_char ( osd_t *ctx, uint8_t chr_address, uint8_t custom_char )
{
    uint8_t tmp;
    uint8_t cnt;
  
    osd_disable( ctx );

    osd_write_byte( ctx, 0x09, chr_address );
  
    for ( cnt = 0; cnt < 53; cnt++ )
    {
        osd_write_byte( ctx, 0x0A, cnt );
        
        switch ( custom_char )
        {
            case 1:
            {
                osd_write_byte( ctx, 0x0B, custom_c1[ cnt ] );
                break;
            }
            case 2:
            {
                osd_write_byte( ctx, 0x0B, custom_c2[ cnt ] );
                break;
            }
            case 3:
            {
                osd_write_byte( ctx, 0x0B, custom_c3[ cnt ] );
                break;
            }
            case 4:
            {
                osd_write_byte( ctx, 0x0B, custom_c4[ cnt ] );
                break;
            }
            case 5:
            {
                osd_write_byte( ctx, 0x0B, custom_c5[ cnt ] );
                break;
            }
            case 6:
            {
                osd_write_byte( ctx, 0x0B, custom_c6[ cnt ] );
                break;
            }
            default :
            {
                osd_write_byte( ctx, 0x0B, custom_c1[ cnt ] );
                break;
            }
        }
    }
  
    osd_write_byte( ctx, 0x08, 0xA0 );
  
    for ( ; ; )
    {
        tmp = osd_read_byte( ctx, 0xA0 );
        tmp &= 0x20;
    
        if ( !tmp )
        {
            break;
        }
    }

    osd_enable( ctx );
}

void osd_clears_char_places ( osd_t *ctx, uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y )
{
    uint8_t cnt_i;
    uint8_t cnt_j;
    
    for ( cnt_i = start_x; cnt_i < end_x; cnt_i++ )
    {
        for ( cnt_j = start_y; cnt_j < end_y; cnt_j++ )
        {
            osd_write_character( ctx, cnt_i, cnt_j, 0 );
        }
    }
}

void osd_set_ntsc ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_VM0_REG );
    tmp &= 0xBF;
    osd_write_byte( ctx, OSD_VM0_REG, tmp );
}

void osd_set_pal ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_VM0_REG );
    tmp &= 0x40;
    osd_write_byte( ctx, OSD_VM0_REG, tmp );
}

void osd_set_video_sync_mode ( osd_t *ctx, uint8_t sync_mode )
{
    uint8_t tmp;
    
    sync_mode %= 3;
    
    tmp = osd_read_byte( ctx, OSD_VM0_REG );
    tmp &= 0xCF;
    
    switch ( sync_mode )
    {
        case 0:
        {
            tmp |= 0x00;
            break;
        }
        case 1:
        {
            tmp |= 0x20;
            break;
        }
        case 2:
        {
            tmp |= 0x30;
            break;
        }
    }
    
    osd_write_byte( ctx, OSD_VM0_REG, tmp );
}

void osd_enable_display_image ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_VM0_REG );
    tmp |= 0x08;
    osd_write_byte( ctx, OSD_VM0_REG, tmp );
}

void osd_disable_display_image ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_VM0_REG );
    tmp &= 0xF7;
    osd_write_byte( ctx, OSD_VM0_REG, tmp );
}

void osd_vertical_sync_screen ( osd_t *ctx, uint8_t vsync )
{
    uint8_t tmp;
    
    vsync %= 2;

    tmp = osd_read_byte( ctx, OSD_VM0_REG );
    
    if ( vsync )
    {
        tmp |= 0x04;
    }
    else
    {
        tmp &= 0xFB;
    }

    osd_write_byte( ctx, OSD_VM0_REG, tmp );
}

void osd_soft_reset ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_VM0_REG );
    tmp |= 0x02;
    osd_write_byte( ctx, OSD_VM0_REG, tmp );
    Delay_1ms();
}

void osd_enable_video_buffer ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_VM0_REG );
    tmp &= 0xFE;
    osd_write_byte( ctx, OSD_VM0_REG, tmp );
}

void osd_disable_video_buffer ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_VM0_REG );
    tmp |= 0x01;
    osd_write_byte( ctx, OSD_VM0_REG, tmp );
}

void osd_set_background_mode ( osd_t *ctx, uint8_t b_mode )
{
    uint8_t tmp;
    
    b_mode %= 2;

    tmp = osd_read_byte( ctx, OSD_VM1_REG );

    if ( b_mode )
    {
        tmp |= 0x80;
    }
    else
    {
        tmp &= 0x7F;
    }

    osd_write_byte( ctx, OSD_VM1_REG, tmp );
}

void osd_set_background_brightness ( osd_t *ctx, uint8_t brightness )
{
    uint8_t tmp;

    brightness %= 8;
    brightness <<= 4;

    tmp = osd_read_byte( ctx, OSD_VM1_REG );
    tmp &= 0x8F;
    tmp |= brightness;
    osd_write_byte( ctx, OSD_VM1_REG, tmp );
}

void osd_set_blinking_time ( osd_t *ctx, uint8_t blinking_time )
{
    uint8_t tmp;

    blinking_time %= 4;
    blinking_time <<= 2;

    tmp = osd_read_byte( ctx, OSD_VM1_REG );
    tmp &= 0xF3;
    tmp |= blinking_time;
    osd_write_byte( ctx, OSD_VM1_REG, tmp );
}

void osd_set_blinking_duty_cycle ( osd_t *ctx, uint8_t blink_duty_cycle )
{
    uint8_t tmp;

    blink_duty_cycle %= 4;

    tmp = osd_read_byte( ctx, OSD_VM1_REG );
    tmp &= 0xF3;
    tmp |= blink_duty_cycle;
    osd_write_byte( ctx, OSD_VM1_REG, tmp );
}

void osd_set_horizontal_offset ( osd_t *ctx, uint8_t h_offset )
{
    uint8_t tmp;

    h_offset %= 64;

    tmp = osd_read_byte( ctx, OSD_HOS_REG );
    tmp |= h_offset;
    osd_write_byte( ctx, OSD_HOS_REG, tmp );
}

void osd_set_vertical_offset ( osd_t *ctx, uint8_t v_offset )
{
    uint8_t tmp;

    v_offset %= 32;

    tmp = osd_read_byte( ctx, OSD_VOS_REG );
    tmp |= v_offset;
    osd_write_byte( ctx, OSD_VOS_REG, tmp );
}

void osd_set_operation_mode ( osd_t *ctx, uint8_t op_mode )
{
    uint8_t tmp;

    op_mode %= 2;
    op_mode <<= 6;

    tmp = osd_read_byte( ctx, OSD_DMM_REG );
    tmp &= 0xBF;
    tmp |= op_mode;
    osd_write_byte( ctx, OSD_DMM_REG, tmp );
}

void osd_set_local_background_control ( osd_t *ctx, uint8_t lb_mode )
{
    uint8_t tmp;

    lb_mode %= 2;
    lb_mode <<= 5;

    tmp = osd_read_byte( ctx, OSD_DMM_REG );
    tmp &= 0xDF;
    tmp |= lb_mode;
    osd_write_byte( ctx, OSD_DMM_REG, tmp );
}

void osd_blinking_on ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_DMM_REG );
    tmp |= 0x10;
    osd_write_byte( ctx, OSD_DMM_REG, tmp );
}

void osd_blinking_off ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_DMM_REG );
    tmp &= 0xEF;
    osd_write_byte( ctx, OSD_DMM_REG, tmp );
}

void osd_invert_pixels_display ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_DMM_REG );
    tmp |= 0x08;
    osd_write_byte( ctx, OSD_DMM_REG, tmp );
}

void osd_normal_pixels_display ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_DMM_REG );
    tmp &= 0xF7;
    osd_write_byte( ctx, OSD_DMM_REG, tmp );
}

void osd_clear_display_memory ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_DMM_REG );
    tmp |= 0x04;
    osd_write_byte( ctx, OSD_DMM_REG, tmp );
    Delay_1ms();
}

void osd_write_chars ( osd_t *ctx, uint8_t *symbol_buff, osd_write_chars_t *write_ctx )
{
    uint8_t  cnt;
    uint16_t offset;

    offset = write_ctx->line_pos * 30 + write_ctx->row_pos;

    osd_enable( ctx );

    osd_write_byte( ctx, OSD_DMM_REG, ( ( write_ctx->flags & 1 ) ? 0x10 : 0x00 ) |
                                      ( ( write_ctx->flags & 2 ) ? 0x08 : 0x00 ) | 
                                      ( ( write_ctx->n_byte != 1 ) ? 0x01 : 0x00 ) );

    osd_write_byte( ctx, OSD_DMAH_REG, offset >> 8 );
    osd_write_byte( ctx, OSD_DMAL_REG, offset & 0xFF );


    for ( cnt = 0; cnt < write_ctx->n_byte; cnt++ )
    {
        osd_write_byte( ctx, OSD_DMDI_REG, symbol_buff[ cnt ] );
    }

    if ( write_ctx->n_byte != 1 )
    {
        osd_write_byte( ctx, OSD_DMDI_REG, OSD_END_STRING );
    }
}

void osd_write_nvm_character ( osd_t *ctx, uint8_t v_chars, uint16_t v_index )
{
    uint8_t cnt;
    uint8_t tmp;

    osd_enable( ctx );

    osd_write_byte( ctx, OSD_CMAH_REG, v_chars );

    for ( cnt = 0; cnt < OSD_NVM_RAM_SIZE; cnt++ )
    {
        osd_write_byte( ctx, OSD_CMAL_REG, cnt );
        osd_write_byte( ctx, OSD_CMDI_REG, fontdata[ v_index + cnt ] );
    }

    osd_write_byte( ctx, OSD_CMM_REG, OSD_WRITE_NVR );

    while ( osd_read_byte( ctx, OSD_STAT_REG ) & OSD_STATUS_REG_NVR_BUSY )
    {
        Delay_10us();
    }

    tmp = osd_read_byte( ctx, OSD_VM0_REG );
    tmp |= 0x0C;
    
    osd_write_byte( ctx, OSD_VM0_REG, tmp );
}

void osd_set_character_color_white ( osd_t *ctx )
{
    uint8_t tmp;
    
    osd_set_operation_mode( ctx, 0x01 );

    tmp = osd_read_byte( ctx, OSD_DMAH_REG );
    osd_write_byte( ctx, OSD_DMAH_REG, tmp | 0x02 );
    
    tmp = osd_read_byte( ctx, OSD_DMDI_REG );
    tmp &= 0x7F;
    osd_write_byte( ctx, OSD_DMDI_REG, tmp );
    
    tmp = osd_read_byte( ctx, OSD_DMAH_REG );
    osd_write_byte( ctx, OSD_DMAH_REG, tmp & 0xFD );
}

void osd_set_character_color_black ( osd_t *ctx )
{
    uint8_t tmp;

    osd_set_operation_mode( ctx, 0x01 );

    tmp = osd_read_byte( ctx, OSD_DMAH_REG );
    osd_write_byte( ctx, OSD_DMAH_REG, tmp | 0x02 );

    tmp = osd_read_byte( ctx, OSD_DMDI_REG );
    tmp |= 0x80;
    osd_write_byte( ctx, OSD_DMDI_REG, tmp );
    
    tmp = osd_read_byte( ctx, OSD_DMAH_REG );
    osd_write_byte( ctx, OSD_DMAH_REG, tmp & 0xFD );
}

void osd_character_blinking_on ( osd_t *ctx )
{
    uint8_t tmp;
    
    osd_set_operation_mode( ctx, 0x01 );

    tmp = osd_read_byte( ctx, OSD_DMAH_REG );
    osd_write_byte( ctx, OSD_DMAH_REG, tmp | 0x02 );

    tmp = osd_read_byte( ctx, OSD_DMDI_REG );
    tmp |= 0x40;
    osd_write_byte( ctx, OSD_DMDI_REG, tmp );

    tmp = osd_read_byte( ctx, OSD_DMAH_REG );
    osd_write_byte( ctx, OSD_DMAH_REG, tmp & 0xFD );
}

void osd_character_blinking_off ( osd_t *ctx )
{
    uint8_t tmp;
    
    osd_set_operation_mode( ctx, 0x01 );

    tmp = osd_read_byte( ctx, OSD_DMAH_REG );
    osd_write_byte( ctx, OSD_DMAH_REG, tmp | 0x02 );

    tmp = osd_read_byte( ctx, OSD_DMDI_REG );
    tmp &= 0xBF;
    osd_write_byte( ctx, OSD_DMDI_REG, tmp );

    tmp = osd_read_byte( ctx, OSD_DMAH_REG );
    osd_write_byte( ctx, OSD_DMAH_REG, tmp & 0xFD );
}

void osd_invert_pixels_character ( osd_t *ctx )
{
    uint8_t tmp;
    
    osd_set_operation_mode( ctx, 0x01 );

    tmp = osd_read_byte( ctx, OSD_DMAH_REG );
    osd_write_byte( ctx, OSD_DMAH_REG, tmp | 0x02 );

    tmp = osd_read_byte( ctx, OSD_DMDI_REG );
    tmp |= 0x20;
    osd_write_byte( ctx, OSD_DMDI_REG, tmp );

    tmp = osd_read_byte( ctx, OSD_DMAH_REG );
    osd_write_byte( ctx, OSD_DMAH_REG, tmp & 0xFD );
}

void osd_normal_pixels_character ( osd_t *ctx )
{
    uint8_t tmp;
    
    osd_set_operation_mode( ctx, 0x01 );

    tmp = osd_read_byte( ctx, OSD_DMAH_REG );
    osd_write_byte( ctx, OSD_DMAH_REG, tmp | 0x02 );

    tmp = osd_read_byte( ctx, OSD_DMDI_REG );
    tmp &= 0xDF;
    osd_write_byte( ctx, OSD_DMDI_REG, tmp );

    tmp = osd_read_byte( ctx, OSD_DMAH_REG );
    osd_write_byte( ctx, OSD_DMAH_REG, tmp & 0xFD );
}

void osd_set_sharpness ( osd_t *ctx, uint8_t s_data )
{
    uint8_t tmp;
    
    s_data %= 6;
    
    tmp = osd_read_byte( ctx, OSD_OSDM_REG );
    tmp |= s_data;
    s_data <<= 3;
    tmp |= s_data;
    osd_write_byte( ctx, OSD_OSDM_REG, tmp );
}

void osd_enable_auto_black ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_OSDBL_REG );
    tmp &= 0xEF;
    osd_write_byte( ctx, OSD_OSDBL_REG, tmp );
}

void osd_disable_auto_black ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_OSDBL_REG );
    tmp |= 0x10;
    osd_write_byte( ctx, OSD_OSDBL_REG, tmp );
}

uint8_t osd_get_status ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_STAT_REG );

    return tmp;
}

uint8_t osd_get_display_data_out ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_DMDO_REG );

    return tmp;
}

uint8_t osd_get_character_data_out ( osd_t *ctx )
{
    uint8_t tmp;

    tmp = osd_read_byte( ctx, OSD_CMDO_REG );

    return tmp;
}

uint8_t osd_get_los ( osd_t *ctx )
{
    return digital_in_read( &ctx->los );
}

uint8_t osd_get_vsync ( osd_t *ctx )
{
    return digital_in_read( &ctx->vsy );
}

uint8_t osd_get_hsync ( osd_t *ctx )
{
    return digital_in_read( &ctx->hsy );
}


// ------------------------------------------------------------------------- END

