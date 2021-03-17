\mainpage Main Page
 
 

---
# Balancer 5 click

Balancer 5 Click is an intelligent 2-cell Li-Ion battery charger, system power manager, and a battery fuel gauge Click board™. Balancer 5 click is based on BQ25887 controller which has some extra features enabling charging without too much hassle.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/balancer5_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/balancer-5-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Balancer5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Balancer5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void balancer5_cfg_setup ( balancer5_cfg_t *cfg ); 
 
- Initialization function.
> BALANCER5_RETVAL balancer5_init ( balancer5_t *ctx, balancer5_cfg_t *cfg );

- Click Default Configuration function.
> void balancer5_default_cfg ( balancer5_t *ctx );


#### Example key functions :

- This function sets charging status.
> void balancer5_charge ( balancer5_t *ctx, uint8_t state );


## Examples Description

> This demo performs neccessary initializations, reads ADC values from click registers and logs it.

**The demo application is composed of two sections :**

### Application Init 

> Initializes Click and Driver, Checks Device ID, starts charging, reads charge status registers and configures ADC.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    balancer5_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    balancer5_cfg_setup( &cfg );
    BALANCER5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    balancer5_init( &balancer5, &cfg );

    //  Device ID sanity check

    temp_data = balancer5_check_id( &balancer5 );

    if ( temp_data == BALANCER5_ERROR_ID )
    {
        log_info( &logger, "ID ERROR!!!" );
        for ( ; ; );
    }
    
    log_info( &logger, "***** ID OK *****" );

    //  Switch charger on

    balancer5_charge( &balancer5, BALANCER5_CHARGE_ON );

    //  Send configuration info to logger

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_CHARGER_STATUS_1 );
    charger_status_1_handler( temp_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_CHARGER_STATUS_2 );
    charger_status_2_handler( temp_data );

    //  Set default configuration

    balancer5_default_cfg ( &balancer5 );
   
}
  
```

### Application Task

Reads ADC values from registers and logs it.

```c

void application_task ( void )
{
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_IBUS_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_IBUS_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- IBUS: %umA\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_ICHG_ADC1 ); 
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_ICHG_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- ICHG: %umA\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VBAT_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VBAT_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- VBAT: %umV\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VBUS_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VBUS_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- VBUS: %umV\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VCELLTOP_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VCELLTOP_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- VCELLTOP: %umV\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VCELLBOT_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VCELLBOT_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- VCELLBOT: %umV\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_TS_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_TS_ADC0 );
    temp_uint_data |= temp_data;
    temp_float_data = temp_uint_data;
    temp_float_data *= 0.098;
    log_printf( &logger, "- TS: %.2f%%\r\n", temp_float_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_TDIE_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_TDIE_ADC0 );
    temp_uint_data |= temp_data;
    temp_float_data = temp_uint_data;
    temp_float_data *= 0.5;
    log_printf( &logger, "- TDIE: %.2f%s\r\n", temp_float_data, log_degree );
    
    log_printf( &logger, "____________________\r\n" );
    Delay_ms( 5000 );
}  

```

## Note

Additional functions charger_status_1_handler() and charger_status_2_handler() 
are used to log charger status 1 and 2. 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Balancer5

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
