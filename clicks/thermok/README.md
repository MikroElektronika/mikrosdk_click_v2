
---
# Thermo K Click

> [Thermo K Click](https://www.mikroe.com/?pid_product=MIKROE-2501) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2501&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Demo application shows basic temperature reading using Thermo K Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ThermoK

### Example Key Functions

- `thermok_cfg_setup` Config Object Initialization function. 
```c
void thermok_cfg_setup ( thermok_cfg_t *cfg );
``` 
 
- `thermok_init` Initialization function. 
```c
err_t thermok_init ( thermok_t *ctx, thermok_cfg_t *cfg );
```

- `thermok_get_temperature` Temperature data. 
```c
float thermok_get_temperature ( thermok_t *ctx, uint8_t reg, uint8_t temp_format );
```
 
- `thermok_get_status` Get status. 
```c
void thermok_get_status ( thermok_t *ctx, thermok_alert_t *status );
```

- `thermok_get_device_info` Functions for read device info. 
```c
uint16_t thermok_get_device_info ( thermok_t *ctx );
```

### Application Init

> Configuring Clicks and log objects.
> Reads the device ID and also checks the Click and MCU communication.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermok_cfg_t cfg;

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

    thermok_cfg_setup( &cfg );
    THERMOK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermok_init( &thermok, &cfg );

    // Check communication and reads device ID

    device_info = thermok_get_device_info( &thermok );

    if ( ( device_info >> 8 ) == THERMOK_DEVICE_ID )
    {
        log_info(&logger, "---- Communication OK!!! ----" );
    }
    else
    {
        log_info(&logger, "---- Communication ERROR!!! ----" );
        for ( ; ; );
    }
    Delay_1sec( );
}
```

### Application Task

> Reads Temperature data(Type K probe) and this data logs to USBUART every 500ms.

```c
void application_task ( void )
{
    float temperature;

    //  Task implementation.

    temperature = thermok_get_temperature( &thermok, 
                                           THERMOK_REG_HOT_JUNCTION_TEMP_THR, 
                                           THERMOK_TEMP_IN_CELSIUS );
    log_printf( &logger, ">> Temperature is %.2f C\r\n", temperature );

    Delay_ms ( 1000 );
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
