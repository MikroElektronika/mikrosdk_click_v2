\mainpage Main Page
 
---
# I2C MUX click

I2C MUX Click is an quad bidirectional translating I2C and SMBus switch with reset function, intended for applications with I2C slave address conflicts (multiple, identical temp sensors). It features a quad bidirectional translating switch controlled via the I2C bus, labeled as TCA9546A from Texas Instruments. Click has three address jumpers, allowing up to eight TCA9546A devices on the same bus. I2C MUX click allows voltage translation between 1.8V, 2.5V, 3.3V, and 5V buses, and also supports hot insertion.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cmux_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/i2c-mux-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the I2cMux Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for I2cMux Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void i2cmux_cfg_setup ( i2cmux_cfg_t *cfg ); 
 
- Initialization function.
> I2CMUX_RETVAL i2cmux_init ( i2cmux_t *ctx, i2cmux_cfg_t *cfg );

- Click Default Configuration function.
> void i2cmux_default_cfg ( i2cmux_t *ctx );


#### Example key functions :

- This function hardware reset I2C MUX click board by cleared to '0' state of the RST pin,
- wait the 100 ms, sets to '1' state of the RST pin and wait another the 100 ms.
> void i2cmux_hw_reset ( i2cmux_t *ctx );
 
- This function sets channel of the I2C MUX click board.
> void i2cmux_set_channel ( i2cmux_t *ctx, uint8_t channel, uint8_t ch_slave_address );

- This function reads data from the desired register.
> void i2cmux_generic_read ( i2cmux_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

## Examples Description

> This app reads "Who am I" register of the connected click boards to the UART MUX click.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - I2C,
> executes call hardware reset, also write log.

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

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "  I2C MUX  Click  \r\n" );
    log_printf( &logger, "------------------\r\n" );

    i2cmux_cfg_setup( &cfg );
    I2CMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux_init( &i2cmux, &cfg );

    log_printf( &logger, " I2C driver init. \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 100 );
     
    i2cmux_hw_reset( &i2cmux );
    log_printf( &logger, "     HW reset     \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> This is an example that demonstrates the use of the I2C MUX Click board.
> In this example, we read "Who am I" register of the connected click boards to the UART MUX click.
> Channel 0 : 6DOF IMU 9 click [ slave address: 0x69; reg: 0x75; id val.: 0xA9 ],
> Channel 1 : RTC 10 click     [ slave address: 0x68; reg: 0x0F; id val.: 0x88 ],
> Channel 2 : Altintude click  [ slave address: 0x60; reg: 0x0C; id val.: 0xC4 ],
> Channel 3 : Temp & Hum click [ slave address: 0x5F; reg: 0x0F; id val.: 0xBC ].
> All data logs write on USB UART changes every 2 sec.

```c

void application_task ( void )
{
    uint8_t rx_data;

    // SET CHANNEL 0: 6DOF IMU 9 click
    i2cmux_set_channel( &i2cmux, I2CMUX_CMD_SET_CH_0, 0x69 );
    Delay_ms( 100 );

    i2cmux_generic_read( &i2cmux, 0x75, &rx_data, 1 );
    log_printf( &logger, " CH-0 : ID = 0x%d\r\n", rx_data );

    // SET CHANNEL 1: RTC 10 click
    i2cmux_set_channel( &i2cmux, I2CMUX_CMD_SET_CH_1, 0x68 );
    Delay_ms( 100 );
    
    i2cmux_generic_read( &i2cmux, 0x0F, &rx_data, 1 );
    log_printf( &logger, " CH-1 : ST = 0x%d\r\n", rx_data );

    // SET CHANNEL 2: Altitude click
    i2cmux_set_channel( &i2cmux, I2CMUX_CMD_SET_CH_2, 0x60 );
    Delay_ms( 100 );
    
    i2cmux_generic_read( &i2cmux, 0x0C, &rx_data, 1 );
    log_printf( &logger, " CH-2 : ID = 0x%d\r\n", rx_data );

    // SET CHANNEL 3: Temp & Hum click
    i2cmux_set_channel( &i2cmux, I2CMUX_CMD_SET_CH_3, 0x5F );
    Delay_ms( 100 );
    
    i2cmux_generic_read( &i2cmux, 0x0F, &rx_data, 1 );
    log_printf( &logger, " CH-3 : ID = 0x%d\r\n", rx_data );

    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 2000 );
}


```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cMux

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
