 
---
# Hall Current 3 click

Hall current 3 click is a very accurate current measurement Click board™, which utilizes the Hall effect to provide a precise and reliable measurement of reasonably high current. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-3-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the HallCurrent3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HallCurrent3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hallcurrent3_cfg_setup ( hallcurrent3_cfg_t *cfg ); 
 
- Initialization function.
> HALLCURRENT3_RETVAL hallcurrent3_init ( hallcurrent3_t *ctx, hallcurrent3_cfg_t *cfg );


#### Example key functions :

- This function calculates the current value.
> float hallcurrent3_getCurrent( hallcurrent3_t *ctx );
 
- This function read two bytes of data from the specified register.
> uint16_t hallcurrent3_read_data ( hallcurrent3_t *ctx, uint8_t reg );

## Examples Description

> The example starts off with the logger and click modules and then starts measuring and displaying current values.

**The demo application is composed of two sections :**

### Application Init 

> Initializes and configures the logger and click modules.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    hallcurrent3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hallcurrent3_cfg_setup( &cfg );
    HALLCURRENT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent3_init( &hallcurrent3, &cfg );
}
  
```

### Application Task

> Reads and displays current values every second.

```c
void application_task ( )
{
    float current_data;

    current_data = hallcurrent3_getCurrent( &hallcurrent3 );
    log_printf( &logger, "Current : %f mA\r\n" );

    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent3

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
