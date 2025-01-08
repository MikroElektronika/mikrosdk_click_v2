
---
# 2x2 RGB Click

> [2x2 RGB Click](https://www.mikroe.com/?pid_product=MIKROE-5917) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5917&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mikroe Team
- **Date**          : Sep 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the 2x2 RGB Click board&trade; 
> by controlling the color of the LEDs [1-4].

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.2x2RGB

### Example Key Functions

- `c2x2rgb_cfg_setup` Config Object Initialization function.
```c
void c2x2rgb_cfg_setup ( c2x2rgb_cfg_t *cfg );
```

- `c2x2rgb_init` Initialization function.
```c
err_t c2x2rgb_init ( c2x2rgb_t *ctx, c2x2rgb_cfg_t *cfg );
```

- `c2x2rgb_default_cfg` Click Default Configuration function.
```c
err_t c2x2rgb_default_cfg ( c2x2rgb_t *ctx );
```

- `c2x2rgb_set_rgb_led` 2x2 RGB set RGB LED function.
```c
err_t c2x2rgb_set_rgb_led ( c2x2rgb_t *ctx, uint8_t led_num, uint16_t ired, uint16_t igrn, uint16_t iblu );
```

- `c2x2rgb_set_control` 2x2 RGB set control function.
```c
err_t c2x2rgb_set_control ( c2x2rgb_t *ctx, uint8_t en_mode, uint8_t be_en, 
                                            uint8_t ce_temp, uint8_t fade_rate );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c2x2rgb_cfg_t c2x2rgb_cfg;  /**< Click config object. */

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
    c2x2rgb_cfg_setup( &c2x2rgb_cfg );
    C2X2RGB_MAP_MIKROBUS( c2x2rgb_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c2x2rgb_init( &c2x2rgb, &c2x2rgb_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C2X2RGB_ERROR == c2x2rgb_default_cfg ( &c2x2rgb ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------" );
    Delay_ms ( 100 );
}
```

### Application Task

> This simple example shows all LEDs in different colors.
> These LEDs actually consist of three single-colored LEDs (Red, Green and Blue) in a single package. 
> Various colors can be reproduced by mixing the intensity of each LED.

```c
void application_task ( void ) 
{
    log_printf( &logger, "\r\nRED: " );
    for ( uint8_t led_pos = C2X2RGB_SET_LD1; led_pos <= C2X2RGB_SET_LD4; led_pos++ )
    {
        if ( C2X2RGB_OK == c2x2rgb_set_rgb_led( &c2x2rgb, led_pos, DEMO_LED_CURRENT,
                                                                   C2X2RGB_LED_CURRENT_OFF, 
                                                                   C2X2RGB_LED_CURRENT_OFF ) )
        {
            log_printf( &logger, "LD%d ", ( uint16_t ) led_pos );
        }
        Delay_ms ( 200 );
    }
    
    log_printf( &logger, "\r\nGREEN: " );
    for ( uint8_t led_pos = C2X2RGB_SET_LD1; led_pos <= C2X2RGB_SET_LD4; led_pos++ )
    {
        if ( C2X2RGB_OK == c2x2rgb_set_rgb_led( &c2x2rgb, led_pos, C2X2RGB_LED_CURRENT_OFF, 
                                                                   DEMO_LED_CURRENT, 
                                                                   C2X2RGB_LED_CURRENT_OFF ) )
        {
            log_printf( &logger, "LD%d ", ( uint16_t ) led_pos );
        }
        Delay_ms ( 200 );
    }
    
    log_printf( &logger, "\r\nBLUE: " );
    for ( uint8_t led_pos = C2X2RGB_SET_LD1; led_pos <= C2X2RGB_SET_LD4; led_pos++ )
    {
        if ( C2X2RGB_OK == c2x2rgb_set_rgb_led( &c2x2rgb, led_pos, C2X2RGB_LED_CURRENT_OFF, 
                                                                   C2X2RGB_LED_CURRENT_OFF, 
                                                                   DEMO_LED_CURRENT ) )
        {
            log_printf( &logger, "LD%d ", ( uint16_t ) led_pos );
        }
        Delay_ms ( 200 );
    }
    
    log_printf( &logger, "\r\nWHITE: " );
    for ( uint8_t led_pos = C2X2RGB_SET_LD1; led_pos <= C2X2RGB_SET_LD4; led_pos++ )
    {
        if ( C2X2RGB_OK == c2x2rgb_set_rgb_led( &c2x2rgb, led_pos, DEMO_LED_CURRENT, 
                                                                   DEMO_LED_CURRENT, 
                                                                   DEMO_LED_CURRENT ) )
        {
            log_printf( &logger, "LD%d ", ( uint16_t ) led_pos );
        }
        Delay_ms ( 200 );
    }
    log_printf( &logger, "\r\n----------------" );
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
