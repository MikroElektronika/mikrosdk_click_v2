
---
# IrThermo 5V Click

> [IrThermo 5V Click](https://www.mikroe.com/?pid_product=MIKROE-1362) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1362&image=1" height=300px>
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
- Click.IrThermo5V

### Example Key Functions

- `irthermo5v_cfg_setup` Config Object Initialization function.
```c
void irthermo5v_cfg_setup ( irthermo5v_cfg_t *cfg );
```

- `irthermo5v_init` Initialization function.
```c
err_t irthermo5v_init ( irthermo5v_t *ctx, irthermo5v_cfg_t *cfg );
```

- `irthermo5v_get_t_ambient` Reads Temperature ambient from sensor.
```c
float irthermo5v_get_t_ambient ( irthermo5v_t* ctx );
```

- `irthermo5v_get_t_object` Reads Temperature object1 from sensor.
```c
float irthermo5v_get_t_object ( irthermo5v_t* ctx );
```

### Application Init

> Initializes IrThermo 5V Driver.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irthermo5v_cfg_t irthermo5v_cfg;  /**< Click config object. */

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
    irthermo5v_cfg_setup( &irthermo5v_cfg );
    IRTHERMO5V_MAP_MIKROBUS( irthermo5v_cfg, MIKROBUS_1 );
    err_t init_flag = irthermo5v_init( &irthermo5v, &irthermo5v_cfg );
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
    measured_temperature = irthermo5v_get_t_ambient( &irthermo5v );
    object_temperature = irthermo5v_get_t_object( &irthermo5v );
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
