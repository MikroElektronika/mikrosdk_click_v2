
---
# ProxFusion click

> ProxFusion click is a multifunctional capacitive and Hall-effect sensor device. This click can detect touch by using two onboard sensor pads, and it can sense a rotation angle of a magnetic field, parallel with the surface of the click board.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proxfusion_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/proxfusion-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the ProxFusion Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ProxFusion Click driver.

#### Standard key functions :

- `proxfusion_cfg_setup` Config Object Initialization function.
```c
void proxfusion_cfg_setup ( proxfusion_cfg_t *cfg ); 
```

- `proxfusion_init` Initialization function.
```c
err_t proxfusion_init ( proxfusion_t *ctx, proxfusion_cfg_t *cfg );
```

- `proxfusion_default_cfg` Click Default Configuration function.
```c
err_t proxfusion_default_cfg ( proxfusion_t *ctx );
```

#### Example key functions :

- `proxfusion_get_touch` Touch event
```c
uint8_t proxfusion_get_touch ( proxfusion_t *ctx );
```

- `proxfusion_set_system_reg` Sets system register
```c
err_t proxfusion_set_system_reg ( proxfusion_t *ctx, uint8_t cfg );
```

- `proxfusion_set_event_reg` Selecting events
```c
err_t proxfusion_set_event_reg ( proxfusion_t *ctx, uint8_t cfg );
```

## Examples Description

> This demo-app reads and displays touch events using ProxFusion click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proxfusion_cfg_t proxfusion_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    proxfusion_cfg_setup( &proxfusion_cfg );
    PROXFUSION_MAP_MIKROBUS( proxfusion_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proxfusion_init( &proxfusion, &proxfusion_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXFUSION_ERROR == proxfusion_default_cfg ( &proxfusion ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
} 
```

### Application Task

> Checks if a new touch event occurred and prints(logs) event message on usbuart.

```c
void application_task ( void )
{
    uint8_t touch = proxfusion_get_touch( &proxfusion );
    if ( 1 == touch )
    {
        log_printf( &logger, " Touch button 1 is pressed\r\n" );
    }
    else if ( 2 == touch )
    {
        log_printf( &logger, " Touch button 2 is pressed\r\n" );
    }
    else if ( 3 == touch )
    {
        log_printf( &logger, " Both touch buttons are pressed\r\n" );
    }
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ProxFusion

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
