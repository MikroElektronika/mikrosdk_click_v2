
---
# LightRanger Click

> [LightRanger Click](https://www.mikroe.com/?pid_product=MIKROE-1897) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1897&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example collects data from the sensor and logs it to the terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger

### Example Key Functions

- `lightranger_cfg_setup` Config Object Initialization function. 
```c
void lightranger_cfg_setup ( lightranger_cfg_t *cfg );
``` 
 
- `lightranger_init` Initialization function. 
```c
err_t lightranger_init ( lightranger_t *ctx, lightranger_cfg_t *cfg );
```

- `lightranger_write_byte` This function writes a byte of data to given address. 
```c
void lightranger_write_byte ( lightranger_t* ctx, uint16_t reg_addr, uint8_t write_command );
```
 
- `lightranger_get_ambiant_light` This function reads register and calculates the light level in lux. 
```c
float lightranger_get_ambiant_light ( lightranger_t* ctx, uint16_t als_gain_check );
```

- `lightranger_get_distance` This function reads range result from register. 
```c
uint16_t lightranger_get_distance ( lightranger_t* ctx );
```

### Application Init

> Initialization driver for sensor Vl6180X and stars logging to terminal.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lightranger_cfg_t cfg;

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

    lightranger_cfg_setup( &cfg );
    LIGHTRANGER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightranger_init( &lightranger, &cfg );
    
    lightranger_default_cfg( &lightranger );
    Delay_ms ( 1000 );
}
```

### Application Task

> Measures and calculates ambient light intensity and distance from sensor,
> when the distance is changed log is updated,
> results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for approximately every 1 sec when the data value changes.

```c
void application_task ( void )
{
    uint8_t range_value;
    float lux_value;
    
    lightranger_start_single_shot_range_mode( &lightranger );
    
    lightranger_poll_range( &lightranger );
    lightranger_interrupts_clear( &lightranger );
    
    range_value = lightranger_get_distance( &lightranger );
    log_printf( &logger, "Proximity : %u mm\r\n", ( uint16_t ) range_value );

    lux_value = lightranger_get_ambiant_light( &lightranger, LIGHTRANGER_CMD_GAIN_1X );
    log_printf( &logger, "Ambient Light: %.2f lux\r\n", lux_value );

    log_printf( &logger, "*******************************************\r\n" );
    Delay_ms ( 500 );
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
