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
 * @file  ecg_gsr_example.c
 * @brief ECG GSR Click example.
 */

// ----------------------------------------------------------------------------
/*!
 * # Description
 * This application collects data from the sensor, calculates it and then logs
 * the result.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, performs SW reset of all the registers, which puts
 * the registers in their initial state.
 * 
 * ## Application Task  
 * Depending on the user selection, application measures:
 *  1. value of oxygen level in human's blood or
 *  2. heartrate or
 *  3. galvanic skin response
 * 
 * \author MikroE Team
 */
// ------------------------------------------------------------------- INCLUDES

#include "ECG_GSR.h"
#include "board.h"
#include "log.h"

// ------------------------------------------------------------------ VARIABLES

// ECG GSR context instance declaration.
static ecg_gsr_t ecg_gsr;

// ECG GSR configuration instance declaration.
ecg_gsr_cfg_t ecg_gsr_cfg;

// Logger context instance declaration.
static log_t logger;

// Result storage.
static uint32_t res_slot[ 100 ];

// Device id slot.
static uint8_t dev_id = 0;

// Status of the Control register.
static uint8_t control_reg = 0;

// Status of the ADC_DATA_L register.
static uint8_t adc_data_l_reg = 0;

// Status of the ADC_DATA_L register.
static uint8_t adc_data_h_reg = 0;

// Status of the low register of ADC.
static uint8_t adc_result_l = 0;

// Status of the high register of ADC.
static uint8_t adc_result_h = 0;

// Final PPG result.
static uint8_t ppg_result = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void ecg_gsr_get_oxygen_saturation( void )
{
    // Enable the Oscillator and LDO.
    ecg_gsr_write_reg( &ecg_gsr, ECG_GSR_CONTROL_REG, ECG_GSR_ENABLE_OSC_AND_LDO);

    // Read Control Register.
    ecg_gsr_read_reg(&ecg_gsr, ECG_GSR_CONTROL_REG, &control_reg, 1 );
    
    // LED1_CURRL register. Set current to 980uA.
    ecg_gsr_write_reg( &ecg_gsr, ECG_GSR_LED1_CURRL_REG, ECG_GSR_PD_LED_CURRENT);

    // LED2_CURRL register. Set current to 980uA.
    ecg_gsr_write_reg( &ecg_gsr, ECG_GSR_LED2_CURRL_REG, ECG_GSR_PD_LED_CURRENT);

    // LED4_CURRL register. Set current to 980uA.
    ecg_gsr_write_reg( &ecg_gsr, ECG_GSR_LED4_CURRL_REG, ECG_GSR_PD_LED_CURRENT);

    // LED_CFG register. Enable signal reference and three diodes.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_LED_CFG_REG, ECG_GSR_ENABLE_REF_AND_DIODES );
        
    // LED12_MODE register. Enable output of LED12 LEDs.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_LED12_MODE_REG, ECG_GSR_ENABLE_LED12_OUTPUT );
    
    // LED34_MODE register. Enable output of LED4 LEDs.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_LED34_MODE_REG, ECG_GSR_ENABLE_LED4_OUTPUT );

    // PD_CFG register. Configure photo diodes.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_PD_CFG_REG, ECG_GSR_CONF_PHOTODIODE );    

    // PDOFFX_LED_ON register. Sunlight interference compensation.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_PDOFFX_LEDON_REG, ECG_GSR_SUNLIGHT_COMPENSATION );
        
    // PD_AMPCFG register. Enable photo amplifier.
    ecg_gsr_write_reg( &ecg_gsr, ECG_GSR_PD_AMPCFG_REG, ECG_GSR_ENABLE_PHOTOAMPLIFIER );
    
    // MAN_SEQ_CFG register. Start PPG!!!
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_MAN_SEQ_CFG_REG, ECG_GSR_START_PPG );
    
    // Enable ADC.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_ADC_CFGB_REG, ECG_GSR_ENABLE_ADC );

    // SEQ_START register. Start one ADC conversion.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_SEQ_START_REG, ECG_GSR_START_ADC_CONVERSION );
    
    // OFE_CFGA register. Enable OFE2 and OFE1 and their bias.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_OFE_CFGA_REG, ECG_GSR_ENABLE_OFE_AND_BIAS );
            
    // Read lower 8 bits of raw ADC data.
    ecg_gsr_read_reg(&ecg_gsr, ECG_GSR_ADC_DATA_L_REG, &adc_data_l_reg, 1 );
    adc_result_l = adc_data_l_reg - ECG_GSR_PPG_SCALE_VAL;

    // Read higher 8 bits of raw ADC data.
    ecg_gsr_read_reg(&ecg_gsr, ECG_GSR_ADC_DATA_H_REG, &adc_data_h_reg, 1 );
    adc_result_h = adc_data_h_reg & ECG_GSR_ADC_DATA_H_MASK;
        
    // Raw ADC result.
    ppg_result = adc_result_l + adc_result_h;
    
    if ( ( adc_result_l > ECG_GSR_PPG_L_THRESHOLD ) && (adc_result_l < ECG_GSR_PPG_H_THRESHOLD ) )
    {
        adc_result_l = ECG_GSR_PPG_H_THRESHOLD;
    }
    
    if (adc_result_l > ECG_GSR_PPG_MAX_VAL )
    {
        adc_result_l = ECG_GSR_PPG_MAX_VAL;
    }
    
    // Final Oximeter results.
    log_printf(&logger, "Level of oxygen saturation in your blood: %d\r\n", ( uint16_t )adc_result_l );
}

void ecg_gsr_get_heartrate( void )
{
    // Enable oscillator and LDO.
    ecg_gsr_write_reg( &ecg_gsr, ECG_GSR_CONTROL_REG, ECG_GSR_ENABLE_OSC_AND_LDO );
        
    // LED_CFG register. Enable signal reference.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_LED_CFG_REG, ECG_GSR_ENABLE_SIG_REFERENCE );

    // EAF_CFG register. Enable EAF bias and Gain Stage.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_EAF_CFG_REG, ECG_GSR_ENABLE_BIAS_AND_GAIN );

    // EAF_GST register. Input selection, reference voltage, Gain.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_EAF_GST_REG, ECG_GSR_INPUT_AND_REF_VOLTAGE );

    // EAF_BIAS register. Resistive biasing.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_EAF_BIAS_REG, ECG_GSR_RESISTIVE_BIASING );

    // ECG_MODE register. Set recommended gain settings in stages 1 and 2.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_ECG_MODE_REG, ECG_GSR_GAIN_SETTINGS_STAGES1_2 );

    // ECG_CFGA register. Enable ECG amplifier.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_ECG_CFGA_REG, ECG_GSR_ENABLE_ECG_AMPLIFIER );

    // ECG_CFGB register. Set recommended gain setting for stage 3.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_ECG_CFGB_REG, ECG_GSR_GAIN_SETTINGS_STAGE3 );

    // ECG_CFGC register. Enable Reference Amplifier.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_ECG_CFGC_REG, ECG_GSR_ENABLE_REF_AMPLIFIER );
    
    // MAN_SEQ_CFG register. Start Sequencer.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_MAN_SEQ_CFG_REG, ECG_GSR_START_SEQUENCER );
    
    // ADC_CFGB register. Enable ADC.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_ADC_CFGB_REG, ECG_GSR_ENABLE_ADC );

    // ADC_CHANNEL_MASK_L register. Select Electrical Front End.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_ADC_CHANNEL_MASK_L_REG, ECG_GSR_SELECT_EFE );

    // ADC_CHANNEL_MASK_H register. Select ECG amlifier input.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_ADC_CHANNEL_MASK_H_REG, ECG_GSR_SELECT_AMPLIFIER_INPUT );

    // SEQ_START register. Start one ADC conversion.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_SEQ_START_REG, ECG_GSR_START_ADC_CONVERSION );
            
    // Read lower 8 bits of raw ADC data.
    ecg_gsr_read_reg(&ecg_gsr, ECG_GSR_ADC_DATA_L_REG, &adc_data_l_reg, 1 );
    adc_result_l = adc_data_l_reg;

    // Read higher 8 bits of raw ADC data.
    ecg_gsr_read_reg(&ecg_gsr, ECG_GSR_ADC_DATA_H_REG, &adc_data_h_reg, 1 );
    adc_result_h = ( adc_data_h_reg & ECG_GSR_ADC_DATA_H_MASK ) * ECG_GSR_ECG_SCALE_VAL;
        
    // Raw ADC result.
    ppg_result = adc_result_l + adc_result_h;
    
    // Final heartrate results.
    log_printf( &logger, "Final heartrate results: %d, %d\r\n", ( uint16_t )adc_result_l, ( uint16_t )adc_result_h );
}

void ecg_gsr_get_galvanic_skin_response( void )
{
    // Enable oscillator and LDO.
    ecg_gsr_write_reg( &ecg_gsr, ECG_GSR_CONTROL_REG, ECG_GSR_ENABLE_OSC_AND_LDO );
    
    // GPIO_A register. Set GPIO1 as analog.
    ecg_gsr_write_reg( &ecg_gsr, ECG_GSR_GPIO_A_REG, ECG_GSR_ENABLE_GPIO1_ANALOG );

    // GPIO_SR register. Set slew rate for GPIO1.
    ecg_gsr_write_reg( &ecg_gsr, ECG_GSR_GPIO_SR_REG, ECG_GSR_SET_SLEW_RATE_GPIO1 );
    
    // EAF_CFG register. Enable EAF bias and Gain Stage.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_EAF_CFG_REG, ECG_GSR_ENABLE_BIAS_AND_GAIN );

    // EAF_GST register. Input selection, reference voltage, Gain.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_EAF_GST_REG, ECG_GSR_SET_GPIO1_AS_INPUT );
    
    // EAF_BIAS register. Resistive biasing.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_EAF_BIAS_REG, ECG_GSR_SET_RES_BIAS_GPIO1 );
    
    // MAN_SEQ_CFG register. Start Sequencer.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_MAN_SEQ_CFG_REG, ECG_GSR_START_SEQUENCER );
    
    // ADC_CFGB register. Enable ADC.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_ADC_CFGB_REG, ECG_GSR_ENABLE_ADC );

    // ADC_CHANNEL_MASK_L register. Select Electrical Front End.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_ADC_CHANNEL_MASK_L_REG, ECG_GSR_SELECT_EFE );

    // SEQ_START register. Start one ADC conversion.
    ecg_gsr_write_reg(&ecg_gsr, ECG_GSR_SEQ_START_REG, ECG_GSR_START_ADC_CONVERSION );
            
    // Read lower 8 bits of raw ADC data.
    ecg_gsr_read_reg(&ecg_gsr, ECG_GSR_ADC_DATA_L_REG, &adc_data_l_reg, 1 );
    adc_result_l = adc_data_l_reg;

    // Read higher 8 bits of raw ADC data.
    ecg_gsr_read_reg(&ecg_gsr, ECG_GSR_ADC_DATA_H_REG, &adc_data_h_reg, 1 );
    adc_result_h = adc_data_h_reg & ECG_GSR_ADC_DATA_H_MASK;
        
    // Raw ADC result.
    ppg_result = adc_result_l + adc_result_h;
    
    // Final Galvanic Skin Response results.
    log_printf( &logger, "Final GSR result: %d \r\n", ( uint16_t )adc_result_h );
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    
    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    
    //  Click initialization.
    ecg_gsr_cfg_setup( &ecg_gsr_cfg );
    ECG_GSR_MAP_MIKROBUS( ecg_gsr_cfg, MIKROBUS_1 );
    ecg_gsr_init( &ecg_gsr, &ecg_gsr_cfg );
    Delay_1sec();
    ecg_gsr_default_cfg( &ecg_gsr, &ecg_gsr_cfg );
    Delay_1sec();
}

ecg_gsr_err_t application_task( void )
{
    // ------------------------------------------------------------
    // Check the presence of the ECG GSR Click by reading device ID.
    // ------------------------------------------------------------
    ecg_gsr_read_dev_id(&ecg_gsr, ECG_GSR_ID_REG, &dev_id , 1);
    
    if ( dev_id != ECG_GSR_DEV_ID )
    {
        return ecg_gsr_init_error;
    }

    // ------------------------------------------------------------
    // Enable desired functionality of the ECG GSR Click.
    // ------------------------------------------------------------
    if ( ecg_gsr_cfg.click_functionality == DEFAULT_ECG_GSR_CLICK_FUNCTIONALITY )
    {
        ecg_gsr_get_oxygen_saturation();
    } else if ( ecg_gsr_cfg.click_functionality == ENABLE_HEARTRATE_FUNCTIONALITY )
    {
        ecg_gsr_get_heartrate();
    } else if ( ecg_gsr_cfg.click_functionality == ENABLE_GALVANIC_SKIN_RESPONSE_FUNCTIONALITY )
    {
        ecg_gsr_get_galvanic_skin_response();
    } else
    {
        return ecg_gsr_init_error;
    }
    
    return ecg_gsr_ok;
}

void main() {

    application_init();
    
    for ( ; ; )
    {
        application_task();
        
        Delay_10ms();
    }
}
