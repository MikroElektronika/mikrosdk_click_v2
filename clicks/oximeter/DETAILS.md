
---
# Oximeter click

Oximeter click is a versatile photometric Click board�, perfectly suited for
measuring the blood oxygen saturation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/oximeter_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/oximeter-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Oximeter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Oximeter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void oximeter_cfg_setup ( oximeter_cfg_t *cfg ); 
 
- Initialization function.
> OXIMETER_RETVAL oximeter_init ( oximeter_t *ctx, oximeter_cfg_t *cfg );

- Click Default Configuration function.
> void oximeter_default_cfg ( oximeter_t *ctx );


#### Example key functions :

- Function writes 16-bit data to the register.
 > uint8_t oxim_write_reg ( oximeter_t* ctx, uint8_t register_address,uint16_t transfer_data );
 
- Function performs the configuration and enables the interrupt on this slot.
> uint8_t oxim_set_time_slotA ( oximeter_t* ctx, uint8_t enable_slotA,
                                uint8_t enable_photodiode, uint8_t enable_LED,
                                uint8_t set_mode );

- Function determines which channel/channels be enabled.
> uint8_t oxim_enable_channels ( oximeter_t* ctx, uint8_t select_channel );

## Examples Description

> This example gets data when IR diode (LEDX2) is enabled, and after that gets data.
> Repeats operation 10 times and then calculates the average value for both results.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and performs the device configuration which puts Time Slot A 
> in enabled mode and LEDX2 (IR diode) to active state. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    oximeter_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    oximeter_cfg_setup( &cfg );
    OXIMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oximeter_init( &oximeter, &cfg );
    oximeter_default_cfg( &oximeter );
}
  
```

### Application Task

> Gets data from the sensor and logs on serial plot as graphic view.

```c

void application_task ( void )
{
    oxim_plot_display();
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Oximeter

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
