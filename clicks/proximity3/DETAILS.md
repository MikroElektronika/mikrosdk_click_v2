
 
 

---
# Proximity 3 click

Proximity 3 click is an intelligent proximity and light sensing device, which features the VCNL4200 sensor from Vishay - high sensitivity long distance proximity sensor (PS), ambient light sensor (ALS) and 940 nm IRED, all in one small package.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/proximity-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proximity3_cfg_setup ( proximity3_cfg_t *cfg ); 
 
- Initialization function.
> PROXIMITY3_RETVAL proximity3_init ( proximity3_t *ctx, proximity3_cfg_t *cfg );

- Click Default Configuration function.
> void proximity3_default_cfg ( proximity3_t *ctx );


#### Example key functions :

- This function writes data to the desired register.
> void proximity3_generic_write ( proximity3_t *ctx, uint8_t reg_address, uint16_t data_in );
 
- This function reads data from the desired register.
> uint16_t proximity3_generic_read ( proximity3_t *ctx, uint8_t reg_address );

- This function gets the data returned by the ambient light sensor.
> uint16_t proximity3_read_ambient_light_sensor ( proximity3_t *ctx );

- This function returns the proximity.
> uint8_t proximity3_read_proximity( proximity3_t *ctx );

- This function calculates distance using data reported by sensor.
> uint8_t proximity3_get_distance( proximity3_t *ctx );

- This function returns illuminance.
> uint16_t proximity3_get_illuminance( proximity3_t *ctx );

## Examples Description

> This example reads the data from the ambient light sensor
> and converts the data into digital form using calculations.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - I2C, initializes VCNL4100,
> write configuration register and starts to write log to Usart Terminal.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    proximity3_cfg_setup( &cfg );
    PROXIMITY3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity3_init( &proximity3, &cfg );

    // Default startup options for Ambient Light Sensor
    proximity3_generic_write( &proximity3, PROXIMITY3_ALS_CONF_REG, PROXIMITY3_ALS_CONF_CONFIG );
    Delay_ms( 10 );

    // Default startup options for Proximity
    proximity3_generic_write( &proximity3, PROXIMITY3_PS_CONF1_CONF2_REG, PROXIMITY3_PS_CONF1_CONF2_CONFIG );
    Delay_ms( 10 );
    proximity3_generic_write( &proximity3, PROXIMITY3_PS_CONF3_MS_REG, PROXIMITY3_PS_CONF3_MS_CONFIG );
    Delay_ms( 10 );

    // Set the proximity interrupt levels
    proximity3_generic_write( &proximity3, PROXIMITY3_PS_THDL_REG, PROXIMITY3_PS_THDL_CONFIG );
    Delay_10ms();
    proximity3_generic_write( &proximity3, PROXIMITY3_PS_THDH_REG, PROXIMITY3_PS_THDH_CONFIG );
    Delay_10ms();    

    // Check device ID
    value_id = proximity3_generic_read( &proximity3, PROXIMITY3_DEVICE_ID_REG );

    if ( value_id != PROXIMITY3_DEVICE_ID_VALUE )
    {
        log_printf( &logger, "        ERROR");
    }
    else
    {
        log_printf( &logger, "       Initialization" );
        log_printf( &logger, "--------------------------" );
    }

    Delay_100ms();
}
  
```

### Application Task

> This is a example which demonstrates the use of Proximity 3 Click board.
> Measured distance ( proximity ) and illuminance ( abmient light ) from sensor,
> results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 3 sec.

```c

void application_task ( void )
{
    result_proximity = proximity3_get_distance( &proximity3 );
    Delay_ms( 10 );

    log_printf( &logger, " Proximity:     %d cm", result_proximity );

    result_ambient_light = proximity3_get_illuminance( &proximity3 );
    log_printf( &logger, " Ambient Light:       %d lux", result_ambient_light );

    log_printf( &logger, "-----------------------------------------" );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity3

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
