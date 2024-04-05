\mainpage Main Page
 
---
# Buck-Boost 3 click

The Buck-Boost 3 click is a voltage converter regulator, which is able to provide a regulated voltage of 3.3V or 5V on the output, even when the input voltage drops under 3V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buckboost3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-boost-3-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the BuckBoost3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BuckBoost3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buckboost3_cfg_setup ( buckboost3_cfg_t *cfg ); 
 
- Initialization function.
> BUCKBOOST3_RETVAL buckboost3_init ( buckboost3_t *ctx, buckboost3_cfg_t *cfg );


#### Example key functions :

- This function enable/disable device.
> void buckboost3_enable ( buckboost3_t *ctx, uint8_t state );

 
- This function gets intterupt pin state.
> uint8_t buckboost3_get_interrupt_state ( buckboost3_t *ctx );

## Examples Description

> This application sets buck-boost voltages.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and enable device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buckboost3_cfg_t cfg;

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

    buckboost3_cfg_setup( &cfg );
    BUCKBOOST3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buckboost3_init( &buckboost3, &cfg );
    
    buckboost3_enable ( &buckboost3, BUCKBOOST3_DEVICE_ENABLE );
    log_info( &logger, " Device enabled " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> It checks if the input voltage is below the operating voltage.

```c
void application_task ( void )
{
    if ( !buckboost3_get_interrupt_state( &buckboost3 ) )
    {
        log_error( &logger, " Low input voltage !!!" );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BuckBoost3

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
