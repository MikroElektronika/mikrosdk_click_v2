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

#include "pixi.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PIXI_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

uint8_t drv_check_reg ( const uint8_t address, uint8_t rw_op );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pixi_cfg_setup ( pixi_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->cnv = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

PIXI_RETVAL pixi_init ( pixi_t *ctx, pixi_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = PIXI_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return PIXI_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, PIXI_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->cnv, cfg->cnv );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    spi_master_deselect_device( ctx->chip_select ); 
    Delay_1ms( );
    digital_out_high( &ctx->cnv );
    Delay_1ms( );

    return PIXI_OK;
}

void pixi_default_cfg ( pixi_t *ctx )
{
    pixi_write_reg( ctx, PIXI_REG_DEVICE_CONTROL, PIXI_CTL_DACREF_INTREF |
                                                  PIXI_CTL_THSHDN_ENABLE );
    pixi_write_reg( ctx, PIXI_REG_GPO_DATA, 1048575 );          
    pixi_write_reg( ctx, PIXI_REG_DAC_DATA_BASE + 0, 4095 );
    pixi_write_reg( ctx, PIXI_REG_PORT_CONFIG_BASE + 0, PIXI_PORT_CFG_MODE_3 );
}

uint8_t pixi_write_reg ( pixi_t *ctx, const uint8_t reg_addr, uint32_t reg_data )
{
    uint8_t n_bytes;
    uint8_t temp[ 5 ];

    n_bytes = drv_check_reg( reg_addr, WRITE_OP );

    if ( 0 != n_bytes )
    {
        temp[ 0 ] = reg_addr << 1;

        switch ( n_bytes )
        {
            case 1:
            {
                temp[ 1 ] = ( reg_data >> 8 );
                temp[ 2 ] = ( reg_data & 0x000000FF );
                break;
            }
            case 2:
            {
                temp[ 1 ] = ( reg_data >> 8 );
                temp[ 2 ] = ( reg_data & 0x000000FF );
                temp[ 3 ] = ( reg_data >> 24 );
                temp[ 4 ] = ( reg_data >> 16 );
                break;
            } 
            default:
            {
                return PIXI_ERR;
            }      
        }
    }
    else 
    {
        return PIXI_ERR;
    }
   
    spi_master_select_device( ctx->chip_select );
    Delay_10us();
    spi_master_write( &ctx->spi, temp, n_bytes * 2 + 1 );
    spi_master_deselect_device( ctx->chip_select ); 
    Delay_1ms();

    return PIXI_OK;
}

uint8_t pixi_read_reg ( pixi_t *ctx, const uint8_t reg_addr, uint32_t *reg_data )
{
    uint8_t n_bytes;
    uint8_t temp[ 5 ];

    n_bytes = drv_check_reg( reg_addr, READ_OP );

    if ( 0 != n_bytes )
    {
        temp[ 0 ] = ( reg_addr << 1 ) | 0x01;

        spi_master_select_device( ctx->chip_select );
        Delay_10us( );
        spi_master_write_then_read( &ctx->spi, &temp, 1, temp, n_bytes * 2 );
        spi_master_deselect_device( ctx->chip_select ); 
        Delay_1ms( );  

        switch ( n_bytes )
        {
            case 1:
            {
                *reg_data = 0;
                *reg_data = temp[ 0 ];
                *reg_data <<= 8;
                *reg_data |= temp[ 1 ];
                break;
            } 
            case 2:
            {
                *reg_data = temp[ 2 ];
                *reg_data <<= 8;
                *reg_data |= temp[ 3 ];
                *reg_data <<= 8;
                *reg_data |= temp[ 0 ];
                *reg_data <<= 8;
                *reg_data |= temp[ 1 ];
                break;
            }    
            default :
                return PIXI_ERR;
        }
    }
    else 
    {
        return PIXI_ERR;
    }
    return PIXI_OK;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

uint8_t drv_check_reg ( const uint8_t address, uint8_t rw_op )
{
    switch (address)
    {
        case 0x00: 
        {
            if ( WRITE_OP == rw_op ) 
            {
                return 0;
            } 
            else 
            {
                return 1;
            }
        }
        case 0x01: 
        {
            if ( WRITE_OP == rw_op ) 
            {
                return 0;
            }
            else 
            {
                return 1;
            }
        }
        case 0x02: 
        {
            if ( WRITE_OP == rw_op ) 
            {
                return 0;
            } 
            else 
            {
                return 2;
            }
        }
        case 0x04: 
        {
            if ( WRITE_OP == rw_op ) 
            {
                return 0;
            }
            else
            {
                return 2;
            }
        }  
        case 0x06: 
        {
            if ( WRITE_OP == rw_op ) 
            {
                return 0;
            } 
            else
            {
                return 2;
            } 
        }
        case 0x08: 
        {
            if ( WRITE_OP == rw_op ) 
            {
                return 0;
            }
            else
            {
                 return 1;
            }
        } 
        case 0x09:
        {
            if ( WRITE_OP == rw_op ) 
            {
                return 0;
            }
            else
            {
                return 1;
            } 
        }
        case 0x0A: 
        {
            if ( WRITE_OP == rw_op ) 
            {
                return 0;
            } 
            else
            {
                return 1;
            }  
        }
        case 0x0B: 
        {
            if ( WRITE_OP == rw_op )
            {
                return 0;
            }
            else
            {
                return 2;
            }
        }   
        case 0x0D: 
        {
            return 2;
        }
        case 0x10: 
        {
            return 1;
        }
        case 0x11: 
        {
            return 1;
        }
        case 0x12: 
        {
            return 1;
        }
        case 0x13: 
        {
            return 1;
        }
        case 0x14: 
        {
            return 1;
        }
        case 0x16: 
        {
            return 1;
        }
        case 0x17: 
        {
            return 1;
        }
        case 0x18: 
        {
            return 1;
        }
        case 0x19: 
        {
            return 1;
        }
        case 0x1A: 
        {
            return 1;
        }
        case 0x1B: 
        {
            return 1;
        }
        case 0x1C: 
        {
            return 1;
        }
        case 0x1D: 
        {
            return 1;
        }
        case 0x1E: 
        {
            return 1;
        }
        default:
        {
            if ( ( 0x20 <= address ) && ( 0x33 > address ) ) 
            {
                return 1;
            }
            if ( (0x40 <= address ) && ( 0x53 > address ) ) if ( WRITE_OP == rw_op ) 
            {
                return 0; 
            }
            else 
            {
                return 1;
            }
            if ( ( 0x60 <= address ) && ( 0x73 > address ) ) 
            {
                return 1;
            }
        }     
    }
    return 0;
}

// ------------------------------------------------------------------------- END

