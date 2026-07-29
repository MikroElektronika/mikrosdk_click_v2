/*!
 * @file main.c
 * @brief mCurrent Sens Click example
 *
 * # Description
 * This example demonstrates the use of mCurrent Sens Click for measuring
 * voltage, current, and temperature on two independent channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes communication, configures the device, optionally performs
 * calibration, and loads calibration data from EEPROM. ADC oversampling
 * ratio is set for faster runtime measurements.
 *
 * ## Application Task
 * Reads and logs voltage, current, and temperature values continuously.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mcurrentsens.h"

#ifndef MIKROBUS_POSITION_MCURRENTSENS
    #define MIKROBUS_POSITION_MCURRENTSENS MIKROBUS_1
#endif

/* Calibration data is stored in EEPROM and fetched on initialization.
 * Set this macro to 1 to run the jumper-guided calibration procedure
 * and store new calibration data to EEPROM. */
#define ENABLE_CALIBRATION 0

static mcurrentsens_t mcurrentsens;
static log_t logger;

/**
 * @brief mCurrent Sens wait setup function.
 * @details This function prints jumper setup instruction and waits for stabilization.
 * @param[in] message : Jumper setup instruction message.
 * @return None.
 * @note Used only during manual calibration procedure.
 */
static void mcurrentsens_wait_setup ( char *message );

/**
 * @brief mCurrent Sens calibrate device function.
 * @details This function performs manual two-point calibration and stores calibration data.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Follow the jumper instructions printed on the log output.
 */
static err_t mcurrentsens_calibrate_device ( mcurrentsens_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mcurrentsens_cfg_t mcurrentsens_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    mcurrentsens_cfg_setup( &mcurrentsens_cfg );
    MCURRENTSENS_MAP_MIKROBUS( mcurrentsens_cfg, MIKROBUS_POSITION_MCURRENTSENS );
    if ( SPI_MASTER_ERROR == mcurrentsens_init( &mcurrentsens, &mcurrentsens_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MCURRENTSENS_ERROR == mcurrentsens_default_cfg ( &mcurrentsens ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

#if ENABLE_CALIBRATION
    if ( MCURRENTSENS_OK == mcurrentsens_calibrate_device ( &mcurrentsens ) )
    {
        log_printf( &logger, " Device calibration success\r\n" );
    }
    else
    {
        log_error( &logger, " Device calibration" );
        for ( ; ; );
    }
#endif

    if ( MCURRENTSENS_OK == mcurrentsens_fetch_calib ( &mcurrentsens ) )
    {
        log_printf( &logger, " Calibration data read from EEPROM\r\n" );
    }
    else
    {
        log_error( &logger, " Calibration fetch - No communication with EEPROM or EEPROM is empty" );
        for ( ; ; );
    }
    
    /* Reduce OSR after calibration for faster runtime measurements. */
    mcurrentsens_set_osr( &mcurrentsens, MCURRENTSENS_CONFIG1_OSR_256 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float ch1_voltage_mv = 0;
    float ch1_current_ma = 0;
    float ch2_voltage_mv = 0;
    float ch2_current_ma = 0;
    float temperature = 0;

    if ( MCURRENTSENS_OK == mcurrentsens_read_ch1_voltage( &mcurrentsens, &ch1_voltage_mv ) )
    {
        log_printf( &logger, " CH1 voltage : %.1f mV\r\n", ch1_voltage_mv );
    }
    else
    {
        log_printf( &logger, " CH1 voltage read error\r\n" );
    }

    if ( MCURRENTSENS_OK == mcurrentsens_read_ch1_current( &mcurrentsens, &ch1_current_ma ) )
    {
        log_printf( &logger, " CH1 current : %.2f mA\r\n", ch1_current_ma );
    }
    else
    {
        log_printf( &logger, " CH1 current read error\r\n" );
    }

    if ( MCURRENTSENS_OK == mcurrentsens_read_ch2_voltage( &mcurrentsens, &ch2_voltage_mv ) )
    {
        log_printf( &logger, " CH2 voltage : %.1f mV\r\n", ch2_voltage_mv );
    }
    else
    {
        log_printf( &logger, " CH2 voltage read error\r\n" );
    }

    if ( MCURRENTSENS_OK == mcurrentsens_read_ch2_current( &mcurrentsens, &ch2_current_ma ) )
    {
        log_printf( &logger, " CH2 current : %.2f mA\r\n", ch2_current_ma );
    }
    else
    {
        log_printf( &logger, " CH2 current read error\r\n" );
    }

    if ( MCURRENTSENS_OK == mcurrentsens_read_temperature( &mcurrentsens, &temperature ) )
    {
        log_printf( &logger, " Temperature : %.2f degC\r\n", temperature );
    }
    else
    {
        log_printf( &logger, " Temperature read error\r\n" );
    }

    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void mcurrentsens_wait_setup ( char *message )
{
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " %s\r\n", message );
    log_printf( &logger, " Waiting 5 seconds...\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

static err_t mcurrentsens_calibrate_device ( mcurrentsens_t *ctx )
{
    err_t error_flag = MCURRENTSENS_OK;
    float measured_1 = 0;
    float measured_2 = 0;
    
    log_printf( &logger, " Starting calibration...\r\n" );
    log_printf( &logger, " Prepare to position jumpers as per the following instructions\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    /* Use maximum OSR during calibration for better measurement stability. */
    error_flag = mcurrentsens_set_osr( ctx, MCURRENTSENS_CONFIG1_OSR_98304 );

    /* ===================== CH1 VOLTAGE ===================== */
    if ( MCURRENTSENS_OK == error_flag )
    {
        mcurrentsens_wait_setup ( "SH1+: open, SH1-: CAL1" );
        error_flag = mcurrentsens_read_ch1_voltage( ctx, &measured_1 );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        mcurrentsens_wait_setup ( "SH1+: 3V, SH1-: open" );
        error_flag = mcurrentsens_read_ch1_voltage( ctx, &measured_2 );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        mcurrentsens_calculate_calib( &ctx->ch1_volt_cal, MCURRENTSENS_CH1_VOLTAGE_COEFF, 
                                      MCURRENTSENS_VOLTAGE_TARGET_0_MV, measured_1, 
                                      MCURRENTSENS_VOLTAGE_TARGET_3000_MV, measured_2 );
    }

    /* ===================== CH1 CURRENT ===================== */
    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_read_ch1_current( ctx, &measured_1 );
    }
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        mcurrentsens_wait_setup ( "SH1+: 3V, SH1-: CAL1" );
        error_flag = mcurrentsens_read_ch1_current( ctx, &measured_2 );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        mcurrentsens_calculate_calib( &ctx->ch1_curr_cal, MCURRENTSENS_CH1_CURRENT_COEFF, 
                                      MCURRENTSENS_CURRENT_TARGET_0_MA, measured_1, 
                                      MCURRENTSENS_CURRENT_TARGET_10_MA, measured_2 );
    }

    /* ===================== CH2 VOLTAGE ===================== */
    if ( MCURRENTSENS_OK == error_flag )
    {
        mcurrentsens_wait_setup ( "SH2+: open, SH2-: CAL2" );
        error_flag = mcurrentsens_read_ch2_voltage( ctx, &measured_1 );
    }
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        mcurrentsens_wait_setup ( "SH2+: 3V, SH2-: open" );
        error_flag = mcurrentsens_read_ch2_voltage( ctx, &measured_2 );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        mcurrentsens_calculate_calib( &ctx->ch2_volt_cal, MCURRENTSENS_CH2_VOLTAGE_COEFF, 
                                      MCURRENTSENS_VOLTAGE_TARGET_0_MV, measured_1, 
                                      MCURRENTSENS_VOLTAGE_TARGET_3000_MV, measured_2 );
    }

    /* ===================== CH2 CURRENT ===================== */
    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_read_ch2_current( ctx, &measured_1 );
    }
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        mcurrentsens_wait_setup ( "SH2+: 3V, SH2-: CAL2" );
        error_flag = mcurrentsens_read_ch2_current( ctx, &measured_2 );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        mcurrentsens_calculate_calib( &ctx->ch2_curr_cal, MCURRENTSENS_CH2_CURRENT_COEFF, 
                                      MCURRENTSENS_CURRENT_TARGET_0_MA, measured_1, 
                                      MCURRENTSENS_CURRENT_TARGET_10_MA, measured_2 );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_store_calib ( ctx );
    }
    log_printf( &logger, "-----------------------------\r\n" );
    return error_flag;
}

// ------------------------------------------------------------------------ END
