
---
# Rotary W 2 Click

> [Rotary W 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5892) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5892&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains the API for the Rotary W 2 Click driver 
> to control LEDs states and a rotary encoder position readings.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RotaryW2

### Example Key Functions

- `rotaryw2_cfg_setup` Config Object Initialization function.
```c
void rotaryw2_cfg_setup ( rotaryw2_cfg_t *cfg );
```

- `rotaryw2_init` Initialization function.
```c
err_t rotaryw2_init ( rotaryw2_t *ctx, rotaryw2_cfg_t *cfg );
```

- `rotaryw2_default_cfg` Click Default Configuration function.
```c
err_t rotaryw2_default_cfg ( rotaryw2_t *ctx );
```

- `rotaryw2_set_led_pos` Rotary W 2 set LED position function.
```c
err_t rotaryw2_set_led_pos ( rotaryw2_t *ctx, uint8_t led_pos );
```

- `rotaryw2_set_led_data` Rotary W 2 set LED data function.
```c
err_t rotaryw2_set_led_data ( rotaryw2_t *ctx, uint16_t data_in );
```

- `rotaryw2_get_state_switch` Rotary W 2 get switch state function.
```c
uint8_t rotaryw2_get_state_switch ( rotaryw2_t *ctx );
```

### Application Init

> Initialization of SPI module and log UART.
> After the driver init, the app executes a default configuration and turn off all LEDs.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryw2_cfg_t rotaryw2_cfg;  /**< Click config object. */

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
    rotaryw2_cfg_setup( &rotaryw2_cfg );
    ROTARYW2_MAP_MIKROBUS( rotaryw2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == rotaryw2_init( &rotaryw2, &rotaryw2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ROTARYW2_ERROR == rotaryw2_default_cfg ( &rotaryw2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Rotary W 2 Click board&trade;.
> The demo example shows the functionality of a rotary encoder used to control LEDs.

```c
void application_task ( void )
{
    if ( ROTARYW2_OK == rotaryw2_set_led_data( &rotaryw2, led_data ) )
    {
        rotaryw2_switch_detection( );
        rotaryw2_encoder_mechanism( );
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
