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
 * @file  ecggsr.c
 * @brief This file contains API header for ECG GSR Click driver.
 */

// ----------------------------------------------------------------------------

#include "ecggsr.h"

void ecggsr_cfg_setup( ecggsr_cfg_t *cfg )
{
    cfg->scl_pin = HAL_PIN_NC;
    cfg->sda_pin = HAL_PIN_NC;
    cfg->enable_pin = HAL_PIN_NC;
    
    cfg->i2c_address = ECGGSR_SLAVE_ADDRESS;
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;
}

err_t ecggsr_init( ecggsr_t *ctx, ecggsr_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;
    
    i2c_cfg.speed = cfg->i2c_speed;
    i2c_cfg.scl = cfg->scl_pin;
    i2c_cfg.sda = cfg->sda_pin;
    
    ctx->slave_address = cfg->i2c_address;
    ctx->enable_pin = cfg->enable_pin;
    
    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) )
    {
        return ecggsr_init_error;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    return ecggsr_ok;
}

void ecggsr_default_cfg( ecggsr_t *ctx, ecggsr_cfg_t *cfg )
{
    // Reset all the registers on the ECG GSR Click.
    ecggsr_reset( ctx );
    Delay_1sec();
    
    /**
     * Set default functionality of the ECG GSR Click:
     *  1. DEFAULT_ECGGSR_CLICK_FUNCTIONALITY ( ENABLE_OXIMETER_FUNCTIONALITY )
     *  2. ENABLE_HEARTRATE_FUNCTIONALITY
     *  3. ENABLE_GALVANIC_SKIN_RESPONSE_FUNCTIONALITY
    */
    cfg->click_functionality = DEFAULT_ECGGSR_CLICK_FUNCTIONALITY;
    
    // Enable the Oscillator and LDO.
    ecggsr_write_reg( ctx, ECGGSR_CONTROL_REG, ECGGSR_ENABLE_OSC_AND_LDO );
    
    if ( ENABLE_OXIMETER_FUNCTIONALITY == cfg->click_functionality )
    {
        // LED1_CURRL register. Set current to 980uA.
        ecggsr_write_reg( ctx, ECGGSR_LED1_CURRL_REG, ECGGSR_PD_LED_CURRENT );

        // LED2_CURRL register. Set current to 980uA.
        ecggsr_write_reg( ctx, ECGGSR_LED2_CURRL_REG, ECGGSR_PD_LED_CURRENT );

        // LED4_CURRL register. Set current to 980uA.
        ecggsr_write_reg( ctx, ECGGSR_LED4_CURRL_REG, ECGGSR_PD_LED_CURRENT );

        // LED_CFG register. Enable signal reference and three diodes.
        ecggsr_write_reg( ctx, ECGGSR_LED_CFG_REG, ECGGSR_ENABLE_REF_AND_DIODES );
            
        // LED12_MODE register. Enable output of LED12 LEDs.
        ecggsr_write_reg( ctx, ECGGSR_LED12_MODE_REG, ECGGSR_ENABLE_LED12_OUTPUT );
        
        // LED34_MODE register. Enable output of LED4 LEDs.
        ecggsr_write_reg( ctx, ECGGSR_LED34_MODE_REG, ECGGSR_ENABLE_LED4_OUTPUT );

        // PD_CFG register. Configure photo diodes.
        ecggsr_write_reg( ctx, ECGGSR_PD_CFG_REG, ECGGSR_CONF_PHOTODIODE );    

        // PDOFFX_LED_ON register. Sunlight interference compensation.
        ecggsr_write_reg( ctx, ECGGSR_PDOFFX_LEDON_REG, ECGGSR_SUNLIGHT_COMPENSATION );
            
        // PD_AMPCFG register. Enable photo amplifier.
        ecggsr_write_reg( ctx, ECGGSR_PD_AMPCFG_REG, ECGGSR_ENABLE_PHOTOAMPLIFIER );
        
        // MAN_SEQ_CFG register. Start PPG!!!
        ecggsr_write_reg( ctx, ECGGSR_MAN_SEQ_CFG_REG, ECGGSR_START_PPG );
        
        // Enable ADC.
        ecggsr_write_reg( ctx, ECGGSR_ADC_CFGB_REG, ECGGSR_ENABLE_ADC );

        // OFE_CFGA register. Enable OFE2 and OFE1 and their bias.
        ecggsr_write_reg( ctx, ECGGSR_OFE_CFGA_REG, ECGGSR_ENABLE_OFE_AND_BIAS );
    } 
    else if ( ENABLE_HEARTRATE_FUNCTIONALITY == cfg->click_functionality )
    {
        // LED_CFG register. Enable signal reference.
        ecggsr_write_reg( ctx, ECGGSR_LED_CFG_REG, ECGGSR_ENABLE_SIG_REFERENCE );

        // EAF_CFG register. Enable EAF bias and Gain Stage.
        ecggsr_write_reg( ctx, ECGGSR_EAF_CFG_REG, ECGGSR_ENABLE_BIAS_AND_GAIN );

        // EAF_GST register. Input selection, reference voltage, Gain.
        ecggsr_write_reg( ctx, ECGGSR_EAF_GST_REG, ECGGSR_INPUT_AND_REF_VOLTAGE );

        // EAF_BIAS register. Resistive biasing.
        ecggsr_write_reg( ctx, ECGGSR_EAF_BIAS_REG, ECGGSR_RESISTIVE_BIASING );

        // ECG_MODE register. Set recommended gain settings in stages 1 and 2.
        ecggsr_write_reg( ctx, ECGGSR_ECG_MODE_REG, ECGGSR_GAIN_SETTINGS_STAGES1_2 );

        // ECG_CFGA register. Enable ECG amplifier.
        ecggsr_write_reg( ctx, ECGGSR_ECG_CFGA_REG, ECGGSR_ENABLE_ECG_AMPLIFIER );

        // ECG_CFGB register. Set recommended gain setting for stage 3.
        ecggsr_write_reg( ctx, ECGGSR_ECG_CFGB_REG, ECGGSR_GAIN_SETTINGS_STAGE3 );

        // ECG_CFGC register. Enable Reference Amplifier.
        ecggsr_write_reg( ctx, ECGGSR_ECG_CFGC_REG, ECGGSR_ENABLE_REF_AMPLIFIER );
        
        // MAN_SEQ_CFG register. Start Sequencer.
        ecggsr_write_reg( ctx, ECGGSR_MAN_SEQ_CFG_REG, ECGGSR_START_SEQUENCER );
        
        // ADC_CFGB register. Enable ADC.
        ecggsr_write_reg( ctx, ECGGSR_ADC_CFGB_REG, ECGGSR_ENABLE_ADC );

        // ADC_CHANNEL_MASK_L register. Select Electrical Front End.
        ecggsr_write_reg( ctx, ECGGSR_ADC_CHANNEL_MASK_L_REG, ECGGSR_SELECT_EFE );

        // ADC_CHANNEL_MASK_H register. Select ECG amlifier input.
        ecggsr_write_reg( ctx, ECGGSR_ADC_CHANNEL_MASK_H_REG, ECGGSR_SELECT_AMPLIFIER_INPUT );
    } 
    else if ( ENABLE_GALVANIC_SKIN_RESPONSE_FUNCTIONALITY == cfg->click_functionality )
    {
        // GPIO_A register. Set GPIO1 as analog.
        ecggsr_write_reg( ctx, ECGGSR_GPIO_A_REG, ECGGSR_ENABLE_GPIO1_ANALOG );

        // GPIO_SR register. Set slew rate for GPIO1.
        ecggsr_write_reg( ctx, ECGGSR_GPIO_SR_REG, ECGGSR_SET_SLEW_RATE_GPIO1 );
        
        // EAF_CFG register. Enable EAF bias and Gain Stage.
        ecggsr_write_reg( ctx, ECGGSR_EAF_CFG_REG, ECGGSR_ENABLE_BIAS_AND_GAIN );

        // EAF_GST register. Input selection, reference voltage, Gain.
        ecggsr_write_reg( ctx, ECGGSR_EAF_GST_REG, ECGGSR_SET_GPIO1_AS_INPUT );
        
        // EAF_BIAS register. Resistive biasing.
        ecggsr_write_reg( ctx, ECGGSR_EAF_BIAS_REG, ECGGSR_SET_RES_BIAS_GPIO1 );
        
        // MAN_SEQ_CFG register. Start Sequencer.
        ecggsr_write_reg( ctx, ECGGSR_MAN_SEQ_CFG_REG, ECGGSR_START_SEQUENCER );
        
        // ADC_CFGB register. Enable ADC.
        ecggsr_write_reg( ctx, ECGGSR_ADC_CFGB_REG, ECGGSR_ENABLE_ADC );

        // ADC_CHANNEL_MASK_L register. Select Electrical Front End.
        ecggsr_write_reg( ctx, ECGGSR_ADC_CHANNEL_MASK_L_REG, ECGGSR_SELECT_EFE );
    } 
}

err_t ecggsr_read_reg( ecggsr_t *ctx, uint8_t register_address, uint8_t *data_out, uint8_t num_of_regs )
{
    if ( register_address > ECGGSR_INTR2_REG )
    {
        return ecggsr_init_error;
    }
    if ( num_of_regs > 128 )
    {
        return ecggsr_init_error;
    }
    return i2c_master_write_then_read( &ctx->i2c, &register_address, 1, data_out, num_of_regs );
}

err_t ecggsr_write_reg( ecggsr_t *ctx, uint8_t register_address, uint8_t transfer_data )
{
    uint8_t data_buffer[ 2 ] = { 0 };
    
    if ( register_address > ECGGSR_INTR2_REG )
    {
        return ecggsr_init_error;
    }
    
    data_buffer[ 0 ] = register_address;
    data_buffer[ 1 ] = transfer_data;      
    
    return i2c_master_write( &ctx->i2c, data_buffer, 2 );
}

void ecggsr_read_dev_id( ecggsr_t *ctx, uint8_t *dev_id_out )
{    
    // Read register ID (0x92).
    ecggsr_read_reg( ctx, ECGGSR_ID_REG, dev_id_out, 1 );
    
    // Device ID mask uses bits [7:2] of the ID register.
    *dev_id_out = *(dev_id_out) & ECGGSR_DEV_ID_MASK;
}

void ecggsr_reset( ecggsr_t *ctx )
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
