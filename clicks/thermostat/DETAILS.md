
---
# Thermostat click

If you need a temperature sensor and relay in one device, you should look no further than Thermostat click.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermostat_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermostat-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermostat Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermostat Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermostat_cfg_setup ( thermostat_cfg_t *cfg ); 
 
- Initialization function.
> THERMOSTAT_RETVAL thermostat_init ( thermostat_t *ctx, thermostat_cfg_t *cfg );


#### Example key functions :

- Generic read 16-bit data function.
>  uint16_t thermostat_read_data( thermostat_t *ctx, uint8_t reg_address );
 
- Get temperature in degrees Celsius.
> float thermostat_get_temperature( thermostat_t *ctx );

- Convert temperature in degrees Celsius to Fahrenheit.
> float thermostat_convert_fahrenheit( thermostat_t *ctx, float temp_celsius );

- Set configuration function.
> void thermostat_set_configuration( thermostat_t *ctx, uint16_t config_value );

- Set temperature hysterezis function
> void thermostat_set_temp_hyst( thermostat_t *ctx, int8_t temp_hyst );

- Set referent temperature function.
> void thermostat_set_temp_ref( thermostat_t *ctx, int8_t temp_ref );

- Soft reset function.
> void thermostat_soft_reset( thermostat_t *ctx );

- Set on thermal switch function
> void thermostat_switch_on( thermostat_t *ctx );

- Set off thermal switch function
> void thermostat_switch_off( thermostat_t *ctx );

- Thermostat enabled function.
> void thermostat_enable( thermostat_t *ctx );

- Thermostat disabled function.
> void thermostat_disable( thermostat_t *ctx );

## Examples Description

> This application regulates value of temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C, soft reset sesnor, set default configuration and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermostat_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    thermostat_cfg_setup( &cfg );
    THERMOSTAT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermostat_init( &thermostat, &cfg );

    thermostat_soft_reset( &thermostat );
    Delay_ms( 100 );
    log_printf( &logger, "     Configuration    \r\n");

    thermostat_set_configuration( &thermostat, THERMOSTAT_DEFAULT_CONFIG );
    Delay_ms( 100 );
    log_printf( &logger, "----------------------\r\n" );
}
  
```

### Application Task

> This is a example which demonstrates the use of Thermostat Click board.

```c

void application_task ( void )
{
    float temperature;
    float limit_max = 25.0;
    float limit_min = 15.0;

    temperature = thermostat_get_temperature( &thermostat );

    log_printf( &logger, " Temperature : %.2f \r\n", temperature );

    if ( ( temperature < limit_max ) && ( temperature > limit_min ) )
    { 
        thermostat_switch_on(  &thermostat  );
    }
    else
    {   
        thermostat_switch_off(  &thermostat  );
        log_printf( &logger, "----------------------\r\n" );
    }
    Delay_ms( 2000 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermostat

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
