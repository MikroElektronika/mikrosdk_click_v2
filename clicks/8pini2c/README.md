\mainpage Main Page
 
---
# 8-pin I2C click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the 8pinI2c Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 8pinI2c Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c8pini2c_cfg_setup ( c8pini2c_cfg_t *cfg ); 
 
- Initialization function.
> C8PINI2C_RETVAL c8pini2c_init ( c8pini2c_t *ctx, c8pini2c_cfg_t *cfg );

#### Example key functions :

- 8pini2c i2c read
> void c8pini2c_i2c_read
(
    c8pini2c_t *ctx, uint8_t slave_addr, 
    uint8_t *data_buf, uint16_t len
);
 
- Getting register content
> void c8pini2c_read_data ( c8pini2c_t *ctx, uint8_t slave_addr, uint8_t reg, uint8_t *buff, uint8_t len );

- Setting register content
> void c8pini2c_write_data( c8pini2c_t *ctx, uint8_t slave_addr, uint8_t reg, uint8_t *buff, uint8_t len );

## Examples Description

> This demo example reads temperature on Surface Click.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and set up another click for test.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c8pini2c_cfg_t cfg;

    uint8_t status;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c8pini2c_cfg_setup( &cfg );
    C8PINI2C_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c8pini2c_init( &c8pini2c, &cfg );

    status = surfacetemp_setup( );
    if ( status == 0 )
    {
        log_printf( &logger, "--- INIT DONE --- \r\n" );
    }
    else
    {
        log_printf( &logger, "--- INIT ERROR --- \r\n" );
        for( ; ; );
    }
}
  
```

### Application Task

> Reads temperature and logs on the USB UART 

```c

void application_task ( void )
{
    float temperature;

    temperature = surfacetemp_get_temperature( );
    log_printf( &logger, "> Temperature : %.2f \r\n", temperature );
    Delay_ms( 1500 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.8pinI2c

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
