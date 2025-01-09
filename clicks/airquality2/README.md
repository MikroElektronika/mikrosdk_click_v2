
---
# Air quality 2 Click

> [Air quality 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2529) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2529&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This app measure indoor air quality.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Airquality2

### Example Key Functions

- `airquality2_cfg_setup` Config Object Initialization function. 
```c
void airquality2_cfg_setup ( airquality2_cfg_t *cfg );
``` 
 
- `airquality2_init` Initialization function. 
```c
err_t airquality2_init ( airquality2_t *ctx, airquality2_cfg_t *cfg );
```

- `airquality2_generic_read` This function reads data. 
```c
void airquality2_generic_read ( airquality2_t *ctx, uint8_t *data_buf, uint8_t len );
```
 
- `airquality2_get_all_data` Reads all data information about the indoor air quality. 
```c
uint8_t airquality2_get_all_data ( airquality2_t *ctx, uint16_t *value_co2, uint16_t *value_tvoc, int32_t *resistance );
```

### Application Init

> Initialization device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality2_cfg_t cfg;

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

    airquality2_cfg_setup( &cfg );
    AIRQUALITY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality2_init( &airquality2, &cfg );
    
    // Click calibration 
    uint8_t dummy_buffer[ 9 ];
    airquality2_generic_read( &airquality2, dummy_buffer, AIRQUALITY2_READ_ALL );
    
    log_printf( &logger, "----------------------------------\r\n" );
    log_printf( &logger, "           Air quality 2          \r\n" );
    log_printf( &logger, "----------------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is a example which demonstrates the use of Air quality 2 Click board.
> Read all data information about the indoor air quality
> from register on the iAQ-Core module, display Prediction Value CO2 [ ppm ],
> Prediction Value TVOC [ ppb ] and Resistance Value.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 5 sec.

```c
void application_task ( void )
{
    uint8_t status_info;
    uint16_t value_co2;
    uint16_t value_tvoc;
    int32_t resistance;

    status_info = airquality2_get_all_data( &airquality2, &value_co2, &value_tvoc, &resistance );
    Delay_100ms( );

    if ( status_info == AIRQUALITY2_STATUS_OK )
    {
        log_printf( &logger, "       | Status : OK     |\r\n" );
    }
    if ( status_info == AIRQUALITY2_STATUS_BUSY )
    {
        log_printf( &logger, "       | Status : BUSY   |\r\n" );
    }
    if ( status_info == AIRQUALITY2_STATUS_ERROR )
    {
        log_printf( &logger, "       | Status : ERROR  |\r\n" );
    }
    if ( status_info == AIRQUALITY2_STATUS_RUNIN )
    {
        log_printf( &logger, "       | Status : RUNIN  |\r\n" );
    }

    log_printf( &logger, "----------------------------------\r\n" );

    log_printf( &logger, " CO2        : %u [ ppm ] \r\n", value_co2 );

    log_printf( &logger, " TVOC       : %u [ ppb ] \r\n", value_tvoc );

    log_printf( &logger, " Resistance : %ld [ Ohm ] \r\n", resistance );

    log_printf( &logger, "----------------------------------\r\n" );

    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
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
