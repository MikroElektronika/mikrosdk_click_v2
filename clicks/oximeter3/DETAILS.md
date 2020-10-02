
---
# Oximeter3 click

Oximeter 3 Click is a compact add-on board perfectly suited for measuring the blood oxygen saturation.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](https://www.mikroe.com/oximeter-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Oximeter3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Oximeter3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void oximeter3_cfg_setup ( oximeter3_cfg_t *cfg ); 
 
- Initialization function.
> OXIMETER3_RETVAL oximeter3_init ( oximeter3_t *ctx, oximeter3_cfg_t *cfg );

#### Example key functions :

- Generic read function.
> uint8_t oximeter3_generic_read ( oximeter3_t *ctx, uint8_t reg );
 
- Gets state of the int pin
> uint8_t oximeter3_get_int_status ( oximeter3_t *ctx );

- Generic function for reading als and proximity values
> uint16_t oximeter3_read_value ( oximeter3_t *ctx, uint8_t type_macro );

## Examples Description

> This demo app is ambient light sensor. 

**The demo application is composed of two sections :**

### Application Init 

> Check id status, configures device for previous selected mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    oximeter3_cfg_t cfg;

    uint8_t dev_status;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    oximeter3_cfg_setup( &cfg );
    OXIMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oximeter3_init( &oximeter3, &cfg );

    dev_status = oximeter3_generic_read( &oximeter3, OXIMETER3_REG_PRODUCT_ID );
    
    if ( dev_status != OXIMETER3_ID_VAL )
    {
        log_printf( &logger, " *****  ERROR!  ***** \r\n" );
        for ( ; ; );
    }

    dev_mode = OXIMETER3_HEART_RATE;

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_COMMAND,
                           OXIMETER3_CMD_MEASUREMENT_DISABLE );

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_LED_CURRENT,
                            OXIMETER3_LED_CURR_MAX );

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_RATE,
                            OXIMETER3_PROX_RATE_125_MPS );

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_MODULATOR_TIMING,
                            OXIMETER3_PROX_TIMING_FREQ_390p625_KHZ );

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_COMMAND,
                            OXIMETER3_CMD_MEASUREMENT_ENABLE |
                            OXIMETER3_CMD_PROX_PERIODIC_MEASUREMENT_ENABLE |
                            OXIMETER3_CMD_ALS_PERIODIC_MEASUREMENT_ENABLE );

    if ( OXIMETER3_HEART_RATE == dev_mode )
    {
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_LED_CURRENT, 12 );
    }

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
}
  
```

### Application Task

> Appliction measures values of heart rate or proximity and als value. 
> It depends of selected device mode. 

```c

void application_task ( void )
{
    if ( OXIMETER3_HEART_RATE == dev_mode )
    {
        rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_PROX );
        log_printf( &logger, "%d, \r\n", rd_val );
        Delay_ms( 3 );
    }
    else
    {
        rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_PROX );
        log_printf( &logger, " * Proximity: %d \r\n", rd_val );
        
        rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_ALS );
        log_printf( &logger, " * ALS: %d \r\n", rd_val );
        
        log_printf( &logger, "******************** \r\n" );
        
        Delay_ms( 500 );
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Oximeter3

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
