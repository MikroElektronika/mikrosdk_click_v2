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
 * @file ism.c
 * @brief ISM Click Driver.
 */

#include "ism.h"

// ------------------------------------------------------------- PRIVATE MACROS 

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                  0x00

/**
 * @brief Switch bank command data.
 * @details Switch bank command and active command data.
 */
#define CMD_SWITCH_BANK        0x53
#define DATA_ACTIVE_CMD        0x73

/**
 * @brief Bit masks.
 * @details Bit masks for power up and for the switch bank command.
 */
#define PWR_UP_BIT_MASK        0x01
#define SWITCH_BANK_BIT_MASK   0x80

/**
 * @brief Configuration data values.
 * @details The configuration data rate, power data and channel 2.410G values.
 */
#define DATA_RATE_1M           0x00
#define POWER_DATA_7dBm        0x01
#define CHANNEL_2_410G         0x0A

/**
 * @brief Bank1 register initialization value.
 * @details In the array bank1_reg0_13, all the register value is the byte reversed.
 */
const uint32_t bank1_reg0_13[ 14 ] = 
{
    0xE2014B40,
    0x00004BC0,
    0x028CFCD0,
    0x41390099,
    0x1B8296F9,
    0xA60F0624,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00127300,
    0x36B48000 
};

/**
 * @brief Bank1 register initialization value.
 * @details In the array bank1_reg0_4, all the register value is the byte reversed.
 */
const unsigned long bank1_reg0_4[ 3 ] = 
{
    0xDB8A96F9,
    0x1B8296F9,
    0xDB8296F9 
};

/**
 * @brief Bank1 register initialization value.
 * @details In the array bank1_reg0_5, all the register value is the byte reversed.
 */
const unsigned long bank1_reg0_5[ 3 ] = 
{
    0xB60F0624,
    0xA60F0624,
    0xB60F0624 
};

/**
 * @brief Bank1 register initialization value.
 * @details The array bank1_reg14 contains the initialization values.
 */
const uint8_t bank1_reg14[ 11 ] = 
{ 
    0x41, 
    0x20, 
    0x08, 
    0x04, 
    0x81, 
    0x20, 
    0xCF,
    0xF7, 
    0xFE, 
    0xFF, 
    0xFF 
};

/**
 * @brief Bank0 register initialization value.
 * @details The array bank0_reg contains the initialization values.
 */
const uint8_t bank0_reg[ 30 ][ 2 ] = 
{
    { 0, 0x0F }, 
    { 1, 0x3F }, 
    { 2, 0x3F }, 
    { 3, 0x03 }, 
    { 4, 0xFF }, 
    { 5, 0x17 }, 
    { 6, 0x07 }, 
    { 7, 0x07 },
    { 8, 0x00 },
    { 9, 0x00 },
    { 12, 0xC3 },
    { 13, 0xC4 },
    { 14, 0xC5 },
    { 15, 0xC6 },
    { 17, 0x20 },
    { 18, 0x20 },
    { 19, 0x20 },
    { 20, 0x20 },
    { 21, 0x20 },
    { 22, 0x20 },
    { 23, 0x00 },
    { 28, 0x3F },
    { 29, 0x07 } 
};

/**
 * @brief RX0 register address.
 * @details The array rx0_address contains the initialization values,
 * receive address data pipe 0.
 */
const uint8_t rx0_address[ 5 ] = 
{ 
    0x34, 
    0x43, 
    0x10, 
    0x10, 
    0x01 
}; // Receive address data pipe 0

/**
 * @brief RX1 register address.
 * @details The array rx1_address contains the initialization values,
 * receive address data pipe 1.
 */
const uint8_t rx1_address[ 5 ] = 
{ 
    0x39, 
    0x38, 
    0x37, 
    0x36, 
    0xC2 
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief The event start-up.
 * @details The event start-up for the control LED on the ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
static void dev_event_startup ( ism_t *ctx );

/**
 * @brief The event trigger.
 * @details The event trigger for the control LED on the ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
static void dev_event_trig_init ( ism_t *ctx );

/**
 * @brief The event receive.
 * @details The event receive for the control LED on the ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
static void dev_event_trig_rec ( ism_t *ctx );

/**
 * @brief The event transmit.
 * @details The event transmit for the control LED on the ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
static void dev_event_trig_trs ( ism_t *ctx );

/**
 * @brief Delay 50ms delay.
 * @details Delay for 50 milliseconds.
 * @return Nothing.
 * @note None.
 */
static void dev_delay_50ms( void );

/**
 * @brief Delay 100ms delay.
 * @details Delay for 100 milliseconds.
 * @return Nothing.
 * @note None.
 */
static void dev_delay_100ms ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ism_cfg_setup ( ism_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->tl   = HAL_PIN_NC;
    cfg->ce   = HAL_PIN_NC;
    cfg->rl   = HAL_PIN_NC;
    cfg->irq  = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t ism_init ( ism_t *ctx, ism_cfg_t *cfg ) 
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

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->tl, cfg->tl );
    digital_out_init( &ctx->ce, cfg->ce );
    digital_out_init( &ctx->rl, cfg->rl );

    digital_in_init( &ctx->irq, cfg->irq );

    return SPI_MASTER_SUCCESS;
}

void ism_default_cfg ( ism_t *ctx ) 
{
    dev_event_startup( ctx );
    
    ism_device_config( ctx );
}

err_t ism_generic_write ( ism_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t reg_addr = ISM_WRITE_BIT_MASK | reg;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_addr, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t ism_generic_read ( ism_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t ism_set_cmd ( ism_t *ctx, uint8_t cmd, uint8_t cmd_data ) 
{
    uint8_t tx_buf[ 2 ] = { 0 };

    tx_buf[ 0 ] = cmd;
    tx_buf[ 1 ] = cmd_data;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void ism_chip_enable ( ism_t *ctx ) 
{
    digital_out_low( &ctx->ce );
}

void ism_chip_disable ( ism_t *ctx ) 
{
    digital_out_high( &ctx->ce );
}

void ism_set_rl_pin_state ( ism_t *ctx, uint8_t rt_pin_state ) 
{
    digital_out_write( &ctx->rl, rt_pin_state );
}

void ism_set_tl_pin_state ( ism_t *ctx, uint8_t tl_pin_state ) 
{
    digital_out_write( &ctx->tl, tl_pin_state );
}

uint8_t ism_check_interrupt_request ( ism_t *ctx ) 
{
    return digital_in_read( &ctx->irq );
}

err_t ism_switch_bank ( ism_t *ctx, uint8_t bank_sel ) 
{
    uint8_t temp = 0;

    err_t error_flag = ism_generic_read( ctx, 7, &temp, 1 );

    temp &= SWITCH_BANK_BIT_MASK;

    if ( ( temp && ( ISM_SEL_BANK_0 == bank_sel ) ) || 
         ( ( 0 == temp ) && ( ISM_SEL_BANK_1 == bank_sel ) ) ) 
    {
        error_flag |= ism_set_cmd( ctx, ISM_CMD_ACTIVATE, CMD_SWITCH_BANK );
    }
    
    return error_flag;
}

err_t ism_switch_rx_mode ( ism_t *ctx ) 
{
    uint8_t value = 0;

    err_t error_flag = ism_set_cmd( ctx, ISM_CMD_FLUSH_RX, 0 );

    error_flag |= ism_generic_read( ctx, ISM_REG_BANK_0_STATUS, &value, 1 ); 
    error_flag |= ism_generic_write( ctx, ISM_REG_BANK_0_STATUS, &value, 1 );

    ism_chip_enable ( ctx );

    error_flag |= ism_generic_read( ctx, ISM_REG_BANK_0_CONFIG, &value, 1 );
    
    value |= PWR_UP_BIT_MASK;
    error_flag |= ism_generic_write( ctx, ISM_REG_BANK_0_CONFIG, &value, 1 );
    
    ism_chip_disable ( ctx );
    
    return error_flag;
}

err_t ism_switch_tx_mode ( ism_t *ctx ) 
{
    uint8_t value = 0;
    
    err_t error_flag = ism_set_cmd( ctx, ISM_CMD_FLUSH_TX, 0 );

    ism_chip_enable ( ctx );

    error_flag |= ism_generic_read( ctx, ISM_REG_BANK_0_CONFIG, &value, 1 );

    value &= ~PWR_UP_BIT_MASK;
    error_flag |= ism_generic_write( ctx, ISM_REG_BANK_0_CONFIG, &value, 1 );

    ism_chip_disable ( ctx );
    
    return error_flag;
}

err_t ism_device_config ( ism_t *ctx ) 
{
    uint8_t n_cnt_i = 0;
    uint8_t n_cnt_j = 0;
    uint8_t tx_buf[ 12 ] = { 0 };
    uint8_t data_rate = 0;
    uint8_t tx_data = 0;
    
    data_rate = DATA_RATE_1M;
    
    dev_event_trig_init( ctx );
    
    err_t error_flag = ism_switch_bank( ctx, ISM_SEL_BANK_0 );
    
    for ( n_cnt_i = 0 ; n_cnt_i < 5; n_cnt_i++ ) 
    {
        tx_data = bank0_reg[ n_cnt_i ][ 1 ];
        ism_generic_write( ctx, bank0_reg[ n_cnt_i ][ 0 ], &tx_data, 1 );
    }
    
    tx_data = CHANNEL_2_410G;
    error_flag |= ism_generic_write( ctx, 5, &tx_data, 1 );
    data_rate |= POWER_DATA_7dBm;
    error_flag |= ism_generic_write( ctx, 6, &data_rate, 1 );
    
    for ( n_cnt_i = 7; n_cnt_i < 21; n_cnt_i++ ) 
    {
        tx_data = bank0_reg[ n_cnt_i ][ 1 ];
        error_flag |= ism_generic_write( ctx, bank0_reg[ n_cnt_i ][ 0 ], &tx_data, 1 );
    }
    
    for ( n_cnt_j = 0; n_cnt_j < 5; n_cnt_j++ ) 
    {
        tx_buf[ n_cnt_j ] = rx0_address[ n_cnt_j ];
    }
    ism_generic_write( ctx, 10, tx_buf, 5 );
    
    for ( n_cnt_j = 0; n_cnt_j < 5; n_cnt_j++ ) 
    {
        tx_buf[ n_cnt_j ] = rx1_address[ n_cnt_j ];
    }
    ism_generic_write( ctx, 11, tx_buf, 5 );

    for ( n_cnt_j = 0; n_cnt_j < 5; n_cnt_j++ ) 
    {
        tx_buf[ n_cnt_j ] = rx0_address[ n_cnt_j ];
    }
    error_flag |= ism_generic_write( ctx, 16, tx_buf, 5 );
    
    error_flag |= ism_generic_read( ctx, 29, &n_cnt_i, 1 );
    if ( 0 == n_cnt_i ) 
    {
        ism_set_cmd( ctx, ISM_CMD_ACTIVATE, DATA_ACTIVE_CMD );
    }
    for ( n_cnt_i = 22; n_cnt_i >= 21; n_cnt_i-- ) 
    {
        tx_data = bank0_reg[ n_cnt_i ][ 1 ];
        error_flag |= ism_generic_write( ctx, bank0_reg[ n_cnt_i ][ 0 ], &tx_data, 1 );
    }
    
    error_flag |= ism_switch_bank( ctx, ISM_SEL_BANK_1 );
    
    for ( n_cnt_i = 0; n_cnt_i <= 3; n_cnt_i++ ) 
    {
        for ( n_cnt_j = 0; n_cnt_j < 4; n_cnt_j++ ) 
        {
            tx_buf[ n_cnt_j ] = ( bank1_reg0_13[ n_cnt_i ] >> ( 8 * ( n_cnt_j ) ) ) & 0xFF;
        }
        error_flag |= ism_generic_write( ctx, n_cnt_i, tx_buf, 4 );
    }

    for ( n_cnt_j = 0; n_cnt_j < 4; n_cnt_j++ ) 
    {
        tx_buf[ n_cnt_j ] = ( bank1_reg0_4[ data_rate + 1 ] >> ( 8 * ( n_cnt_j ) ) ) & 0xFF;
    }
    ism_generic_write( ctx, n_cnt_i, tx_buf, 4 );
    for ( n_cnt_j = 0; n_cnt_j < 4; n_cnt_j++ ) 
    {
        tx_buf[ n_cnt_j ] = ( bank1_reg0_5[ data_rate + 1 ] >> ( 8 * ( n_cnt_j ) ) ) & 0xFF;
    }
    error_flag |= ism_generic_write( ctx, n_cnt_i, tx_buf, 4 );

    for ( n_cnt_i = 6; n_cnt_i <= 8; n_cnt_i++ ) 
    {
        for ( n_cnt_j = 0; n_cnt_j < 4; n_cnt_j++ ) 
        {
            tx_buf[ n_cnt_j ] = ( bank1_reg0_13[ n_cnt_i ] >> ( 8 * ( n_cnt_j ) ) ) & 0xFF;
        }
        error_flag |= ism_generic_write( ctx, n_cnt_i, tx_buf, 4 );
    }

    for ( n_cnt_i = 9; n_cnt_i <= 13; n_cnt_i++ ) 
    {
        for ( n_cnt_j = 0; n_cnt_j < 4; n_cnt_j++ ) 
        {
            tx_buf[ n_cnt_j ] = ( bank1_reg0_13[ n_cnt_i ] >> ( 8 * ( 3 - n_cnt_j ) ) ) & 0xFF;
        }
        error_flag |= ism_generic_write( ctx, n_cnt_i, tx_buf, 4 );
    }

    for ( n_cnt_j = 0; n_cnt_j < 11; n_cnt_j++ ) 
    {
        tx_buf[ n_cnt_j ] = bank1_reg14[ n_cnt_j ];
    }
    error_flag |= ism_generic_write( ctx, 14, tx_buf, 11 );

    for ( n_cnt_j = 0; n_cnt_j < 4; n_cnt_j++ ) 
    {
        tx_buf[ n_cnt_j ] = ( bank1_reg0_13[ 4 ] >> ( 8 * ( n_cnt_j ) ) ) & 0xFF;
    }

    tx_buf[ 0 ] |= 0x06;
    error_flag |= ism_generic_write( ctx, 4, tx_buf, 4 );

    tx_buf[ 0 ] &= 0xF9;
    error_flag |= ism_generic_write( ctx, 4, tx_buf, 4 );

    error_flag |= ism_switch_bank( ctx, ISM_SEL_BANK_0 );
    dev_event_trig_init( ctx );
    
    return error_flag;
}

err_t ism_receive_packet ( ism_t *ctx, uint8_t *rx_data ) 
{
    uint8_t len = 0;
    uint8_t cnt = 0;
    uint8_t status = 0;
    uint8_t fifo_status = 0;
    uint8_t rx_buf[ ISM_MAX_PACKET_LEN ] = { 0 };
  
    err_t error_flag = ism_generic_read( ctx, ISM_REG_BANK_0_STATUS, &status, 1 );
  
    if ( ISM_STATUS_RX_DR == ( ISM_STATUS_RX_DR & status ) ) 
    {
        dev_event_trig_rec( ctx );
        do 
        {
            error_flag |= ism_generic_read( ctx, ISM_CMD_R_RX_PL_WID, &len, 1 );

            if ( len <= ISM_MAX_PACKET_LEN ) 
            {
                error_flag |= ism_generic_read( ctx, ISM_RD_RX_PLOAD, &rx_buf, len );
            } 
            else 
            {
                error_flag |= ism_set_cmd( ctx, ISM_CMD_FLUSH_RX, 0 );
            }

            error_flag |= ism_generic_read( ctx, ISM_REG_BANK_0_FIFO_STATUS, &fifo_status, 1 );
            
        } 
        while ( 0 == ( fifo_status & ISM_FIFO_STATUS_RX_EMPTY ) );
    }
    
    error_flag |= ism_generic_write( ctx, ISM_REG_BANK_0_STATUS, &status, 1 );
    
    for ( cnt = 0; cnt < ISM_MAX_PACKET_LEN; cnt++ ) 
    {
        rx_data[ cnt ] = rx_buf[ cnt ];
    }
    
    return error_flag;
}

err_t ism_transmit_packet ( ism_t *ctx, uint8_t type, uint8_t *tx_data, uint8_t len ) 
{
    uint8_t fifo_status = 0;

    err_t error_flag = ism_switch_tx_mode( ctx );

    error_flag |= ism_generic_read( ctx, ISM_REG_BANK_0_FIFO_STATUS, &fifo_status, 1 );
    
    if ( 0 == ( fifo_status & ISM_FIFO_STATUS_TX_FULL ) ) 
    {
        error_flag |= ism_generic_write( ctx, type, tx_data, len);
    }
    
    dev_event_trig_trs( ctx );
    
    return error_flag;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_event_startup ( ism_t *ctx ) 
{
    for ( uint8_t cnt = 0 ; cnt < 5 ; cnt++ ) 
    {
        ism_set_tl_pin_state( ctx, ISM_RT_PIN_STATE_HIGH );
        ism_set_rl_pin_state( ctx, ISM_RT_PIN_STATE_HIGH );
        dev_delay_100ms( );
        
        ism_set_tl_pin_state( ctx, ISM_RT_PIN_STATE_LOW );
        ism_set_rl_pin_state( ctx, ISM_RT_PIN_STATE_LOW );
        dev_delay_100ms( );
    }
    ism_set_tl_pin_state( ctx, ISM_RT_PIN_STATE_LOW );
    ism_set_rl_pin_state( ctx, ISM_RT_PIN_STATE_LOW );;
}

static void dev_event_trig_init ( ism_t *ctx ) 
{
    for ( uint8_t cnt = 0 ; cnt < 3 ; cnt++ ) 
    {
        ism_set_tl_pin_state( ctx, ISM_RT_PIN_STATE_HIGH );
        ism_set_rl_pin_state( ctx, ISM_RT_PIN_STATE_LOW );
        dev_delay_100ms( );
        
        ism_set_tl_pin_state( ctx, ISM_RT_PIN_STATE_LOW );
        ism_set_rl_pin_state( ctx, ISM_RT_PIN_STATE_HIGH );
        dev_delay_100ms( );
    }
    ism_set_tl_pin_state( ctx, ISM_RT_PIN_STATE_LOW );
    ism_set_rl_pin_state( ctx, ISM_RT_PIN_STATE_LOW );
}

static void dev_event_trig_rec ( ism_t *ctx ) 
{
    for ( uint8_t cnt = 0 ; cnt < 3 ; cnt++ ) 
    {
        ism_set_rl_pin_state( ctx, ISM_RT_PIN_STATE_HIGH );
        dev_delay_50ms( );

        ism_set_rl_pin_state( ctx, ISM_RT_PIN_STATE_LOW );
        dev_delay_50ms( );
    }
    digital_out_low( &ctx->rl );
}

static void dev_event_trig_trs ( ism_t *ctx ) 
{
    for ( uint8_t cnt = 0 ; cnt < 6 ; cnt++ ) 
    {
        ism_set_tl_pin_state( ctx, ISM_RT_PIN_STATE_HIGH );
        dev_delay_50ms( );

        ism_set_tl_pin_state( ctx, ISM_RT_PIN_STATE_LOW );
        dev_delay_50ms( );
    }
    digital_out_low( &ctx->tl );
}

static void dev_delay_50ms ( void ) 
{
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
}

static void dev_delay_100ms ( void ) 
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
