\mainpage Main Page
 
 

---
# Buck 11 click

Buck 11 click is a high-efficiency step-down converter which provides 3.3V on its output, derived from the connected power supply voltage, in the range from 4.2V to 60V. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck11_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/buck-11-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Buck11 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buck11 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck11_cfg_setup ( buck11_cfg_t *cfg ); 
 
- Initialization function.
> BUCK11_RETVAL buck11_init ( buck11_t *ctx, buck11_cfg_t *cfg );

- Click Default Configuration function.
> void buck11_default_cfg ( buck11_t *ctx );


#### Example key functions :

- ADC Read function
> uint16_t buck11_read_adc ( buck11_t *ctx );
 
- Get VOUT function
> buck11_get_vout ( buck11_t *ctx, uint8_t vout_resolution );

- Get Averaged VOUT function
> float buck11_get_averaged_vout ( buck11_t *ctx, uint8_t vout_resolution, uint8_t n_samples );

## Examples Description

> This aplication control voltage using Buck 11.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C serial interface and selects the desired VDD voltage value
> and VOUT value resolution (to get VOUT value in Volts).

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck11_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck11_cfg_setup( &cfg );
    BUCK11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck11_init( &buck11, &cfg );

    Delay_ms( 500 );
    
    buck11_set_vdd_value( 4.935 );
    vout_resol = BUCK11_VOUT_VOLTS;
    
    log_printf( &logger, "** Buck 11 is initialized ** \r\n" );
    log_printf( &logger, "************************************* \r\n" );
    Delay_ms( 200 );
}
  
```

### Application Task

> Reads the averaged VOUT voltage calculated to Volts by performing a 30 conversions
> in one measurement cycle. The measured results will be showed on the uart terminal every 300 milliseconds.

```c

void application_task ( )
{
    float vout_value;
    uint8_t vout_resol;

    vout_value = buck11_get_averaged_vout( &buck11, vout_resol, 30 );

    log_printf( &logger, "VOUT:  \r\n", vout_value );
    
    if (vout_resol == BUCK11_VOUT_VOLTS)
    {
        log_printf( &logger, " V \r\n" );
    }
    else
    {
        log_printf( &logger, " mV \r\n" );
    }
    
    log_printf( &logger, "************************************* \r\n" );
    Delay_ms( 300 );
}

```

## Note

> The user should measure the VDD voltage value and enter this measured value to the function as VDD value to get
> more accurate measurement. This VDD voltage is used as reference voltage for the AD conversion.
> The input voltage (VIN) range is from 4.2V to 60V.
> The output current (IOUT) value should not be greater than 1.5A.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck11

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
