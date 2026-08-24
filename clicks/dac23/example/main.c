/*!
 * @file main.c
 * @brief DAC 23 Click example
 *
 * # Description
 * This example demonstrates the use of the DAC 23 Click board by
 * configuring all four DAC output channels and verifying their output
 * voltages through the integrated analog multiplexer and ADC. The
 * application also monitors the output current of each channel.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger, configures the DAC 23 Click board, and applies
 * the default device configuration.
 *
 * ## Application Task
 * Cycles the output voltage of all four DAC channels across the full
 * 0 V to 2.5 V output range, measures each output voltage using the
 * internal analog multiplexer and ADC, then measures and logs the
 * corresponding output current for every channel.
 *
 * @author Stefan Filipovic
 *
 */
#include "board.h"
#include "log.h"
#include "dac23.h"

#ifndef MIKROBUS_POSITION_DAC23
    #define MIKROBUS_POSITION_DAC23 MIKROBUS_1
#endif

// The number of steps by which we will divide the entire voltage range. 
#define NUMBER_OF_STEPS 10

static dac23_t dac23;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac23_cfg_t dac23_cfg;  /**< Click config object. */

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
    dac23_cfg_setup( &dac23_cfg );
    DAC23_MAP_MIKROBUS( dac23_cfg, MIKROBUS_POSITION_DAC23 );
    if ( SPI_MASTER_ERROR == dac23_init( &dac23, &dac23_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC23_ERROR == dac23_default_cfg ( &dac23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static float step = DAC23_VFS_OUT_RANGE_0_TO_2_5V / NUMBER_OF_STEPS;
    static float out_voltage = DAC23_VFS_OUT_RANGE_0_TO_2_5V / NUMBER_OF_STEPS;
    float mux_voltage = 0;
    for ( uint8_t channel = DAC23_CHANNEL_0; channel <= DAC23_CHANNEL_3; channel++ )
    {
        if ( ( DAC23_OK == dac23_set_mux_sel ( &dac23, DAC23_MUX_SEL_VOUT0 + 
                                                       channel * ( DAC23_MUX_SEL_VOUT1 - 
                                                                   DAC23_MUX_SEL_VOUT0 ) ) ) && 
             ( DAC23_OK == dac23_set_out_voltage ( &dac23, channel, out_voltage ) ) )
        {
            log_printf ( &logger, " VOUT%u set: %.3f V\r\n", ( uint16_t ) channel, out_voltage );
            if ( DAC23_OK == dac23_read_voltage_avg ( &dac23, DAC23_NUM_CONVERSIONS, &mux_voltage ) ) 
            {
                log_printf ( &logger, " VOUT%u read: %.3f V\r\n", ( uint16_t ) channel, mux_voltage );
            }
        }
        if ( DAC23_OK == dac23_set_mux_sel ( &dac23, DAC23_MUX_SEL_IOUT0_SOURCE + 
                                                     channel * ( DAC23_MUX_SEL_IOUT1_SOURCE - 
                                                                 DAC23_MUX_SEL_IOUT0_SOURCE ) ) )
        {
            if ( DAC23_OK == dac23_read_voltage_avg ( &dac23, DAC23_NUM_CONVERSIONS, &mux_voltage ) ) 
            {
                log_printf ( &logger, " IOUT%u read: %.1f mA\r\n\n", 
                             ( uint16_t ) channel, mux_voltage * DAC23_MUX_CURRENT_RESOLUTION_MA );
            }
        }
    }
    out_voltage += step;
    if ( ( out_voltage > DAC23_VFS_OUT_RANGE_0_TO_2_5V ) || 
         ( out_voltage < DAC23_VZS_OUT_RANGE_0_TO_2_5V ) )
    {
        step = -step;
        out_voltage += step;
        out_voltage += step;
    }
    Delay_ms ( 1000 ); 
    Delay_ms ( 1000 );
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

// ------------------------------------------------------------------------ END
