
---
# Thunder EMU Click

> [Thunder EMU Click](https://www.mikroe.com/?pid_product=MIKROE-5904) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5904&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Thunder EMU Click board by generating
CLOSE, MID, or FAR range thunder signal depending on the Click push-buttons state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ThunderEMU

### Example Key Functions

- `thunderemu_cfg_setup` Config Object Initialization function.
```c
void thunderemu_cfg_setup ( thunderemu_cfg_t *cfg );
```

- `thunderemu_init` Initialization function.
```c
err_t thunderemu_init ( thunderemu_t *ctx, thunderemu_cfg_t *cfg );
```

- `thunderemu_default_cfg` Click Default Configuration function.
```c
err_t thunderemu_default_cfg ( thunderemu_t *ctx );
```

- `thunderemu_generate_thunder` This function generates close, mid or far range thunder signal by setting the predefined DAC output profile at the specific timing.
```c
err_t thunderemu_generate_thunder ( thunderemu_t *ctx, uint8_t mode );
```

- `thunderemu_get_close_pin` This function returns the CLOSE pin logic state.
```c
uint8_t thunderemu_get_close_pin ( thunderemu_t *ctx );
```

- `thunderemu_get_mid_pin` This function returns the MID pin logic state.
```c
uint8_t thunderemu_get_mid_pin ( thunderemu_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thunderemu_cfg_t thunderemu_cfg;  /**< Click config object. */

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
    thunderemu_cfg_setup( &thunderemu_cfg );
    THUNDEREMU_MAP_MIKROBUS( thunderemu_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thunderemu_init( &thunderemu, &thunderemu_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THUNDEREMU_ERROR == thunderemu_default_cfg ( &thunderemu ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks if any of the Click board buttons are pressed and then generates a thunder
signal related to the pressed button and displays an appropriate message on the USB UART.

```c
void application_task ( void )
{
    if ( !thunderemu_get_close_pin ( &thunderemu ) )
    {
        if ( THUNDEREMU_OK == thunderemu_generate_thunder ( &thunderemu, THUNDEREMU_MODE_CLOSE ) )
        {
            log_printf( &logger, " Close range thunder signal generated!\r\n\n" );
            Delay_ms ( 500 );
        }
    }
    else if ( !thunderemu_get_mid_pin ( &thunderemu ) )
    {
        if ( THUNDEREMU_OK == thunderemu_generate_thunder ( &thunderemu, THUNDEREMU_MODE_MID ) )
        {
            log_printf( &logger, " Mid range thunder signal generated!\r\n\n" );
            Delay_ms ( 500 );
        }
    }
    else if ( !thunderemu_get_far_pin ( &thunderemu ) )
    {
        if ( THUNDEREMU_OK == thunderemu_generate_thunder ( &thunderemu, THUNDEREMU_MODE_FAR ) )
        {
            log_printf( &logger, " Far range thunder signal generated!\r\n\n" );
            Delay_ms ( 500 );
        }
    }
}
```

### Note

> Thunder EMU Click should be used in combination with a Thunder Click which detects
a lightning presence. The emulator is calibrated for ranges of up to 15cm from the sensor board.
It's recommended to distant both Click boards from their development boards using a Shuttle Click
to reduce the board noise that can affect the sensor and emulator performance.

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
