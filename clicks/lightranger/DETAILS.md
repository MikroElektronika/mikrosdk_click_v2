

---
# LightRanger click

LightRanger click is a proximity sensor carrying ST�s VL6180X IC. This chip is based on STs patented FlightSense technology...

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lightranger_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lightranger-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the LightRanger Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LightRanger Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lightranger_cfg_setup ( lightranger_cfg_t *cfg ); 
 
- Initialization function.
> LIGHTRANGER_RETVAL lightranger_init ( lightranger_t *ctx, lightranger_cfg_t *cfg );


#### Example key functions :

- This function writes a byte of data to given address.
> void lightranger_write_byte ( lightranger_t* ctx, uint16_t reg_addr, uint8_t write_command );
 
- This function reads register and calculates the light level in lux.
> float lightranger_get_ambiant_light ( lightranger_t* ctx, uint16_t als_gain_check );

- This function reads range result from register.
> uint16_t lightranger_get_distance ( lightranger_t* ctx );

## Examples Description

> This example collects data from the sensor and logs it to the terminal.


**The demo application is composed of two sections :**

### Application Init 

> Initialization driver for sensor Vl6180X and stars logging to terminal.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lightranger_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lightranger_cfg_setup( &cfg );
    LIGHTRANGER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightranger_init( &lightranger, &cfg );
    
    lightranger_default_cfg( &lightranger );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Measures and calculates ambient light intensity and distance from sensor,
> when the distance is changed log is updated,
> results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for approximately every 1 sec when the data value changes.

```c

void application_task ( void )
{
    uint8_t range_value;
    float lux_value;
    
    lightranger_start_single_shot_range_mode( &lightranger );
    
    lightranger_poll_range( &lightranger );
    lightranger_interrupts_clear( &lightranger );
    
    range_value = lightranger_get_distance( &lightranger );
    log_printf( &logger, "Proximity : %u mm\r\n", ( uint16_t ) range_value );

    lux_value = lightranger_get_ambiant_light( &lightranger, LIGHTRANGER_CMD_GAIN_1X );
    log_printf( &logger, "Ambient Light: %.2f lux\r\n", lux_value );

    log_printf( &logger, "*******************************************\r\n" );
    Delay_ms( 500 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger

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
