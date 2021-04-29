\mainpage Main Page
 
 

---
# Boost 4 click

Boost 4 click carries the TPS61230A, a high efficiency fully integrated synchronous boost converter from Texas Instruments. The click is designed to run on a 3.3V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/boost4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/boost-4-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Boost4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Boost4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void boost4_cfg_setup ( boost4_cfg_t *cfg ); 
 
- Initialization function.
> BOOST4_RETVAL boost4_init ( boost4_t *ctx, boost4_cfg_t *cfg );


#### Example key functions :

- Generic SPI transfer, for sending and receiving packages.
> void boost4_generic_transfer ( boost4_t *ctx, spi_master_transfer_data_t *block );
 
- Function set output voltage by write 12-bit data to the register on the TPS61230A High Efficiency Step-Up Converter of Boost 4 Click.
> void boost4_set_out_voltage ( boost4_t *ctx, uint16_t value );

- Function is used to enabled or disabled the device.
> void boost4_enable ( boost4_t *ctx, uint8_t state );

## Examples Description

> This example demonstrates the use of Boost 4 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and logger, and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    boost4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    boost4_cfg_setup( &cfg );
    BOOST4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost4_init( &boost4, &cfg );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, "        Boost 4 Click        \r\n" );
    log_printf( &logger, "-----------------------------\r\n" );
    boost4_enable( &boost4, BOOST4_ENABLE );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Set the desired output voltage by cycling through a couple of predefined voltage values.
> All data are being logged on USB UART every 3 seconds.

```c

void application_task ( void )
{
    log_printf( &logger, " Set the max Vout \r\n" );
    boost4_set_out_voltage( &boost4, BOOST4_VOUT_MAX );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );

    log_printf( &logger, " Set Vout to 5V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_5 );

    Delay_ms( 3000 );
    
    log_printf( &logger, "-----------------------------\r\n" );

    log_printf( &logger, " Set Vout to 4.5V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_4_5 );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set Vout to 4V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_4 );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set Vout to 3.5V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_3_5 );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set Vout to 3V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_3 );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set Vout to 2.5V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_2_5 );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set the min Vout \r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_MIN );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
}  

```

## Note

> Vout cannot be set to voltage below Vin. So in order to get all values at Vout exactly 
> as it is set in this example, please provide 2.5V to Vin. 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost4

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
