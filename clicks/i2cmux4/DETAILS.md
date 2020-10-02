
---
# I2C MUX 4 click

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

We provide a library for the I2cMux4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for I2cMux4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void i2cmux4_cfg_setup ( i2cmux4_cfg_t *cfg ); 
 
- Initialization function.
> I2CMUX4_RETVAL i2cmux4_init ( i2cmux4_t *ctx, i2cmux4_cfg_t *cfg );

#### Example key functions :

- Get channel interrupt function
> uint8_t i2cmux4_get_ch_interrupt
( i2cmux4_t *ctx );
 
- Generic read data function
> void i2cmux4_rmt_read_bytes
( i2cmux4_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );

- Check interrupt function.
> uint8_t i2cmux4_check_int
( i2cmux4_t *ctx );

## Examples Description

> This demo app demonstrates the use of the I2C MUX 4 Click.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - I2C,
> executes call power On and hardware reset, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    i2cmux4_cfg_setup( &cfg );
    I2CMUX4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux4_init( &i2cmux4, &cfg );

    i2cmux4_power_on( &i2cmux4, I2CMUX4_ENABLE_POWER_ON );
    Delay_ms( 100 );
    
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_ALL_DISABLE, 0x00 );
    Delay_ms( 100 );
}
  
```

### Application Task

> This is an example that demonstrates the use of the I2C MUX 4 Click board.
> In this example, we read "Who am I" ( or "State" ) register
> of the connected click boards to the I2C MUX 4 click.
> Channel 0 : 6DOF IMU 12 click [slave address: 0x0E; reg: 0x00; id val.: 0x24],
> Channel 1 : RTC 10 click      [slave address: 0x68; reg: 0x0F; st val.: 0x88].
> All data logs write on USB UART changes approximately every 2 sec.

```c

void application_task ( void )
{
    // CH 0 - 6DOF IMU 12 click
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_0, 0x68 );
    Delay_ms( 100 );

    i2cmux4_rmt_read_bytes( &i2cmux4, 0x00, &rx_data, 1 );
    Delay_ms( 100 );

    log_printf( &logger, "    6DOF IMU 12 click   \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    log_printf( &logger, "       ID = 0x%d  \r\n", rx_data );
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms( 1000 );
    
    
    // CH 1 - RTC 10 click
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_1, 0x68 );
    Delay_ms( 100 );

    i2cmux4_rmt_read_bytes( &i2cmux4, 0x0F, &rx_data, 1 );
    Delay_ms( 100 );

    log_printf( &logger, "      RTC 10 click      \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    log_printf( &logger, "       ID = 0x%d \r\n ", rx_data );
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cMux4

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
