
---
# BATT-MAN Click

BATT-MAN Click is a very versatile battery operated power manager. When powered via mikroBUS™, it will charge the connected Li-Ion/Li-Po 3.7V battery, while providing the output voltage on all its outputs at the same time. The interesting feature of this device is that it can provide additional current to the connected load if the current provided from the mikroBUS™ socket is not enough.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/battman_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/batt-man-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : sep 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the BattMan Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BattMan Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void battman_cfg_setup ( battman_cfg_t *cfg ); 
 
- Initialization function.
> BATTMAN_RETVAL battman_init ( battman_t *ctx, battman_cfg_t *cfg );


#### Example key functions :

- Controls the operation of the Click.
> void battman_set_enable ( battman_t *ctx, uint8_t state );
 
- Charging indicator status.
> uint8_t battman_get_charging_indicator ( battman_t *ctx );

## Examples Description

> BATT-MAN Click is a very versatile battery operated power manager. When powered via mikroBUS,
> it will charge the connected Li-Ion/Li-Po 3.7V battery, while providing the output voltage 
> on all its outputs at the same time.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the Click driver and logger utility and enables the Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    battman_cfg_t cfg;

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

    battman_cfg_setup( &cfg );
    BATTMAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    battman_init( &battman, &cfg );
    
    battman_set_enable( &battman, 1 );
    log_printf( &logger, "BATT-MAN Click enabled.\r\n" );
    chg_flag = 0;
}
  
```

### Application Task

> Checks the charging indicator status, and in relation to its state it displays an appropriate message on USB UART.

```c

void application_task ( void )
{
    if ( !battman_get_charging_indicator ( &battman ) )
    {
        if ( chg_flag == 1 )
        {
            log_printf( &logger, "Charging enabled.\r\n" );
        }
        chg_flag = 0;
    }
    else
    {
        if ( chg_flag == 0 )
        {
            log_printf( &logger, "Charging disabled.\r\n" );
        }
        chg_flag = 1;
    }
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BattMan

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
