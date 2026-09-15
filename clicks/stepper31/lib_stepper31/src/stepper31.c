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
 * @file stepper31.c
 * @brief Stepper 31 Click Driver.
 */

#include "stepper31.h"

/**
 * @brief Stepper 31 communication test patterns.
 * @details Alternating patterns exercise both logic levels in unused OLATA
 * bits without changing SEL or TRQ. GPA4-GPA7 remain inputs.
 */
#define STEPPER31_COM_PATTERN_1                0xA0
#define STEPPER31_COM_PATTERN_2                0x50

/**
 * @brief Stepper 31 configuration table sizes.
 * @details Total settings to verify and the first entries already written during startup.
 */
#define STEPPER31_DEFAULT_REG_COUNT            9
#define STEPPER31_STARTUP_REG_COUNT            3

/**
 * @brief Stepper 31 full-step sequence length.
 * @details One electrical cycle uses four full steps. Half-step and quarter-step
 * sequence lengths are obtained by shifting this count by the selected mode.
 */
#define STEPPER31_FULL_STEP_COUNT              4

/**
 * @brief Stepper 31 I/O signal table for full step resolution.
 * @details Signal order: PHASEA, INA1, INA2, PHASEB, INB1, and INB2.
 * Both windings are energized at 100% current.
 */
static uint8_t stepper31_full_step[ 4 ][ 6 ] =
{
    { 1, 1, 1, 1, 1, 1 },
    { 0, 1, 1, 1, 1, 1 },
    { 0, 1, 1, 0, 1, 1 },
    { 1, 1, 1, 0, 1, 1 }
};

/**
 * @brief Stepper 31 I/O signal table for half step resolution.
 * @details Signal order: PHASEA, INA1, INA2, PHASEB, INB1, and INB2.
 * Alternates one-phase and two-phase excitation at 100% current.
 */
static uint8_t stepper31_half_step[ 8 ][ 6 ] =
{
    { 1, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 1, 1, 1 },
    { 0, 1, 1, 1, 1, 1 },
    { 0, 1, 1, 0, 0, 0 },
    { 0, 1, 1, 0, 1, 1 },
    { 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 0, 1, 1 },
    { 1, 1, 1, 0, 0, 0 }
};

/**
 * @brief Stepper 31 I/O signal table for quarter step resolution.
 * @details Signal order: PHASEA, INA1, INA2, PHASEB, INB1, and INB2.
 * Uses 38%, 71%, and 100% current levels, starting at A = +71%, B = +71%.
 */
static uint8_t stepper31_quarter_step[ 16 ][ 6 ] =
{
    { 1, 1, 0, 1, 1, 0 },
    { 1, 0, 1, 1, 1, 1 },
    { 0, 0, 0, 1, 1, 1 },
    { 0, 0, 1, 1, 1, 1 },
    { 0, 1, 0, 1, 1, 0 },
    { 0, 1, 1, 1, 0, 1 },
    { 0, 1, 1, 0, 0, 0 },
    { 0, 1, 1, 0, 0, 1 },
    { 0, 1, 0, 0, 1, 0 },
    { 0, 0, 1, 0, 1, 1 },
    { 0, 0, 0, 0, 1, 1 },
    { 1, 0, 1, 0, 1, 1 },
    { 1, 1, 0, 0, 1, 0 },
    { 1, 1, 1, 0, 0, 1 },
    { 1, 1, 1, 0, 0, 0 },
    { 1, 1, 1, 1, 0, 1 }
};

/**
 * @brief Stepper 31 excitation state application function.
 * @details Checks faults and applies one excitation state in a single port B write.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[in] index : State index within the selected excitation sequence.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid state, motor fault, or communication error.
 * See #err_t definition for detailed explanation.
 * @note Does not advance the index; errors release winding currents.
 */
static err_t stepper31_apply_step ( stepper31_t *ctx, uint8_t index );

/**
 * @brief Stepper 31 motor speed delay function.
 * @details Applies the preset delay between excitation states.
 * @param[in] speed : Motor speed selection. See STEPPER31_SPEED macros.
 * @return Nothing.
 * @note Called after the drive function validates the speed selection.
 */
static void stepper31_speed_delay ( uint8_t speed );

void stepper31_cfg_setup ( stepper31_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->pha  = HAL_PIN_NC;
    cfg->spx  = HAL_PIN_NC;
    cfg->phb  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_address = STEPPER31_SPI_ADDRESS_DEFAULT;
}

err_t stepper31_init ( stepper31_t *ctx, stepper31_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    // SPX also resets the expander. Keep the motor asleep during SPI setup.
    digital_out_init( &ctx->spx, cfg->spx );
    digital_out_low( &ctx->spx );

    ctx->spi_address = cfg->spi_address;
    ctx->step_mode = STEPPER31_MODE_FULL_STEP;
    ctx->direction = STEPPER31_DIR_CW;
    ctx->step_index = 0;
    ctx->decay_mode = STEPPER31_DECAY_ADMD;

    if ( STEPPER31_SPI_ADDRESS_MASK < cfg->spi_address )
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, STEPPER31_SPI_DUMMY_DATA ) ) 
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

    // Keep direct phases inactive; default_cfg selects the expander phase outputs.
    digital_out_init( &ctx->pha, cfg->pha );
    digital_out_init( &ctx->phb, cfg->phb );
    digital_out_low( &ctx->pha );
    digital_out_low( &ctx->phb );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t stepper31_default_cfg ( stepper31_t *ctx ) 
{
    err_t error_flag = STEPPER31_OK;
    uint8_t address = ctx->spi_address;
    uint8_t index = 0;
    uint8_t read_value = 0;
    uint8_t bootstrap_address[ 2 ] = { STEPPER31_SPI_ADDRESS_DEFAULT, STEPPER31_SPI_ADDRESS_A2 };
    uint8_t config_regs[ STEPPER31_DEFAULT_REG_COUNT ][ 2 ] =
    {
        { STEPPER31_REG_OLATB,    STEPPER31_DEFAULT_OLATB },
        { STEPPER31_REG_IODIRB,   STEPPER31_DEFAULT_IODIRB },
        { STEPPER31_REG_IOCON,    STEPPER31_DEFAULT_IOCON },
        { STEPPER31_REG_OLATA,    STEPPER31_DEFAULT_OLATA },
        { STEPPER31_REG_IODIRA,   STEPPER31_DEFAULT_IODIRA },
        { STEPPER31_REG_GPPUA,    STEPPER31_DEFAULT_GPPUA },
        { STEPPER31_REG_DEFVALA,  STEPPER31_DEFAULT_DEFVALA },
        { STEPPER31_REG_INTCONA,  STEPPER31_DEFAULT_INTCONA },
        { STEPPER31_REG_GPINTENA, STEPPER31_DEFAULT_GPINTENA }
    };

    ctx->step_mode = STEPPER31_MODE_FULL_STEP;
    ctx->direction = STEPPER31_DIR_CW;
    ctx->step_index = 0;
    ctx->decay_mode = STEPPER31_DECAY_ADMD;

    digital_out_low( &ctx->pha );
    digital_out_low( &ctx->phb );
    // SPX resets both devices, including expander pin directions and output latches.
    digital_out_low( &ctx->spx );
    Delay_1ms( );
    digital_out_high( &ctx->spx );
    Delay_1us( );

    // Address 0 is used after reset; address 4 also covers the Rev. A A2 erratum.
    // Set winding currents off before enabling jumper-based addressing.
    for ( index = 0; ( index < 2 ) && ( STEPPER31_OK == error_flag ); index++ )
    {
        ctx->spi_address = bootstrap_address[ index ];
        error_flag = stepper31_write_reg( ctx, STEPPER31_REG_OLATB, STEPPER31_DEFAULT_OLATB );
        if ( STEPPER31_OK == error_flag )
        {
            error_flag = stepper31_write_reg( ctx, STEPPER31_REG_IODIRB, STEPPER31_DEFAULT_IODIRB );
        }
        if ( STEPPER31_OK == error_flag )
        {
            error_flag = stepper31_write_reg( ctx, STEPPER31_REG_IOCON, STEPPER31_DEFAULT_IOCON );
        }
    }
    // Restore the jumper-selected address even if a bootstrap transfer failed.
    ctx->spi_address = address;

    if ( STEPPER31_OK == error_flag )
    {
        error_flag = stepper31_check_com( ctx );
    }

    // Write the remaining settings and verify all registers at the selected address.
    for ( index = 0; ( index < STEPPER31_DEFAULT_REG_COUNT ) && ( STEPPER31_OK == error_flag ); index++ )
    {
        // The first three registers were written during startup; only read them back.
        if ( STEPPER31_STARTUP_REG_COUNT <= index )
        {
            error_flag = stepper31_write_reg( ctx, config_regs[ index ][ 0 ], config_regs[ index ][ 1 ] );
        }
        if ( STEPPER31_OK == error_flag )
        {
            error_flag = stepper31_read_reg( ctx, config_regs[ index ][ 0 ], &read_value );
            if ( config_regs[ index ][ 1 ] != read_value )
            {
                error_flag = STEPPER31_ERROR;
            }
        }
    }

    if ( STEPPER31_OK == error_flag )
    {
        // Allow the motor driver's maximum sleep-to-operating transition time.
        Delay_10ms( );
    }
    else
    {
        // Leave both devices in reset/sleep after an incomplete configuration.
        digital_out_low( &ctx->spx );
    }

    return error_flag;
}

err_t stepper31_check_com ( stepper31_t *ctx )
{
    err_t error_flag = STEPPER31_OK;
    uint8_t original = 0;
    uint8_t expected = 0;
    uint8_t read_value = 0;
    uint8_t index = 0;
    uint8_t patterns[ 2 ] = { STEPPER31_COM_PATTERN_1, STEPPER31_COM_PATTERN_2 };

    error_flag = stepper31_read_reg( ctx, STEPPER31_REG_OLATA, &original );
    if ( STEPPER31_OK == error_flag )
    {
        for ( index = 0; ( index < 2 ) && ( STEPPER31_OK == error_flag ); index++ )
        {
            // Preserve control bits and exercise only the unused upper-nibble latch bits.
            expected = ( original & ( uint8_t ) ~STEPPER31_PA_UNUSED_MASK ) | patterns[ index ];
            error_flag = stepper31_write_reg( ctx, STEPPER31_REG_OLATA, expected );
            if ( STEPPER31_OK == error_flag )
            {
                error_flag = stepper31_read_reg( ctx, STEPPER31_REG_OLATA, &read_value );
                if ( expected != read_value )
                {
                    error_flag = STEPPER31_ERROR;
                }
            }
        }

        // Restore the latch even when the pattern comparison or a transfer failed.
        if ( STEPPER31_OK != stepper31_write_reg( ctx, STEPPER31_REG_OLATA, original ) )
        {
            error_flag = STEPPER31_ERROR;
        }
    }

    return error_flag;
}

err_t stepper31_write_reg ( stepper31_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return stepper31_write_regs( ctx, reg, &data_in, 1 );
}

err_t stepper31_write_regs ( stepper31_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = STEPPER31_ERROR;
    uint8_t header[ 2 ] = { 0 };

    // Reject transfers that would wrap past the BANK = 0 register map.
    if ( ( 0 != data_in ) && ( 0 < len ) &&
         ( STEPPER31_REG_COUNT >= ( uint16_t ) reg + len ) &&
         ( STEPPER31_SPI_ADDRESS_MASK >= ctx->spi_address ) )
    {
        // Opcode bits 3:1 carry A2:A0; bit 0 selects read or write.
        header[ 0 ] = STEPPER31_SPI_WRITE | ( ctx->spi_address << 1 );
        header[ 1 ] = reg;

        // Keep CS asserted across opcode, register address, and payload.
        spi_master_select_device( ctx->chip_select );
        if ( SPI_MASTER_SUCCESS == spi_master_write( &ctx->spi, header, 2 ) )
        {
            if ( SPI_MASTER_SUCCESS == spi_master_write( &ctx->spi, data_in, len ) )
            {
                error_flag = STEPPER31_OK;
            }
        }
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

err_t stepper31_read_reg ( stepper31_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return stepper31_read_regs( ctx, reg, data_out, 1 );
}

err_t stepper31_read_regs ( stepper31_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t error_flag = STEPPER31_ERROR;
    uint8_t header[ 2 ] = { 0 };

    if ( ( 0 != data_out ) && ( 0 < len ) &&
         ( STEPPER31_REG_COUNT >= ( uint16_t ) reg + len ) &&
         ( STEPPER31_SPI_ADDRESS_MASK >= ctx->spi_address ) )
    {
        header[ 0 ] = STEPPER31_SPI_READ | ( ctx->spi_address << 1 );
        header[ 1 ] = reg;

        // Keep header and response in one transaction; release CS even on failure.
        spi_master_select_device( ctx->chip_select );
        if ( SPI_MASTER_SUCCESS == spi_master_write_then_read( &ctx->spi, header, 2, data_out, len ) )
        {
            error_flag = STEPPER31_OK;
        }
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

err_t stepper31_drive_motor ( stepper31_t *ctx, uint32_t steps, uint8_t speed )
{
    err_t error_flag = STEPPER31_ERROR;
    uint32_t num_steps = 0;
    uint8_t fault = STEPPER31_FAULT_NONE;

    if ( ( STEPPER31_SPEED_VERY_FAST >= speed ) &&
         ( STEPPER31_MODE_QUARTER_STEP >= ctx->step_mode ) && ( STEPPER31_DIR_CCW >= ctx->direction ) )
    {
        error_flag = STEPPER31_OK;
        // A zero-step request leaves winding outputs and timing unchanged.
        if ( 0 < steps )
        {
            error_flag = stepper31_enable_device( ctx );
            if ( STEPPER31_OK == error_flag )
            {
                // Allow the initial excitation state to settle before stepping.
                Delay_10ms( );
            }

            // Abort at the first failed step without scheduling another state or delay.
            for ( num_steps = 0; ( num_steps < steps ) && ( STEPPER31_OK == error_flag ); num_steps++ )
            {
                error_flag = stepper31_step( ctx, ctx->direction );
                if ( STEPPER31_OK == error_flag )
                {
                    stepper31_speed_delay( speed );
                }
            }

            // Include faults that appeared during the final step's settling delay.
            if ( STEPPER31_OK == error_flag )
            {
                error_flag = stepper31_get_fault( ctx, &fault );
                if ( STEPPER31_FAULT_NONE != fault )
                {
                    error_flag = STEPPER31_ERROR;
                }
            }

            // Stop on completion or failure without clearing a latched motor fault.
            if ( STEPPER31_OK != stepper31_disable_device( ctx ) )
            {
                error_flag = STEPPER31_ERROR;
            }
        }
    }

    return error_flag;
}

err_t stepper31_set_step_mode ( stepper31_t *ctx, uint8_t mode )
{
    err_t error_flag = STEPPER31_ERROR;

    if ( STEPPER31_MODE_QUARTER_STEP >= mode )
    {
        // Restart at the new table's first state; the caller must stop the motor first.
        ctx->step_mode = mode;
        ctx->step_index = 0;
        error_flag = STEPPER31_OK;
    }

    return error_flag;
}

err_t stepper31_set_direction ( stepper31_t *ctx, uint8_t dir )
{
    err_t error_flag = STEPPER31_ERROR;

    if ( STEPPER31_DIR_CCW >= dir )
    {
        // Store the next move's direction without changing the active phase outputs.
        ctx->direction = dir;
        error_flag = STEPPER31_OK;
    }

    return error_flag;
}

err_t stepper31_switch_direction ( stepper31_t *ctx )
{
    err_t error_flag = STEPPER31_ERROR;

    if ( STEPPER31_DIR_CW == ctx->direction )
    {
        error_flag = stepper31_set_direction( ctx, STEPPER31_DIR_CCW );
    }
    else if ( STEPPER31_DIR_CCW == ctx->direction )
    {
        error_flag = stepper31_set_direction( ctx, STEPPER31_DIR_CW );
    }

    return error_flag;
}

err_t stepper31_set_decay ( stepper31_t *ctx, uint8_t mode )
{
    err_t error_flag = STEPPER31_ERROR;
    uint8_t output = 0;

    if ( 0 == ( mode & ( uint8_t ) ~STEPPER31_PB_DECAY_MASK ) )
    {
        error_flag = stepper31_read_reg( ctx, STEPPER31_REG_OLATB, &output );
        if ( STEPPER31_OK == error_flag )
        {
            // Change only DECAY1/DECAY2, preserving the current excitation pattern.
            output = ( output & ( uint8_t ) ~STEPPER31_PB_DECAY_MASK ) | mode;
            error_flag = stepper31_write_reg( ctx, STEPPER31_REG_OLATB, output );
        }

        if ( STEPPER31_OK == error_flag )
        {
            // Retain only a decay setting that was successfully written.
            ctx->decay_mode = mode;
        }
        else
        {
            stepper31_disable_device( ctx );
        }
    }

    return error_flag;
}

err_t stepper31_set_torque ( stepper31_t *ctx, uint8_t mode )
{
    err_t error_flag = STEPPER31_ERROR;
    uint8_t output = 0;
    uint8_t direction = 0;

    if ( STEPPER31_TORQUE_SWITCH >= mode )
    {
        error_flag = stepper31_read_reg( ctx, STEPPER31_REG_IODIRA, &direction );
        if ( ( STEPPER31_OK == error_flag ) && ( STEPPER31_TORQUE_SWITCH != mode ) )
        {
            error_flag = stepper31_read_reg( ctx, STEPPER31_REG_OLATA, &output );
            if ( STEPPER31_OK == error_flag )
            {
                output &= ( uint8_t ) ~STEPPER31_PA_TRQ;
                if ( STEPPER31_TORQUE_50 == mode )
                {
                    output |= STEPPER31_PA_TRQ;
                }

                // Set the requested level before enabling the TRQ output driver.
                error_flag = stepper31_write_reg( ctx, STEPPER31_REG_OLATA, output );
            }
        }

        if ( STEPPER31_OK == error_flag )
        {
            direction &= ( uint8_t ) ~STEPPER31_PA_TRQ;
            if ( STEPPER31_TORQUE_SWITCH == mode )
            {
                // Release GPA0 so the physical SW1 switch can control TRQ.
                direction |= STEPPER31_PA_TRQ;
            }
            error_flag = stepper31_write_reg( ctx, STEPPER31_REG_IODIRA, direction );
        }

        if ( STEPPER31_OK != error_flag )
        {
            stepper31_disable_device( ctx );
        }
    }

    return error_flag;
}

err_t stepper31_enable_device ( stepper31_t *ctx )
{
    // Restore holding current at the saved index without advancing the sequence.
    return stepper31_apply_step( ctx, ctx->step_index );
}

err_t stepper31_step ( stepper31_t *ctx, uint8_t direction )
{
    err_t error_flag = STEPPER31_ERROR;
    uint8_t next_index = ctx->step_index;
    uint8_t step_count = 0;

    if ( ( STEPPER31_DIR_CCW >= direction ) &&
         ( STEPPER31_MODE_QUARTER_STEP >= ctx->step_mode ) )
    {
        // Modes 0/1/2 select 4/8/16 states per electrical cycle.
        step_count = STEPPER31_FULL_STEP_COUNT << ctx->step_mode;
        if ( STEPPER31_DIR_CW == direction )
        {
            next_index++;
            if ( step_count <= next_index )
            {
                next_index = 0;
            }
        }
        else
        {
            // Wrap before decrementing to avoid unsigned underflow.
            if ( 0 == next_index )
            {
                next_index = step_count;
            }
            next_index--;
        }

        error_flag = stepper31_apply_step( ctx, next_index );
        if ( STEPPER31_OK == error_flag )
        {
            // Advance the saved index only after a successful state write.
            ctx->step_index = next_index;
        }
    }

    return error_flag;
}

err_t stepper31_disable_device ( stepper31_t *ctx )
{
    err_t error_flag = STEPPER31_OK;

    // Keeping only decay bits clears both winding current selections.
    error_flag = stepper31_write_reg( ctx, STEPPER31_REG_OLATB, ctx->decay_mode );
    if ( STEPPER31_OK != error_flag )
    {
        // Sleep is only a fallback: it also resets the expander and loses its settings.
        digital_out_low( &ctx->spx );
    }

    return error_flag;
}

err_t stepper31_get_fault ( stepper31_t *ctx, uint8_t *fault )
{
    err_t error_flag = STEPPER31_ERROR;
    uint8_t input = 0;

    if ( 0 != fault )
    {
        // GPIOA reads acknowledge the expander interrupt, not the motor fault latch.
        error_flag = stepper31_read_reg( ctx, STEPPER31_REG_GPIOA, &input );
        if ( STEPPER31_OK == error_flag )
        {
            *fault = STEPPER31_FAULT_NONE;
            // LO1 also asserts for thermal faults, so check LO2 first.
            if ( 0 == ( input & STEPPER31_PA_LO2 ) )
            {
                *fault = STEPPER31_FAULT_OVERTEMPERATURE;
            }
            else if ( 0 == ( input & STEPPER31_PA_LO1 ) )
            {
                *fault = STEPPER31_FAULT_OVERCURRENT;
            }
        }
    }

    return error_flag;
}

uint8_t stepper31_get_int_pin ( stepper31_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

static err_t stepper31_apply_step ( stepper31_t *ctx, uint8_t index )
{
    err_t error_flag = STEPPER31_ERROR;
    uint8_t fault = STEPPER31_FAULT_NONE;
    uint8_t output = 0;
    uint8_t step_count = 0;
    uint8_t *pins_array = 0;

    if ( STEPPER31_MODE_QUARTER_STEP >= ctx->step_mode )
    {
        step_count = STEPPER31_FULL_STEP_COUNT << ctx->step_mode;
    }

    // Check faults and index bounds before accessing an excitation table.
    if ( ( STEPPER31_OK == stepper31_get_fault( ctx, &fault ) ) &&
         ( STEPPER31_FAULT_NONE == fault ) && ( step_count > index ) )
    {
        switch ( ctx->step_mode )
        {
            case STEPPER31_MODE_FULL_STEP:
            {
                pins_array = stepper31_full_step[ index ];
                error_flag = STEPPER31_OK;
                break;
            }
            case STEPPER31_MODE_HALF_STEP:
            {
                pins_array = stepper31_half_step[ index ];
                error_flag = STEPPER31_OK;
                break;
            }
            case STEPPER31_MODE_QUARTER_STEP:
            {
                pins_array = stepper31_quarter_step[ index ];
                error_flag = STEPPER31_OK;
                break;
            }
            default:
            {
                break;
            }
        }
    }

    if ( STEPPER31_OK == error_flag )
    {
        // Pack PHASEA, INA1, INA2, PHASEB, INB1, INB2 into one port B update.
        output = ( pins_array[ 0 ] << 6 ) | ( pins_array[ 1 ] << 3 ) | ( pins_array[ 2 ] << 2 ) |
                 ( pins_array[ 3 ] << 7 ) | ( pins_array[ 4 ] << 1 ) | pins_array[ 5 ] | ctx->decay_mode;
        error_flag = stepper31_write_reg( ctx, STEPPER31_REG_OLATB, output );
    }

    if ( STEPPER31_OK != error_flag )
    {
        stepper31_disable_device( ctx );
    }

    return error_flag;
}

static void stepper31_speed_delay ( uint8_t speed )
{
    switch ( speed )
    {
        case STEPPER31_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER31_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER31_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER31_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case STEPPER31_SPEED_VERY_FAST:
        {
            Delay_500us( );
            break;
        }
        default:
        {
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
