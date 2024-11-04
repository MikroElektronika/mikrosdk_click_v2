
# BOOST Click

Boost Click carries Microchip’s MIC2606, a 2MHz, PWM DC/DC boost switching regulator available in a 2mm x 2mm MLF® package.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/boost_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/boost-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Boost Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Boost Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void boost_cfg_setup ( boost_cfg_t *cfg ); 
 
- Initialization function.
> BOOST_RETVAL boost_init ( boost_t *ctx, boost_cfg_t *cfg );

- Click Default Configuration function.
> void boost_default_cfg ( boost_t *ctx );


#### Example key functions :

- Generic write 14-bit data function.
> void boost_write_byte ( boost_t *ctx, uint16_t write_data );
 
- Generic read 22-bit of data function.
> uint32_t boost_read_byte ( boost_t *ctx );

- Set configuration function.
> void boost_set_configuration ( boost_t *ctx, uint8_t pwr_src );

## Examples Description

> Boost Click provides an adjustable output voltage through the onboard DAC that drives the FB pin of the MIC2606 to set desired output voltage.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - SPI, set configuration and start write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    boost_cfg_t cfg;

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

    boost_cfg_setup( &cfg );
    BOOST_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost_init( &boost, &cfg );

    boost_default_cfg ( &boost );

    Delay_100ms( );
}
  
```

### Application Task

> This is a example which demonstrates the use of Boost Click board.
  Boost Click communicates with register via SPI by read from MCP3551 chip and write DAC value to the MCP4921 chip.
  This example periodicaly increases and decreases voltage in range between 15 and 30 Volts.
  All data logs write on usb uart for aproximetly every 3 sec. 

```c

void application_task ( void )
{
  log_printf( &logger, " Setting voltage to 15000 mV \r\n" );

  boost_set_voltage( &boost, 15000 );
  Delay_ms ( 1000 );
  Delay_ms ( 1000 );
  Delay_ms ( 1000 );
  Delay_ms ( 1000 );
  Delay_ms ( 1000 );

  log_printf( &logger, " Setting voltage to 30000 mV \r\n" );

  boost_set_voltage( &boost, 30000 );
  Delay_ms ( 1000 );
  Delay_ms ( 1000 );
  Delay_ms ( 1000 );
  Delay_ms ( 1000 );
  Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
