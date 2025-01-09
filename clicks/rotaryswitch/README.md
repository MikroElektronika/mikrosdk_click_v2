
---
# Rotary Switch Click

> [Rotary Switch Click](https://www.mikroe.com/?pid_product=MIKROE-6332) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6332&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Rotary Switch Click board by reading and displaying the switch position on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RotarySwitch

### Example Key Functions

- `rotaryswitch_cfg_setup` Config Object Initialization function.
```c
void rotaryswitch_cfg_setup ( rotaryswitch_cfg_t *cfg );
```

- `rotaryswitch_init` Initialization function.
```c
err_t rotaryswitch_init ( rotaryswitch_t *ctx, rotaryswitch_cfg_t *cfg );
```

- `rotaryswitch_default_cfg` Click Default Configuration function.
```c
err_t rotaryswitch_default_cfg ( rotaryswitch_t *ctx );
```

- `rotaryswitch_get_position` This function reads the rotary switch position.
```c
err_t rotaryswitch_get_position ( rotaryswitch_t *ctx, uint8_t *position );
```

- `rotaryswitch_write_reg` This function writes a desired data to the selected register by using I2C serial interface.
```c
err_t rotaryswitch_write_reg ( rotaryswitch_t *ctx, uint8_t reg, uint8_t data_in );
```

- `rotaryswitch_read_reg` This function reads data from the selected register by using I2C serial interface.
```c
err_t rotaryswitch_read_reg ( rotaryswitch_t *ctx, uint8_t reg, uint8_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryswitch_cfg_t rotaryswitch_cfg;  /**< Click config object. */

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
    rotaryswitch_cfg_setup( &rotaryswitch_cfg );
    ROTARYSWITCH_MAP_MIKROBUS( rotaryswitch_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rotaryswitch_init( &rotaryswitch, &rotaryswitch_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ROTARYSWITCH_ERROR == rotaryswitch_default_cfg ( &rotaryswitch ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the switch position every 20ms and displays it on the USB UART on position change.

```c
void application_task ( void )
{
    static uint8_t old_position = 0xFF;
    uint8_t position = 0;
    if ( ( ROTARYSWITCH_OK == rotaryswitch_get_position ( &rotaryswitch, &position ) ) && 
         ( position != old_position ) )
    {
        Delay_ms ( 20 );
        // Double-check for debouncing
        if ( ( ROTARYSWITCH_OK == rotaryswitch_get_position ( &rotaryswitch, &position ) ) && 
             ( position != old_position ) )
        {
            old_position = position;
            log_printf ( &logger, " Switch position: %.1X\r\n", ( uint16_t ) position );
        }
    }
    Delay_ms ( 20 );
}
```

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
