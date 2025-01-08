
---
# Temp Log 4 Click

> [Temp-Log 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3329) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3329&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measures the temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog4

### Example Key Functions

- `templog4_cfg_setup` Config Object Initialization function. 
```c
void templog4_cfg_setup ( templog4_cfg_t *cfg );
``` 
 
- `templog4_init` Initialization function. 
```c
err_t templog4_init ( templog4_t *ctx, templog4_cfg_t *cfg );
```

- `templog4_default_cfg` Click Default Configuration function. 
```c
void templog4_default_cfg ( templog4_t *ctx );
```

- `templog4_write_reg` Generic Write function. 
```c
uint8_t templog4_write_reg ( templog4_t *ctx, uint8_t reg, uint16_t input_data );
```
 
- `templog4_read_reg` Generic Read function. 
```c
uint8_t templog4_read_reg ( templog4_t *ctx, uint8_t reg, uint16_t *out_var );
```

- `templog4_set_addr_ptr` Set Address Pointer function. 
```c
void templog4_set_addr_ptr ( templog4_t *ctx, uint8_t addr );
```

### Application Init

> Initializes I2C interface and performs a device configuration    for properly working. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    templog4_cfg_t cfg;

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

    templog4_cfg_setup( &cfg );
    TEMPLOG4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    templog4_init( &templog4, &cfg );
    templog4_default_cfg ( &templog4 );
}
```

### Application Task

> First ensures that the minimum conversion time is met, and then reads the ambient temperature calculated to the Celsius degrees.

```c
void application_task ( void )
{
    float temperature;

    wait_conversion_done( );

    ret_status = templog4_get_temp( &templog4, TEMPLOG4_TEMP_AMBIENT_REG, &temperature );

    log_printf( &logger, "** Ambient temperature: %f C **\r\n", temperature );

    check_limit_status( );

    log_printf( &logger, "\r\n", temperature );

    Delay_ms ( 300 );
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
