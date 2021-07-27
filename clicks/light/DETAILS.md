
---
# Light click

Light click is the add-on board with PD15-22CTR8 PIN photodiode, providing an effective and easy way to measure ambient light intensity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/light_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/light-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Light Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Light Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void light_cfg_setup ( light_cfg_t *cfg ); 
 
- Initialization function.
> LIGHT_RETVAL light_init ( light_t *ctx, light_cfg_t *cfg );



#### Example key functions :

- Generic write data function.
> void light_write_data ( light_t *ctx, uint8_t address, uint8_t write_command );
 
- Generic read data function.
> uint16_t light_read_data ( light_t *ctx );

- Function calculate percent.
> uint8_t light_calculate_percent ( light_t *ctx, uint16_t light_value );

## Examples Description

> This application return the ambient light intensity.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - SPI and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    light_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    light_cfg_setup( &cfg );
    LIGHT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    light_init( &light, &cfg );
}
  
```

### Application Task

> This is a example which demonstrates the use of Light Click board. Measured light intensity and calculate light intensity percent from sensor, results are being sent to the Usart Terminal where you can track their changes. All data logs on usb uart for aproximetly every 100 ms when the data value changes.

```c

void application_task ( void )
{
    uint16_t light_value;
    uint8_t light_percent;
    uint8_t percent_old = 1;

    light_value = light_read_data( &light );
    light_percent = light_calculate_percent( &light, light_value );
    

    if ( percent_old != light_percent )
    {
        log_printf( &logger, " Light Intensity : %d \r\n", light_percent );

        log_printf( &logger, " Light Value     : %d\r\n", light_value );

        percent_old = light_percent;
        Delay_100ms();
    }
    Delay_ms( 1000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Light

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
