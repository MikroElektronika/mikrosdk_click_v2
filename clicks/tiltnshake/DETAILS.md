
---
# TILT-n-SHAKE click

TILT-n-SHAKE click carries Freescale’s MMA8491Q IC. It’s a multifunctional 3-axis digital accelerometer that can also be configured as a 45-degree Tilt sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tiltnshake_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/tilt-n-shake-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TiltNshake Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TiltNshake Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void tiltnshake_cfg_setup ( tiltnshake_cfg_t *cfg ); 
 
- Initialization function.
> TILTNSHAKE_RETVAL tiltnshake_init ( tiltnshake_t *ctx, tiltnshake_cfg_t *cfg );


#### Example key functions :

- Function for read status and axis
> void tiltnshake_read_status_and_axis ( tiltnshake_t *ctx, uint8_t *status, uint16_t *out_x, uint16_t *out_y, uint16_t *out_z );
 
- Function for conversion
> void tiltnshake_conversion ( uint16_t *out_x, uint16_t *out_y, uint16_t *out_z, float *out_x_flo, float *out_y_flo, float *out_z_flo );

- Function for enabled chip
> void tiltnshake_enable ( tiltnshake_t *ctx, uint8_t en );

## Examples Description

> This application is multifunctional 3-axis digital accelerometer that can also be configured as a 45-degree Tilt sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device init.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    tiltnshake_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    tiltnshake_cfg_setup( &cfg );
    TILTNSHAKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tiltnshake_init( &tiltnshake, &cfg );
}
  
```

### Application Task

> Reads every tilt and shake and logs to USBUART_A.

```c
void application_task ( )
{
    uint8_t tiltnshake_status;
    float tiltnshake_out_x_float;
    float tiltnshake_out_y_float;
    float tiltnshake_out_z_float;
    uint16_t tiltnshake_out_x;
    uint16_t tiltnshake_out_y;
    uint16_t tiltnshake_out_z;

    tiltnshake_enable( &tiltnshake, TILTNSHAKE_ENABLE );
    tiltnshake_read_status_and_axis( &tiltnshake, &tiltnshake_status, &tiltnshake_out_x, &tiltnshake_out_y, &tiltnshake_out_z );
    tiltnshake_enable( &tiltnshake, TILTNSHAKE_DISABLE );

    if ( tiltnshake_status == TILTNSHAKE_DATA_READY )
    {
        tiltnshake_conversion
        ( 
             &tiltnshake_out_x, 
             &tiltnshake_out_y, 
             &tiltnshake_out_z,
             &tiltnshake_out_x_float, 
             &tiltnshake_out_y_float, 
             &tiltnshake_out_z_float 
        ); 
        
        log_printf( &logger, " \r\n" );
        log_printf( &logger, "X_out = %.2f \r\n", tiltnshake_out_x_float );
        log_printf( &logger, "Y_out = %.2f\r\n", tiltnshake_out_y_float );
        log_printf( &logger, "Z_out = %.2f\r\n", tiltnshake_out_z_float );
        log_printf( &logger, "-----------------------------------------------\r\n");
        Delay_ms( 500 );
    }
    Delay_ms( 1700 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TiltNshake

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
