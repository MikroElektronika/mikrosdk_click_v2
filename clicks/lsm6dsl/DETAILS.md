
---
# LSM6DSL click

LSM6DSL click measures linear and angular velocity with six degrees of freedom. It carries the LSM6DSL high-performance 3-axis digital accelerometer and 3-axis digital gyroscope. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lsm6dsl_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lsm6dsl-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Lsm6Dsl Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Lsm6Dsl Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lsm6dsl_cfg_setup ( lsm6dsl_cfg_t *cfg ); 
 
- Initialization function.
> LSM6DSL_RETVAL lsm6dsl_init ( lsm6dsl_t *ctx, lsm6dsl_cfg_t *cfg );

- Click Default Configuration function.
> void lsm6dsl_default_cfg ( lsm6dsl_t *ctx );


#### Example key functions :

- This function set accel configuration to the target LSM6DSL_CTRL1_XL register of LSM6DSL sensor.
> void lsm6dsl_set_accel_config ( lsm6dsl_t *ctx, uint8_t odr_sel, uint8_t full_scale );
 
- This function set gyro configuration to the target LSM6DSL_CTRL1_XL register of LSM6DSL sensor.
> void lsm6dsl_set_gyro_config ( lsm6dsl_t *ctx, uint8_t odr_sel, uint8_t full_scale );

- This function get axis value from the two target 8-bit register address of LSM6DSL sensor.
> uint16_t lsm6dsl_get_axis ( lsm6dsl_t *ctx, uint8_t reg_address_low );

## Examples Description

> This app measures linear and angular velocity with six degrees of freedom.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lsm6dsl_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    lsm6dsl_cfg_setup( &cfg );
    LSM6DSL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lsm6dsl_init( &lsm6dsl, &cfg );

    lsm6dsl_default_cfg( &lsm6dsl );

    log_printf( &logger, "---------------------------------------\r\n" );
    log_printf( &logger, "|            LSM6DSL Click            |\r\n" );
    log_printf( &logger, "---------------------------------------\r\n" );
    log_printf( &logger, "|     Accel       |       Gyro        |\r\n" );
    log_printf( &logger, "---------------------------------------\r\n" );

    Delay_ms( 100 );
}
  
```

### Application Task

> This is a example which demonstrates the use of LSM6DSL Click board.
> LSM6DSL Click communicates with register via SPI by write to register and read from register,
> measured acceleration and gyroscope coordinates values ( X,Y,Z )
> Result are being sent to the uart where you can track their changes.
> All data logs on usb uart for aproximetly every 3 sec.

```c

void application_task ( void )
{

    lsm6dsl_get_accel( &lsm6dsl, &accel, LSM6DSL_FULLSCALE_XL_2 );
    
    Delay_ms( 10 );
    
    lsm6dsl_get_gyro( &lsm6dsl, &gyro, LSM6DSL_FULLSCALE_G_245 );
    
    Delay_ms( 10 );

    log_printf( &logger, " Accel X : %f |  Gyro X : %f |\r\n", accel.accel_x, gyro.gyro_x );

    log_printf( &logger, " Accel Y : %f |  Gyro Y : %f |\r\n", accel.accel_y, gyro.gyro_y );

    log_printf( &logger, " Accel Z : %f |  Gyro Z : %f |\r\n", accel.accel_z, gyro.gyro_z );

    log_printf( &logger, "---------------------------------------\r\n" );

    Delay_ms( 3000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Lsm6Dsl

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
