\mainpage Main Page
 
 

---
# LightRanger 2 click

LightRanger 2 click carries VL53L0X IC from STMicroelectronics, the world's 
smallest Time-of-Flight ranging and gesture detector sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lightranger2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lightranger-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the LightRanger2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LightRanger2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lightranger2_cfg_setup ( lightranger2_cfg_t *cfg ); 
 
- Initialization function.
> LIGHTRANGER2_RETVAL lightranger2_init ( lightranger2_t *ctx, lightranger2_cfg_t *cfg );

- Click Default Configuration function.
> void lightranger2_default_cfg ( lightranger2_t *ctx );


#### Example key functions :

- This function writes a byte of data to the targeted 8-bit register board.
> void lightranger2_write_byte ( lightranger2_t* ctx, uint8_t reg_address, uint8_t write_data );
 
- Function read a sequential data starting from the targeted 8-bit register.
> void lightranger2_read_bytes ( lightranger2_t* ctx, uint8_t reg_address, uint8_t* read_data, uint8_t n_bytes );

- Function gets a range measurement in millimeters when continuous mode is active.
> uint16_t lightranger2_get_range_continuous ( lightranger2_t* ctx );

## Examples Description

> This example measures the distance of the object from the sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver,enable Vl6180X sensor and sets default configuration for Vl6180X.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lightranger2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lightranger2_cfg_setup( &cfg );
    LIGHTRANGER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightranger2_init( &lightranger2, &cfg );
    lightranger2_default_cfg( &lightranger2 );
    
    lightranger2_start_continuous( &lightranger2, 0 );
    Delay_ms( 100 );
}
  
```

### Application Task

> Measures the distance of the object from the sensor and logs on terminal.

```c

void application_task ( void )
{
    uint16_t distance;
    
    distance = lightranger2_get_range_continuous( &lightranger2 );
    Delay_ms( 10 );
    
    if ( distance )
    {
        log_printf( &logger, "Distance: %u mm \r\n", distance );
        Delay_ms( 100 );
    }
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger2

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
