\mainpage Main Page
 
---
# Thermo 12 click

Thermo 12 click is a Click board™ equipped with the sensor IC, which can digitize temperature measurements between -40°C and +150°C so that the temperature measurement data can be processed by the host MCU. Thermo 12 click provides an accuracy of ±0.2°C in the range from -10°C to +85°C.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo12_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/thermo-12-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo12 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo12 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo12_cfg_setup ( thermo12_cfg_t *cfg ); 
 
- Initialization function.
> THERMO12_RETVAL thermo12_init ( thermo12_t *ctx, thermo12_cfg_t *cfg );

- Click Default Configuration function.
> void thermo12_default_cfg ( thermo12_t *ctx );


#### Example key functions :

- This function writes data to the desired register.
> void thermo12_set ( thermo12_t *ctx, uint8_t reg_address, uint8_t *data_buf, uint8_t len );
 
- This function reads data from the desired register.
> void thermo12_get ( thermo12_t *ctx, uint8_t reg_address, uint8_t *data_buf, uint8_t len );

- This function returns INT pin state.
> uint8_t thermo12_int_get ( themot12_t *ctx );

- This function returns CT pin state.
> uint8_t thermo12_ct_get ( thermo12_t *ctx );

- This function issues soft reset command.
> void thermo12_soft_reset ( thermo12_t *ctx );

- This function reads temperature registers and calculates temperature value.
> float thermo12_get_temperature ( thermo12_t *ctx );

- This function returns status register value.
> uint8_t thermo12_get_status ( thermo12_t *ctx );

- This function sets high threshold value.
> uint8_t thermo12_set_high_threshold ( thermo12_t *ctx, float high_threshold );

- This function sets low threshold value.
> uint8_t thermo12_set_low_threshold ( thermo12_t *ctx, float low_threshold );

- This function sets critical threshold value.
> uint8_t thermo12_set_critical_threshold ( thermo12_t *ctx, float critical_threshold );

- This function sets hysteresis value.
> uint8_t thermo12_set_hysteresis ( thermo12_t *ctx, uint8_t hysteresis_value );


## Examples Description

> This application demonstrates the use of Thermo 12 Click to measure temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver, click board and sets thresholds.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo12_cfg_t cfg;
    uint8_t init_check;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    thermo12_cfg_setup( &cfg );
    THERMO12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo12_init( &thermo12, &cfg );
    Delay_ms( 500 );

    init_check = thermo12_default_cfg( &thermo12 );

    thermo12_set_high_threshold( 40.00 );
    thermo12_set_low_threshold( 10.00 );
    thermo12_set_critical_threshold( 70.00 );
    thermo12_set_hysteresis ( 0 );


    if (init_check == 0)
    {
        log_printf( &logger, "App init successful\r\n" );
    }
    else 
    {
        log_printf( &logger, "App init failed\r\n" );
    }

}
  
```

### Application Task

> Checks status register value, logs messages and temperature value.

```c

void application_task ( void )
{
    status_register = thermo12_get_status( &thermo12 );

    if ( ( status_register & THERMO12_RDY_MASK ) == THERMO12_RDY_MASK )
    {
        log_printf( &logger, "Temperature: normal\r\n" );
        log_printf( &logger, "Temperature: %.2f %s\r\n", thermo12_get_temperature( &thermo12 ), celsius );
        Delay_ms( 500 );
    }

    if ( ( status_register & THERMO12_LOW_MASK ) == THERMO12_T_LOW_MASK )
    {
        log_printf( &logger, "Temperature: low\r\n" );
        log_printf( &logger, "Temperature: %.2f %s\r\n", thermo12_get_temperature( &thermo12 ), celsius );
        Delay_ms( 500 );
    }
    if ( ( status_register & THERMO12_CRIT_MASK ) == THERMO12_T_CRIT_MASK )
    {
        log_printf( &logger, "Temperature: critical\r\n" );
        log_printf( &logger, "Temperature: %.2f %s\r\n", thermo12_get_temperature( &thermo12 ), celsius );
        Delay_ms( 500 );
    }
     if ( ( status_register & THERMO12_HIGH_MASK ) == THERMO12_T_HIGH_MASK )
    {
        log_printf( &logger, "Temperature: high\r\n" );
        log_printf( &logger, "Temperature: %.2f %s\r\n", thermo12_get_temperature( &thermo12 ), celsius );
        Delay_ms( 500 );
    }

}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo12

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
