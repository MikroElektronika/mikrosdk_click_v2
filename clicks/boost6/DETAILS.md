

---
# Boost 6 Click

The Boost 6 Click is a Click board™ which features the TPS55332-Q1, a monolithic high-voltage switching regulator with integrated 3-A, 60-V power MOSFET.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/boost6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/boost-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Boost6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Boost6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void boost6_cfg_setup ( boost6_cfg_t *cfg ); 
 
- Initialization function.
> BOOST6_RETVAL boost6_init ( boost6_t *ctx, boost6_cfg_t *cfg );

- Click Default Configuration function.
> void boost6_default_cfg ( boost6_t *ctx );


#### Example key functions :

- This function hardware reset the TPS55332-Q1 60-V Output Step Up DC/DC Converter
- on Boost 6 Click by cleared to '0' state of the RST pin,
- wait the 100 ms, sets to '1' state of the RST pin and wait another the 100 ms.
> void boost6_hw_reset ( boost6_t *ctx );
 
- This function power OFF provides electrical off control of the regulator
- TPS55332-Q1 60-V Output Step Up DC/DC Converter
- on Boost 6 Click by cleared to '0' state of the EN pin.
> void boost6_power_off ( boost6_t *ctx );

- This function power ON provides electrical off control of the regulator
- TPS55332-Q1 60-V Output Step Up DC/DC Converter
- on Boost 6 Click by sets to '1' state of the EN pin.
> void boost6_power_on ( boost6_t *ctx );

## Examples Description

> This app enable or disable monolithic high-voltage switching regulator.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    boost6_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    boost6_cfg_setup( &cfg );
    BOOST6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost6_init( &boost6, &cfg );

    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, "  Boost 6 Click  \r\n" );
    log_printf( &logger, "-----------------\r\n" );

    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, " Hardware  Reset \r\n" );
    log_printf( &logger, "-----------------\r\n" );
    boost6_hw_reset ( &boost6 );
    Delay_100ms( );

    boost6_power_off(  &boost6  );
    log_printf( &logger, "     Disable     \r\n" );
    log_printf( &logger, "-----------------\r\n" );
    Delay_100ms( );
}
  
```

### Application Task

> This is an example which demonstrates the use of Boost 6 Click board.
> Enable device 5000ms and disable device 5000ms.

```c

void application_task ( void )
{
    boost6_power_on( &boost6 );
    log_printf( &logger, "     Enable      \r\n" );
    log_printf( &logger, "-----------------\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    boost6_power_off(  &boost6  );
    log_printf( &logger, "     Disable     \r\n" );
    log_printf( &logger, "-----------------\r\n" );

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
- Click.Boost6

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
