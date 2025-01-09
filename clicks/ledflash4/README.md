
---
# LED Flash 4 Click

> [LED Flash 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6282) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6282&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of LED Flash 4 Click board by toggling the LEDs output.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDFlash4

### Example Key Functions

- `ledflash4_cfg_setup` Config Object Initialization function.
```c
void ledflash4_cfg_setup ( ledflash4_cfg_t *cfg );
```

- `ledflash4_init` Initialization function.
```c
err_t ledflash4_init ( ledflash4_t *ctx, ledflash4_cfg_t *cfg );
```

- `ledflash4_default_cfg` Click Default Configuration function.
```c
err_t ledflash4_default_cfg ( ledflash4_t *ctx );
```

- `ledflash4_set_led1_current` This function sets the LED1 maximum current in mA.
```c
err_t ledflash4_set_led1_current ( ledflash4_t *ctx, uint16_t led_current );
```

- `ledflash4_set_led2_current` This function sets the LED2 maximum current in mA.
```c
err_t ledflash4_set_led2_current ( ledflash4_t *ctx, uint16_t led_current );
```

- `ledflash4_set_stb_pin` This function sets the strobe (STB) pin logic state.
```c
void ledflash4_set_stb_pin ( ledflash4_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets
the Click in flash mode with the LED current of 50mA for both LEDs. The strobe pin is set to active high level type.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ledflash4_cfg_t ledflash4_cfg;  /**< Click config object. */

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
    ledflash4_cfg_setup( &ledflash4_cfg );
    LEDFLASH4_MAP_MIKROBUS( ledflash4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ledflash4_init( &ledflash4, &ledflash4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDFLASH4_ERROR == ledflash4_default_cfg ( &ledflash4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Toggles the LEDs output every 2 seconds using the strobe pin, and displays the LEDs state on the USB UART.

```c
void application_task ( void )
{
    log_printf( &logger, " LEDs ON\r\n\n" );
    ledflash4_set_stb_pin ( &ledflash4, LEDFLASH4_STROBE_PIN_HIGH );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " LEDs OFF\r\n\n" );
    ledflash4_set_stb_pin ( &ledflash4, LEDFLASH4_STROBE_PIN_LOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
