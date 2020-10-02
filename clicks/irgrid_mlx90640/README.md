\mainpage Main Page
 
 

---
# IR Grid MLX90640 click

IR Grid (MLX90640) click is a thermal imaging sensor. It has an array of 768 very sensitive factory calibrated IR elements (pixels), arranged in 32 rows of 24 pixels.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/ir-grid-click-group.png" height=300px>
</p>

> - [Product page - IR Grid 2 click](<https://www.mikroe.com/ir-grid-2-click>)
> - [Product page - IR Grid 3 click](<https://www.mikroe.com/ir-grid-3-click>)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the IrGridMlx90640 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IrGridMlx90640 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void irgrid_mlx90640_cfg_setup ( irgrid_mlx90640_cfg_t *cfg ); 
 
- Initialization function.
> IRGRID_MLX90640_RETVAL irgrid_mlx90640_init ( irgrid_mlx90640_t *ctx, irgrid_mlx90640_cfg_t *cfg );

- Click Default Configuration function.
> void irgrid_mlx90640_default_cfg ( irgrid_mlx90640_t *ctx );


#### Example key functions :

- Functions for gets Ambient temperature
> float irgrid_mlx90640_get_temp_ambient ( irgrid_mlx90640_t *ctx, uint16_t *frame_data );
 
- Functions for gets Pixels temperature
> void irgrid_mlx90640_get_pixel_temperature ( irgrid_mlx90640_t *ctx, float *temp_ambient, float *pixel_temp );

## Examples Description

> The demo application displays a reading of ambient temperature and 
> a 32x24 pixel object temperature matrix.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    irgrid_mlx90640_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    irgrid_mlx90640_cfg_setup( &cfg );
    IRGRID_MLX90640_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irgrid_mlx90640_init( &irgrid_mlx90640, &cfg );

    irgrid_mlx90640_default_cfg( &irgrid_mlx90640 );

    Delay_ms( 1000 );
    log_info( &logger, "---- Start measurement ----" );
}
```

### Application Task

> Reads the temperature of all pixels and creates a pixel temperature matrix
> that logs on usbuart every 500ms.

```c
void application_task ( void )
{
    uint16_t cnt;
    static float px_matrix[ 768 ];
    float temp_ambient;

    //  Task implementation.

    irgrid_mlx90640_get_pixel_temperature( &irgrid_mlx90640, &temp_ambient, px_matrix );

    log_printf( &logger, "** Ambient temperautre is %f C\r\n", temp_ambient );

    log_printf( &logger, "\r\n>> Pixel temperature matrix 32x24 <<\r\n" );

    for ( cnt = 0 ; cnt < 768 ; cnt++)
    {
        log_printf( &logger, " %.2f |", px_matrix[ cnt ] );
        Delay_1ms( );
        if ( ( ( cnt % 32 ) == 0 ) && ( cnt > 0 ) )
        {
            log_printf( &logger, "\r\n" );
        }
    }
    log_printf( &logger, "\r\n" );
    Delay_ms( 500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IrGridMlx90640

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
