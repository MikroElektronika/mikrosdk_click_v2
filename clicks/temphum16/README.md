
---
# Temp&Hum 16 Click

> [TempHum 16 Click](https://www.mikroe.com/?pid_product=MIKROE-4733) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4733&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for the Temp&Hum 16 Click driver.
> This demo application shows an example of 
> humidity and temperature measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum16

### Example Key Functions

- `temphum16_cfg_setup` Config Object Initialization function.
```c
void temphum16_cfg_setup ( temphum16_cfg_t *cfg );
```

- `temphum16_init` Initialization function.
```c
err_t temphum16_init ( temphum16_t *ctx, temphum16_cfg_t *cfg );
```

- `temphum16_default_cfg` Click Default Configuration function.
```c
void temphum16_default_cfg ( temphum16_t *ctx );
```

- `temphum16_check_ready` Temp&Hum 16 check ready function.
```c
uint8_t temphum16_check_ready ( temphum16_t *ctx );
```

- `temphum16_get_humidity` Temp&Hum 16 get humidity function.
```c
err_t temphum16_get_humidity ( temphum16_t *ctx, float *humidity );
```

- `temphum16_get_temperature` Temp&Hum 16 get temperature function.
```c
err_t temphum16_get_temperature ( temphum16_t *ctx, float *temperature );
```

### Application Init

> Initialization of SPI or I2C module and log UART.
> After driver initialization and default settings, 
> the app display retrieves the sensor parameters 
> such as temperature and humidity.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    temphum16_cfg_t temphum16_cfg;  /**< Click config object. */

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

    temphum16_cfg_setup( &temphum16_cfg );
    TEMPHUM16_MAP_MIKROBUS( temphum16_cfg, MIKROBUS_1 );
    err_t init_flag  = temphum16_init( &temphum16, &temphum16_cfg );
    if ( ( init_flag == I2C_MASTER_ERROR ) || ( init_flag == SPI_MASTER_ERROR ) ) {
        log_info( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    temphum16_default_cfg ( &temphum16 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );

    temphum16_get_device_id( &temphum16, &device_id );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "  Check communication  \r\n" ); 
    if ( device_id == TEMPHUM16_DEVICE_ID ){
        log_printf( &logger, "      Successful   \r\n" );    
    } else {
        log_printf( &logger, "        Failed     \r\n" );
        
        for ( ; ; );
    }
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "   Start measurements  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}
```

### Application Task

> This is an example that shows the use of a Temp&Hum 16 Click board&trade;.
> Logs humidity [ % ] and temperature [ degree Celsius ] data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    if ( temphum16_check_ready( &temphum16 ) == TEMPHUM16_DRDY ) {
        temphum16_get_temperature( &temphum16, &temperature );
        log_printf( &logger, " Temperature : %.2f C\r\n", temperature ); 
        
        temphum16_get_humidity( &temphum16, &humidity );
        log_printf( &logger, " Humidity    : %.2f %%\r\n", humidity ); 
        log_printf( &logger, "-----------------------\r\n" );
        Delay_ms ( 1000 );
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
