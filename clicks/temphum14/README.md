
---
# TempHum 14 Click

> [TempHum 14 Click](https://www.mikroe.com/?pid_product=MIKROE-4306) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4306&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Temp-Hum 14 Click board. Temp-Hum 14 Click board can be used to measure temperature and relative humidity. All data logs write on USB uart changes every 3 sec.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum14

### Example Key Functions

- `temphum14_cfg_setup` Config Object Initialization function.
```c
void temphum14_cfg_setup ( temphum14_cfg_t *cfg );
```

- `temphum14_init` Initialization function.
```c
err_t temphum14_init ( temphum14_t *ctx, temphum14_cfg_t *cfg );
```

- `temphum14_set_conversion` The function set conversion a single temperature and humidity conversion and select data resolution to the HTU31D RH/T SENSOR IC Digital Relative Humidity sensor with Temperature output on the Temp-Hum 14 Click board.
```c
void temphum14_set_conversion ( temphum14_t *ctx, uint8_t hum_osr, uint8_t temp_osr );
```

- `temphum14_read_t_and_rh` The function read temperature and humidity data of the HTU31D RH/T SENSOR IC Digital Relative Humidity sensor with Temperature output on the Temp-Hum 14 Click board.
```c
void temphum14_read_t_and_rh ( temphum14_t *ctx, uint8_t *p_rx_data );
```

- `temphum14_get_temp_and_hum` The function get temperature and humidity value of the HTU31D RH/T SENSOR IC Digital Relative Humidity sensor with Temperature output on the Temp-Hum 14 Click board.
```c
void temphum14_get_temp_and_hum ( temphum14_t *ctx, float *temp, float *hum );
```

### Application Init

> Initialization driver enables I2C, and hardware reset the device and read the serial number.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum14_cfg_t temphum14_cfg;  /**< Click config object. */

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
    log_printf( &logger, "-----------------------------\r\n" );
    log_info( &logger, " Application Init " );
    log_printf( &logger, "-----------------------------\r\n" );

    // Click initialization.
    temphum14_cfg_setup( &temphum14_cfg );
    TEMPHUM14_MAP_MIKROBUS( temphum14_cfg, MIKROBUS_1 );
    err_t init_flag = temphum14_init( &temphum14, &temphum14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " Hardware Reset \r\n" );
    temphum14_hw_reset( &temphum14 );
    Delay_ms ( 100 );
    
    ser_numb = temphum14_get_serial_number( &temphum14 );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " Serial Number : %lu \r\n", ser_numb );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " Software Reset \r\n" );
    temphum14_soft_reset( &temphum14 );
    Delay_ms ( 100 );
    
    temphum14_get_diagnostic( &temphum14, &status_data );
    Delay_ms ( 10 );

    display_diagnostic( );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
}
```

### Application Task

> Reading temperature and humidity, and loging it on the USB uart. 

```c
void application_task ( void ) 
{
    temphum14_set_conversion( &temphum14, TEMPHUM14_CONVERSION_HUM_OSR_0_020, TEMPHUM14_CONVERSION_TEMP_0_040 );
    Delay_ms ( 10 );
    
    temphum14_get_temp_and_hum( &temphum14, &temperature, &humidity );
    Delay_ms ( 10 );
    
    log_printf( &logger, "  Temperature : %.2f C \r\n", temperature );
    log_printf( &logger, "  Humidity    : %.2f %% \r\n", humidity );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 1000 );
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
