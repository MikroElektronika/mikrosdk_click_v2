
---
# HTU21D Click

> [HTU21D Click](https://www.mikroe.com/?pid_product=MIKROE-1687) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1687&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> The application is composed of two sections.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Htu21d

### Example Key Functions

- `htu21d_cfg_setup` Config Object Initialization function. 
```c
void htu21d_cfg_setup ( htu21d_cfg_t *cfg );
``` 
 
- `htu21d_init` Initialization function. 
```c
err_t htu21d_init ( htu21d_t *ctx, htu21d_cfg_t *cfg );
```

- `htu21d_default_cfg` Click Default Configuration function. 
```c
void htu21d_default_cfg ( htu21d_t *ctx );
```

- `htu21d_cfg_setup` This function initializes Click configuration structure to init state. 
```c
void htu21d_cfg_setup ( htu21d_cfg_t *cfg );
```

- `htu21d_init` This function initializes all necessary pins and peripherals used for this Click. 
```c
err_t htu21d_init ( htu21d_t *ctx, htu21d_cfg_t *cfg );
```

- `htu21d_generic_write` This function writes data to the desired register. 
```c
void htu21d_generic_write ( htu21d_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

- `htu21d_generic_read` This function reads data from the desired register. 
```c
void htu21d_generic_read ( htu21d_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

- `htu21d_read_data` Function read 24-bit data from register address of HTU21D. 
```c
uint32_t htu21d_read_data ( htu21d_t *ctx, uint8_t reg_adr );
```

- `htu21d_send_cmd` Function sends command to HTU21D. 
```c
void htu21d_send_cmd ( htu21d_t *ctx, uint8_t cmd_byte );
```

- `htu21d_readdata` This function reads data from the desired register. 
```c
void htu21d_readdata ( htu21d_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

- `htu21d_get_temperature` Function read and calculate temperature in degrees Celsius from the HTU21D sensor. 
```c
float htu21d_get_temperature ( htu21d_t *ctx );
```

- `htu21d_get_humidity` Function read and calculate humidity percentage from the HTU21D sensor. 
```c
float htu21d_get_humidity ( htu21d_t *ctx );
```

### Application Init

>
> Initialization driver enable's - I2C, soft reset switch OFF and ON the HTU21D sensor,hold ( required ) 
> after reset 100 [ ms ] and start write log.
> 

void application_init ( void )
{
    log_cfg_t log_cfg;
    htu21d_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    htu21d_cfg_setup( &cfg );
    HTU21D_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    htu21d_init( &htu21d, &cfg );
    
    htu21d_send_cmd ( &htu21d, HTU21D_SOFT_RESET );
    Delay_ms ( 15 );

    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "         HTU21D       \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
}


### Application Task

> This is a example which demonstrates the use of
> HTU21D Click board.Measured temperature and humidity 
> data from the HDC1000 sensor.Convert temperature data
> to degrees Celsius and humidity data to percentarg.
> Results are being sent to the Usart Terminal
> where you can track their changes.
> All data logs on usb uart for aproximetly every 3 sec.
>

void application_task ( void )
{
    //  Task implementation.
    temperature = htu21d_get_temperature( &htu21d );
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    
    humidity = htu21d_get_humidity( &htu21d );
    log_printf( &logger, " Humidity : %.2f % \r\n", humidity );

    log_printf( &logger, "---------------------------\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
 

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
