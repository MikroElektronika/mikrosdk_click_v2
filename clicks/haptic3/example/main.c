/*!
 * @file main.c
 * @brief Haptic 3 Click example
 *
 * # Description
 * This example demonstrates the use of the Haptic 3 Click board for
 * controlling an LRA actuator. Depending on the selected script, the
 * application either changes the vibration level or plays the available
 * predefined haptic sequences.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Haptic 3 Click driver, applies the default
 * configuration, and logs the actuator type supported by the selected script.
 *
 * ## Application Task
 * In generic mode, alternates between minimum and maximum vibration levels.
 * In script mode, reads the number of available sequences and plays each
 * sequence while waiting for playback completion.
 *
 * @note
 * Connect a supported LRA vibration motor to the Haptic 3 Click board output.
 * Select the desired operating mode by configuring the HAPTIC3_SCRIPT_SELECTOR
 * macro in the driver before building the example. The LRA2024A scripts are
 * optimized for the LRA2024A-1088F [MIKROE-6810] actuator, while the LRA0825BC
 * script is optimized for the LRA0825BC-0167F [MIKROE-6809] actuator.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "haptic3.h"

#ifndef MIKROBUS_POSITION_HAPTIC3
    #define MIKROBUS_POSITION_HAPTIC3 MIKROBUS_1
#endif

static haptic3_t haptic3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    haptic3_cfg_t haptic3_cfg;  /**< Click config object. */

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
    haptic3_cfg_setup( &haptic3_cfg );
    HAPTIC3_MAP_MIKROBUS( haptic3_cfg, MIKROBUS_POSITION_HAPTIC3 );
    if ( I2C_MASTER_ERROR == haptic3_init( &haptic3, &haptic3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HAPTIC3_ERROR == haptic3_default_cfg ( &haptic3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

#if ( HAPTIC3_SCRIPT_SELECTOR == HAPTIC3_SCRIPT_LRA2024A_SINE || \
      HAPTIC3_SCRIPT_SELECTOR == HAPTIC3_SCRIPT_LRA2024A_CLICK || \
      HAPTIC3_SCRIPT_SELECTOR == HAPTIC3_SCRIPT_LRA2024A_BUZZ )
    log_printf( &logger, " The selected script is optimized for LRA2024A-1088F [MIKROE-6810] actuator.\r\n" );
#elif ( HAPTIC3_SCRIPT_SELECTOR == HAPTIC3_SCRIPT_LRA0825BC )
    log_printf( &logger, " The selected script is optimized for LRA0825BC-0167F [MIKROE-6809] actuator.\r\n" );
#elif ( HAPTIC3_SCRIPT_SELECTOR == HAPTIC3_SCRIPT_GENERIC )
    log_printf( &logger, " No optimizations, the driver is configured to default settings for LRA actuators.\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#if ( HAPTIC3_SCRIPT_SELECTOR == HAPTIC3_SCRIPT_GENERIC )
    float vibration_level;
    if ( HAPTIC3_OK == haptic3_set_vibration_level ( &haptic3, HAPTIC3_VIBRATION_LEVEL_MAX ) )
    {
        if ( HAPTIC3_OK == haptic3_get_vibration_level ( &haptic3, &vibration_level ) )
        {
            log_printf( &logger, " Vibration level: %.3f \r\n\n", vibration_level );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( HAPTIC3_OK == haptic3_set_vibration_level ( &haptic3, HAPTIC3_VIBRATION_LEVEL_MIN ) )
    {
        if ( HAPTIC3_OK == haptic3_get_vibration_level ( &haptic3, &vibration_level ) )
        {
            log_printf( &logger, " Vibration level: %.3f \r\n\n", vibration_level );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    uint8_t num_seq = 0;
    // Read a number of sequences stored within the loaded script
    if ( HAPTIC3_OK == haptic3_read_register ( &haptic3, HAPTIC3_REG_SNP_MEM_1, &num_seq ) )
    {
        log_printf( &logger, " Number of sequences available: %u\r\n\n", ( uint16_t ) num_seq );
        for ( uint8_t seq = 0; seq < num_seq; seq++ )
        {
            // Start each sequence playback
            log_printf( &logger, " Starting playback of sequence %u\r\n", ( uint16_t ) seq );

            // The upper nibble [bits 7:4] of HAPTIC3_REG_SEQ_CTL2 register is the sequence repetition number
            // 0x0 = No repetition (sequence played once), 0xF = 15 repetitions (sequence played 16 times)
            haptic3_write_register ( &haptic3, HAPTIC3_REG_SEQ_CTL2, seq );
            haptic3_write_register ( &haptic3, HAPTIC3_REG_TOP_CTL1, HAPTIC3_TOP_CTL1_SEQ_START | 
                                                                     HAPTIC3_TOP_CTL1_OP_MODE_RTWM );
            
            // Wait for a playback complete event and clear it
            while ( haptic3_get_int_pin ( &haptic3 ) );

            log_printf( &logger, " Playback complete\r\n\n" );

            haptic3_clear_events ( &haptic3 );
            Delay_ms ( 1000 );
        }
    }
#endif
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
