 

---
# Magnetic Rotary click

Magnetic rotary click is a very accurate position sensing Click board™ which utilizes the HMC1512, a magnetic field displacement sensor IC. This integrated sensor uses two coplanar saturated-mode Wheatstone bridges which consist of four magneto-resistive elements per bridge. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneticrotary_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/magnetic-rotary-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the MagneticRotary Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MagneticRotary Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void magneticrotary_cfg_setup ( magneticrotary_cfg_t *cfg ); 
 
- Initialization function.
> MAGNETICROTARY_RETVAL magneticrotary_init ( magneticrotary_t *ctx, magneticrotary_cfg_t *cfg );

- Click Default Configuration function.
> void magneticrotary_default_cfg ( magneticrotary_t *ctx );


#### Example key functions :

- This function returns a 12bit result of AD conversion.
> uint16_t magnrotary_read_adc ( magneticrotary_t *ctx, uint8_t cmnd_byte );
 
- This function returns ADC voltage value calculated to millivolts, depending on the voltage selection.
> uint16_t magnrotary_out_volt_adc ( magneticrotary_t *ctx, uint8_t cmd_byte, uint16_t pwr_volt );

- This function returns a magnetic field angle calculated to degrees,from -90 to 90 degrees.
> double magnrotary_get_field_angle( magneticrotary_t *ctx, uint8_t cmd_byte );

## Examples Description

> This example reads a magnetic field angle calculated to degrees for channel A
> The angle can be measured in the range from -90 to 90 degrees.

**The demo application is composed of two sections :**

### Application Init 

> Initializes peripherals, pins, SPI interface for communication with the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneticrotary_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    magneticrotary_cfg_setup( &cfg );
    MAGNETICROTARY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneticrotary_init( &magneticrotary, &cfg );
    log_info(&logger, "Magnetic rotary successufully initialized!\r\n");

}

```

### Application Task

> Reads a magnetic field angle calculated to degrees for channel A in Single-Ended Mode and logs results.

```c

void application_task ( void )
{
    //  Task implementation.

    magn_angle = magnrotary_get_field_angle( &magneticrotary, MAGNROTARY_CHA_POS_GND_NEG | 
                                                              MAGNROTARY_MSB_ZEROS_ORDER );

    log_printf( &logger, "Angle:    %.2lf \r\n ", magn_angle );
    
    Delay_ms( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.MagneticRotary

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
