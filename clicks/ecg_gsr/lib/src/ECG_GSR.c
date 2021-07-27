/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The mikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  ecg_gsr.c
 * @brief This file contains API header for ECG GSR Click driver.
 */

// ----------------------------------------------------------------------------

#include "ECG_GSR.h"


void ecg_gsr_cfg_setup( ecg_gsr_cfg_t *cfg )
{
    cfg->scl_pin = HAL_PIN_NC;
    cfg->sda_pin = HAL_PIN_NC;
    cfg->enable_pin = HAL_PIN_NC;
    
    cfg->i2c_address = ECG_GSR_SLAVE_ADDRESS;
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;
}

ecg_gsr_err_t ecg_gsr_init( ecg_gsr_t *ctx, ecg_gsr_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;
    
    i2c_cfg.speed = cfg->i2c_speed;
    i2c_cfg.scl = cfg->scl_pin;
    i2c_cfg.sda = cfg->sda_pin;
    
    ctx->slave_address = cfg->i2c_address;
    ctx->enable_pin = cfg->enable_pin;
    
    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ecg_gsr_init_error;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    return ecg_gsr_ok;
}

void ecg_gsr_default_cfg( ecg_gsr_t *ctx, ecg_gsr_cfg_t *cfg )
{
    // Reset all the registers on the ECG GSR Click.
    ecg_gsr_reset( ctx );
    
    /**
     * Set default functionality of the ECG GSR Click:
     *  1. DEFAULT_ECG_GSR_CLICK_FUNCTIONALITY ( ENABLE_OXIMETER_FUNCTIONALITY )
     *  2. ENABLE_HEARTRATE_FUNCTIONALITY
     *  3. ENABLE_GALVANIC_SKIN_RESPONSE_FUNCTIONALITY
    */
    cfg->click_functionality = DEFAULT_ECG_GSR_CLICK_FUNCTIONALITY;
}

static void delay_30msec()
{
    Delay_10ms();
    Delay_10ms();
    Delay_10ms();
}

static void delay_100usec()
{
    uint8_t counter = 0;
    
    for ( counter = 0; counter < 10; counter++ )
    {
        Delay_10us();
    }
}

ecg_gsr_err_t ecg_gsr_read_reg( ecg_gsr_t *ctx, uint8_t register_address, uint16_t *data_out, uint8_t num_of_regs )
{
    
    uint8_t buff_data[ 256 ];
    uint8_t n_bytes;
    
    if ( register_address > ECG_GSR_INTR2_REG )
    {
        return ecg_gsr_init_error;
    }
    if ( num_of_regs > 128 )
    {
        return ecg_gsr_init_error;
    }
    
    n_bytes = num_of_regs * 1;
    
    delay_30msec();
    i2c_master_write_then_read( &ctx->i2c, &register_address, 1, buff_data, n_bytes );
    delay_100usec();
    
    data_out[0] = buff_data[0];
    
    return ecg_gsr_ok;
}

ecg_gsr_err_t ecg_gsr_write_reg( ecg_gsr_t *ctx, uint8_t register_address, uint8_t transfer_data )
{
    uint8_t data_buffer[ 2 ];
    
    if ( register_address > ECG_GSR_INTR2_REG )
    {
        return ecg_gsr_init_error;
    }
    
    data_buffer[ 0 ] = register_address;
    data_buffer[ 1 ] = transfer_data;      
    
    delay_30msec();
    i2c_master_write( &ctx->i2c, data_buffer, 2 );
    delay_100usec();
    
    return ecg_gsr_ok;
}

void ecg_gsr_read_dev_id( ecg_gsr_t *ctx, uint8_t register_address, uint8_t *dev_id_out, uint8_t num_of_regs )
{    
    // Read register ID (0x92).
    ecg_gsr_read_reg( ctx, register_address, dev_id_out, num_of_regs );
    
    // Device ID mask uses bits [7:2] of the ID register.
    *dev_id_out = *(dev_id_out) & ECG_GSR_DEV_ID_MASK;
}

void ecg_gsr_reset( ecg_gsr_t *ctx )
{
    // Create neccessary digital pin struct instance.
    digital_out_t cs_pin;
    
    // Initialize GPIO pin of MCU which controls ENABLE pin of ECG GSR Click.
    digital_out_init( &cs_pin, ctx->enable_pin );
    
    // Deassert this ENABLE pin (reset all the registers on the ECG GSR Click).
    digital_out_low( &cs_pin );
    
    // Give it some time.
    Delay_1sec();
    
    // Assert it again (make sure that register on th ECG GSR Click are available to user).
    digital_out_high( &cs_pin );
}
