
---
# Altitude 3 Click

> [Altitude 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3328) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3328&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application enables high-resolution barometric pressure measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Altitude3

### Example Key Functions

- `altitude3_cfg_setup` Config Object Initialization function. 
```c
void altitude3_cfg_setup ( altitude3_cfg_t *cfg );
``` 
 
- `altitude3_init` Initialization function. 
```c
err_t altitude3_init ( altitude3_t *ctx, altitude3_cfg_t *cfg );
```

- `altitude3_default_cfg` Click Default Configuration function. 
```c
void altitude3_default_cfg ( altitude3_t *ctx );
```

- `altitude3_soft_reset` Function sends a command to perform a SW Reset of the device. 
```c
void altitude3_soft_reset ( altitude3_t *ctx );
```
 
- Function reads results of AD conversion, which consists of the 16bit temperature and 24bit
- `altitude3_read_adc_results` pressure data in determined order. 
```c
uint8_t altitude3_read_adc_results ( altitude3_t *ctx, uint8_t read_order );
```

- Function performs a calibration data reading, only once, and then reads a temperature and pressure
- data and calculates these values
- `altitude3_get_data` to standard units. Also calculates the altitude depending on the temperature and pressure data. 
```c
uint8_t altitude3_get_data ( altitude3_t *ctx, uint8_t read_order );
```

### Application Init

> Initializes I2C interface and performs a SW Reset of the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    altitude3_cfg_t cfg;

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

    altitude3_cfg_setup( &cfg );
    ALTITUDE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    altitude3_init( &altitude3, &cfg );

    altitude3_default_cfg ( &altitude3 );

    log_printf( &logger, "** Altitude 3 Click is initialized **\r\n\r\n" );
}
```

### Application Task

> Selects the desired measurement mode and data reading order, and after that
> calculates the temperature, pressure and altitude data to standard units and shows results to uart
> terminal.

```c
void application_task ( void )
{
    uint8_t response;

    response = altitude3_measurement_mode( &altitude3, ALTITUDE3_NORMAL_T_FIRST );

    Delay_ms ( 100 );

    response = altitude3_get_data( &altitude3, response );
    
    if ( response != ALTITUDE3_ERROR )
    {
        log_printf( &logger, "Temperature is : %d C\r\n", ( int16_t ) altitude3.sens_data.temperature );
       
        log_printf( &logger, "Pressure is : %u  mbar[hPa]\r\n", ( uint16_t ) altitude3.sens_data.pressure );
    
        log_printf( &logger, "Altitude is : %d m\r\n\r\n", ( int16_t ) altitude3.sens_data.altitude );

        Delay_ms ( 400 );
    }
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
