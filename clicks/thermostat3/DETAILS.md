
---
# Thermostat 3 click

Thermostat 3 Click is a general-purpose thermostat Click board™ designed to be used with any temperature sensor based on the MAX31855 sensor design.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermostat3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/thermostat-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Thermostat3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermostat3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermostat3_cfg_setup ( thermostat3_cfg_t *cfg ); 
 
- Initialization function.
> THERMOSTAT_RETVAL thermostat3_init ( thermostat3_t *ctx, thermostat3_cfg_t *cfg );

- Click Default Configuration function.
> void thermostat3_default_cfg ( thermostat3_t *ctx );


#### Example key functions :

- This function enables control of the relay.
> void thermostat3_relay_control ( thermostat3_t *ctx, uint8_t relay_pos );
 
- This function returns Fault data Value.
> uint8_t thermostat3_get_fault_data ( temp_vals_t *tmp, uint8_t err );

- This function returns 14-Bit Thermocouple Temperature Data
> float thermostat3_get_thermocouple_temperature ( temp_vals_t *tmp, uint8_t temp_in );

## Examples Description

> This application enables usage of the general purpose Thermostat click 
> to be used with temperature sensors.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermostat3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    Delay_ms( 100 );

    //  Click initialization.

    thermostat3_cfg_setup( &cfg );
    THERMOSTAT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermostat3_init( &thermostat3, &cfg );

    // Power on delay
    Delay_ms( 200 );
    log_printf( &logger, "---- Start Thermostat 3 ----\r\n" );
}
  
```

### Application Task

> Waits for valid user input and executes functions based on set of valid commands

```c

void application_task ( void )
{
    //  Task implementation.

    float internal_temp;
    float thermocouple_temp;

    thermostat3_process( &thermostat3, &temp_val );

    internal_temp = thermostat3_get_internal_temperature( &temp_val, THERMOSTAT3_TEMP_IN_CELSIUS );
    log_printf( &logger, "# Internal Temperature: %.2f", internal_temp );
    Delay_ms( 200 );
   
    thermocouple_temp = thermostat3_get_thermocouple_temperature( &temp_val, THERMOSTAT3_TEMP_IN_CELSIUS );
    log_printf( &logger, "# Thermocouple Temperature: %.2f", thermocouple_temp );
    Delay_ms( 200 );
    
    if( thermostat3.relay_flag == 1)
    {
        thermostat3.relay_flag = 0;
        thermostat3_relay_control( &thermostat3, THERMOSTAT3_RELAY_OFF );
        log_printf( &logger, "# Relay OFF\r\n" );
    }
    else
    {
        thermostat3.relay_flag = 1;
        thermostat3_relay_control( &thermostat3, THERMOSTAT3_RELAY_ON );
        log_printf( &logger, "# Relay ON\r\n" );
    }
    Delay_ms( 200 );

    if( thermostat3.fault_flag == 1 )
    {
        thermostat3.fault_flag = 0;
        log_printf( &logger, "# Fault status -- OFF\r\n" );
    }
    else
    {
        thermostat3.fault_flag = 1;
        log_printf( &logger, "# Fault status -- ON\r\n" );
    }
    Delay_ms( 200 );

    if( thermostat3.fault_flag == 1 )
        {
            thermostat3.f_error++;
            if( thermostat3.f_error > 3 )
            {
                thermostat3.f_error = 0;
            }
            display_fault( thermostat3.f_error );
            
            thermostat3.fault_status = thermostat3_get_fault_data( &temp_val, 0x01 << thermostat3.f_error );
            
            if ( thermostat3.fault_status == 1 )
            {
                log_printf( &logger, " -- ERROR\r\n" );
            }
            else
            {
                log_printf( &logger, " -- OK\r\n" );
            }
        }
}

```

## Note

> - Additional Functions :
>  -void _displayFault( uint8_t f_error )  - Display fault

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermostat3

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