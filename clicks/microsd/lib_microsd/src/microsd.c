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
 * @file microsd.c
 * @brief microSD Click Driver.
 */

#include "microsd.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void microsd_cfg_setup ( microsd_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->cd_pin = HAL_PIN_NC;
}

err_t microsd_init ( microsd_t *ctx, microsd_cfg_t *cfg ) 
{
    sdspi_config_t sd_conf;

    sd_conf.spi_cs   = cfg->cs;
    sd_conf.spi_sck  = cfg->sck;
    sd_conf.spi_miso = cfg->miso;
    sd_conf.spi_mosi = cfg->mosi;

    // Initilize SD SPI physical drive structure and prepare SPI bus for communication with SD card with initial
    // SPI clock frequency in between 100kHz and 400kHz, where exact clock depends on MCU
    if ( PDS_OK != sdspi_physical_drive_init( &ctx->sd_pdrive, &sd_conf ) ) 
    {
        return MICROSD_ERROR;
    }
    // Initilize FatFs logical drive and prepare it for usage of FAT file system
    if ( FSS_OK != fatfs_initialize ( &ctx->fat_ldrive ) )
    {
        return MICROSD_ERROR;
    }
    
    digital_in_init ( &ctx->cd_pin, cfg->cd_pin );

    return MICROSD_OK;
}

uint8_t microsd_get_card_detect ( microsd_t *ctx )
{
    return digital_in_read ( &ctx->cd_pin );
}

// ------------------------------------------------------------------------- END
