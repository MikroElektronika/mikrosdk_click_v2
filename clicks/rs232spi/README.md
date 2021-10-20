\mainpage Main Page
 
---
# RS232 SPI click

RS232 SPI click is based around the MAX3100, a universal asynchronous receiver transmitter (UART) - the first UART specifically optimized for small microcontroller-based systems, from Maxim Integrated. Because of the features contained in its modules, the RS232 SPI click can be used for handheld instruments, small networks in HVAC or Building control, UART in SPI systems, battery-powered systems, PDAs, notebooks and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs232spi_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rs232-spi-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

We provide a library for the Rs232Spi Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rs232Spi Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rs232spi_cfg_setup ( rs232spi_cfg_t *cfg ); 
 
- Initialization function.
> RS232SPI_RETVAL rs232spi_init ( rs232spi_t *ctx, rs232spi_cfg_t *cfg );

- Click Default Configuration function.
> void rs232spi_default_cfg ( rs232spi_t *ctx );

#### Example key functions :

- This function writes two bytes of data using the SPI serial interface.
> void rs232spi_reg_write ( rs232spi_t *ctx, uint16_t write_data );
 
- This function reads two bytes of data using the SPI serial interface.
> uint16_t rs232spi_reg_read ( rs232spi_t *ctx, uint16_t write_data );

- This function writes the specified digital signal to the RST pin.
> void rs232spi_digital_write_rst ( rs232spi_t *ctx, uint8_t signal );

## Examples Description

> This example showcases how to initialize and use the RS232 SPI click. The click has a uni-
  versal asynchronous transceiver which uses a SPI serial interface to communicate with the 
  MCU. In order for this example to work, 2 clicks are needed - a receiver and a transmitter. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. Additional configura-
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

        Delay_ms( 2000 );
    }
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs232Spi

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
