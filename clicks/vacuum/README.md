
---
# Vacuum Click

> [Vacuum Click](https://www.mikroe.com/?pid_product=MIKROE-3195) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3195&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measuring absolute pressure.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Vacuum

### Example Key Functions

- `vacuum_cfg_setup` Config Object Initialization function. 
```c
void vacuum_cfg_setup ( vacuum_cfg_t *cfg );
``` 
 
- `vacuum_init` Initialization function. 
```c
err_t vacuum_init ( vacuum_t *ctx, vacuum_cfg_t *cfg );
```

- `vacuum_generic_write` Generic write function. 
```c
void vacuum_generic_write ( vacuum_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```
 
- `vacuum_get_voltage` Voltage reading function. 
```c
float vacuum_get_voltage ( vacuum_t *ctx );
```

- `vacuum_get_percentage_of_vacuum` Function for converting ADC value to percentage of Vacuum. 
```c
float vacuum_get_percentage_of_vacuum ( vacuum_t *ctx );
```

### Application Init

> Initialization driver init and calibration of the chip to start measuring.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    vacuum_cfg_t cfg;

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

    vacuum_cfg_setup( &cfg );
    VACCUM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vacuum_init( &vacuum, &cfg );

    vacuum_calibration( &vacuum );
}
```

### Application Task

> Reads vacuum percentage that sensor reads.

```c
void application_task ( void )
{
    //  Task implementation.
    vacuum_volt = vacuum_get_voltage(  &vacuum );
    log_printf ( &logger, "Vacuum (voltage) : %.2f V\r\n ", vacuum_volt );
     
    vacuum_data = vacuum_get_percentage_of_vacuum(  &vacuum );
    log_printf ( &logger, "Percentage of vacuum: %.2f : \r\n ", vacuum_data );
    
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
