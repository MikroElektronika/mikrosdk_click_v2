
---
# Environment 3 Click

> [Environment 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4893) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4893&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Environment 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Environment3

### Example Key Functions

- `environment3_cfg_setup` Config Object Initialization function.
```c
void environment3_cfg_setup ( environment3_cfg_t *cfg );
```

- `environment3_init` Initialization function.
```c
err_t environment3_init ( environment3_t *ctx, environment3_cfg_t *cfg );
```

- `environment3_default_cfg` Click Default Configuration function.
```c
err_t environment3_default_cfg ( environment3_t *ctx );
```

- `environment3_get_all_data` This function reads the temperature, humidity, pressure, and gas resistance data from the sensor.
```c
int8_t environment3_get_all_data ( environment3_t *ctx, float *temp, float *hum, float *pres, uint32_t *gas );
```

- `environment3_enable_heater` This function enables or disables the gas sensor heater.
```c
int8_t environment3_enable_heater ( environment3_t *ctx, uint8_t state );
```

- `environment3_soft_reset` This function soft-resets the sensor.
```c
int8_t environment3_soft_reset ( environment3_t *ctx );
```

### Application Init

> Initializes the driver, sets the default configuration, and disables the gas sensor heater.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    environment3_cfg_t environment3_cfg;  /**< Click config object. */

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

    environment3_cfg_setup( &environment3_cfg );
    ENVIRONMENT3_MAP_MIKROBUS( environment3_cfg, MIKROBUS_1 );
    err_t init_flag  = environment3_init( &environment3, &environment3_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( ENVIRONMENT3_OK != environment3_default_cfg ( &environment3 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    environment3_enable_heater ( &environment3, ENVIRONMENT3_DISABLE );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature, humidity, pressure, and gas resistance data from the sensor and 
> displays all values on the USB UART approximately every second.

```c
void application_task ( void )
{
    float temperature, pressure, humidity;
    uint32_t gas_resistance;
    if ( ENVIRONMENT3_OK == environment3_get_all_data ( &environment3, 
                                                        &temperature, 
                                                        &humidity, 
                                                        &pressure, 
                                                        &gas_resistance ) )
    {
        log_printf( &logger, " Temperature : %.2f C\r\n", temperature );
    
        log_printf( &logger, " Humidity : %.2f %%\r\n", humidity );
        
        log_printf( &logger, " Pressure : %.3f mBar\r\n", pressure );
        
        if ( ENVIRONMENT3_ENABLE == environment3.gas_sett.enable )
        {
            log_printf( &logger, " Gas Resistance : %ld Ohms\r\n", gas_resistance );
            log_printf( &logger, "--------------------------------\r\n" );
        }
        else
        {
            log_printf( &logger, "--------------------------------\r\n" );
            Delay_ms ( 1000 );
        }
    }
}
```

### Note

> The heater is disabled by default, enable it in the Application Init if you need gas resistance data.
> Gas resistance data is RAW data, if you need VOCs, please contact Bosch Sensortec for VOC calculation library.
> The temperature and humidity data don't represent the real environmental data when the heater is enabled.

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
