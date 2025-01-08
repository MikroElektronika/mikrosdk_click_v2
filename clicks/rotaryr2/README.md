
---
# Rotary R 2 Click

> [Rotary R 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5975) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5975&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains the API for the Rotary R 2 Click driver 
> to control LEDs states and a rotary encoder position readings.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RotaryR2

### Example Key Functions

- `rotaryr2_cfg_setup` Config Object Initialization function.
```c
void rotaryr2_cfg_setup ( rotaryr2_cfg_t *cfg );
```

- `rotaryr2_init` Initialization function.
```c
err_t rotaryr2_init ( rotaryr2_t *ctx, rotaryr2_cfg_t *cfg );
```

- `rotaryr2_default_cfg` Click Default Configuration function.
```c
err_t rotaryr2_default_cfg ( rotaryr2_t *ctx );
```

- `rotaryr2_set_led_pos` This function turns on the LED for the selected LED position.
```c
err_t rotaryr2_set_led_pos ( rotaryr2_t *ctx, uint8_t led_pos );
```

- `rotaryr2_set_led_data` This function, using SPI serial interface, writes a desired 16-bit data.
```c
err_t rotaryr2_set_led_data ( rotaryr2_t *ctx, uint16_t data_in );
```

- `rotaryr2_get_state_switch` This function return rotary encoder switch signal, states of the SW(INT).
```c
uint8_t rotaryr2_get_state_switch ( rotaryr2_t *ctx );
```

### Application Init

> Initialization of SPI module and log UART.
> After the driver init, the app executes a default configuration and turn off all LEDs.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryr2_cfg_t rotaryr2_cfg;  /**< Click config object. */

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
    rotaryr2_cfg_setup( &rotaryr2_cfg );
    ROTARYR2_MAP_MIKROBUS( rotaryr2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == rotaryr2_init( &rotaryr2, &rotaryr2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ROTARYR2_ERROR == rotaryr2_default_cfg ( &rotaryr2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Rotary R 2 Click board&trade;.
> The demo example shows the functionality of a rotary encoder used to control LEDs.

```c
void application_task ( void )
{
    if ( ROTARYR2_OK == rotaryr2_set_led_data( &rotaryr2, led_data ) )
    {
        rotaryr2_switch_detection( );
        rotaryr2_encoder_mechanism( );
    }
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
