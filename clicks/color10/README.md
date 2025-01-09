
---
# Color 10 Click

> [Color 10 Click](https://www.mikroe.com/?pid_product=MIKROE-3997) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3997&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> Color 10 Click is carrying a sensor for RGB and IR light sensing as well as 
> the RGB diode incorporated on the board which makes it good color detection 
> device when its combined with a white LED. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color10

### Example Key Functions

- `color10_cfg_setup` Config Object Initialization function. 
```c
void color10_cfg_setup ( color10_cfg_t *cfg );
``` 
 
- `color10_init` Initialization function. 
```c
err_t color10_init ( color10_t *ctx, color10_cfg_t *cfg );
```

- `color10_generic_read` This function reads data from the desired register. 
```c
uint16_t color10_generic_read ( color10_t *ctx, uint8_t cmd_addr );
```

- `color10_get_color_value` This function calculates the color value. 
```c
float color10_get_color_value ( color10_t *ctx );
```

- `color10_get_color` This function identifies the color using the color value. 
```c
uint8_t color10_get_color ( float color_value );
```

### Application Init

> Initialize I2C driver

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    color10_cfg_t cfg;
    uint8_t id_data;

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

    color10_cfg_setup( &cfg );
    COLOR10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color10_init( &color10, &cfg );
    Delay_ms ( 500 );

    if ( color10_get_id( &color10 ) == COLOR10_DEVICE_ID )
    {
         log_printf( &logger, " -DEVICE ID OK\r\n" );
    }
    else
    {
        log_printf( &logger, " -DEVICE ID ERROR\r\n" );
        for( ; ; );
    }

    color10_config( &color10, COLOR10_CFG_HIGH_DYNAMIC_RANGE_1 |
                    COLOR10_CFG_INTEGRATION_TIME_SETT_50_MS |
                    COLOR10_CFG_AUTO_MODE |
                    COLOR10_CFG_TRIGGER_NO |
                    COLOR10_CFG_POWER_ON |
                    COLOR10_CFG_GAIN_1_X1 |
                    COLOR10_CFG_GAIN_2_X1 );
    log_printf( &logger, "-----Init done------\r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

> This example senses orange, red, pink, purple, blue, cyan, green or yellow color
> and IR light and print it via UART terminal. 

```c
void application_task ( void )
{
    uint16_t read_data;
    float color_data;

    read_data = color10_generic_read ( &color10, COLOR10_CMD_REG_IR );
    log_printf( &logger, " -IR value: %d\r\n", read_data );
    log_printf( &logger, " -Color: " );
    write_color( );

    log_printf( &logger, " ********************** \r\n" );
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
