
---
# Temp Hum 11 Click

> [TempHum 11 Click](https://www.mikroe.com/?pid_product=MIKROE-3469) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3469&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This Click has two sensors which can be set to sample measurements with the resolution 
> of 8, 11 or 14 bits, based on the measurement time. Calibration coefficients that are applied 
> to the measured value and the results are stored in the MSB/LSB format, on the output registers. 
> These values are then used in formulas so that the final temperature or relative humidity data can be calculated.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum11

### Example Key Functions

- `temphum11_cfg_setup` Config Object Initialization function. 
```c
void temphum11_cfg_setup ( temphum11_cfg_t *cfg );
``` 
 
- `temphum11_init` Initialization function. 
```c
err_t temphum11_init ( temphum11_t *ctx, temphum11_cfg_t *cfg );
```

- `temphum11_default_cfg` Click Default Configuration function. 
```c
void temphum11_default_cfg ( temphum11_t *ctx );
```

- `temphum11_get_temperature` This function reads temperature data in desired unit. 
```c
float temphum11_get_temperature ( temphum11_t *ctx, uint8_t temp_in );
```
 
- `temphum11_get_humidity` This function reads relative huminidy data. 
```c
float temphum11_get_humidity ( temphum11_t *ctx );
```

- `temphum11_read_data` This function reads data from the desired register. 
```c
uint16_t temphum11_read_data ( temphum11_t *ctx, uint8_t reg );
```

### Application Init

> Initializes driver init, test comunication and configuration chip for measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum11_cfg_t cfg;

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

    temphum11_cfg_setup( &cfg );
    TEMPHUM11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum11_init( &temphum11, &cfg );

    // Test comunication

    if ( temphum11_read_data( &temphum11, TEMPHUM11_REG_DEVICE_ID ) == TEMPHUM11_DEVICE_ID )
    {
        log_printf( &logger, "--- Comunication OK!!! ---\r\n" );
    }
    else
    {
        log_printf( &logger, "--- Comunication ERROR!!! ---\r\n" );
        for ( ; ; );
    }

    temphum11_default_cfg( &temphum11 );
    log_printf( &logger, "--- Start measurement --- \r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

> Reads Temperature and Humidity data. This data logs to USBUART every 1500ms.

```c
void application_task ( void )
{
    temperature = temphum11_get_temperature( &temphum11, TEMPHUM11_TEMP_IN_CELSIUS );
    
    log_printf( &logger, " Temperature : %.2f\r\n", temperature );
    
    humidity = temphum11_get_humidity( &temphum11 );
    
    log_printf( &logger, " Humidity :  %.2f\r\n", humidity );
    
    log_printf( &logger, "-----------------\r\n" );
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
