\mainpage Main Page
 
---
# Smoke click

Smoke click carries the MAX30105 high-sensitivity optical sensor for smoke detection. The click is designed to run on either 3.3V or 5V power supply. It communicates with the target MCU over I2C interface with additional functionality provided by the INT pin on the mikroBUS™ line.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smoke_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/smoke-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Smoke Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Smoke Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void smoke_cfg_setup ( smoke_cfg_t *cfg ); 
 
- Initialization function.
> SMOKE_RETVAL smoke_init ( smoke_t *ctx, smoke_cfg_t *cfg );

- Click Default Configuration function.
> void smoke_default_cfg ( smoke_t *ctx );


#### Example key functions :

- Function is used to read desired interrupt specified by flag.
> uint8_t smoke_get_intrrupt ( smoke_t *ctx, uint8_t flag );
 
- Function is used to read the oldest Green value.
> uint32_t smoke_get_green_val ( smoke_t *ctx );

- Function is used to read the oldest RED value.
> uint32_t smoke_get_red_val ( smoke_t *ctx );

## Examples Description

>  This click includes internal LEDs, photodetectors, optical elements, and low-noise electronics 
> with ambient light rejection. The sensor can detect a wide variety of smoke particle sizes. 
> It also has an on-chip temperature sensor for calibrating the temperature dependence of the 
> particle sensing subsystem. The temperature sensor has an inherent resolution 0.0625°C.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver, applies "set registers check green values" settings,  "enable FIFO data ready interrupt" and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    smoke_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    smoke_cfg_setup( &cfg );
    SMOKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    smoke_init( &smoke, &cfg );

    smoke_default_cfg ( &smoke );

    deg_cel[ 0 ] = 176;
    deg_cel[ 1 ] = 67;
    deg_cel[ 2 ] = 0;

    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, "         Smoke  Click         \r\n" );
    log_printf( &logger, "------------------------------\r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> This example demonstrates the use of Smoke Click board. It reads reflected green values and
> temperature from an internal sensor and displays the results on USART terminal.
> It usualy takes two or three readings in order to get corect readings. Expect big values when you do.

```c

void application_task ( void )
{
    if ( smoke_get_intrrupt( &smoke, 1 ) & 0x40 )
    {
        grn_val = smoke_get_green_val( &smoke );
    }
    
    log_printf( &logger, "GREEN LED Pulse Amplitude : %u\r\n", grn_val );
    log_printf( &logger, "------------------------------\r\n" );
    
    temperature = smoke_read_temp_c( &smoke );
    
    log_printf( &logger, "Read Temperature : %.2f %s\r\n",  temperature, deg_cel );
    log_printf( &logger, "------------------------------\r\n" );

    Delay_ms( 1000 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Smoke

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
