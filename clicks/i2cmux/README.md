\mainpage Main Page
 
---
# I2C MUX click

I2C MUX Click is an quad bidirectional translating I2C and SMBus switch with reset function, intended for applications with I2C slave address conflicts (multiple, identical temp sensors). It features a quad bidirectional translating switch controlled via the I2C bus, labeled as TCA9546A from Texas Instruments. Click has three address jumpers, allowing up to eight TCA9546A devices on the same bus. I2C MUX click allows voltage translation between 1.8V, 2.5V, 3.3V, and 5V buses, and also supports hot insertion.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cmux_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/i2c-mux-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the I2cMux Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for I2cMux Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void i2cmux_cfg_setup ( i2cmux_cfg_t *cfg ); 
 
- Initialization function.
> I2CMUX_RETVAL i2cmux_init ( i2cmux_t *ctx, i2cmux_cfg_t *cfg );

#### Example key functions :

- This function resets I2C MUX 2 click board by clearing the RST pin for 100ms.
> void i2cmux_hw_reset ( i2cmux_t *ctx );
 
- This function sets channel of the I2C MUX click board.
> void i2cmux_set_channel ( i2cmux_t *ctx, uint8_t channel, uint8_t ch_slave_address );

- This function reads data from the desired register.
> void i2cmux_generic_read ( i2cmux_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

## Examples Description

> This example demonstrates the use of I2C MUX Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes the driver, preforms hardware reset, then enables channel 0 and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    i2cmux_cfg_setup( &cfg );
    I2CMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux_init( &i2cmux, &cfg );
    Delay_ms( 100 );
    i2cmux_hw_reset( &i2cmux );
    Delay_ms( 100 );
    
    i2cmux_set_channel( &i2cmux, I2CMUX_CMD_SET_CH_0, 0x39 );
    log_printf( &logger, " Please connect a Spectrometer click to channel 0\r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms( 2000 );
}
  
```

### Application Task

> Reads the device ID of a Spectrometer click (dev ID: 0x24) and displays it on the USB UART each second.

```c

void application_task ( void )
{
    uint8_t rx_data;
    
    i2cmux_generic_read( &i2cmux, 0x92, &rx_data, 1 );
    log_printf( &logger, " The click device ID is:  0x%.2X\r\n", ( uint16_t ) rx_data );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms( 1000 );
}


```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cMux

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
