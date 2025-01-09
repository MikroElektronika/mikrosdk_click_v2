
---
# Pressure 16 Click

> [Pressure 16 Click](https://www.mikroe.com/?pid_product=MIKROE-4765) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4765&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for the Pressure 16 Click driver.
> This demo application shows an example of pressure and temperature measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure16

### Example Key Functions

- `pressure16_cfg_setup` Config Object Initialization function.
```c
void pressure16_cfg_setup ( pressure16_cfg_t *cfg );
```

- `pressure16_init` Initialization function.
```c
err_t pressure16_init ( pressure16_t *ctx, pressure16_cfg_t *cfg );
```

- `pressure16_default_cfg` Click Default Configuration function.
```c
void pressure16_default_cfg ( pressure16_t *ctx );
```

- `pressure16_get_press_temp` Pressure 16 get pressure and temperature function.
```c
err_t pressure16_get_press_temp ( pressure16_t *ctx, float *pressure, float *temperature );
```

- `pressure16_set_ctrl_config` Pressure 16 set control configuration function.
```c
err_t pressure16_set_ctrl_config( pressure16_t *ctx, pressure16_ctrl_cfg_t ctrl_cfg_data );
```

- `pressure16_get_device_id` Pressure 16 get device ID function.
```c
err_t pressure16_get_device_id ( pressure16_t *ctx, uint8_t *dev_id );
```

### Application Init

> Initialization of I2C and SPI module and log UART.
> After driver initialization and default settings, 
> the app display retrieves the sensor parameters 
> such as pressure and temperature.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    pressure16_cfg_t pressure16_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    pressure16_cfg_setup( &pressure16_cfg );
    PRESSURE16_MAP_MIKROBUS( pressure16_cfg, MIKROBUS_1 );
    err_t init_flag  = pressure16_init( &pressure16, &pressure16_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    pressure16_default_cfg ( &pressure16 );
    log_info( &logger, " Application Task " );
    
    pressure16_get_device_id( &pressure16, &device_id );
    if ( device_id == PRESSURE16_DEVICE_ID ) {
        log_info( &logger, " Communication OK" );    
    } else {
        log_info( &logger, " Communication ERROR" ); 
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "      Start measuring\r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of a Pressure 16 Click board&trade;.
> Logs the pressure [ mbar ] and temperature [ degree Celsius ] data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    static float pressure, temperature;
    
    pressure16_get_press_temp( &pressure16, &pressure, &temperature );
    log_printf( &logger, " Pressure    : %.2f mbar \r\n", pressure );
    log_printf( &logger, " Temperature :  %.2f C \r\n", temperature );
    log_printf( &logger, "---------------------------\r\n" ); 
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
