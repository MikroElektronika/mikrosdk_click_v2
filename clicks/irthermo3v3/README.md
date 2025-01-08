
---
# IrThermo 3V3 Click

> [IrThermo 3V3 Click](https://www.mikroe.com/?pid_product=MIKROE-1361) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1361&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This application collects data from the sensor, and logs the results.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrThermo3V3

### Example Key Functions

- `irthermo3v3_cfg_setup` Config Object Initialization function.
```c
void irthermo3v3_cfg_setup ( irthermo3v3_cfg_t *cfg );
```

- `irthermo3v3_init` Initialization function.
```c
err_t irthermo3v3_init ( irthermo3v3_t *ctx, irthermo3v3_cfg_t *cfg );
```

- `irthermo3v3_get_t_ambient` Reads Temperature ambient from sensor.
```c
float irthermo3v3_get_t_ambient ( irthermo3v3_t* ctx );
```

- `irthermo3v3_get_t_object` Reads Temperature object1 from sensor.
```c
float irthermo3v3_get_t_object ( irthermo3v3_t* ctx );
```

### Application Init

> Initializes IrThermo 3V3 Driver.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irthermo3v3_cfg_t irthermo3v3_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init \r\n " );
    log_printf( &logger, "--------------------------------\r\n " );

    // Click initialization.
    irthermo3v3_cfg_setup( &irthermo3v3_cfg );
    IRTHERMO3V3_MAP_MIKROBUS( irthermo3v3_cfg, MIKROBUS_1 );
    err_t init_flag = irthermo3v3_init( &irthermo3v3, &irthermo3v3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task \r\n" );
    log_printf( &logger, " --------------------------------\r\n " );
}
```

### Application Task

> Reading Ambient and Object Temperature and displaying the value periodically.

```c
void application_task ( void ) 
{
    measured_temperature = irthermo3v3_get_t_ambient( &irthermo3v3 );
    object_temperature = irthermo3v3_get_t_object( &irthermo3v3 );
    log_printf( &logger, " Ambient Temperature: %.2f\r\n ", measured_temperature );
    log_printf( &logger, " Object Temperature: %.2f\r\n ", object_temperature );
    log_printf( &logger, " --------------------------------\r\n " );
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
