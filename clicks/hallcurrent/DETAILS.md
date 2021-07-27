
---
# Hall Current click

Hall current click is a high precision current sensor. It carries a galvanically isolated TLI4970-D050T4 miniature magnetic digital current sensor that utilizes the Hall effect to measure electric current.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the HallCurrent Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HallCurrent Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hallcurrent_cfg_setup ( hallcurrent_cfg_t *cfg ); 
 
- Initialization function.
> HALLCURRENT_RETVAL hallcurrent_init ( hallcurrent_t *ctx, hallcurrent_cfg_t *cfg );


#### Example key functions :

- Generic read 16-bit data function
>  hallcurrent_read_data ( hallcurrent_t *ctx )
 
- Check status of read data function.
> hallcurrent_chack_status ( hallcurrent_t *ctx )

- Read electric current function
> hallcurrent_read_current ( hallcurrent_t *ctx )

## Examples Description

>  The application is current sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - SPI and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hallcurrent_cfg_setup( &cfg );
    HALLCURRENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent_init( &hallcurrent, &cfg );

    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger,  "       Hall Current     \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}
  
```

### Application Task

> This is a example which demonstrates the use of Hall Current Click board.

```c

void application_task ( void )
{
    float current_read_float;
    current_read_float = hallcurrent_read_current( &hallcurrent );
    
    Delay_ms( 100 );

    log_printf( &logger, " Current : %f ", current_read_float );
    log_printf( &logger, " [ A ] \r\n" );
    log_printf( &logger, "------------------------\r\n" );

    Delay_ms( 5000 );
} 

```
The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent

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
