\mainpage Main Page
 
---
# I2C MUX 2 click

I2C MUX 2 Click is a quad bidirectional translating I2C and SMBus switch with reset and interrupt functions, intended for applications with I2C slave address conflicts. It features a quad bidirectional translating switch controlled via the I2C bus, labeled as TCA9545A from Texas Instruments. Four interrupt inputs (INT3–INT0), one for each of the downstream pairs, are provided on click board. One interrupt (INT) output acts as an AND of the four interrupt inputs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cmux2_click.png">
</p>

[click Product page](https://www.mikroe.com/i2c-mux-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the I2cMux2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for I2cMux2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void i2cmux2_cfg_setup ( i2cmux2_cfg_t *cfg ); 
 
- Initialization function.
> I2CMUX2_RETVAL i2cmux2_init ( i2cmux2_t *ctx, i2cmux2_cfg_t *cfg );

#### Example key functions :

- This function resets I2C MUX 2 click board by clearing the RST pin for 100ms.
> void i2cmux2_hw_reset ( i2cmux2_t *ctx );
 
- Function sets channel of the I2C MUX 2 click board.
> void i2cmux2_set_channel ( i2cmux2_t *ctx, uint8_t channel, uint8_t ch_slave_address );

- This function reads data from the desired register.
> void i2cmux2_generic_read ( i2cmux2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

## Examples Description

> This example demonstrates the use of the I2C MUX 2 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, performs the device reset, and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    i2cmux2_cfg_setup( &cfg );
    I2CMUX2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux2_init( &i2cmux2, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "I2C MUX 2 Click driver init\r\n");
    log_printf( &logger, "---------------------------------------\r\n");
    Delay_ms( 100 );

    i2cmux2_hw_reset( &i2cmux2 );
    log_printf( &logger, "I2C MUX 2 Click HW reset\r\n");
    log_printf( &logger, "---------------------------------------\r\n");
    Delay_ms( 100 );
}
  
```

### Application Task

> In this example, we read the device ID register of the connected click boards.
> Channel 0 : 6DOF IMU 11 click [slave address: 0x0E; reg: 0x00; id val.: 0x2D],
> Channel 1 : Altitude click    [slave address: 0x60; reg: 0x0C; id val.: 0xC4],
> Channel 2 : 6DOF IMU 9 click  [slave address: 0x69; reg: 0x75; id val.: 0xA9],
> Channel 3 : Compass 3 click   [slave address: 0x30; reg: 0x2F; id val.: 0x0C].
> All data logs write on USB UART changes every 2 sec.

```c

void application_task ( void )
{
    log_printf( &logger, "  CH  |   ID   |  INT \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    
    // SET CHANNEL 0: 6DOF IMU 11 click
    i2cmux2_set_channel( &i2cmux2, I2CMUX2_CMD_SET_CH_0, 0x0E );
    Delay_ms( 100 );
    i2cmux2_generic_read( &i2cmux2, 0x00, &rx_data, 1 );
    display_log( I2CMUX2_CMD_SET_CH_0 );
    
    // SET CHANNEL 1: Altitude click
    i2cmux2_set_channel( &i2cmux2, I2CMUX2_CMD_SET_CH_1, 0x60 );
    Delay_ms( 100 );
    i2cmux2_generic_read( &i2cmux2, 0x0C, &rx_data, 1 );
    display_log( I2CMUX2_CMD_SET_CH_1 );
    
    // SET CHANNEL 2: 6DOF IMU 9 click
    i2cmux2_set_channel( &i2cmux2, I2CMUX2_CMD_SET_CH_2, 0x69 );
    Delay_ms( 100 );
    i2cmux2_generic_read( &i2cmux2, 0x75, &rx_data, 1 );
    display_log( I2CMUX2_CMD_SET_CH_2 );

    // SET CHANNEL 3: Compass 3 click
    i2cmux2_set_channel( &i2cmux2, I2CMUX2_CMD_SET_CH_3, 0x30 );
    Delay_ms( 100 );
    i2cmux2_generic_read( &i2cmux2, 0x2F, &rx_data, 1 );
    display_log( I2CMUX2_CMD_SET_CH_3 );

    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 2000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cMux2

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
