\mainpage Main Page
 
---
# I2C Isolator 2 click

I2C Isolator 2 click provides I2C lines and power isolation for slave devices. It carries the ADM3260 dual I2C isolator with an integrated DC-to-DC converter. I2C Isolator 2 click is designed to run on either 3.3V or 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cisolator2_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/i2c-isolator-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the I2CIsolator2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for I2CIsolator2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void i2cisolator2_cfg_setup ( i2cisolator2_cfg_t *cfg ); 
 
- Initialization function.
> I2CISOLATOR2_RETVAL i2cisolator2_init ( i2cisolator2_t *ctx, i2cisolator2_cfg_t *cfg );

- Click Default Configuration function.
> void i2cisolator2_default_cfg ( i2cisolator2_t *ctx );


#### Example key functions :

- This function writes data to the desired register.
> void i2cisolator2_generic_write ( i2cisolator2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

- This function reads data from the desired register.
> void i2cisolator2_generic_read ( i2cisolator2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

## Examples Description

> This example showcases how to initialize, configure and use the I2C Isolator 2 click module.
  The click provides I2C lines and power isolation for slave devices. In order for this exam-
  ple to work, you need the IrThermo 2 click.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the click and logger modules. Additional configuring
  is done in the default_cfg(...) function.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cisolator2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    i2cisolator2_cfg_setup( &cfg );
    I2CISOLATOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cisolator2_init( &i2cisolator2, &cfg );
    Delay_100ms( );
    digital_out_low( &ctx->pdis );
    Delay_100ms( );
    i2cisolator2_default_cfg( &i2cisolator2 );
}
  
```

### Application Task

> This function reads temperature data from the IrThermo 2 click and displays that data in the
  UART console every second.

```c

void application_task ( void )
{
    float temp;

    temp = get_object_temperature( );
    Delay_100ms( );

    log_printf( &logger, " .temperature: %f C\r\n", temp );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_1sec( );
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CIsolator2

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
