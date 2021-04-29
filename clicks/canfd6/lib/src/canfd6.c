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
 * @file canfd6.c
 * @brief CAN FD 6 Click Driver.
 */

#include "canfd6.h"

// ------------------------------------------------------------- PRIVATE MACROS

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                                                   0x00

/**
 * @brief Bitmask last 4 bits.
 * @details Bitmask for masking least significant 4 bits.
 */
#define DEV_BITMASK_LASTB_4                                     0x0F

/**
 * @brief Bitmask last 5 bits.
 * @details Bitmask for masking least significant 5 bits.
 */
#define DEV_BITMASK_LASTB_5                                     0x1F

/**
 * @brief Bitmask last 6 bits.
 * @details Bitmask for masking least significant 6 bits.
 */
#define DEV_BITMASK_LASTB_6                                     0x3F

/**
 * @brief Bitmask last 7 bits.
 * @details Bitmask for masking least significant 7 bits.
 */
#define DEV_BITMASK_LASTB_7                                     0x7F

/**
 * @brief Bitmask last 8 bits.
 * @details Bitmask for masking a whole least significant byte.
 */
#define DEV_BITMASK_LASTB_8                                     0xFF

/**
 * @brief Bitmask last 9 bits.
 * @details Bitmask for masking a least significant 9 bits.
 */
#define DEV_BITMASK_LASTB_9                                     0x1FF

/**
 * @brief Bitmask last 6 bits of MSByte.
 * @details Bitmask for masking 6 bits of a most significant byte (uint16_t).
 */
#define DEV_BITMASK_FIRSTB_6                                    0x3F00

/**
 * @brief Bitmask half word.
 * @details Bitmask for masking a half of the word (uint32_t).
 */
#define DEV_BITMASK_HWORD                                       0x0000FFFF

/**
 * @brief Bitmask last 29 bits.
 * @details Bitmask for masking a least significant 29 bits.
 */
#define DEV_BITMASK_LASTB_29                                    0x1FFFFFFF

/**
 * @brief Bitmask second byte.
 * @details Bitmask for masking a second byte (uint32_t).
 */
#define DEV_BITMASK_SECOND_BYTE                                 0x00FF0000

/**
 * @brief Bitmask all.
 * @details Bitmask for masking a whole word.
 */
#define DEV_BITMASK_ALL                                         0xFFFFFFFF

/**
 * @brief Mask lsb.
 * @details Mask for a least significant bit.
 */
#define DEV_MASK_BIT_1                                          0x01

/**
 * @brief Mask bit 30.
 * @details Mask for bit 30 from a whole word.
 */
#define DEV_MASK_BIT_30                                         0x20000000

/**
 * @brief Mask bit 31.
 * @details Mask for bit 31 from a whole word.
 */
#define DEV_MASK_BIT_31                                         0x40000000

/**
 * @brief Mask bit 32.
 * @details Mask for bit 32 from a whole word.
 */
#define DEV_MASK_BIT_32                                         0x80000000

/**
 * @brief Bitmask normal ID.
 * @details Bitmask for a normal header ID.
 */
#define DEV_BITMASK_NORMAL_ID                                   0x1FFC0000

/**
 * @brief Bitmask extended ID.
 * @details Bitmask for a extended header ID.
 */
#define DEV_BITMASK_EXTENDED_ID                                 0x1FFFFFFF

/**
 * @brief Bitmask DLC.
 * @details Bitmask for a header DLC data.
 */
#define DEV_BITMASK_DLC                                         0x000F0000

/**
 * @brief Bitmask BRS.
 * @details Bitmask for a header BRS data.
 */
#define DEV_BITMASK_BRS                                         0x00100000

/**
 * @brief Bitmask FDF.
 * @details Bitmask for a header FDF data.
 */
#define DEV_BITMASK_FDF                                         0x00200000

/**
 * @brief Bitmask FIDX.
 * @details Bitmask for a header FIDX data.
 */
#define DEV_BITMASK_FIDX                                        0x7F000000

/**
 * @brief Write opcode.
 * @details Opcode for initialization of write data to the device.
 */
#define DEV_WRITE_OPCODE                                        0x61

/**
 * @brief Read opcode.
 * @details Opcode for initialization of read data to the device.
 */
#define DEV_READ_OPCODE                                         0x41

#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
/**
 * @brief MCAN Cache.
 * @details If caching is enabled, defines the necessary variables.
 */
uint32_t CANFD6_MCAN_CACHE[ 9 ];
#endif

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

//-----------------------------------------------------------------------------
//                                Write Functions
//-----------------------------------------------------------------------------

/**
 * @brief CAN FD 6 single word write function.
 * @details This function writes a single 32-bit word to a desired address.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] address : A 16-bit address of the destination register.
 * @param[in] data_in : A 32-bit word of data to write to the destination register.
 *
 * @note None.
 */
static void dev_write_word ( canfd6_t *ctx, uint16_t address, uint32_t data_in );

/**
 * @brief CAN FD 6 burst write init function.
 * @details This function is the start, where the register address and number of
 * words are transmitted.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] address : A 16-bit address of the destination register.
 * @param[in] words : The number of 4-byte words that will be transferred.
 *
 * @note None.
 */
static void dev_burst_write_init ( canfd6_t *ctx, uint16_t address, uint8_t words );

/**
 * @brief CAN FD 6 burst write data function.
 * @details This function writes a single word at a time.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] data_in : A 32-bit word of data to write to the destination register.
 *
 * @note None.
 */
static void dev_burst_write_data ( canfd6_t *ctx, uint32_t data_in );

/**
 * @brief CAN FD 6 burst write terminate function.
 * @details This function ends the burst transaction by pulling CS high.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 *
 * @note None.
 */
static void dev_burst_write_terminate ( canfd6_t *ctx );

//-----------------------------------------------------------------------------
//                                 Read Functions
//-----------------------------------------------------------------------------

/**
 * @brief CAN FD 6 single word read function.
 * @details This function reads a single 32-bit from a desired address.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] address : A 16-bit address of the destination register.
 * @return A 32-bit word of data from source register.
 *
 * @note None.
 */
static uint32_t dev_read_word ( canfd6_t *ctx, uint16_t address );

/**
 * @brief CAN FD 6 burst read init function.
 * @details This function is the start, where the register address and number of
 * words are transmitted.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] address : A 16-bit address of the destination register.
 * @param[in] words : The number of 4-byte words that will be transferred.
 *
 * @note None.
 */
static void dev_burst_read_init ( canfd6_t *ctx, uint16_t address, uint8_t words );

/**
 * @brief CAN FD 6 burst read data function.
 * @details This function reads a single word at a time.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @return A 32-bit single data word that is read at a time.
 *
 * @note None.
 */
static uint32_t dev_burst_read_data ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 burst read terminate function.
 * @details This function ends the burst transaction by pulling CS high.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 *
 * @note None.
 */
static void dev_burst_read_terminate ( canfd6_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void canfd6_cfg_setup ( canfd6_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->wkr  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->wkp  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t canfd6_init ( canfd6_t *ctx, canfd6_cfg_t *cfg ) {
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

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->wkr, cfg->wkr );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wkp, cfg->wkp );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

void canfd6_default_cfg ( canfd6_t *ctx ) {
    // Click default configuration.
    canfd6_rst_pin_state( ctx, CANFD6_PIN_STATE_LOW );
    canfd6_wkr_pin_state( ctx, CANFD6_PIN_STATE_LOW );
    canfd6_wkp_pin_state( ctx, CANFD6_PIN_STATE_LOW );
    
    canfd6_device_clear_spierr( ctx );

    canfd6_device_interrupt_enable_t canfd6_dev_ie = { 0 };
    canfd6_device_configure_ie( ctx, &canfd6_dev_ie );

    canfd6_device_interrupts_t canfd6_dev_ir = { 0 };
    canfd6_device_read_interrupts( ctx, &canfd6_dev_ir );

    if ( canfd6_dev_ir.PWRON ) {
        canfd6_device_clear_interrupts( ctx, &canfd6_dev_ir );
    }

    canfd6_mcan_nominal_timing_simple_t canfd6_nominal_timing = { 0 };
    canfd6_nominal_timing.nominal_bitrate_prescaler = 2;
    canfd6_nominal_timing.nominal_tqbefore_samplepoint = 32;
    canfd6_nominal_timing.nominal_tqafter_samplepoint = 8;

    canfd6_mcan_data_timing_simple_t canfd6_data_timing = { 0 };
    canfd6_data_timing.data_bitrate_prescaler = 1;
    canfd6_data_timing.data_tqbefore_samplepoint = 15;
    canfd6_data_timing.data_tqafter_samplepoint = 5;

    canfd6_mcan_cccr_config_t canfd6_cccr_config = { 0 };
    canfd6_cccr_config.FDOE = 1;
    canfd6_cccr_config.BRSE = 1;

    canfd6_mcan_global_filter_configuration_t canfd6_gfc = { 0 };
    canfd6_gfc.RRFE = 1;
    canfd6_gfc.RRFS = 1;
    canfd6_gfc.ANFE = CANFD6_GFC_ACCEPT_INTO_RXFIFO0;
    canfd6_gfc.ANFS = CANFD6_GFC_ACCEPT_INTO_RXFIFO0;

    canfd6_mram_config_t canfd6_mram_configuration = { 0 };
    canfd6_mram_configuration.sid_num_elements = 1;
    canfd6_mram_configuration.xid_num_elements = 1;
    canfd6_mram_configuration.rx0_num_elements = 5;
    canfd6_mram_configuration.rx0_element_size = CANFD6_MRAM_64_Byte_Data;
    canfd6_mram_configuration.rx1_num_elements = 0;
    canfd6_mram_configuration.rx1_element_size = CANFD6_MRAM_64_Byte_Data;
    canfd6_mram_configuration.rx_buf_num_elements = 0;
    canfd6_mram_configuration.rx_buf_element_size = CANFD6_MRAM_64_Byte_Data;
    canfd6_mram_configuration.tx_event_fifo_num_elements = 0;
    canfd6_mram_configuration.tx_buffer_num_elements = 2;
    canfd6_mram_configuration.tx_buf_element_size = CANFD6_MRAM_64_Byte_Data;

    canfd6_enable_protected_registers( ctx );
    canfd6_configure_cccr_register( ctx, &canfd6_cccr_config );
    canfd6_mcan_configure_globalfilter( ctx, &canfd6_gfc );
    canfd6_mcan_configure_nominaltiming_simple( ctx, &canfd6_nominal_timing );
    canfd6_mcan_configure_datatiming_simple( ctx, &canfd6_data_timing );
    canfd6_mram_clear( ctx );
    canfd6_mram_configure( ctx, &canfd6_mram_configuration );
    canfd6_disable_protected_registers( ctx );

    canfd6_mcan_interrupt_enable_t canfd6_mcan_ie = { 0 };
    canfd6_mcan_ie.RF0NE = 1;

    canfd6_mcan_configure_interrupt_enable( ctx, &canfd6_mcan_ie );

    canfd6_mcan_sid_filter_t canfd6_sid_id = { 0 };
    canfd6_sid_id.SFT = CANFD6_SID_SFT_CLASSIC;
    canfd6_sid_id.SFEC = CANFD6_SID_SFEC_PRIORITYSTORERX0;
    canfd6_sid_id.SFID1 = 0x055;
    canfd6_sid_id.SFID2 = 0x7FF;
    canfd6_mcan_write_sid_filter( ctx, 0, &canfd6_sid_id );

    canfd6_mcan_xid_filter_t canfd6_xid_id = { 0 };
    canfd6_xid_id.EFT = CANFD6_XID_EFT_CLASSIC;
    canfd6_xid_id.EFEC = CANFD6_XID_EFEC_PRIORITYSTORERX0;
    canfd6_xid_id.EFID1 = 0x12345678;
    canfd6_xid_id.EFID2 = 0x1FFFFFFF;
    canfd6_mcan_write_xid_filter( ctx, 0, &canfd6_xid_id );

    canfd6_dev_config_t canfd6_dev_config = { 0 };
    canfd6_dev_config.SWE_DIS = 0;
    canfd6_dev_config.DEVICE_RESET = 0;
    canfd6_dev_config.WD_EN = 0;
    canfd6_dev_config.nWKRQ_CONFIG = 0;
    canfd6_dev_config.INH_DIS = 0;
    canfd6_dev_config.GPIO1_GPO_CONFIG = CANFD6_DEV_CONFIG_GPO1_MCAN_INT1;
    canfd6_dev_config.FAIL_SAFE_EN = 0;
    canfd6_dev_config.GPIO1_CONFIG = CANFD6_DEV_CONFIG_GPIO1_CONFIG_GPO;
    canfd6_dev_config.WD_ACTION = CANFD6_DEV_CONFIG_WDT_ACTION_nINT;
    canfd6_dev_config.WD_BIT_RESET = 0;
    canfd6_dev_config.nWKRQ_VOLTAGE = 0;
    canfd6_dev_config.GPO2_CONFIG = CANFD6_DEV_CONFIG_GPO2_NO_ACTION;
    canfd6_dev_config.CLK_REF = 1;
    canfd6_dev_config.WAKE_CONFIG = CANFD6_DEV_CONFIG_WAKE_BOTH_EDGES;
    canfd6_device_configure( ctx, &canfd6_dev_config );

    canfd6_device_set_mode( ctx, CANFD6_DEVICE_MODE_NORMAL );

    canfd6_mcan_clear_interrupts_all( ctx );
}

void canfd6_wkr_pin_state ( canfd6_t *ctx, canfd6_pin_state_t state ) {
    digital_out_write( &ctx->wkr, state );
}

void canfd6_rst_pin_state ( canfd6_t *ctx, canfd6_pin_state_t state ) {
    digital_out_write( &ctx->rst, state );
}

void canfd6_wkp_pin_state ( canfd6_t *ctx, canfd6_pin_state_t state ) {
    digital_out_write( &ctx->wkp, state );
}

uint8_t canfd6_get_int_pin ( canfd6_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

err_t canfd6_enable_protected_registers ( canfd6_t *ctx ) {
    uint8_t cnt_f;
    uint32_t read_val;
    uint32_t first_read;

    first_read = dev_read_word( ctx, CANFD6_REG_MCAN_CCCR );
    
    if ( ( first_read & ( CANFD6_REG_BITS_MCAN_CCCR_CCE | CANFD6_REG_BITS_MCAN_CCCR_INIT ) ) == ( CANFD6_REG_BITS_MCAN_CCCR_CCE | CANFD6_REG_BITS_MCAN_CCCR_INIT ) ) {
        return CANFD6_OK;
    }

    first_read &= ~( CANFD6_REG_BITS_MCAN_CCCR_CSA | CANFD6_REG_BITS_MCAN_CCCR_CSR | CANFD6_REG_BITS_MCAN_CCCR_CCE | CANFD6_REG_BITS_MCAN_CCCR_INIT );
    
    for ( cnt_f = 5; cnt_f > 0; cnt_f-- ) {
        dev_write_word( ctx, CANFD6_REG_MCAN_CCCR, first_read | CANFD6_REG_BITS_MCAN_CCCR_CCE | CANFD6_REG_BITS_MCAN_CCCR_INIT );
        read_val = dev_read_word( ctx, CANFD6_REG_MCAN_CCCR );

        if ( ( read_val & ( CANFD6_REG_BITS_MCAN_CCCR_CCE | CANFD6_REG_BITS_MCAN_CCCR_INIT ) ) == ( CANFD6_REG_BITS_MCAN_CCCR_CCE | CANFD6_REG_BITS_MCAN_CCCR_INIT ) ) {
            return CANFD6_OK;
        } else if ( cnt_f == 1 ) {
            return CANFD6_ERROR;
        }
    }
    
    return CANFD6_OK;
}

err_t canfd6_disable_protected_registers ( canfd6_t *ctx ) {
    uint8_t cnt_f;
    uint32_t read_val;

    read_val = dev_read_word( ctx, CANFD6_REG_MCAN_CCCR );
    
    if ( ( read_val & CANFD6_REG_BITS_MCAN_CCCR_CCE ) == 0 ) {
        return CANFD6_OK;
    }
    
    for ( cnt_f = 5; cnt_f > 0; cnt_f-- ) {
        dev_write_word( ctx, CANFD6_REG_MCAN_CCCR, ( read_val & ~( CANFD6_REG_BITS_MCAN_CCCR_CSA | CANFD6_REG_BITS_MCAN_CCCR_CSR | CANFD6_REG_BITS_MCAN_CCCR_CCE | CANFD6_REG_BITS_MCAN_CCCR_INIT ) ) );
        read_val = dev_read_word( ctx, CANFD6_REG_MCAN_CCCR );

        if ( ( read_val & CANFD6_REG_BITS_MCAN_CCCR_CCE ) == 0 ) {
            return CANFD6_OK;
        } else if ( cnt_f == 1 ) {
            return CANFD6_ERROR;
        }
    }
    
    return CANFD6_OK;
}

void canfd6_configure_cccr_register ( canfd6_t *ctx, canfd6_mcan_cccr_config_t *cccr_config ) {
    uint32_t value;

    value = cccr_config->word;
    value &= ~( CANFD6_REG_BITS_MCAN_CCCR_RESERVED_MASK | CANFD6_REG_BITS_MCAN_CCCR_CSA | CANFD6_REG_BITS_MCAN_CCCR_CCE | CANFD6_REG_BITS_MCAN_CCCR_INIT );
    value |= ( CANFD6_REG_BITS_MCAN_CCCR_INIT | CANFD6_REG_BITS_MCAN_CCCR_CCE );

    dev_write_word( ctx, CANFD6_REG_MCAN_CCCR, value );
}

void canfd6_read_cccr_register ( canfd6_t *ctx, canfd6_mcan_cccr_config_t *cccr_config ) {
    cccr_config->word = dev_read_word( ctx, CANFD6_REG_MCAN_CCCR );
}

void canfd6_mcan_read_datatimingfd_simple ( canfd6_t *ctx, canfd6_mcan_data_timing_simple_t *data_timing ) {
    uint32_t reg_data;

    reg_data = dev_read_word( ctx, CANFD6_REG_MCAN_DBTP );

    data_timing->data_bitrate_prescaler = ( ( reg_data >> 16 ) & DEV_BITMASK_LASTB_5 ) + 1;
    data_timing->data_tqbefore_samplepoint = ( ( reg_data >> 8 ) & DEV_BITMASK_LASTB_5 ) + 2;
    data_timing->data_tqafter_samplepoint = ( ( reg_data >> 4 ) & DEV_BITMASK_LASTB_4 ) + 1;
}

void canfd6_mcan_read_datatimingfd_raw ( canfd6_t *ctx, canfd6_mcan_data_timing_raw_t *data_timing ) {
    uint32_t reg_data;

    reg_data = dev_read_word( ctx, CANFD6_REG_MCAN_DBTP );

    data_timing->data_bitrate_prescaler = ( ( reg_data >> 16 ) & DEV_BITMASK_LASTB_5 );
    data_timing->data_time_seg1_and_prop = ( ( reg_data >> 8 ) & DEV_BITMASK_LASTB_5 );
    data_timing->data_time_seg2 = ( ( reg_data >> 4 ) & DEV_BITMASK_LASTB_4 );
    data_timing->data_sync_jumpwidth = ( reg_data & DEV_BITMASK_LASTB_4 );

    if ( reg_data & CANFD6_REG_BITS_MCAN_DBTP_TDC_EN ) {
        reg_data = dev_read_word( ctx, CANFD6_REG_MCAN_TDCR );
        data_timing->tdc_offset = ( ( reg_data >> 8 ) & DEV_BITMASK_LASTB_7 );
        data_timing->tdc_filter = ( reg_data & DEV_BITMASK_LASTB_7 );
    } else {
        data_timing->tdc_offset = 0;
        data_timing->tdc_filter = 0;
    }
}

void canfd6_mcan_configure_datatiming_simple ( canfd6_t *ctx, canfd6_mcan_data_timing_simple_t *data_timing ) {
    uint32_t write_val;
    uint32_t tdco_write_val;
    uint32_t temp_val;

    temp_val = data_timing->data_bitrate_prescaler;
    if ( temp_val > 32 ) {
        temp_val = 32;
    } else if ( temp_val == 0 ) {
        temp_val = 1;
    }

    write_val = ( ( uint32_t )( temp_val - 1 ) ) << 16;

    temp_val = data_timing->data_tqbefore_samplepoint;
    if ( temp_val > 33 ) {
        temp_val = 33;
    } else if ( temp_val < 2 ) {
        temp_val = 2;
    }

    write_val |= ( ( uint32_t )( temp_val - 2 ) ) << 8;
    tdco_write_val = ( uint32_t )( temp_val - 1 ) << 8;
    
    temp_val = data_timing->data_tqafter_samplepoint;
    if ( temp_val > 16 ) {
        temp_val = 16;
    } else if ( temp_val == 0 ) {
        temp_val = 1;
    }

    write_val |= ( ( uint32_t )( temp_val - 1 ) ) << 4;

    write_val |= ( ( uint32_t )( temp_val - 1 ) );

    write_val |= CANFD6_REG_BITS_MCAN_DBTP_TDC_EN;
    dev_write_word( ctx, CANFD6_REG_MCAN_DBTP, write_val );

    dev_write_word( ctx, CANFD6_REG_MCAN_TDCR, tdco_write_val );

    dev_write_word( ctx, CANFD6_REG_MCAN_TSCC, CANFD6_REG_BITS_MCAN_TSCC_COUNTER_EXTERNAL );
}

void canfd6_mcan_configure_datatiming_raw ( canfd6_t *ctx, canfd6_mcan_data_timing_raw_t *data_timing ) {
    uint32_t write_val;

    write_val = ( ( uint32_t )( data_timing->data_bitrate_prescaler & DEV_BITMASK_LASTB_5 ) ) << 16;
    write_val |= ( ( uint32_t )( data_timing->data_time_seg1_and_prop & DEV_BITMASK_LASTB_5 ) ) << 8;
    write_val |= ( ( uint32_t )( data_timing->data_time_seg2 & DEV_BITMASK_LASTB_4 ) ) << 4;
    write_val |= ( ( uint32_t )( data_timing->data_sync_jumpwidth & DEV_BITMASK_LASTB_4 ) );
    
    if ( ( data_timing->tdc_offset > 0 ) || ( data_timing->tdc_filter > 0 ) ) {
        write_val |= CANFD6_REG_BITS_MCAN_DBTP_TDC_EN;
        dev_write_word( ctx, CANFD6_REG_MCAN_DBTP, write_val );

        write_val = ( uint32_t )( data_timing->tdc_offset & DEV_BITMASK_LASTB_7 ) << 8;
        write_val |= ( uint32_t )( data_timing->tdc_filter & DEV_BITMASK_LASTB_7 );
        dev_write_word( ctx, CANFD6_REG_MCAN_TDCR, write_val );
    } else {
        dev_write_word( ctx, CANFD6_REG_MCAN_DBTP, write_val );
    }

    dev_write_word( ctx, CANFD6_REG_MCAN_TSCC, CANFD6_REG_BITS_MCAN_TSCC_COUNTER_EXTERNAL );
}

void canfd6_mcan_read_nominaltiming_simple ( canfd6_t *ctx, canfd6_mcan_nominal_timing_simple_t *nom_timing ) {
    uint32_t read_val;

    read_val = dev_read_word( ctx, CANFD6_REG_MCAN_NBTP );

    nom_timing->nominal_bitrate_prescaler = ( ( read_val >> 16 ) & DEV_BITMASK_LASTB_9 ) + 1;
    nom_timing->nominal_tqbefore_samplepoint = ( ( read_val >> 8 ) & DEV_BITMASK_LASTB_8 ) + 2;
    nom_timing->nominal_tqafter_samplepoint = ( read_val & DEV_BITMASK_LASTB_7 ) + 1;
}

void canfd6_mcan_read_nominaltiming_raw ( canfd6_t *ctx, canfd6_mcan_nominal_timing_raw_t *nom_timing ) {
    uint32_t read_val;

    read_val = dev_read_word( ctx, CANFD6_REG_MCAN_NBTP );

    nom_timing->nominal_sync_jumpwidth = ( ( read_val >> 25 ) & DEV_BITMASK_LASTB_7 );
    nom_timing->nominal_bitrate_prescaler = ( ( read_val >> 16 ) & DEV_BITMASK_LASTB_9 );
    nom_timing->nominal_time_seg1_and_prop = ( ( read_val >> 8 ) & DEV_BITMASK_LASTB_8 );
    nom_timing->nominal_time_seg2 = ( read_val & DEV_BITMASK_LASTB_7 );
}

void canfd6_mcan_configure_nominaltiming_simple ( canfd6_t *ctx, canfd6_mcan_nominal_timing_simple_t *nom_timing ) {
    uint32_t write_val;
    uint32_t temp_val;

    temp_val = nom_timing->nominal_bitrate_prescaler;
    if ( temp_val > 512 ) {
        temp_val = 512;
    } else if ( temp_val == 0 ) {
        temp_val = 1;
    }
    write_val = ( ( uint32_t )( temp_val - 1 ) ) << 16;

    temp_val = nom_timing->nominal_tqbefore_samplepoint;
    if ( temp_val > 257 ) {
        temp_val = 257;
    } else if ( temp_val < 2 ) {
        temp_val = 2;
    }
    write_val |= ( ( uint32_t )( temp_val - 2 ) ) << 8;

    temp_val = nom_timing->nominal_tqafter_samplepoint;
    if ( temp_val > 128 ) {
        temp_val = 128;
    } else if ( temp_val < 2 ) {
        temp_val = 2;
    }
    write_val |= ( ( uint32_t )( temp_val - 1 ) );
    write_val |= ( ( uint32_t )( temp_val - 1 ) ) << 25;

    dev_write_word( ctx, CANFD6_REG_MCAN_NBTP, write_val );
}

void canfd6_mcan_configure_nominaltiming_raw ( canfd6_t *ctx, canfd6_mcan_nominal_timing_raw_t *nom_timing ) {
    uint32_t write_val;

    write_val = ( ( uint32_t )( nom_timing->nominal_sync_jumpwidth & DEV_BITMASK_LASTB_7 ) ) << 25;
    write_val |= ( ( uint32_t )( nom_timing->nominal_bitrate_prescaler & DEV_BITMASK_LASTB_9 ) ) << 16;
    write_val |= ( ( uint32_t )( nom_timing->nominal_time_seg1_and_prop ) ) << 8;
    write_val |= ( ( uint32_t )( nom_timing->nominal_time_seg2 & DEV_BITMASK_LASTB_7 ) );
    dev_write_word( ctx, CANFD6_REG_MCAN_NBTP, write_val );
}

void canfd6_mcan_configure_globalfilter ( canfd6_t *ctx, canfd6_mcan_global_filter_configuration_t *gfc ) {
    uint32_t write_val;

    write_val = ( gfc->word & CANFD6_REG_BITS_MCAN_GFC_MASK );
    dev_write_word( ctx, CANFD6_REG_MCAN_GFC, write_val );
}

err_t canfd6_mram_configure ( canfd6_t *ctx, canfd6_mram_config_t *mram_config ) {
    uint16_t start_address = 0x0000;
    uint32_t register_value = 0;
    uint32_t read_val = 0;
    uint8_t mram_val;

    mram_val = mram_config->sid_num_elements;
    if ( mram_val > 128 ) {
        mram_val = 128;
    }

    register_value = 0;
    if ( mram_val > 0 ) {
        register_value = ( ( uint32_t )( mram_val ) << 16 ) | ( ( uint32_t )start_address );
    }
    start_address += ( 4 * ( uint16_t )mram_val );
    dev_write_word( ctx, CANFD6_REG_MCAN_SIDFC, register_value );
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_SIDFC ] = register_value;
#endif

    mram_val = mram_config->xid_num_elements;
    if ( mram_val > 64 ) {
        mram_val = 64;
    }

    register_value = 0;
    if ( mram_val > 0 ) {
        register_value = ( ( uint32_t )( mram_val ) << 16 ) | ( ( uint32_t )start_address );
    }
    start_address += ( 8 * ( uint16_t )mram_val );
    dev_write_word( ctx, CANFD6_REG_MCAN_XIDFC, register_value );
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_XIDFC ] = register_value;
#endif

    mram_val = mram_config->rx0_num_elements;
    if ( mram_val > 64 ) {
        mram_val = 64;
    }

    register_value = 0;
    if ( mram_val > 0 ) {
        register_value = ( ( uint32_t )( mram_val ) << 16 ) | ( ( uint32_t )start_address );
        register_value |= CANFD6_REG_BITS_MCAN_RXF0C_F0OM_OVERWRITE;
    }
    start_address += ( ( ( uint32_t )canfd6_mcan_txrxesc_data_byte_value( ( uint8_t )mram_config->rx0_element_size ) + 8 ) * ( uint16_t )mram_val );
    dev_write_word( ctx, CANFD6_REG_MCAN_RXF0C, register_value );
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_RXF0C ] = register_value;
#endif

    mram_val = mram_config->rx1_num_elements;
    if ( mram_val > 64 ) {
        mram_val = 64;
    }

    register_value = 0;
    if ( mram_val > 0 ) {
        register_value = ( ( uint32_t )( mram_val ) << 16 ) | ( ( uint32_t )start_address );
    }
    start_address += ( ( ( uint32_t )canfd6_mcan_txrxesc_data_byte_value( ( uint8_t )mram_config->rx1_element_size ) + 8 ) * ( uint16_t )mram_val );
    dev_write_word( ctx, CANFD6_REG_MCAN_RXF1C, register_value );
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_RXF1C ] = register_value;
#endif

    mram_val = mram_config->rx_buf_num_elements;
    if ( mram_val > 64 ) {
        mram_val = 64;
    }

    register_value = 0;
    if ( mram_val > 0 ) {
        register_value = ( ( uint32_t )start_address );
    }
    start_address += ( ( ( uint32_t )canfd6_mcan_txrxesc_data_byte_value( ( uint8_t )mram_config->rx_buf_element_size ) + 8 ) * ( uint16_t )mram_val );
    dev_write_word( ctx, CANFD6_REG_MCAN_RXBC, register_value );
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_RXBC ] = register_value;
#endif

    mram_val = mram_config->tx_event_fifo_num_elements;
    if ( mram_val > 32 ) {
        mram_val = 32;
    }

    register_value = 0;
    if ( mram_val > 0 ) {
        register_value = ( ( uint32_t )( mram_val ) << 16 ) | ( ( uint32_t )start_address );
    }
    start_address += ( 8 * ( uint16_t )mram_val );
    dev_write_word( ctx, CANFD6_REG_MCAN_TXEFC, register_value );
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_TXEFC ] = register_value;
#endif

    mram_val = mram_config->tx_buffer_num_elements;
    if ( mram_val > 32 ) {
        mram_val = 32;
    }

    register_value = 0;
    if ( mram_val > 0 ) {
        register_value = ( ( uint32_t )( mram_val ) << 24 ) | ( ( uint32_t )start_address );
        register_value |= CANFD6_REG_BITS_MCAN_TXBC_TFQM;
    }
    start_address += ( ( ( uint32_t )canfd6_mcan_txrxesc_data_byte_value( ( uint8_t )mram_config->tx_buf_element_size ) + 8 ) * ( uint16_t )mram_val );
    dev_write_word( ctx, CANFD6_REG_MCAN_TXBC, register_value );
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_TXBC ] = register_value;
#endif

    if ( ( start_address - 1 ) > ( CANFD6_MRAM_SIZE + CANFD6_REG_MRAM ) ) {
        return CANFD6_ERROR;
    }

    register_value = ( ( uint32_t )( mram_config->rx_buf_element_size ) << 8 ) | ( ( uint32_t )( mram_config->rx1_element_size ) << 4 ) | ( uint32_t )( mram_config->rx0_element_size );
    dev_write_word( ctx, CANFD6_REG_MCAN_RXESC, register_value );
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_RXESC ] = register_value;
#endif

    register_value = ( uint32_t )( mram_config->tx_buf_element_size );
    dev_write_word( ctx, CANFD6_REG_MCAN_TXESC, register_value );
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_TXESC ] = register_value;
#endif

    return CANFD6_OK;
}

void canfd6_mram_clear ( canfd6_t *ctx ) {
    uint16_t cur_addr;
    const uint16_t end_addr = CANFD6_REG_MRAM + CANFD6_MRAM_SIZE;

    cur_addr = CANFD6_REG_MRAM;

    while ( cur_addr < end_addr ) {
        dev_write_word( ctx, cur_addr, 0 );
        cur_addr += 4;
    }
}

uint8_t canfd6_mcan_read_nextfifo ( canfd6_t *ctx, canfd6_mcan_fifo_enum_t fifo_def, canfd6_mcan_rx_header_t *header, uint8_t data_payload[ ] ) {
    uint32_t rd_data;
    uint16_t start_address;
    uint8_t cnt_f;
    uint8_t get_index;
    uint8_t element_size;

    switch ( fifo_def ) {
        default: {
            rd_data = dev_read_word( ctx, CANFD6_REG_MCAN_RXF0S );
            if ( ( rd_data & DEV_BITMASK_LASTB_7 ) == 0 ) {
                return 0;
            }
            get_index = ( uint8_t )( ( rd_data & DEV_BITMASK_FIRSTB_6 ) >> 8 );
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
            rd_data = CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_RXF0C ];
#else
            rd_data = dev_read_word( ctx, CANFD6_REG_MCAN_RXF0C );
#endif
            start_address = ( uint16_t )( rd_data & DEV_BITMASK_HWORD ) + CANFD6_REG_MRAM;
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
            rd_data = CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_RXESC ];
#else
            rd_data = dev_read_word( ctx, CANFD6_REG_MCAN_RXESC );
#endif
            rd_data &= 0x07;
            element_size = canfd6_mcan_txrxesc_data_byte_value( rd_data );
            start_address += ( ( ( uint32_t )element_size + 8 ) * get_index );
            break;
        }

        case CANFD6_RXFIFO1: {
            rd_data = dev_read_word( ctx, CANFD6_REG_MCAN_RXF1S );
            if ( ( rd_data & DEV_BITMASK_LASTB_7 ) == 0 ) {
                return 0;
            }
            get_index = ( uint8_t )( ( rd_data & DEV_BITMASK_FIRSTB_6 ) >> 8 );
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
            rd_data = CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_RXF1C ];
#else
            rd_data = dev_read_word( ctx, CANFD6_REG_MCAN_RXF1C );
#endif
            start_address = ( uint16_t )( rd_data & DEV_BITMASK_HWORD ) + CANFD6_REG_MRAM;
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
            rd_data = CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_RXESC ];
#else
            rd_data = dev_read_word( ctx, CANFD6_REG_MCAN_RXESC );
#endif
            rd_data = ( rd_data & 0x70 ) >> 4;
            element_size = canfd6_mcan_txrxesc_data_byte_value( rd_data );
            start_address += ( ( ( uint32_t )element_size + 8 ) * get_index );
            break;
        }
    }

    dev_burst_read_init( ctx, start_address, 2 );
    rd_data = dev_burst_read_data( ctx );
    header->ESI = ( rd_data & DEV_MASK_BIT_32 ) >> 31;
    header->XTD = ( rd_data & DEV_MASK_BIT_31 ) >> 30;
    header->RTR = ( rd_data & DEV_MASK_BIT_30 ) >> 29;

    if ( header->XTD ) {
        header->ID  = ( rd_data & DEV_BITMASK_EXTENDED_ID );
    } else {
        header->ID  = ( rd_data & DEV_BITMASK_NORMAL_ID ) >> 18;
    }

    rd_data = dev_burst_read_data( ctx );
    dev_burst_read_terminate( ctx );
    header->RXTS = ( rd_data & DEV_BITMASK_HWORD );
    header->DLC  = ( rd_data & DEV_BITMASK_DLC  ) >> 16;
    header->BRS  = ( rd_data & DEV_BITMASK_BRS  ) >> 20;
    header->FDF  = ( rd_data & DEV_BITMASK_FDF  ) >> 21;
    header->FIDX = ( rd_data & DEV_BITMASK_FIDX ) >> 24;
    header->ANMF = ( rd_data & DEV_MASK_BIT_32  ) >> 31;

    if ( canfd6_mcan_dlc_to_bytes( header->DLC ) < element_size ) {
        element_size = canfd6_mcan_dlc_to_bytes( header->DLC );
    }

    if ( element_size > 0 ) {
        dev_burst_read_init( ctx, start_address + 8, ( element_size + 3 ) >> 2 );
        cnt_f = 0;
        while ( cnt_f < element_size ) {
            if ( ( cnt_f % 4 ) == 0 ) {
                rd_data = dev_burst_read_data( ctx );
            }

            data_payload[ cnt_f ] = ( uint8_t )( ( rd_data >> ( ( cnt_f % 4 ) * 8 ) ) & DEV_BITMASK_LASTB_8 );
            cnt_f++;
            if ( cnt_f > element_size ) {
                cnt_f = element_size;
            }
        }
        dev_burst_read_terminate( ctx );
    }
    
    switch ( fifo_def ) {
        default:
        dev_write_word( ctx, CANFD6_REG_MCAN_RXF0A, get_index );
        break;

        case CANFD6_RXFIFO1:
        dev_write_word( ctx, CANFD6_REG_MCAN_RXF1A, get_index );
        break;
    }

    return cnt_f;
}

uint8_t canfd6_mcan_read_rxbuffer ( canfd6_t *ctx, uint8_t buf_index, canfd6_mcan_rx_header_t *header, uint8_t data_payload[ ] ) {
    uint32_t rd_data;
    uint16_t start_address;
    uint8_t cnt_f;
    uint8_t get_index;
    uint8_t element_size;

    get_index = buf_index;
    if ( get_index > 64 ) {
        get_index = 64;
    }

#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    rd_data = CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_RXBC ];
#else
    rd_data = dev_read_word( ctx, CANFD6_REG_MCAN_RXBC );
#endif
    start_address = ( uint16_t )( rd_data & DEV_BITMASK_HWORD ) + CANFD6_REG_MRAM;
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    rd_data = CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_RXESC ];
#else
    rd_data = dev_read_word( ctx, CANFD6_REG_MCAN_RXESC );
#endif
    rd_data = ( rd_data & 0x0700 ) >> 8;
    element_size = canfd6_mcan_txrxesc_data_byte_value( rd_data );

    start_address += ( ( ( uint32_t )element_size + 8 ) * get_index );

    dev_burst_read_init( ctx, start_address, 2 );
    rd_data = dev_burst_read_data( ctx );
    header->ESI = ( rd_data & DEV_MASK_BIT_32 ) >> 31;
    header->XTD = ( rd_data & DEV_MASK_BIT_31 ) >> 30;
    header->RTR = ( rd_data & DEV_MASK_BIT_30 ) >> 29;

    if ( header->XTD ) {
        header->ID  = ( rd_data & DEV_BITMASK_EXTENDED_ID );
    } else {
        header->ID  = ( rd_data & DEV_BITMASK_NORMAL_ID ) >> 18;
    }

    rd_data = dev_burst_read_data( ctx );
    dev_burst_read_terminate( ctx );
    header->RXTS = ( rd_data & DEV_BITMASK_HWORD );
    header->DLC  = ( rd_data & DEV_BITMASK_DLC  ) >> 16;
    header->BRS  = ( rd_data & DEV_BITMASK_BRS  ) >> 20;
    header->FDF  = ( rd_data & DEV_BITMASK_FDF  ) >> 21;
    header->FIDX = ( rd_data & DEV_BITMASK_FIDX ) >> 24;
    header->ANMF = ( rd_data & DEV_MASK_BIT_32  ) >> 31;

    if ( canfd6_mcan_dlc_to_bytes( header->DLC ) < element_size ) {
        element_size = canfd6_mcan_dlc_to_bytes( header->DLC );
    }

    if ( element_size > 0 ) {
        dev_burst_read_init( ctx, start_address + 8, ( element_size + 3 ) >> 2 );
        cnt_f = 0;
        while ( cnt_f < element_size ) {
            if ( ( cnt_f % 4 ) == 0 ) {
                rd_data = dev_burst_read_data( ctx );
            }

            data_payload[ cnt_f ] = ( uint8_t )( ( rd_data >> ( ( cnt_f % 4 ) * 8 ) ) & DEV_BITMASK_LASTB_8 );
            cnt_f++;
            if ( cnt_f > element_size ) {
                cnt_f = element_size;
            }
        }
        dev_burst_read_terminate( ctx );
    }
    if ( get_index < 32 ) {
        dev_write_word( ctx, CANFD6_REG_MCAN_NDAT1, 1 << get_index );
    } else {
        dev_write_word( ctx, CANFD6_REG_MCAN_NDAT2, 1 << ( get_index - 32 ) );
    }

    return cnt_f;
}

uint32_t canfd6_mcan_write_txbuffer ( canfd6_t *ctx, uint8_t buf_index, canfd6_mcan_tx_header_t *header, uint8_t data_payload[ ] ) {
    uint32_t spi_data;
    uint16_t start_address;
    uint8_t cnt_f;
    uint8_t element_size;
    uint8_t temp;

#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    spi_data = CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_TXBC ];
#else
    spi_data = dev_read_word( ctx, CANFD6_REG_MCAN_TXBC );
#endif
    start_address = ( uint16_t )( spi_data & DEV_BITMASK_HWORD ) + 0x8000;
    temp = ( uint8_t )( ( spi_data >> 24 ) & DEV_BITMASK_LASTB_6 );
    element_size = temp > 32 ? 32 : temp;
    temp = ( uint8_t )( ( spi_data >> 16 ) & DEV_BITMASK_LASTB_6 );
    element_size += temp > 32 ? 32 : temp;

    if ( buf_index > ( element_size - 1 ) ) {
        return 0;
    }

#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    spi_data = CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_TXESC ];
#else
    spi_data = dev_read_word( ctx, CANFD6_REG_MCAN_TXESC );
#endif
    element_size = canfd6_mcan_txrxesc_data_byte_value( spi_data & 0x07 ) + 8;

    start_address += ( ( uint32_t )element_size * buf_index );

    element_size = ( canfd6_mcan_dlc_to_bytes( header->DLC & DEV_BITMASK_LASTB_4 ) + 8 ) >> 2;
    if ( canfd6_mcan_dlc_to_bytes( header->DLC & DEV_BITMASK_LASTB_4 ) % 4 ) {
        element_size += 1;
    }

    dev_burst_write_init( ctx, start_address, element_size );
    spi_data = 0;

    spi_data |= ( ( uint32_t )header->ESI & DEV_MASK_BIT_1 ) << 31;
    spi_data |= ( ( uint32_t )header->XTD & DEV_MASK_BIT_1 ) << 30;
    spi_data |= ( ( uint32_t )header->RTR & DEV_MASK_BIT_1 ) << 29;

    if ( header->XTD )
        spi_data |= ( ( uint32_t )header->ID & DEV_BITMASK_EXTENDED_ID );
    else
        spi_data |= ( ( uint32_t )header->ID & 0x07FF ) << 18;

    dev_burst_write_data( ctx, spi_data );

    spi_data = 0;
    spi_data |= ( ( uint32_t )header->DLC & DEV_BITMASK_LASTB_4 ) << 16;
    spi_data |= ( ( uint32_t )header->BRS & DEV_MASK_BIT_1 ) << 20;
    spi_data |= ( ( uint32_t )header->FDF & DEV_MASK_BIT_1 ) << 21;
    spi_data |= ( ( uint32_t )header->EFC & DEV_MASK_BIT_1 ) << 23;
    spi_data |= ( ( uint32_t )header->MM & DEV_BITMASK_LASTB_8 ) << 24;
    dev_burst_write_data( ctx, spi_data );

    element_size = canfd6_mcan_dlc_to_bytes( header->DLC & DEV_BITMASK_LASTB_4 );
    cnt_f = 0;
    while ( cnt_f < element_size ) {
        spi_data = 0;
        if ( ( element_size - cnt_f ) < 4 ) {
            while ( cnt_f < element_size ) {
                spi_data |= ( ( uint32_t )data_payload[ cnt_f ] << ( ( cnt_f % 4 ) * 8 ) );
                cnt_f++;
            }

            dev_burst_write_data( ctx, spi_data );
        } else {
            spi_data |= ( ( uint32_t )data_payload[ cnt_f++ ] );
            spi_data |= ( ( uint32_t )data_payload[ cnt_f++ ] ) << 8;
            spi_data |= ( ( uint32_t )data_payload[ cnt_f++ ] ) << 16;
            spi_data |= ( ( uint32_t )data_payload[ cnt_f++ ] ) << 24;

            dev_burst_write_data( ctx, spi_data );
        }

        if ( cnt_f > element_size ) {
            cnt_f = element_size;
        }
    }
    dev_burst_write_terminate( ctx );

    return ( uint32_t )1 << buf_index;
}

err_t canfd6_mcan_transmit_buffer_contents ( canfd6_t *ctx, uint8_t buf_index ) {
    uint32_t write_val;
    uint8_t req_buf = buf_index;

    if ( req_buf > 31 ) {
        return CANFD6_ERROR;
    }

    write_val = 1 << req_buf;

    dev_write_word( ctx, CANFD6_REG_MCAN_TXBAR, write_val );
    
    return CANFD6_OK;
}

err_t canfd6_mcan_write_sid_filter ( canfd6_t *ctx, uint8_t filter_index, canfd6_mcan_sid_filter_t *filter ) {
    uint32_t rd_data;
    uint16_t start_address;
    uint8_t get_index;
    
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    rd_data = CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_SIDFC ];
#else
    rd_data = dev_read_word( ctx, CANFD6_REG_MCAN_SIDFC );
#endif
    get_index = ( rd_data & DEV_BITMASK_SECOND_BYTE ) >> 16;
    if ( filter_index > get_index ) {
        return CANFD6_ERROR;
    } else {
        get_index = filter_index;
    }

    start_address = ( uint16_t )( rd_data & DEV_BITMASK_HWORD ) + CANFD6_REG_MRAM;
    
    start_address += ( get_index << 2 );

    dev_write_word( ctx, start_address, filter->word );

    return CANFD6_OK;
}

err_t canfd6_mcan_read_sid_filter ( canfd6_t *ctx, uint8_t filter_index, canfd6_mcan_sid_filter_t *filter ) {
    uint32_t rd_data;
    uint16_t start_address;
    uint8_t get_index;
    
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    rd_data = CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_SIDFC ];
#else
    rd_data = dev_read_word( ctx, CANFD6_REG_MCAN_SIDFC );
#endif
    get_index = ( rd_data & DEV_BITMASK_SECOND_BYTE ) >> 16;
    if ( filter_index > get_index ) {
        return CANFD6_ERROR;
    } else {
        get_index = filter_index;
    }

    start_address = ( uint16_t )( rd_data & DEV_BITMASK_HWORD ) + CANFD6_REG_MRAM;
    
    start_address += ( get_index << 2 );

    filter->word = dev_read_word( ctx, start_address );
    
    return CANFD6_OK;
}

err_t canfd6_mcan_write_xid_filter ( canfd6_t *ctx, uint8_t filter_index, canfd6_mcan_xid_filter_t *filter ) {
    uint32_t rd_data;
    uint32_t wr_data;
    uint16_t start_address;
    uint8_t get_index;
    
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    rd_data = CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_XIDFC ];
#else
    rd_data = dev_read_word( ctx, CANFD6_REG_MCAN_XIDFC );
#endif
    get_index = ( rd_data & DEV_BITMASK_SECOND_BYTE ) >> 16;
    if ( filter_index > get_index ) {
        return CANFD6_ERROR;
    } else {
        get_index = filter_index;
    }

    start_address = ( uint16_t )( rd_data & DEV_BITMASK_HWORD ) + CANFD6_REG_MRAM;

    start_address += ( get_index << 3 );

    wr_data = ( uint32_t )( filter->EFEC ) << 29;
    wr_data |= ( uint32_t )( filter->EFID1 );
    dev_write_word( ctx, start_address, wr_data );

    start_address += 4;
    wr_data = ( uint32_t )( filter->EFT ) << 30;
    wr_data |= ( uint32_t )( filter->EFID2 );
    dev_write_word( ctx, start_address, wr_data );

    return CANFD6_OK;
}

err_t canfd6_mcan_read_xid_filter ( canfd6_t *ctx, uint8_t filter_index, canfd6_mcan_xid_filter_t *filter ) {
    uint32_t rd_data;
    uint16_t start_address;
    uint8_t get_index;
    
#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
    rd_data = CANFD6_MCAN_CACHE[ CANFD6_MCAN_CACHE_XIDFC ];
#else
    rd_data = dev_read_word( ctx, CANFD6_REG_MCAN_XIDFC );
#endif
    get_index = ( rd_data & DEV_BITMASK_SECOND_BYTE ) >> 16;
    if ( filter_index > get_index ) {
        return CANFD6_ERROR;
    } else {
        get_index = filter_index;
    }

    start_address = ( uint16_t )( rd_data & DEV_BITMASK_HWORD ) + CANFD6_REG_MRAM;

    start_address += ( get_index << 3 );

    dev_burst_read_init( ctx, start_address, 2 );
    rd_data = dev_burst_read_data( ctx );

    filter->EFEC = ( canfd6_xid_efec_values_t )( ( rd_data >> 29 ) & 0x07 );
    filter->EFID1 = rd_data & DEV_BITMASK_LASTB_29;

    rd_data = dev_burst_read_data( ctx );
    dev_burst_read_terminate( ctx );
    filter->EFT = ( canfd6_xid_eft_values_t )( ( rd_data >> 30 ) & 0x03 );
    filter->EFID2 = rd_data & DEV_BITMASK_LASTB_29;

    return CANFD6_OK;
}

void canfd6_mcan_read_interrupts ( canfd6_t *ctx, canfd6_mcan_interrupts_t *ir ) {
    ir->word = dev_read_word( ctx, CANFD6_REG_MCAN_IR );
}

void canfd6_mcan_clear_interrupts ( canfd6_t *ctx, canfd6_mcan_interrupts_t *ir ) {
    dev_write_word( ctx, CANFD6_REG_MCAN_IR, ir->word );
}

void canfd6_mcan_clear_interrupts_all ( canfd6_t *ctx ) {
    dev_write_word( ctx, CANFD6_REG_MCAN_IR, DEV_BITMASK_ALL );
}

void canfd6_mcan_read_interrupt_enable ( canfd6_t *ctx, canfd6_mcan_interrupt_enable_t *ie ) {
    ie->word = dev_read_word( ctx, CANFD6_REG_MCAN_IE );
}

void canfd6_mcan_configure_interrupt_enable ( canfd6_t *ctx, canfd6_mcan_interrupt_enable_t *ie ) {
    dev_write_word( ctx, CANFD6_REG_MCAN_IE, ie->word );
    dev_write_word( ctx, CANFD6_REG_MCAN_ILE, CANFD6_REG_BITS_MCAN_ILE_EINT0 );
}

uint8_t canfd6_mcan_dlc_to_bytes ( uint8_t input_dlc ) {
    static const uint8_t lookup[ 7 ] = { 12, 16, 20, 24, 32, 48, 64 };

    if ( input_dlc < 9 ) {
        return input_dlc;
    }

    if ( input_dlc < 16 ) {
        return lookup[ ( uint8_t )( input_dlc - 9 ) ];
    }

    return 0;
}

uint8_t canfd6_mcan_txrxesc_data_byte_value ( uint8_t input_esc_value ) {
    static const uint8_t lookup[ 8 ] = { 8, 12, 16, 20, 24, 32, 48, 64 };
    
    return lookup[ ( uint8_t )( input_esc_value & 0x07 ) ];
}

uint16_t canfd6_device_read_version ( canfd6_t *ctx ) {
    uint32_t read_val;

    read_val = dev_read_word( ctx, CANFD6_REG_SPI_REVISION );

    return ( uint16_t )( read_val & 0xFFFF );
}

void canfd6_device_configure ( canfd6_t *ctx, canfd6_dev_config_t *dev_cfg ) {
    uint32_t read_dev = dev_read_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS );

    read_dev &= ~( CANFD6_REG_BITS_DEVICE_MODE_SWE_MASK   | CANFD6_REG_BITS_DEVICE_MODE_DEVICE_RESET    | CANFD6_REG_BITS_DEVICE_MODE_WDT_MASK        |
            CANFD6_REG_BITS_DEVICE_MODE_NWKRQ_CONFIG_MASK | CANFD6_REG_BITS_DEVICE_MODE_INH_MASK        | CANFD6_REG_BITS_DEVICE_MODE_GPO1_FUNC_MASK  |
            CANFD6_REG_BITS_DEVICE_MODE_FAIL_SAFE_MASK    | CANFD6_REG_BITS_DEVICE_MODE_GPO1_MODE_MASK  | CANFD6_REG_BITS_DEVICE_MODE_WDT_ACTION_MASK |
            CANFD6_REG_BITS_DEVICE_MODE_WDT_RESET_BIT     | CANFD6_REG_BITS_DEVICE_MODE_NWKRQ_VOLT_MASK | CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_ENMASK |
            CANFD6_REG_BITS_DEVICE_MODE_GPO2_MASK         | CANFD6_REG_BITS_DEVICE_MODE_WD_CLK_MASK     | CANFD6_REG_BITS_DEVICE_MODE_WAKE_PIN_MASK );

    canfd6_dev_config_t tempCfg;
    tempCfg.word = dev_cfg->word;

    tempCfg.RESERVED0 = 0;
    tempCfg.RESERVED1 = 0;
    tempCfg.RESERVED2 = 0;
    tempCfg.RESERVED3 = 0;
    tempCfg.RESERVED4 = 0;
    tempCfg.RESERVED5 = 0;

    read_dev |= ( CANFD6_REG_BITS_DEVICE_MODE_FORCED_SET_BITS | tempCfg.word );

    dev_write_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS, read_dev );
}

void canfd6_device_read_config ( canfd6_t *ctx, canfd6_dev_config_t *dev_cfg ) {
    dev_cfg->word = dev_read_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS );
}

void canfd6_device_read_interrupts ( canfd6_t *ctx, canfd6_device_interrupts_t *ir ) {
    ir->word = dev_read_word( ctx, CANFD6_REG_DEV_IR );
}

void canfd6_device_clear_interrupts ( canfd6_t *ctx, canfd6_device_interrupts_t *ir ) {
    dev_write_word( ctx, CANFD6_REG_DEV_IR, ir->word );
}

void canfd6_device_clear_interrupts_all ( canfd6_t *ctx ) {
    dev_write_word( ctx, CANFD6_REG_DEV_IR, DEV_BITMASK_ALL );
}

void canfd6_device_clear_spierr ( canfd6_t *ctx ) {
    dev_write_word( ctx, CANFD6_REG_SPI_STATUS, DEV_BITMASK_ALL );
}

void canfd6_device_read_interrupt_enable ( canfd6_t *ctx, canfd6_device_interrupt_enable_t *ie ) {
    ie->word = dev_read_word( ctx, CANFD6_REG_DEV_IE );
}

void canfd6_device_configure_ie ( canfd6_t *ctx, canfd6_device_interrupt_enable_t *ie ) {
    dev_write_word( ctx, CANFD6_REG_DEV_IE, ie->word );
}

err_t canfd6_device_set_mode ( canfd6_t *ctx, canfd6_device_mode_enum_t mode_define ) {
    uint32_t write_val = ( dev_read_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS ) & ~CANFD6_REG_BITS_DEVICE_MODE_DEVICEMODE_MASK );

    switch ( mode_define ) {
        case CANFD6_DEVICE_MODE_NORMAL:
            write_val |= CANFD6_REG_BITS_DEVICE_MODE_DEVICEMODE_NORMAL;
            break;

        case CANFD6_DEVICE_MODE_SLEEP:
            write_val |= CANFD6_REG_BITS_DEVICE_MODE_DEVICEMODE_SLEEP;
            break;

        case CANFD6_DEVICE_MODE_STANDBY:
            write_val |= CANFD6_REG_BITS_DEVICE_MODE_DEVICEMODE_STANDBY;
            break;

        default:
            return CANFD6_ERROR;
    }

    dev_write_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS, write_val );

    return CANFD6_OK;
}

canfd6_device_mode_enum_t canfd6_device_read_mode ( canfd6_t *ctx ) {
    uint32_t read_val = ( dev_read_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS ) & CANFD6_REG_BITS_DEVICE_MODE_DEVICEMODE_MASK );

    switch ( read_val ) {
        case CANFD6_REG_BITS_DEVICE_MODE_DEVICEMODE_NORMAL:
            return CANFD6_DEVICE_MODE_NORMAL;

        case CANFD6_REG_BITS_DEVICE_MODE_DEVICEMODE_SLEEP:
            return CANFD6_DEVICE_MODE_SLEEP;

        case CANFD6_REG_BITS_DEVICE_MODE_DEVICEMODE_STANDBY:
            return CANFD6_DEVICE_MODE_STANDBY;

        default:
            return CANFD6_DEVICE_MODE_STANDBY;
    }
}

err_t canfd6_device_enable_testmode ( canfd6_t *ctx, canfd6_device_test_mode_enum_t mode_define ) {
    uint32_t rd_wr_val = dev_read_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS );
    
    rd_wr_val &= ~CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_MASK;

    switch ( mode_define ) {
        case CANFD6_DEVICE_TEST_MODE_NORMAL:
            canfd6_device_disable_testmode( ctx );
            break;

        case CANFD6_DEVICE_TEST_MODE_CONTROLLER:
            rd_wr_val |= CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_CONTROLLER | CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_EN;
            break;

        case CANFD6_DEVICE_TEST_MODE_PHY:
            rd_wr_val |= CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_PHY | CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_EN;
            break;

        default:
            return CANFD6_ERROR;
    }
    
    dev_write_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS, rd_wr_val );

    return CANFD6_OK;
}

void canfd6_device_disable_testmode ( canfd6_t *ctx ) {
    uint32_t rd_wr_val = dev_read_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS );
    
    rd_wr_val &= ~( CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_MASK | CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_ENMASK );
    
    dev_write_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS, rd_wr_val );
}

canfd6_device_test_mode_enum_t canfd6_device_read_testmode ( canfd6_t *ctx ) {
    uint32_t read_val = dev_read_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS );

    if ( read_val & CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_ENMASK ) {
        if ( read_val & CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_CONTROLLER ) {
            return CANFD6_DEVICE_TEST_MODE_CONTROLLER;
        } else {
            return CANFD6_DEVICE_TEST_MODE_PHY;
        }
    }
    return CANFD6_DEVICE_TEST_MODE_NORMAL;
}

err_t canfd6_wdt_configure ( canfd6_t *ctx, canfd6_wdt_timer_enum_t wdt_timeout ) {
    uint32_t rd_wr_val = dev_read_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS );
    
    rd_wr_val &= ~CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_MASK;

    switch ( wdt_timeout ) {
        case CANFD6_WDT_60MS:
            rd_wr_val |= CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_60MS;
            break;

        case CANFD6_WDT_600MS:
            rd_wr_val |= CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_600MS;
            break;

        case CANFD6_WDT_3S:
            rd_wr_val |= CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_3S;
            break;

        case CANFD6_WDT_6S:
            rd_wr_val |= CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_6S;
            break;

        default:
            return CANFD6_ERROR;
    }
    
    dev_write_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS, rd_wr_val );

    return CANFD6_OK;
}

canfd6_wdt_timer_enum_t canfd6_wdt_read ( canfd6_t *ctx ) {
    uint32_t read_val = dev_read_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS );
    
    read_val &= CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_MASK;

    switch ( read_val ) {
        case CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_60MS:
            return CANFD6_WDT_60MS;

        case CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_600MS:
            return CANFD6_WDT_600MS;

        case CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_3S:
            return CANFD6_WDT_3S;

        case CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_6S:
            return CANFD6_WDT_6S;

        default:
            return CANFD6_WDT_60MS;
    }
}

void canfd6_wdt_enable ( canfd6_t *ctx ) {
    uint32_t rd_wr_val = dev_read_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS ) | CANFD6_REG_BITS_DEVICE_MODE_WDT_EN;
    
    dev_write_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS, rd_wr_val );
}

void canfd6_wdt_disable ( canfd6_t *ctx ) {
    uint32_t write_val = dev_read_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS );
    
    write_val &= ~CANFD6_REG_BITS_DEVICE_MODE_WDT_EN;
    
    dev_write_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS, write_val );
}

void canfd6_wdt_reset ( canfd6_t *ctx ) {
    uint32_t write_val = dev_read_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS );
    
    write_val |= CANFD6_REG_BITS_DEVICE_MODE_WDT_RESET_BIT;
    
    dev_write_word( ctx, CANFD6_REG_DEV_MODES_AND_PINS, write_val );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_write_word ( canfd6_t *ctx, uint16_t address, uint32_t data_in ) {
    dev_burst_write_init( ctx, address, 1 );
    dev_burst_write_data( ctx, data_in );
    dev_burst_write_terminate( ctx );
}

static uint32_t dev_read_word ( canfd6_t *ctx, uint16_t address ) {
    uint32_t returnData;

    dev_burst_read_init( ctx, address, 1 );
    returnData = dev_burst_read_data( ctx );
    dev_burst_read_terminate( ctx );

    return returnData;
}

static void dev_burst_write_init ( canfd6_t *ctx, uint16_t address, uint8_t words ) {
    uint8_t tx_buf[ 4 ];
    
    tx_buf[ 0 ] = DEV_WRITE_OPCODE;
    tx_buf[ 1 ] = ( uint8_t )( address >> 8 );
    tx_buf[ 2 ] = ( uint8_t )address;
    tx_buf[ 3 ] = words;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 4 );
}

static void dev_burst_write_data ( canfd6_t *ctx, uint32_t data_in ) {
    uint8_t tx_buf[ 4 ];
    
    tx_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 24 ) & DEV_BITMASK_LASTB_8 );
    tx_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 16 ) & DEV_BITMASK_LASTB_8 );
    tx_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & DEV_BITMASK_LASTB_8 );
    tx_buf[ 3 ] = ( uint8_t ) ( data_in & DEV_BITMASK_LASTB_8 );
    
    spi_master_write( &ctx->spi, tx_buf, 4 );
}

static void dev_burst_write_terminate ( canfd6_t *ctx ) {
    spi_master_deselect_device( ctx->chip_select );
}

static void dev_burst_read_init ( canfd6_t *ctx, uint16_t address, uint8_t words ) {
    uint8_t tx_buf[ 4 ];
    
    tx_buf[ 0 ] = DEV_READ_OPCODE;
    tx_buf[ 1 ] = ( uint8_t )( address >> 8 );
    tx_buf[ 2 ] = ( uint8_t )address;
    tx_buf[ 3 ] = words;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 4 );
}

static uint32_t dev_burst_read_data ( canfd6_t *ctx ) {
    uint8_t rx_buf[ 4 ];
    uint32_t returnData;
    
    spi_master_read( &ctx->spi, rx_buf, 4 );
    
    returnData = rx_buf[ 0 ];
    returnData <<= 8;
    returnData |= rx_buf[ 1 ];
    returnData <<= 8;
    returnData |= rx_buf[ 2 ];
    returnData <<= 8;
    returnData |= rx_buf[ 3 ];
    
    return returnData;
}

static void dev_burst_read_terminate ( canfd6_t *ctx ) {
    spi_master_deselect_device( ctx->chip_select );
}

// ------------------------------------------------------------------------- END
