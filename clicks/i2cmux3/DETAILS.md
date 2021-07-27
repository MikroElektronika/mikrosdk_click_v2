
---
# I2C MUX 3 click

I2C MUX 3 Click is a compact add-on board that contains eight bidirectional translating switches dedicated for applications with I2C slave address conflicts. This board features the TCA9548APWR, a low voltage 8-channel I2C bus switch with an active-low reset input from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cmux3_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/i2c-mux-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the I2cMux3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for I2cMux3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void i2cmux3_cfg_setup ( i2cmux3_cfg_t *cfg ); 
 
- Initialization function.
> I2CMUX3_RETVAL i2cmux3_init ( i2cmux3_t *ctx, i2cmux3_cfg_t *cfg );

#### Example key functions :

- Slave Device Read function
> void i2cmux3_rd_slv ( i2cmux3_t *ctx, uint8_t slv_sel_adr, uint8_t reg, uint8_t *p_rd_data, uint8_t n_bytes );
 
- Device enable function
> void i2cmux3_dev_enable ( i2cmux3_t *ctx, uint8_t stat );

- Hardware reset function
> void i2cmux3_hw_rst ( i2cmux3_t *ctx );

## Examples Description

> This example demonstrates the use of I2C MUX 3 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes the driver, preforms hardware reset, then enables channel 0 and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    i2cmux3_cfg_setup( &cfg );
    I2CMUX3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux3_init( &i2cmux3, &cfg );
    Delay_ms( 100 );
    
    i2cmux3_hw_rst( &i2cmux3 );
    Delay_ms( 100 );
    i2cmux3_ch_sel( &i2cmux3, 0 );
    log_printf( &logger, " Please connect a 6DOF IMU 12 click to channel 0\r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms( 2000 );
}
  
```

### Application Task

> Reads the device ID of a 6DOF IMU 12 click (dev ID: 0x24) and displays it on the USB UART each second.

```c

void application_task ( void )
{
    i2cmux3_rd_slv ( &i2cmux3, 0x68, 0x00, &id_val, 1 );
    log_printf( &logger, " The click device ID is:  0x%.2X \r\n", ( uint16_t ) id_val );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cMux3

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
