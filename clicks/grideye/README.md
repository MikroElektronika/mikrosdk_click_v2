\mainpage Main Page
 
---
# Grid Eye click

Grid-EYE click is a 8x8 thermal array sensor-detector that carries the AMG8853 infrared array sensor from Panasonic.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grideye_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/grid-eye-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Grideye Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Grideye Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void grideye_cfg_setup ( grideye_cfg_t *cfg ); 
 
- Initialization function.
> GRIDEYE_RETVAL grideye_init ( grideye_t *ctx, grideye_cfg_t *cfg );

- Click Default Configuration function.
> void grideye_default_cfg ( grideye_t *ctx );


#### Example key functions :

- Generic write function.
> void grideye_generic_write ( grideye_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
 
- Generic read function.
> void grideye_generic_read ( grideye_t *ctx,  uint8_t reg, uint8_t *data_buf, uint8_t len );

- Write data function
> void grideye_write_data ( grideye_t *ctx, uint8_t wr_addr, uint16_t wr_data );

## Examples Description

> 64 individual thermal sensors build an image on a display. The detecting distance is 5m.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver, applies default settings, and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    grideye_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    grideye_cfg_setup( &cfg );
    
    GRIDEYE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    grideye_init( &grideye, &cfg );

    grideye_default_cfg ( &grideye );
}
  
```

### Application Task

> This example demonstrates the use of Grid-EYE click board by reading full grid and displaying values via USART terminal.

```c

void application_task ( void )
{
    uint8_t i;
    uint8_t j;
    uint16_t grid_array[ 64 ];
    uint16_t grid_array_tmp;

    grideye_read_grid( &grideye, &grid_array );

    for( i = 1; i < 9; i++ )
    {
        for( j = 1; j < 9; j++ )
        {
            log_printf( &logger, "| " );
            grid_array_tmp = grid_array[ i * j ];
            
            log_printf( &logger, "%d ", grid_array_tmp );
        }
        log_printf( &logger, " \r\n" );
        log_printf( &logger, "-------------------------------------- \r\n" );
    }
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Grideye

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
