
---
# THERMO Click

> [THERMO Click](https://www.mikroe.com/?pid_product=MIKROE-1197) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1197&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example measures temperature and then logs the results.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo

### Example Key Functions

- `thermo_cfg_setup` Config Object Initialization function. 
```c
void thermo_cfg_setup ( thermo_cfg_t *cfg );
``` 
 
- `thermo_init` Initialization function. 
```c
err_t thermo_init ( thermo_t *ctx, thermo_cfg_t *cfg );
```

- `thermo_get_temperature` Function gets thermocouple temperature data. 
```c
float thermo_get_temperature ( thermo_t* ctx );
```
 
- `thermo_check_fault` Function checks fault states of MAX31855 sensor on Thermo Click board. 
```c
uint8_t thermo_check_fault ( thermo_t* ctx );
```

- `thermo_read_data` Function reads the 32-bit of data from the sensor. 
```c
uint32_t thermo_read_data ( thermo_t* ctx );
```

### Application Init

> Initializes driver and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo_cfg_t cfg;


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

    thermo_cfg_setup( &cfg );
    THERMO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo_init( &thermo, &cfg );

    if ( thermo_check_fault( &thermo ) )
    {
        display_error_msg();
    }
    else
    {
        log_printf( &logger, "Status OK\r\n" );
    }

}
```

### Application Task

> Temperature measured by the thermocouple is converter and the results are logged. 

```c
void application_task ( void )
{
    temperature = thermo_get_temperature( &thermo );

    log_printf( &logger, "Temperature : %f\r\n", temperature );

}
```

### Note

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
