
---
# Ambient 3 Click

> [Ambient 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3686) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3686&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient3

### Example Key Functions

- `ambient3_cfg_setup` Config Object Initialization function. 
```c
void ambient3_cfg_setup ( ambient3_cfg_t *cfg );
``` 
 
- `ambient3_init` Initialization function. 
```c
err_t ambient3_init ( ambient3_t *ctx, ambient3_cfg_t *cfg );
```

- `ambient3_default_cfg` Click Default Configuration function. 
```c
void ambient3_default_cfg ( ambient3_t *ctx );
```

- `ambient3_get_device_temperature` This function reads device temperature. 
```c
uint8_t ambient3_get_device_temperature ( ambient3_t *ctx );
```

- `ambient3_get_data_in_LUX` This function reads data in LUX. 
```c
uint16_t ambient3_get_data_in_LUX ( ambient3_t *ctx );
```

- This function reads CCT data in K.
uint16_t ambient3_get_cct_data ( ambient3_t *ctx );

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient3_cfg_t cfg;

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

    ambient3_cfg_setup( &cfg );
    AMBIENT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient3_init( &ambient3, &cfg );
    ambient3_default_cfg( &ambient3 );
    Delay_ms ( 100 );
}
```

### Application Task

> Reads the device temperature, and daylight in LUX and logs results to USB UART each second.

```c
void application_task ( )
{
    temperature = ambient3_get_device_temperature( &ambient3 );
    log_printf( &logger, " - Device temperature in Celsius : %u\r\n", ( uint16_t ) temperature );

    data_lux = ambient3_get_data_in_lux( &ambient3 );
    log_printf( &logger, " - Light in LUX : %u\r\n", data_lux );
    log_printf( &logger, " --------------------\r\n" );
    
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
