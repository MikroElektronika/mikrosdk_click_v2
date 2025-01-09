
---
# DHT22 2 Click

> [DHT22 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2818) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2818&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of DHT22 2 Click board by reading the temperature and humidity data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Dht222

### Example Key Functions

- `dht222_cfg_setup` Config Object Initialization function.
```c
void dht222_cfg_setup ( dht222_cfg_t *cfg ); 
```

- `dht222_init` Initialization function.
```c
err_t dht222_init ( dht222_t *ctx, dht222_cfg_t *cfg );
```

- `dht222_read_reg` This function reads data from the desired register.
```c
err_t dht222_read_reg ( dht222_t *ctx, uint8_t address, uint8_t *data_out, uint8_t len );
```

- `dht222_write_reg` This function writes data to the desired register.
```c
err_t dht222_write_reg ( dht222_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len );
```

- `dht222_get_temp_hum` The function reads the temperature and humidity data from the sensor AM2322 on the DHT22 2 Click.
```c
err_t dht222_get_temp_hum ( dht222_t *ctx, uint16_t *temperature, uint16_t *humidity );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dht222_cfg_t cfg;

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
    dht222_cfg_setup( &cfg );
    DHT222_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dht222_init( &dht222, &cfg );
    Delay_ms ( 500 );
}
```

### Application Task

> Reads the temperature (degrees C) and the relative humidity (%RH) data and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    uint16_t temperature = 0;
    uint16_t humidity = 0;
    if ( DHT222_OK == dht222_get_temp_hum ( &dht222, &temperature, &humidity ) )
    {
        log_printf( &logger, " Humidity   : %.1f %%\r\n", ( float ) humidity / 10 );
        log_printf( &logger, " Temperature: %.1f C \r\n", ( float ) temperature / 10 );
        log_printf( &logger, "---------------------\r\n" );
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
