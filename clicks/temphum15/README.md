
---
# Temp&Hum 15 Click

> [TempHum 15 Click](https://www.mikroe.com/?pid_product=MIKROE-4496) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4496&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Nikolic
- **Date**          : jan 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo app represents the performance of the Temp&Hum 15 Click board. The log displays the temperature and humidity obtained from the sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum15

### Example Key Functions

- `temphum15_cfg_setup` Config Object Initialization function.
```c
void temphum15_cfg_setup ( temphum15_cfg_t *cfg );
```

- `temphum15_init` Initialization function.
```c
err_t temphum15_init ( temphum15_t *ctx, temphum15_cfg_t *cfg );
```

- `temphum15_default_cfg` Click Default Configuration function.
```c
void temphum15_default_cfg ( temphum15_t *ctx );
```

- `temphum15_get_temp_and_hum` This function reads temperature and humidity with the power consumption based on the precision mode selected.
```c
err_t temphum15_get_temp_and_hum ( temphum15_t *ctx, uint8_t precision_mode, float *temp_val, float *hum_val );
```

- `temphum15_soft_reset` This function sends soft reset command to the sensor.
```c
err_t temphum15_soft_reset ( temphum15_t *ctx );
```

- `temphum15_read_serial` This function reads unique serial number of the sensor.
```c
err_t temphum15_read_serial ( temphum15_t *ctx, uint32_t *serial_number );
```

### Application Init

> Initialization of UART LOG and I2C drivers. The application also performs reset upon init.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    temphum15_cfg_t temphum15_cfg;  /**< Click config object. */

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

    temphum15_cfg_setup( &temphum15_cfg );
    TEMPHUM15_MAP_MIKROBUS( temphum15_cfg, MIKROBUS_1 );
    err_t init_flag = temphum15_init( &temphum15, &temphum15_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    Delay_ms ( 100 );
    temphum15_default_cfg( &temphum15 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

 > Temperature and humidity data are being acquired every two seconds. If the acquisition fails, LOG states that no data is available.

```c
void application_task ( void ) 
{
    err_t status_data;
    
    status_data = temphum15_get_temp_and_hum( &temphum15, TEMPHUM15_MODE_HIGH_PRECISION, &temperature, &humidity );
    if ( status_data == TEMPHUM15_SUCCESS ) {
        log_printf( &logger, "----------------------------\r\n" );
        log_printf( &logger, "> Temperature : %.2f C\r\n", temperature );
        log_printf( &logger, "> Humidity: %.2f %RH\r\n", humidity );
    } else {
        log_printf( &logger, "----------------------------\r\n" );
        log_printf( &logger, "> No data\r\n" );
    }
    Delay_ms ( 1000 );
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
