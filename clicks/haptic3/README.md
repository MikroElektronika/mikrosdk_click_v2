
---
# Haptic 3 Click

> [Haptic 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5087) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5087&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Haptic 3 Click board for
controlling an LRA actuator. Depending on the selected script, the
application either changes the vibration level or plays the available
predefined haptic sequences.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Haptic3

### Example Key Functions

- `haptic3_cfg_setup` Config Object Initialization function.
```c
void haptic3_cfg_setup ( haptic3_cfg_t *cfg );
```

- `haptic3_init` Initialization function.
```c
err_t haptic3_init ( haptic3_t *ctx, haptic3_cfg_t *cfg );
```

- `haptic3_default_cfg` Click Default Configuration function.
```c
err_t haptic3_default_cfg ( haptic3_t *ctx );
```

- `haptic3_set_vibration_level` This function sets the motor vibration level.
```c
err_t haptic3_set_vibration_level ( haptic3_t *ctx, float level );
```

- `haptic3_get_vibration_level` This function reads the motor vibration level.
```c
err_t haptic3_get_vibration_level ( haptic3_t *ctx, float *level );
```

- `haptic3_write_register` This function writes a desired data to the selected register by using I2C serial interface.
```c
err_t haptic3_write_register ( haptic3_t *ctx, uint8_t reg, uint8_t data_in );
```

### Application Init

> Initializes the logger and Haptic 3 Click driver, applies the default
configuration, and logs the actuator type supported by the selected script.

```c
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
```

### Application Task

> In generic mode, alternates between minimum and maximum vibration levels.
In script mode, reads the number of available sequences and plays each
sequence while waiting for playback completion.

```c
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
```

### Note

> Connect a supported LRA vibration motor to the Haptic 3 Click board output.
Select the desired operating mode by configuring the HAPTIC3_SCRIPT_SELECTOR
macro in the driver before building the example. The LRA2024A scripts are
optimized for the LRA2024A-1088F [MIKROE-6810] actuator, while the LRA0825BC
script is optimized for the LRA0825BC-0167F [MIKROE-6809] actuator.

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
