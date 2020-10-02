\mainpage Main Page
 
 

---
# Hall Current 6 click

Hall Current 6 Click is a very accurate current measurement Click board™, based on the ACS723 IC. This IC is a galvanically isolated current sensor, which utilizes the Hall-effect principle.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent6_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/hall-current-6-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the HallCurrent6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HallCurrent6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hallcurrent6_cfg_setup ( hallcurrent6_cfg_t *cfg ); 
 
- Initialization function.
> HALLCURRENT6_RETVAL hallcurrent6_init ( hallcurrent6_t *ctx, hallcurrent6_cfg_t       *cfg );

- Click Default Configuration function.
> void hallcurrent6_default_cfg ( hallcurrent6_t *ctx );


#### Example key functions :

- Config Object Initialization function.
> This function initializes click configuration structure to init state.
 
- Initialization function.
> This function initializes all necessary pins and peripherals used for this            click.

- Generic write function.
> This function writes data from the desired register.

- Reads ADC current data
> The value of 2065 is 0A

- Reads current data
> Bipolar current sensor - nominal 400mV/A or 5A full scale

## Examples Description

> 
> This application reads current data.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initializations driver init
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent6_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- App Init ----" );

    //  Click initialization.

    hallcurrent6_cfg_setup( &cfg );
    HALLCURRENT6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent6_init( &hallcurrent6, &cfg );

    log_info( &logger, "---- App Init Done ----" );
}
  
```

### Application Task

>
> Reads Current data in mA and logs this data to USBUART every 1 sec.
> 

```c

void application_task ( void )
{
    uint8_t reg; 
    uint8_t *data_buf;
    float current;

    current = hallcurrent6_get_current(&hallcurrent6, reg, &data_buf);

    log_printf( &logger, " Current value: %f.2  mA \r\n" , current);

    log_printf( &logger, " --------------------------------- \r\n" );
    Delay_ms( 1000 );
}  

```

## Note

> 
> <NOTE>
> 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent6

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
