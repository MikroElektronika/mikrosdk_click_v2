
---
# Balancer 2 Click

> [Balancer 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4058) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4058&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application enable the batery charge. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Balancer2

### Example Key Functions

- `balancer2_cfg_setup` Config Object Initialization function. 
```c
void balancer2_cfg_setup ( balancer2_cfg_t *cfg );
``` 
 
- `balancer2_init` Initialization function. 
```c
err_t balancer2_init ( balancer2_t *ctx, balancer2_cfg_t *cfg );
```

- `balancer2_default_cfg` Click Default Configuration function. 
```c
void balancer2_default_cfg ( balancer2_t *ctx );
```

- `balancer2_get_batttery_lvl` Function for getting real battery lvl. 
```c
float balancer2_get_batttery_lvl ( balancer2_t *ctx, uint8_t bat_num );
```
 
- `balancer2_adc_to_mv` Function for converting adc value to mV. 
```c
float balancer2_adc_to_mv ( balancer2_t *ctx, uint16_t adc_val );
```

- `balancer2_read_adc` Function for reading adc value. 
```c
uint16_t balancer2_read_adc ( balancer2_t *ctx, uint8_t cmd_byte );
```

### Application Init

> Sets reference volatage of device, sets pins for supply and cells to high.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    balancer2_cfg_t cfg;

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

    balancer2_cfg_setup( &cfg );
    BALANCER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    balancer2_init( &balancer2, &cfg );

    Delay_ms ( 100 );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "  Balancer 2 Click  \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 100 );
    balancer2_default_cfg ( &balancer2 );
    Delay_ms ( 100 );
}
```

### Application Task

> Every 2 seconds logs readings of battery mV lvl

```c
void application_task ( void )
{
    float battery;

    battery = balancer2_get_batttery_lvl( &balancer2, BALANCER2_BATT1 );
    log_printf( &logger, "Battery 1 : %f mV\r\n", battery );

    battery = balancer2_get_batttery_lvl( &balancer2, BALANCER2_BATT2 );
    log_printf( &logger, "Battery 2 : %f mV\r\n", battery );

    battery = balancer2_get_batttery_lvl( &balancer2, BALANCER2_BATT_BOTH );
    log_printf( &logger, "Batteries : %f mV\r\n", battery );

    log_printf( &logger, "__________________________________________\r\n" );

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
