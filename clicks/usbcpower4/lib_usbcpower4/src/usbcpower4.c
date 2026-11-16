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
 * @file usbcpower4.c
 * @brief USB-C Power 4 Click Driver.
 */

#include "usbcpower4.h"

/**
 * @brief USB-C Power 4 internal buffer positions.
 * @details Defines the TPS26750A Unique Address Interface header positions and
 * register byte positions used by the data conversion functions.
 */
#define USBCPOWER4_UAI_REG_INDEX                  0
#define USBCPOWER4_UAI_COUNT_INDEX                1
#define USBCPOWER4_UAI_PAYLOAD_INDEX              2
#define USBCPOWER4_UAI_RX_COUNT_INDEX             0
#define USBCPOWER4_UAI_RX_PAYLOAD_INDEX           1
#define USBCPOWER4_STATUS_FLAGS_INDEX             0
#define USBCPOWER4_POWER_FLAGS_INDEX              0
#define USBCPOWER4_PD_FLAGS_INDEX                 0
#define USBCPOWER4_PDO_BYTE_0                     0
#define USBCPOWER4_PDO_BYTE_1                     1
#define USBCPOWER4_PDO_BYTE_2                     2
#define USBCPOWER4_PDO_BYTE_3                     3
#define USBCPOWER4_BYTE_SHIFT_8                   8
#define USBCPOWER4_BYTE_SHIFT_16                  16
#define USBCPOWER4_BYTE_SHIFT_24                  24
#define USBCPOWER4_PDO_VALID                      1
#define USBCPOWER4_PBMS_SIZE_0_INDEX              0
#define USBCPOWER4_PBMS_SIZE_1_INDEX              1
#define USBCPOWER4_PBMS_SIZE_2_INDEX              2
#define USBCPOWER4_PBMS_SIZE_3_INDEX              3
#define USBCPOWER4_PBMS_TARGET_INDEX              4
#define USBCPOWER4_PBMS_TIMEOUT_INDEX             5

/**
 * @brief USB-C Power 4 execute task function.
 * @details Writes optional task data, starts a four-character TPS26750A task,
 * and waits for the command register to clear.
 * @param[in] ctx : Click context object.
 * @param[in] task : Pointer to the four-byte task code.
 * @param[in] task_data : Pointer to the optional task input data.
 * @param[in] data_len : Number of task input bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
static err_t usbcpower4_exec_task ( usbcpower4_t *ctx, uint8_t *task, uint8_t *task_data, uint8_t data_len );

void usbcpower4_cfg_setup ( usbcpower4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->epr = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = USBCPOWER4_DEVICE_ADDRESS;
}

err_t usbcpower4_init ( usbcpower4_t *ctx, usbcpower4_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->epr, cfg->epr );
    digital_out_low( &ctx->epr );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t usbcpower4_default_cfg ( usbcpower4_t *ctx ) 
{
    err_t error_flag = USBCPOWER4_ERROR;

    // Verify I2C communication before applying the default pin state.
    error_flag = usbcpower4_check_communication( ctx );
    if ( USBCPOWER4_OK == error_flag )
    {
        // Start in SPR mode; EPR must be enabled only by an EPR-aware policy.
        usbcpower4_set_epr_mode( ctx, USBCPOWER4_EPR_MODE_DISABLED );
    }

    return error_flag;
}

err_t usbcpower4_write_reg ( usbcpower4_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return usbcpower4_write_regs( ctx, reg, &data_in, 1 );
}

err_t usbcpower4_write_regs ( usbcpower4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = USBCPOWER4_ERROR;
    uint8_t tx_buf[ USBCPOWER4_MAX_REG_SIZE + USBCPOWER4_UAI_HEADER_SIZE ] = { 0 };
    uint8_t cnt = 0;

    if ( ( NULL != data_in ) && ( 0 < len ) && ( USBCPOWER4_MAX_REG_SIZE >= len ) )
    {
        // TPS26750A register writes contain the register offset and byte count.
        tx_buf[ USBCPOWER4_UAI_REG_INDEX ] = reg;
        tx_buf[ USBCPOWER4_UAI_COUNT_INDEX ] = len;
        for ( cnt = 0; cnt < len; cnt++ )
        {
            tx_buf[ cnt + USBCPOWER4_UAI_PAYLOAD_INDEX ] = data_in[ cnt ];
        }
        error_flag = i2c_master_write( &ctx->i2c, tx_buf, len + USBCPOWER4_UAI_HEADER_SIZE );
    }

    return error_flag;
}

err_t usbcpower4_read_reg ( usbcpower4_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return usbcpower4_read_regs( ctx, reg, data_out, 1 );
}

err_t usbcpower4_read_regs ( usbcpower4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t error_flag = USBCPOWER4_ERROR;
    uint8_t rx_buf[ USBCPOWER4_MAX_REG_SIZE + USBCPOWER4_UAI_COUNT_SIZE ] = { 0 };
    uint8_t cnt = 0;

    if ( ( NULL != data_out ) && ( 0 < len ) && ( USBCPOWER4_MAX_REG_SIZE >= len ) )
    {
        // The first received byte reports the complete register payload size.
        error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, len + USBCPOWER4_UAI_COUNT_SIZE );
        if ( ( USBCPOWER4_OK == error_flag ) &&
             ( len <= rx_buf[ USBCPOWER4_UAI_RX_COUNT_INDEX ] ) )
        {
            for ( cnt = 0; cnt < len; cnt++ )
            {
                data_out[ cnt ] = rx_buf[ cnt + USBCPOWER4_UAI_RX_PAYLOAD_INDEX ];
            }
        }
        else
        {
            error_flag = USBCPOWER4_ERROR;
        }
    }

    return error_flag;
}

err_t usbcpower4_check_communication ( usbcpower4_t *ctx )
{
    uint8_t mode[ USBCPOWER4_MODE_SIZE ] = { 0 };

    return usbcpower4_read_mode( ctx, mode );
}

err_t usbcpower4_read_mode ( usbcpower4_t *ctx, uint8_t *mode )
{
    err_t error_flag = USBCPOWER4_ERROR;

    if ( NULL != mode )
    {
        error_flag = usbcpower4_read_regs( ctx, USBCPOWER4_REG_MODE, mode, USBCPOWER4_MODE_SIZE );
    }

    return error_flag;
}

err_t usbcpower4_load_app ( usbcpower4_t *ctx, const uint8_t *app_image, uint32_t app_size )
{
    err_t error_flag = USBCPOWER4_ERROR;
    err_t restore_flag = USBCPOWER4_ERROR;
    uint8_t mode[ USBCPOWER4_MODE_SIZE ] = { 0 };
    uint8_t pbms_task[ USBCPOWER4_TASK_SIZE ] = { 'P', 'B', 'M', 's' };
    uint8_t pbmc_task[ USBCPOWER4_TASK_SIZE ] = { 'P', 'B', 'M', 'c' };
    uint8_t pbms_data[ USBCPOWER4_PBMS_DATA_SIZE ] = { 0 };
    uint8_t burst_buf[ USBCPOWER4_PATCH_BURST_SIZE ] = { 0 };
    uint8_t patch_status = USBCPOWER4_ERROR;
    uint8_t burst_len = 0;
    uint8_t cnt = 0;
    uint16_t retry_cnt = 0;
    uint32_t offset = 0;
    uint32_t remaining = 0;

    if ( ( NULL != app_image ) && ( 0 < app_size ) )
    {
        error_flag = usbcpower4_read_mode( ctx, mode );
    }

    if ( ( USBCPOWER4_OK == error_flag ) &&
         ( ( USBCPOWER4_MODE_APP_0 != mode[ 0 ] ) ||
           ( USBCPOWER4_MODE_APP_1 != mode[ 1 ] ) ||
           ( USBCPOWER4_MODE_APP_2 != mode[ 2 ] ) ||
           ( USBCPOWER4_MODE_APP_3 != mode[ 3 ] ) ) )
    {
        if ( ( USBCPOWER4_MODE_PTCH_0 == mode[ 0 ] ) &&
             ( USBCPOWER4_MODE_PTCH_1 == mode[ 1 ] ) &&
             ( USBCPOWER4_MODE_PTCH_2 == mode[ 2 ] ) &&
             ( USBCPOWER4_MODE_PTCH_3 == mode[ 3 ] ) )
        {
            // PBMs defines the image size, temporary target address, and timeout.
            pbms_data[ USBCPOWER4_PBMS_SIZE_0_INDEX ] = ( uint8_t ) app_size;
            pbms_data[ USBCPOWER4_PBMS_SIZE_1_INDEX ] = ( uint8_t ) ( app_size >> USBCPOWER4_BYTE_SHIFT_8 );
            pbms_data[ USBCPOWER4_PBMS_SIZE_2_INDEX ] = ( uint8_t ) ( app_size >> USBCPOWER4_BYTE_SHIFT_16 );
            pbms_data[ USBCPOWER4_PBMS_SIZE_3_INDEX ] = ( uint8_t ) ( app_size >> USBCPOWER4_BYTE_SHIFT_24 );
            pbms_data[ USBCPOWER4_PBMS_TARGET_INDEX ] = USBCPOWER4_PATCH_TARGET_ADDRESS;
            pbms_data[ USBCPOWER4_PBMS_TIMEOUT_INDEX ] = USBCPOWER4_PATCH_TIMEOUT;

            error_flag = usbcpower4_exec_task( ctx, pbms_task, pbms_data, USBCPOWER4_PBMS_DATA_SIZE );
            if ( USBCPOWER4_OK == error_flag )
            {
                error_flag = usbcpower4_read_reg( ctx, USBCPOWER4_REG_DATA1, &patch_status );
                if ( USBCPOWER4_TASK_SUCCESS != patch_status )
                {
                    error_flag = USBCPOWER4_ERROR;
                }
            }

            if ( USBCPOWER4_OK == error_flag )
            {
                // Stream the image to the temporary patch target in 64-byte bursts.
                error_flag = i2c_master_set_slave_address( &ctx->i2c, USBCPOWER4_PATCH_TARGET_ADDRESS );
                while ( ( USBCPOWER4_OK == error_flag ) && ( offset < app_size ) )
                {
                    remaining = app_size - offset;
                    if ( USBCPOWER4_PATCH_BURST_SIZE < remaining )
                    {
                        burst_len = USBCPOWER4_PATCH_BURST_SIZE;
                    }
                    else
                    {
                        burst_len = ( uint8_t ) remaining;
                    }

                    // Use a RAM buffer so the generated image can remain in flash.
                    for ( cnt = 0; cnt < burst_len; cnt++ )
                    {
                        burst_buf[ cnt ] = app_image[ offset + cnt ];
                    }
                    error_flag = i2c_master_write( &ctx->i2c, burst_buf, burst_len );
                    if ( USBCPOWER4_OK == error_flag )
                    {
                        offset += burst_len;
                    }
                }

                // Restore the fundamental target address before issuing PBMc.
                restore_flag = i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
                if ( USBCPOWER4_OK != restore_flag )
                {
                    error_flag = USBCPOWER4_ERROR;
                }
            }

            if ( USBCPOWER4_OK == error_flag )
            {
                // PBMc applies the image and restarts the controller into APP mode.
                usbcpower4_write_regs( ctx, USBCPOWER4_REG_CMD1, pbmc_task, USBCPOWER4_TASK_SIZE );
                Delay_10ms( );
                error_flag = USBCPOWER4_ERROR;
                for ( retry_cnt = 0; retry_cnt < USBCPOWER4_APP_RETRY_COUNT; retry_cnt++ )
                {
                    if ( USBCPOWER4_OK == usbcpower4_read_mode( ctx, mode ) )
                    {
                        if ( ( USBCPOWER4_MODE_APP_0 == mode[ 0 ] ) &&
                             ( USBCPOWER4_MODE_APP_1 == mode[ 1 ] ) &&
                             ( USBCPOWER4_MODE_APP_2 == mode[ 2 ] ) &&
                             ( USBCPOWER4_MODE_APP_3 == mode[ 3 ] ) )
                        {
                            error_flag = USBCPOWER4_OK;
                            break;
                        }
                    }
                    Delay_10ms( );
                }
            }
        }
        else
        {
            error_flag = USBCPOWER4_ERROR;
        }
    }

    return error_flag;
}

err_t usbcpower4_read_status ( usbcpower4_t *ctx, usbcpower4_status_t *status )
{
    err_t error_flag = USBCPOWER4_ERROR;
    uint8_t status_buf[ USBCPOWER4_STATUS_SIZE ] = { 0 };
    uint8_t power_buf[ USBCPOWER4_POWER_STATUS_SIZE ] = { 0 };
    uint8_t pd_buf[ USBCPOWER4_PD_STATUS_SIZE ] = { 0 };

    if ( NULL != status )
    {
        status->plug_present = 0;
        status->connection_state = 0;
        status->orientation = 0;
        status->power_role = 0;
        status->data_role = 0;
        status->vbus_state = 0;
        status->power_connection = 0;
        status->typec_current = 0;
        status->cc_pullup = 0;
        status->port_type = 0;

        error_flag = usbcpower4_read_regs( ctx, USBCPOWER4_REG_STATUS, status_buf, USBCPOWER4_STATUS_SIZE );
    }
    if ( USBCPOWER4_OK == error_flag )
    {
        error_flag = usbcpower4_read_regs( ctx, USBCPOWER4_REG_POWER_STATUS, power_buf, USBCPOWER4_POWER_STATUS_SIZE );
    }
    if ( USBCPOWER4_OK == error_flag )
    {
        error_flag = usbcpower4_read_regs( ctx, USBCPOWER4_REG_PD_STATUS, pd_buf, USBCPOWER4_PD_STATUS_SIZE );
    }

    if ( USBCPOWER4_OK == error_flag )
    {
        // Decode the status bit fields only after all three register reads pass.
        status->plug_present = status_buf[ USBCPOWER4_STATUS_FLAGS_INDEX ] & USBCPOWER4_STATUS_PLUG_MASK;
        status->connection_state = ( status_buf[ USBCPOWER4_STATUS_FLAGS_INDEX ] & USBCPOWER4_STATUS_CONN_MASK ) >>
                                     USBCPOWER4_STATUS_CONN_SHIFT;
        status->orientation = ( status_buf[ USBCPOWER4_STATUS_FLAGS_INDEX ] & USBCPOWER4_STATUS_ORIENTATION_MASK ) >>
                                USBCPOWER4_STATUS_ORIENTATION_SHIFT;
        status->power_role = ( status_buf[ USBCPOWER4_STATUS_FLAGS_INDEX ] & USBCPOWER4_STATUS_POWER_ROLE_MASK ) >>
                               USBCPOWER4_STATUS_POWER_ROLE_SHIFT;
        status->data_role = ( status_buf[ USBCPOWER4_STATUS_FLAGS_INDEX ] & USBCPOWER4_STATUS_DATA_ROLE_MASK ) >>
                              USBCPOWER4_STATUS_DATA_ROLE_SHIFT;
        status->vbus_state = ( status_buf[ USBCPOWER4_STATUS_VBUS_INDEX ] & USBCPOWER4_STATUS_VBUS_MASK ) >>
                               USBCPOWER4_STATUS_VBUS_SHIFT;
        status->power_connection = power_buf[ USBCPOWER4_POWER_FLAGS_INDEX ] & USBCPOWER4_POWER_CONNECTION_MASK;
        status->typec_current = ( power_buf[ USBCPOWER4_POWER_FLAGS_INDEX ] & USBCPOWER4_TYPEC_CURRENT_MASK ) >>
                                  USBCPOWER4_TYPEC_CURRENT_SHIFT;
        status->cc_pullup = ( pd_buf[ USBCPOWER4_PD_FLAGS_INDEX ] & USBCPOWER4_PD_CC_PULLUP_MASK ) >>
                              USBCPOWER4_PD_CC_PULLUP_SHIFT;
        status->port_type = ( pd_buf[ USBCPOWER4_PD_FLAGS_INDEX ] & USBCPOWER4_PD_PORT_TYPE_MASK ) >>
                              USBCPOWER4_PD_PORT_TYPE_SHIFT;
    }

    return error_flag;
}

err_t usbcpower4_read_active_pdo ( usbcpower4_t *ctx, usbcpower4_contract_t *contract )
{
    err_t error_flag = USBCPOWER4_ERROR;
    uint8_t pdo_buf[ USBCPOWER4_ACTIVE_PDO_SIZE ] = { 0 };
    uint32_t pdo = 0;

    if ( NULL != contract )
    {
        contract->valid = 0;
        contract->supply_type = 0;
        contract->apdo_type = 0;
        contract->voltage_mv = 0;
        contract->min_voltage_mv = 0;
        contract->max_voltage_mv = 0;
        contract->current_ma = 0;
        contract->power_mw = 0;
        contract->raw_pdo = 0;

        error_flag = usbcpower4_read_regs( ctx, USBCPOWER4_REG_ACTIVE_PDO, pdo_buf, USBCPOWER4_ACTIVE_PDO_SIZE );
    }

    if ( USBCPOWER4_OK == error_flag )
    {
        // The selected PDO is stored as a little-endian 32-bit value.
        pdo = ( uint32_t ) pdo_buf[ USBCPOWER4_PDO_BYTE_0 ];
        pdo |= ( uint32_t ) pdo_buf[ USBCPOWER4_PDO_BYTE_1 ] << USBCPOWER4_BYTE_SHIFT_8;
        pdo |= ( uint32_t ) pdo_buf[ USBCPOWER4_PDO_BYTE_2 ] << USBCPOWER4_BYTE_SHIFT_16;
        pdo |= ( uint32_t ) pdo_buf[ USBCPOWER4_PDO_BYTE_3 ] << USBCPOWER4_BYTE_SHIFT_24;

        contract->raw_pdo = pdo;
        if ( 0 != pdo )
        {
            contract->valid = USBCPOWER4_PDO_VALID;
            contract->supply_type = ( uint8_t ) ( ( pdo & USBCPOWER4_PDO_TYPE_MASK ) >> USBCPOWER4_PDO_TYPE_SHIFT );

            switch ( contract->supply_type )
            {
                case USBCPOWER4_PDO_TYPE_FIXED:
                {
                    contract->voltage_mv = ( uint16_t ) ( ( ( pdo & USBCPOWER4_FIXED_VOLTAGE_MASK ) >>
                                                            USBCPOWER4_FIXED_VOLTAGE_SHIFT ) *
                                                            USBCPOWER4_PDO_VOLTAGE_STEP_MV );
                    contract->min_voltage_mv = contract->voltage_mv;
                    contract->max_voltage_mv = contract->voltage_mv;
                    contract->current_ma = ( uint16_t ) ( ( pdo & USBCPOWER4_PDO_CURRENT_MASK ) * USBCPOWER4_PDO_CURRENT_STEP_MA );
                    contract->power_mw = ( ( uint32_t ) contract->voltage_mv * contract->current_ma ) / 1000;
                    break;
                }
                case USBCPOWER4_PDO_TYPE_BATTERY:
                {
                    contract->max_voltage_mv = ( uint16_t ) ( ( ( pdo & USBCPOWER4_PDO_MAX_VOLTAGE_MASK ) >>
                                                                USBCPOWER4_PDO_MAX_VOLTAGE_SHIFT ) *
                                                                USBCPOWER4_PDO_VOLTAGE_STEP_MV );
                    contract->min_voltage_mv = ( uint16_t ) ( ( ( pdo & USBCPOWER4_PDO_MIN_VOLTAGE_MASK ) >>
                                                                USBCPOWER4_PDO_MIN_VOLTAGE_SHIFT ) *
                                                                USBCPOWER4_PDO_VOLTAGE_STEP_MV );
                    contract->power_mw = ( pdo & USBCPOWER4_PDO_POWER_MASK ) * USBCPOWER4_PDO_POWER_STEP_MW;
                    break;
                }
                case USBCPOWER4_PDO_TYPE_VARIABLE:
                {
                    contract->max_voltage_mv = ( uint16_t ) ( ( ( pdo & USBCPOWER4_PDO_MAX_VOLTAGE_MASK ) >>
                                                                USBCPOWER4_PDO_MAX_VOLTAGE_SHIFT ) *
                                                                USBCPOWER4_PDO_VOLTAGE_STEP_MV );
                    contract->min_voltage_mv = ( uint16_t ) ( ( ( pdo & USBCPOWER4_PDO_MIN_VOLTAGE_MASK ) >>
                                                                USBCPOWER4_PDO_MIN_VOLTAGE_SHIFT ) *
                                                                USBCPOWER4_PDO_VOLTAGE_STEP_MV );
                    contract->current_ma = ( uint16_t ) ( ( pdo & USBCPOWER4_PDO_CURRENT_MASK ) * USBCPOWER4_PDO_CURRENT_STEP_MA );
                    contract->power_mw = ( ( uint32_t ) contract->max_voltage_mv * contract->current_ma ) / 1000;
                    break;
                }
                case USBCPOWER4_PDO_TYPE_AUGMENTED:
                {
                    contract->apdo_type = ( uint8_t ) ( ( pdo & USBCPOWER4_APDO_TYPE_MASK ) >> USBCPOWER4_APDO_TYPE_SHIFT );
                    if ( USBCPOWER4_APDO_TYPE_PPS == contract->apdo_type )
                    {
                        contract->max_voltage_mv = ( uint16_t ) ( ( ( pdo & USBCPOWER4_PPS_MAX_VOLTAGE_MASK ) >>
                                                                    USBCPOWER4_PPS_MAX_VOLTAGE_SHIFT ) *
                                                                    USBCPOWER4_PPS_VOLTAGE_STEP_MV );
                        contract->min_voltage_mv = ( uint16_t ) ( ( ( pdo & USBCPOWER4_PPS_MIN_VOLTAGE_MASK ) >>
                                                                    USBCPOWER4_PPS_MIN_VOLTAGE_SHIFT ) *
                                                                    USBCPOWER4_PPS_VOLTAGE_STEP_MV );
                        contract->current_ma = ( uint16_t ) ( ( pdo & USBCPOWER4_PPS_CURRENT_MASK ) * USBCPOWER4_PPS_CURRENT_STEP_MA );
                        contract->power_mw = ( ( uint32_t ) contract->max_voltage_mv * contract->current_ma ) / 1000;
                    }
                    break;
                }
                default:
                {
                    contract->valid = 0;
                    error_flag = USBCPOWER4_ERROR;
                    break;
                }
            }
        }
    }

    return error_flag;
}

err_t usbcpower4_read_adc_results ( usbcpower4_t *ctx, usbcpower4_adc_t *adc_result )
{
    err_t error_flag = USBCPOWER4_ERROR;
    uint8_t adc_buf[ USBCPOWER4_ADC_RESULTS_SIZE ] = { 0 };

    if ( NULL != adc_result )
    {
        adc_result->adcin1_mv = 0;
        adc_result->adcin2_mv = 0;
        adc_result->ldo_3v3_mv = 0;
        adc_result->vbus_mv = 0;
        adc_result->vbus_mean_ma = 0;
        adc_result->vbus_peak_ma = 0;

        error_flag = usbcpower4_read_regs( ctx, USBCPOWER4_REG_ADC_RESULTS, adc_buf, USBCPOWER4_ADC_RESULTS_SIZE );
    }

    if ( USBCPOWER4_OK == error_flag )
    {
        // Convert raw ADC bytes using the integer LSB scales from the TRM.
        adc_result->adcin1_mv = ( uint16_t ) adc_buf[ USBCPOWER4_ADC_ADCIN1_INDEX ] * USBCPOWER4_ADC_GPIO_LSB_MV;
        adc_result->adcin2_mv = ( uint16_t ) adc_buf[ USBCPOWER4_ADC_ADCIN2_INDEX ] * USBCPOWER4_ADC_GPIO_LSB_MV;
        adc_result->ldo_3v3_mv = ( uint16_t ) adc_buf[ USBCPOWER4_ADC_LDO3V3_INDEX ] * USBCPOWER4_ADC_GPIO_LSB_MV;
        adc_result->vbus_mv = ( uint16_t ) adc_buf[ USBCPOWER4_ADC_VBUS_INDEX ] * USBCPOWER4_ADC_VBUS_LSB_MV;
        adc_result->vbus_mean_ma = ( ( uint16_t ) adc_buf[ USBCPOWER4_ADC_IVBUS_MEAN_INDEX ] * USBCPOWER4_ADC_CURRENT_SCALE ) /
                                     USBCPOWER4_ADC_CURRENT_DIVIDER;
        adc_result->vbus_peak_ma = ( ( uint16_t ) adc_buf[ USBCPOWER4_ADC_IVBUS_PEAK_INDEX ] * USBCPOWER4_ADC_CURRENT_SCALE ) /
                                     USBCPOWER4_ADC_CURRENT_DIVIDER;
    }

    return error_flag;
}

err_t usbcpower4_set_current_monitor ( usbcpower4_t *ctx, uint8_t state )
{
    err_t error_flag = USBCPOWER4_ERROR;
    uint8_t port_control[ USBCPOWER4_PORT_CONTROL_SIZE ] = { 0 };

    error_flag = usbcpower4_read_regs( ctx, USBCPOWER4_REG_PORT_CONTROL, port_control, USBCPOWER4_PORT_CONTROL_SIZE );
    if ( USBCPOWER4_OK == error_flag )
    {
        // Preserve every PORT_CONTROL field except Enable Current Monitor.
        if ( USBCPOWER4_CURRENT_MONITOR_ENABLED == state )
        {
            port_control[ USBCPOWER4_PORT_CURRENT_INDEX ] |= USBCPOWER4_PORT_CURRENT_MASK;
        }
        else
        {
            port_control[ USBCPOWER4_PORT_CURRENT_INDEX ] &= ( uint8_t ) ~USBCPOWER4_PORT_CURRENT_MASK;
        }
        error_flag = usbcpower4_write_regs( ctx, USBCPOWER4_REG_PORT_CONTROL, port_control, USBCPOWER4_PORT_CONTROL_SIZE );
    }

    return error_flag;
}

void usbcpower4_set_epr_mode ( usbcpower4_t *ctx, uint8_t mode )
{
    if ( USBCPOWER4_EPR_MODE_ENABLED == mode )
    {
        digital_out_high( &ctx->epr );
    }
    else
    {
        digital_out_low( &ctx->epr );
    }
}

uint8_t usbcpower4_get_int_pin ( usbcpower4_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

static err_t usbcpower4_exec_task ( usbcpower4_t *ctx, uint8_t *task, uint8_t *task_data, uint8_t data_len )
{
    err_t error_flag = USBCPOWER4_ERROR;
    uint8_t task_state[ USBCPOWER4_TASK_SIZE ] = { 0 };
    uint16_t retry_cnt = 0;

    if ( ( NULL != task ) &&
         ( ( 0 == data_len ) || ( ( NULL != task_data ) && ( USBCPOWER4_MAX_REG_SIZE >= data_len ) ) ) )
    {
        error_flag = USBCPOWER4_OK;
        if ( 0 < data_len )
        {
            error_flag = usbcpower4_write_regs( ctx, USBCPOWER4_REG_DATA1, task_data, data_len );
        }
        if ( USBCPOWER4_OK == error_flag )
        {
            error_flag = usbcpower4_write_regs( ctx, USBCPOWER4_REG_CMD1, task, USBCPOWER4_TASK_SIZE );
        }
    }

    if ( USBCPOWER4_OK == error_flag )
    {
        // CMD1 clears to zero when the task has completed successfully.
        error_flag = USBCPOWER4_ERROR;
        for ( retry_cnt = 0; retry_cnt < USBCPOWER4_TASK_RETRY_COUNT; retry_cnt++ )
        {
            Delay_1ms( );
            if ( USBCPOWER4_OK == usbcpower4_read_regs( ctx, USBCPOWER4_REG_CMD1, task_state, USBCPOWER4_TASK_SIZE ) )
            {
                if ( ( 0 == task_state[ 0 ] ) && ( 0 == task_state[ 1 ] ) &&
                     ( 0 == task_state[ 2 ] ) && ( 0 == task_state[ 3 ] ) )
                {
                    error_flag = USBCPOWER4_OK;
                    break;
                }
            }
        }
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
