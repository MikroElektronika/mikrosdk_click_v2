
---
# RS232 SPI Click

> [RS232 SPI Click](https://www.mikroe.com/?pid_product=MIKROE-3912) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3912&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases how to initialize and use the RS232 SPI Click. The Click has a uni-
  versal asynchronous transceiver which uses a SPI serial interface to communicate with the 
  MCU. In order for this example to work, 2 Clicks are needed - a receiver and a transmitter. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs232Spi

### Example Key Functions

- `rs232spi_cfg_setup` Config Object Initialization function. 
```c
void rs232spi_cfg_setup ( rs232spi_cfg_t *cfg );
``` 
 
- `rs232spi_init` Initialization function. 
```c
err_t rs232spi_init ( rs232spi_t *ctx, rs232spi_cfg_t *cfg );
```

- `rs232spi_default_cfg` Click Default Configuration function. 
```c
void rs232spi_default_cfg ( rs232spi_t *ctx );
```

- `rs232spi_reg_write` This function writes two bytes of data using the SPI serial interface. 
```c
void rs232spi_reg_write ( rs232spi_t *ctx, uint16_t write_data );
```
 
- `rs232spi_reg_read` This function reads two bytes of data using the SPI serial interface. 
```c
uint16_t rs232spi_reg_read ( rs232spi_t *ctx, uint16_t write_data );
```

- `rs232spi_digital_write_rst` This function writes the specified digital signal to the RST pin. 
```c
void rs232spi_digital_write_rst ( rs232spi_t *ctx, uint8_t signal );
```

### Application Init

> This function initializes and configures the logger and Click modules. Additional configura-
  ting is done in the default_cfg(...) function.

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    rs232spi_cfg_t cfg;

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

    rs232spi_cfg_setup( &cfg );
    RS232SPI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs232spi_init( &rs232spi, &cfg );
    Delay_100ms( );
    rs232spi_digital_write_rst( &rs232spi, 1 );
    Delay_10ms( );
    rs232spi_default_cfg( &rs232spi, 19200 );
    Delay_10ms( );
    rs232spi_flush( &rs232spi );
    Delay_100ms( );
}
```

### Application Task

> This function receives and displays UART data in the "read mode" and sends the predefined 
  message in the "write mode". 

```c
void application_task ( )
{
    uint8_t mode = 0;
    uint8_t cnt;

    if ( mode == 1 )
    {
        if ( rs232spi_data_ready( &rs232spi ) != 0 )
        {
            log_printf( &logger, "%c\r\n", rs232spi_transfer( &rs232spi, RS232SPI_CMD_READ_DATA ) );
        }
    }
    else if ( mode == 0 )
    {
        for ( cnt = 0; cnt < 9; cnt++ )
        {
            rs232spi_data_write( &rs232spi, message[ cnt ] );
            if ( cnt < 6 )
            {
                Delay_100ms( );
            }
        }

        Delay_ms ( 1000 );
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
