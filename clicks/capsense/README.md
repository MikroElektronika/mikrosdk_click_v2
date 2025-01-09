
---
# CapSense Click

> [CapSense Click](https://www.mikroe.com/?pid_product=MIKROE-1446) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1446&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example waits user to press top and bottom button to turn Click's LEDs ON or OFF.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CapSense

### Example Key Functions

- `capsense_cfg_setup` Config Object Initialization function.
```c
void capsense_cfg_setup ( capsense_cfg_t *cfg ); 
```
 
- `capsense_init` Initialization function.
```c
err_t capsense_init ( capsense_t *ctx, capsense_cfg_t *cfg );
```

- `capsense_default_cfg` Click Default Configuration function.
```c
err_t capsense_default_cfg ( capsense_t *ctx );
```

- `capsense_get_slider_lvl` This function gets slider level.
```c
err_t capsense_get_slider_lvl( capsense_t *ctx, uint8_t *slider_lvl );
```

- `capsense_read_data` Read one byte from register address
```c
err_t capsense_read_data( capsense_t *ctx, uint8_t reg_address, uint8_t *read_data );
```

- `capsense_write_data` Generic write data function
```c
err_t capsense_write_data( capsense_t *ctx, uint8_t reg_address, uint8_t write_command );
```

### Application Init

> Initialize CapSense Click and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    capsense_cfg_t cfg;

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
    capsense_cfg_setup( &cfg );
    CAPSENSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capsense_init( &capsense, &cfg );
    
    if ( CAPSENSE_ERROR == capsense_default_cfg ( &capsense ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Press top and bottom button and turn it ON or OFF button LED's.

```c
void application_task ( void )
{
    static uint8_t current_led_state = 0;
    uint8_t output_lvl[ 10 ] = { 0 };
    uint8_t button_select = 0;
    uint8_t slider_lvl = 0;
    capsense_read_data( &capsense, CAPSENSE_CS_READ_STATUS0, &button_select );
    capsense_get_slider_lvl( &capsense, &slider_lvl );
    capsense_write_data( &capsense, CAPSENSE_OUTPUT_PORT0, current_led_state );
    Delay_ms ( 100 );

    if ( 8 == button_select )
    {
        current_led_state ^= 0x01;
        log_printf( &logger, "Toggle LED1\r\n");
        Delay_ms ( 100 );
    }
    if ( 16 == button_select )
    {
        current_led_state ^= 0x02;
        log_printf( &logger, "Toggle LED2\r\n");
        Delay_ms ( 100 );
    }
    if ( 24 == button_select )
    {
        current_led_state = ~current_led_state;
        log_printf( &logger, "Toggle both LEDs\r\n");
        Delay_ms ( 100 );
    }

    if ( slider_lvl )
    {
        bits_to_str( slider_lvl, output_lvl );
        log_printf( &logger, "Slider level - channels [5-1]:\t%s \r\n", &output_lvl[ 3 ] );
        Delay_ms ( 100 );
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
