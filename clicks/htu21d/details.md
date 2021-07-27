
---
# HTU21D click

HTU21D click carries a high-precision, easy-to-use relative humidity sensor with temperature output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/htu21d_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/htu21d-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Htu21d Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This is explanation for Htu21d Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void htu21d_cfg_setup ( htu21d_cfg_t *cfg ); 
 
- Initialization function.
> HTU21D_RETVAL htu21d_init ( htu21d_t *ctx, htu21d_cfg_t *cfg );

- Click Default Configuration function.
> void htu21d_default_cfg ( htu21d_t *ctx );


#### Example key functions :

- This function initializes click configuration structure to init state.
> void htu21d_cfg_setup ( htu21d_cfg_t *cfg );

- This function initializes all necessary pins and peripherals used for this click.
> HTU21D_RETVAL htu21d_init ( htu21d_t *ctx, htu21d_cfg_t *cfg );

- This function writes data to the desired register.
> void htu21d_generic_write ( htu21d_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

- This function reads data from the desired register.
> void htu21d_generic_read ( htu21d_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

- Function read 24-bit data from register address of HTU21D.
> uint32_t htu21d_read_data ( htu21d_t *ctx, uint8_t reg_adr );

- Function sends command to HTU21D.
> void htu21d_send_cmd ( htu21d_t *ctx, uint8_t cmd_byte );

- This function reads data from the desired register.
> void htu21d_readdata ( htu21d_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );


- Function read and calculate temperature in degrees Celsius from the HTU21D sensor.
> float htu21d_get_temperature ( htu21d_t *ctx );

- Function read and calculate humidity percentage from the HTU21D sensor.
> float htu21d_get_humidity ( htu21d_t *ctx );

## Examples Description

> 
> The application is composed of two sections.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initialization driver enable's - I2C, soft reset switch OFF and ON the HTU21D sensor,hold ( required ) 
> after reset 100 [ ms ] and start write log.
> 

void application_init ( void )
{
    log_cfg_t log_cfg;
    htu21d_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    htu21d_cfg_setup( &cfg );
    HTU21D_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    htu21d_init( &htu21d, &cfg );
    
    htu21d_send_cmd ( &htu21d, HTU21D_SOFT_RESET );
    Delay_ms( 15 );

    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "         HTU21D       \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
}


### Application Task

> This is a example which demonstrates the use of
> HTU21D Click board.Measured temperature and humidity 
> data from the HDC1000 sensor.Convert temperature data
> to degrees Celsius and humidity data to percentarg.
> Results are being sent to the Usart Terminal
> where you can track their changes.
> All data logs on usb uart for aproximetly every 3 sec.
>

void application_task ( void )
{
    //  Task implementation.
    temperature = htu21d_get_temperature( &htu21d );
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    
    humidity = htu21d_get_humidity( &htu21d );
    log_printf( &logger, " Humidity : %.2f % \r\n", humidity );

    log_printf( &logger, "---------------------------\r\n" );

    Delay_ms( 3000 );
}
 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Htu21d

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
