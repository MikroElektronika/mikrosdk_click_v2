
---
# LED Driver 8 Click

> [LED Driver 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4268) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4268&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of LED Driver 8 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver8

### Example Key Functions

- `leddriver8_cfg_setup` Config Object Initialization function. 
```c
void leddriver8_cfg_setup ( leddriver8_cfg_t *cfg );
``` 
 
- `leddriver8_init` Initialization function. 
```c
err_t leddriver8_init ( leddriver8_t *ctx, leddriver8_cfg_t *cfg );
```

- `leddriver8_set_brightness` Function for set Brightness. 
```c
void leddriver8_set_brightness ( leddriver8_t *ctx, uint8_t num_led, uint8_t value );
```
 
- `leddriver8_set_output_gain` Function for set output gain. 
```c
void leddriver8_set_output_gain ( leddriver8_t *ctx, uint8_t num_led, uint8_t value );
```

- `leddriver8_set_mode_register` Function for set mode registers. 
```c
void leddriver8_set_mode_register ( leddriver8_t *ctx, uint8_t mode_1, uint8_t mode_2 );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver8_cfg_t cfg;

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

    leddriver8_cfg_setup( &cfg );
    LEDDRIVER8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver8_init( &leddriver8, &cfg );

    leddriver8_reset( &leddriver8 );
    Delay_ms ( 500 );
    
    leddriver8_output_enable_pin( &leddriver8, LEDDRIVER8_ENABLE_LED_OUTPUTS );
    leddriver8_set_output_gain( &leddriver8, LEDDRIVER8_OUTPUT_GAIN_ALL_LED, LEDDRIVER8_FULL_OUTPUT_CURRENT_GAIN );
    leddriver8_set_mode_register( &leddriver8, LEDDRIVER8_MODE1_NORMAL_MODE, LEDDRIVER8_MODE2_DMBLNK_DIMMING |
                                  LEDDRIVER8_MODE2_CLRERR_ALL | LEDDRIVER8_MODE2_EXP_DISABLE );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 500 );
}
```

### Application Task

> Increases the LEDs brightness then toggles all LEDs with a one-second delay.
> Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    uint16_t cnt;

    log_printf( &logger, "Increasing LEDs brightness...\r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    for ( cnt = LEDDRIVER8_MIN_BRIGHTNESS; cnt <= LEDDRIVER8_MAX_BRIGHTNESS; cnt++ )
    {
        leddriver8_set_brightness( &leddriver8, LEDDRIVER8_BRIGHTNESS_ALL_LED, cnt );
        Delay_ms ( 20 );
    }
    
    log_printf( &logger, "Toggling all LEDs...\r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    for ( cnt = 0; cnt < 5; cnt++ )
    {
       leddriver8_set_brightness( &leddriver8, LEDDRIVER8_BRIGHTNESS_ALL_LED, LEDDRIVER8_MAX_BRIGHTNESS );
       Delay_ms ( 1000 );
       leddriver8_set_brightness( &leddriver8, LEDDRIVER8_BRIGHTNESS_ALL_LED, LEDDRIVER8_MIN_BRIGHTNESS );
       Delay_ms ( 1000 );
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
