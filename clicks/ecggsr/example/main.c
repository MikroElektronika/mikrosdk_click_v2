/*!
 * @file  main.c
 * @brief ECG GSR Click example.
 * 
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
#include "ecggsr.h"
#include "board.h"
#include "log.h"

// ------------------------------------------------------------------ VARIABLES

// ECG GSR context instance declaration.
static ecggsr_t ecggsr;

// ECG GSR configuration instance declaration.
ecggsr_cfg_t ecggsr_cfg;

// Logger context instance declaration.
static log_t logger;

// Device id slot.
static uint8_t dev_id = 0;

// Status of the ADC_DATA_L register.
static uint8_t adc_data_l_reg = 0;

// Status of the ADC_DATA_L register.
static uint8_t adc_data_h_reg = 0;

// Status of the low register of ADC.
static uint8_t adc_result_l = 0;

// Status of the high register of ADC.
static uint8_t adc_result_h = 0;

// ADC result.
static uint16_t adc_result = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void ecggsr_get_oxy_saturation( void )
{
    // SEQ_START register. Start one ADC conversion.
    ecggsr_write_reg( &ecggsr, ECGGSR_SEQ_START_REG, ECGGSR_START_ADC_CONVERSION );
    Delay_1ms( );
    ecggsr_write_reg( &ecggsr, ECGGSR_SEQ_START_REG, ECGGSR_START_ADC_CONVERSION );
    Delay_5ms( );
            
    // Read lower 8 bits of raw ADC data.
    ecggsr_read_reg( &ecggsr, ECGGSR_ADC_DATA_L_REG, &adc_data_l_reg, 1 );
    adc_result_l = adc_data_l_reg - ECGGSR_PPG_SCALE_VAL;

    // Read higher 8 bits of raw ADC data.
    ecggsr_read_reg( &ecggsr, ECGGSR_ADC_DATA_H_REG, &adc_data_h_reg, 1 );
    adc_result_h = adc_data_h_reg & ECGGSR_ADC_DATA_H_MASK;
        
    // Raw ADC result.
    adc_result = ( ( uint16_t ) adc_result_h << 8 ) | adc_result_l;
    
    if ( adc_result < ECGGSR_PPG_H_THRESHOLD )
    {
        adc_result = ECGGSR_PPG_H_THRESHOLD;
    }
    
    if ( adc_result_l > ECGGSR_PPG_MAX_VAL )
    {
        adc_result = ECGGSR_PPG_MAX_VAL;
    }
    
    // Final Oximeter results.
    log_printf( &logger, "Level of oxygen saturation in your blood: %u\r\n", adc_result );
    Delay_1sec ( );
}

void ecggsr_get_heartrate( void )
{
    // SEQ_START register. Start one ADC conversion.
    ecggsr_write_reg( &ecggsr, ECGGSR_SEQ_START_REG, ECGGSR_START_ADC_CONVERSION );
    Delay_1ms( );
    ecggsr_write_reg( &ecggsr, ECGGSR_SEQ_START_REG, ECGGSR_START_ADC_CONVERSION );
    Delay_5ms( );
            
    // Read lower 8 bits of raw ADC data.
    ecggsr_read_reg( &ecggsr, ECGGSR_ADC_DATA_L_REG, &adc_data_l_reg, 1 );
    adc_result_l = adc_data_l_reg;

    // Read higher 8 bits of raw ADC data.
    ecggsr_read_reg( &ecggsr, ECGGSR_ADC_DATA_H_REG, &adc_data_h_reg, 1 );
    adc_result_h = ( adc_data_h_reg & ECGGSR_ADC_DATA_H_MASK );
    // Raw ADC result.
    adc_result = ( ( uint16_t ) adc_result_h << 8 ) | adc_result_l;
    
    // Final heartrate results.
    log_printf( &logger, "%u\r\n", adc_result );
}

void ecggsr_get_gal_skin_resp( void )
{
    // SEQ_START register. Start one ADC conversion.
    ecggsr_write_reg( &ecggsr, ECGGSR_SEQ_START_REG, ECGGSR_START_ADC_CONVERSION );
    Delay_1ms( );
    // SEQ_START register. Start one ADC conversion.
    ecggsr_write_reg( &ecggsr, ECGGSR_SEQ_START_REG, ECGGSR_START_ADC_CONVERSION );
    Delay_5ms( );
            
    // Read lower 8 bits of raw ADC data.
    ecggsr_read_reg( &ecggsr, ECGGSR_ADC_DATA_L_REG, &adc_data_l_reg, 1 );
    adc_result_l = adc_data_l_reg;

    // Read higher 8 bits of raw ADC data.
    ecggsr_read_reg( &ecggsr, ECGGSR_ADC_DATA_H_REG, &adc_data_h_reg, 1 );
    adc_result_h = adc_data_h_reg & ECGGSR_ADC_DATA_H_MASK;
        
    // Raw ADC result.
    adc_result = ( ( uint16_t ) adc_result_h << 8 ) | adc_result_l;
    
    // Final Galvanic Skin Response results.
    log_printf( &logger, "%u\r\n", ( uint16_t ) adc_result );
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
    ecggsr_cfg_setup( &ecggsr_cfg );
    ECGGSR_MAP_MIKROBUS( ecggsr_cfg, MIKROBUS_1 );
    ecggsr_init( &ecggsr, &ecggsr_cfg );
    Delay_1sec();
    ecggsr_default_cfg( &ecggsr, &ecggsr_cfg );
    Delay_1sec();
}

void application_task( void )
{
    // ------------------------------------------------------------
    // Check the presence of the ECG GSR Click by reading device ID.
    // ------------------------------------------------------------
    ecggsr_read_dev_id( &ecggsr, &dev_id );
    if ( ECGGSR_DEV_ID == dev_id  )
    {
        // ------------------------------------------------------------
        // Enable desired functionality of the ECG GSR Click.
        // ------------------------------------------------------------
        if ( ENABLE_OXIMETER_FUNCTIONALITY == ecggsr_cfg.click_functionality )
        {
            ecggsr_get_oxy_saturation( );
        } 
        else if ( ENABLE_HEARTRATE_FUNCTIONALITY == ecggsr_cfg.click_functionality )
        {
            ecggsr_get_heartrate( );
        } 
        else if ( ENABLE_GALVANIC_SKIN_RESPONSE_FUNCTIONALITY == ecggsr_cfg.click_functionality )
        {
            ecggsr_get_gal_skin_resp( );
        } 
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}
