\mainpage Main Page
  
---
# BUCK click

BUCK click is a buck switching regulator that accepts a wide input voltage range of up to 40V and steps it down to 3.3V or 5V. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-click)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Buck Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buck Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck_cfg_setup ( buck_cfg_t *cfg ); 
 
- Initialization function.
> BUCK_RETVAL buck_init ( buck_t *ctx, buck_cfg_t *cfg );

- Click Default Configuration function.
> void buck_default_cfg ( buck_t *ctx );


#### Example key functions :

- Setting the switching frequency function
> void buck_switch_frequency ( buck_t *ctx, uint8_t frequency );
 
- Select buck mode (Disable / Enable)
> void buck_set_mode ( buck_t *ctx, uint8_t mode );

- Get state internal comparator function
> uint8_t buck_get_power_good ( buck_t *ctx );

## Examples Description

> The demo application displays frequency change and voltage 
> regulation using a BUCK click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck_cfg_t cfg;

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

    buck_cfg_setup( &cfg );
    BUCK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck_init( &buck, &cfg );
    Delay_ms ( 100 );

    buck_software_reset( &buck );
    buck_default_cfg( &buck );
}
```

### Application Task

> This is a example which demonstrates the use of Buck Click board.
> Checks if it has reached the set output voltage and sets 
> a different frequency to the LT3976 chip every 5 sec.

```c
void application_task ( void )
{
    //  Task implementation.
    if ( buck_get_power_good( &buck ) == 1 )
    {
        log_info( &logger, "----  Power good output voltage!  ----" );
    }
    Delay_ms ( 1000 );

    log_info( &logger, "----  Switching frequency 400kHz!  ----" );
    buck_switch_frequency( &buck, BUCK_FREQ_400KHz );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_info( &logger, "----  Switching frequency 800kHz!  ----" );
    buck_switch_frequency( &buck, BUCK_FREQ_800KHz );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck

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
