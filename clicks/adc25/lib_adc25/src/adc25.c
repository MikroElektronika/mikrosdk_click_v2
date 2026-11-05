/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file adc25.c
 * @brief ADC 25 Click Driver.
 */

#include "adc25.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief ADC 25 configure step function.
 * @details This function configures a single sequence step by switching to the
 * corresponding Step Configuration Page.
 * @param[in] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @param[in] step : Step index (0-31).
 * @param[in] ain_cfg : Channel selection value for STEPx_AIN_CFG register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t adc25_configure_step ( adc25_t *ctx, uint8_t step, uint8_t ain_cfg );

/**
 * @brief ADC 25 wait data ready function.
 * @details This function polls the DRDY pin until it goes low,
 * indicating that a sequence has completed.
 * @param[in] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t adc25_wait_drdy ( adc25_t *ctx );

void adc25_cfg_setup ( adc25_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->st   = HAL_PIN_NC;
    cfg->rdy  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t adc25_init ( adc25_t *ctx, adc25_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->st, cfg->st );

    digital_in_init( &ctx->rdy, cfg->rdy );

    digital_out_high( &ctx->rst );
    digital_out_low( &ctx->st );

    return SPI_MASTER_SUCCESS;
}

err_t adc25_default_cfg ( adc25_t *ctx ) 
{
    err_t error_flag = ADC25_OK;
    uint8_t device_id = 0;

    adc25_hw_reset( ctx );
    
    /* Check communication by reading the device ID from DEVICE_ID register(00h) */
    error_flag |= adc25_read_reg( ctx, ADC25_REG_DEVICE_ID, &device_id );
    if ( ADC25_DEVICE_ID_INVALID == device_id )
    {
        return ADC25_ERROR;
    }
    
    /* ADC_CFG register(Status and General Configuration Page, 12h):
     *     bit[3:2] = 01 -> Speed mode set to Low speed mode:             
     *                      -fclk = 3.2Mhz (datasheet page 32, table 7-5).
     *                      -fmod = fclk/2 = 1.6Mhz (datasheet page 31).
     *                      -max data rate = 133kSPS (datasheet page 32, table 7-5).
     *                      -power dissipation = 11mW (datasheet page 10). */
    error_flag |= adc25_write_reg( ctx, ADC25_REG_ADC_CFG, ADC25_ADC_CFG_SPEED_MODE_1 );

    /* REFERENCE_CFG register(Status and General Configuration Page, 13h):
     *     bit[1] = 0 -> Internal ADC reference value is 2.5V
     *     bit[0] = 1 -> Enable positive reference buffer */
    error_flag |= adc25_write_reg( ctx, ADC25_REG_REFERENCE_CFG, ADC25_REF_CFG_VREF_2_5V | ADC25_REF_CFG_REFP_BUF_EN );

    /* GPIO_CFG register(Status and General Configuration Page, 17h):
     *     bit[7:6] = 00 -> GPIO3 disabled.
     *     bit[5:4] = 00 -> GPIO2 disabled.
     *     bit[3:2] = 11 -> Set alternate function for GPIO1 pin to operate as a DRDY output.
     *     bit[1:0] = 11 -> Set alternate function for GPIO0 pin to operate as a START input. */
    error_flag |= adc25_write_reg( ctx, ADC25_REG_GPIO_CFG, ADC25_GPIO_CFG_GPIO1_DRDY | ADC25_GPIO_CFG_GPIO0_START );

    /* Configure 8 sequence steps - one per terminal on the Click board:
     *     Step 0 -> AIN0  single-ended (TB1, pin 1 - Single Ended Current)
     *     Step 1 -> AIN1  single-ended (TB1, pin 2 - Single Ended Current)
     *     Step 2 -> AIN6  single-ended (TB2, pin 1 - Single Ended Current)
     *     Step 3 -> AIN7  single-ended (TB2, pin 2 - Single Ended Current)
     *     Step 4 -> AIN8/AIN9   differential (TB3 - Differential Voltage)
     *     Step 5 -> AIN10/AIN11 differential (TB4 - Differential Voltage)
     *     Step 6 -> AIN12/AIN13 differential (TB5 - Differential Current)
     *     Step 7 -> AIN14/AIN15 differential (TB6 - Differential Current) */
    error_flag |= adc25_configure_step( ctx, 0, ADC25_AIN_CFG_AIN0_SE );
    error_flag |= adc25_configure_step( ctx, 1, ADC25_AIN_CFG_AIN1_SE );
    error_flag |= adc25_configure_step( ctx, 2, ADC25_AIN_CFG_AIN6_SE );
    error_flag |= adc25_configure_step( ctx, 3, ADC25_AIN_CFG_AIN7_SE );
    error_flag |= adc25_configure_step( ctx, 4, ADC25_AIN_CFG_AIN8_AIN9_DIFF );
    error_flag |= adc25_configure_step( ctx, 5, ADC25_AIN_CFG_AIN10_AIN11_DIFF );
    error_flag |= adc25_configure_step( ctx, 6, ADC25_AIN_CFG_AIN12_AIN13_DIFF );
    error_flag |= adc25_configure_step( ctx, 7, ADC25_AIN_CFG_AIN14_AIN15_DIFF );

    /* SEQUENCER_CFG register(Status and General Configuration Page, 20h):
     *     bit[7:6] = 11 -> Sequencer enabled, execute the sequence continuously.
     *     bit[1:0] = 10 -> DRDY transitions after every completed sequence. */
    error_flag |= adc25_write_reg( ctx, ADC25_REG_SEQUENCER_CFG, ADC25_SEQ_CFG_MODE_CONT_SEQ | ADC25_SEQ_CFG_DRDY_PER_SEQ );

    /* SEQUENCE_STEP_EN_0 register(Status and General Configuration Page, 21h):
     *     bit[7:0] = 0xFF -> Enable sequences from 0 to 7 */
    error_flag |= adc25_write_reg( ctx, ADC25_REG_SEQUENCE_STEP_EN_0, ADC25_SEQ_STEP_0_TO_7_EN );
    
    /* FIFO_CFG register(Status and General Configuration Page, 25h):
     *     bit[0] = 1 -> FIFO enabled */
    error_flag |= adc25_write_reg( ctx, ADC25_REG_FIFO_CFG, ADC25_FIFO_CFG_FIFO_EN );

    error_flag |= adc25_start_conversion( ctx );

    return error_flag;
}

err_t adc25_write_reg ( adc25_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    /* Write register frame: CS_low | write_command(0x80 | reg_addr) | data_byte | cs_high */
    uint8_t tx_buf[ 2 ] = { ADC25_CMD_WRITE_REG | reg, data_in };

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t adc25_read_reg ( adc25_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    /* Read register(two separate CS frames):
    *  
    *  Frame 1 - send read command:
    *      CS_low | read_command(0x40 | reg_addr) | dummy_byte | CS_high
    * 
    *  Frame 2 - retrieve register value:
    *      Byte 1: 0x00  (dummy) -> chip returns: register_value
    *      Byte 2: 0x00  (dummy) -> chip returns: register_address echo 
    *      Byte 3: 0x00  (dummy) -> chip returns: 0x00
    *      CS_low | dummy_byte(0x00) | dummy_byte(0x00) | dummy_byte(0x00) | CS_high */
    uint8_t tx_buf[ 2 ] = { ADC25_CMD_READ_REG | reg, DUMMY };
    uint8_t rx_buf[ 3 ] = { DUMMY };

    /* Frame 1: send the read command */
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    /* Frame 2: clock out 3 dummy bytes, capture the register value from byte 0 */
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );

    *data_out = rx_buf[ 0 ];

    return error_flag;
}

void adc25_hw_reset ( adc25_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_10ms( );
    digital_out_high( &ctx->rst );
    Delay_10ms( );
}

err_t adc25_sw_reset ( adc25_t *ctx )
{
    err_t error_flag = adc25_write_reg( ctx, ADC25_REG_RESET, ADC25_RESET_SW_CODE );
    Delay_1ms( );

    return error_flag;
}

err_t adc25_start_conversion ( adc25_t *ctx )
{
    /* Start conversion by setting the START bit in CONVERSION_CTRL register(10h) */
    return adc25_write_reg( ctx, ADC25_REG_CONVERSION_CTRL, ADC25_CONV_CTRL_START );
}

err_t adc25_stop_conversion ( adc25_t *ctx )
{
    /* Stop conversion by setting the STOP bit in CONVERSION_CTRL register(10h) */
    return adc25_write_reg( ctx, ADC25_REG_CONVERSION_CTRL, ADC25_CONV_CTRL_STOP );
}

err_t adc25_read_raw_data ( adc25_t *ctx, int32_t *raw_data )
{
    int32_t raw_data_val = 0;

    /* Read FIFO buffer frame:
     *     Frame 1 - send Read FIFO command:
     *         CS_low | 0x0F | dummy_byte | CS_high
     *
     *     Frame 2 - retrieve FIFO result:
     *         CS_low | dummy_byte | dummy_byte | dummy_byte | CS_high
     *         Chip returns: 24-bit conversion result, MSB first. */
    uint8_t tx_buf[ 2 ] = { ADC25_CMD_READ_FIFO, DUMMY };
    uint8_t rx_buf[ 3 ] = { DUMMY };

    /* Frame 1: send the Read FIFO command */
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    /* Frame 2: clock out 3 dummy bytes, capture the FIFO result */
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );

    /* Assemble the three bytes into a 32-bit integer (MSB first) */
    raw_data_val = ( ( int32_t ) rx_buf[ 0 ] << 16 ) | ( ( int32_t ) rx_buf[ 1 ] << 8 ) | ( int32_t ) rx_buf[ 2 ];
    
    /* Sign extend */
    if ( raw_data_val & ADC25_BIT_23_MASK )
    {
        raw_data_val |= ADC25_ONES_EXTEND_MASK;
    }
    else
    {
        raw_data_val &= ADC25_ZERO_EXTEND_MASK;
    }

    *raw_data = raw_data_val;

    return error_flag;
}

err_t adc25_get_voltage_seq ( adc25_t *ctx, float *voltage, uint8_t len )
{
    int32_t raw_data = DUMMY;

    /* Stop conversions before flushing FIFO to ensure the sequencer is idle
     * and no new data is written to the FIFO during the flush operation. */
    err_t error_flag = adc25_stop_conversion( ctx );

    /* Flush the FIFO to discard stale results from previous sequences,
     * by disabling it and then re-enabling it.
     * Disabling the FIFO resets both write and read pointers. */
    error_flag |= adc25_write_reg( ctx, ADC25_REG_FIFO_CFG, DUMMY );
    error_flag |= adc25_write_reg( ctx, ADC25_REG_FIFO_CFG, ADC25_FIFO_CFG_FIFO_EN );

    /* Restart conversions */
    error_flag |= adc25_start_conversion( ctx );
    
    /* Wait for sequence to complete */
    error_flag = adc25_wait_drdy( ctx );
    if ( ADC25_OK != error_flag )
    {
        return ADC25_ERROR;
    }

    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        error_flag |= adc25_read_raw_data( ctx, &raw_data );

        /* Convert raw 24-bit two's complement value to input voltage:
         *
         *     V_input = raw * 1LSB
         *             = raw * FSR / 2^23
         *             = raw * (Vref * attenuation_factor) / 2^23
         *             = raw * (2.5V * 10) / 2^23
         *
         *     1LSB = FSR / 2^23 (datasheet page 112, table 7-53)
         *     FSR  = Vref * attenuation_factor (datasheet page 28, footnote(1))
         *     Vref = 2.5V
         *     attenuation = 10 (datasheet page 28, table 7-3) */
        voltage[ cnt ] = ( ( float ) raw_data / ADC25_FULL_SCALE ) * ADC25_VREF_INTERNAL_V * ADC25_ATTENUATION_FACTOR;
    }

    return error_flag;
}

uint8_t adc25_get_data_ready ( adc25_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

static err_t adc25_configure_step ( adc25_t *ctx, uint8_t step, uint8_t ain_cfg )
{
    /* PAGE_POINTER register(3Fh): switch to the Step Configuration Page for the desired sequence step.
     * Page index = step + 1 (page 0x01 = step 0, page 0x02 = step 1, etc.) */
    err_t error_flag = adc25_write_reg( ctx, ADC25_REG_PAGE_POINTER, ADC25_PAGE_STEP_0 + step );

    /* STEPx_AIN_CFG register(Step Configuration Page, 00h):
     *     bit[4:0] = ain_cfg -> Select the input channel for this step and 
                                 whether its single-ended or differential. */
    error_flag |= adc25_write_reg( ctx, ADC25_REG_STEPX_AIN_CFG, ain_cfg );

    /* STEPx_ADC_REF_CFG register(Step Configuration Page, 02h):
     *     bit[7:6] = 00b   -> Gain set to 1.
     *     bit[5]   = 0     -> Conversion data coding set to two's complement format.
     *     bit[4]   = 1     -> Use internal voltage reference.
     *     bit[3:0] = 0000b -> 1 conversion per sequence step. */
    error_flag |= adc25_write_reg( ctx, ADC25_REG_STEPX_ADC_REF_CFG, ADC25_ADC_REF_CFG_GAIN_1         |
                                                                     ADC25_ADC_REF_CFG_CODING_BIPOLAR |
                                                                     ADC25_ADC_REF_CFG_REF_INT        |
                                                                     ADC25_ADC_REF_CFG_NUM_CONV_1 );

    /* STEPx_FLTR1_CFG register(Step Configuration Page, 03h):
     *     bit[5]   = 0      -> Sinc4 selected as first stage filter.
     *     bit[4:0] = 00011b -> OSR set to 32. fDATA = fMOD / OSR = 1.6MHz / 32 = 50kSPS. */
    error_flag |= adc25_write_reg( ctx, ADC25_REG_STEPX_FLTR1_CFG, ADC25_FLTR_CFG_SINC4 | ADC25_FLTR_CFG_OSR_32 );

    /* STEPx_PAGE_POINTER register(Step Configuration Page, 3Fh):
     *     bit[7:0] = 0x00 -> Switch back to General Configuration Page. */
    error_flag |= adc25_write_reg( ctx, ADC25_REG_STEPX_PAGE_POINTER, ADC25_PAGE_GENERAL_CFG );

    return error_flag;
}

static err_t adc25_wait_drdy ( adc25_t *ctx )
{
    uint16_t cnt = ADC25_TIMEOUT_MS;

    while ( adc25_get_data_ready( ctx ) )
    {
        if ( 0 == cnt )
        {
            return ADC25_ERROR;
        }
        cnt--;
        Delay_1ms( );
    }

    return ADC25_OK;
}

// ------------------------------------------------------------------------- END
