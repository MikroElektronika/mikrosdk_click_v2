\mainpage Main Page
 
 

---
# Buck Boost 2 Click

Buck-Boost 2 Click is an advanced DC-DC step-down/step-up regulator (buck/boost), which is able to provide regulated 5V on its output, regardless of the input voltage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buckboost2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/buck-boost-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the BuckBoost2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BuckBoost2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buckboost2_cfg_setup ( buckboost2_cfg_t *cfg ); 
 
- Initialization function.
> BUCKBOOST2_RETVAL buckboost2_init ( buckboost2_t *ctx, buckboost2_cfg_t *cfg );

- Click Default Configuration function.
> void buckboost2_default_cfg ( buckboost2_t *ctx );


#### Example key functions :

- This function sets the working mode.
> void buckboost2_set_mode ( buckboost2_t *ctx , uint8_t mode );
 
- This function powers OFF the chip
> void buckboost2_power_off ( buckboost2_t *ctx );

- This function powers on the chip.
> void buckboost2_power_on ( buckboost2_t *ctx  );

## Examples Description

> This application enables use of DC-DC step-down/step-up regulator (buck/boost).

**The demo application is composed of two sections :**

### Application Init 

> Initializes Driver init and turn ON chip and settings mode with improvement current.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buckboost2_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    buckboost2_cfg_setup( &cfg );
    BUCKBOOST2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buckboost2_init( &buckboost2, &cfg );

    buckboost2_power_on( &buckboost2 );
    buckboost2_set_mode( &buckboost2, BUCKBOOST2_WITH_IMPROVEMENT );
}
  
```

### Application Task

> The Click has a constant output voltage of 5V, no additional settings are required. 

```c

void application_task ( void )
{
    //  Task implementation.

     Delay_1sec( );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BuckBoost2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
