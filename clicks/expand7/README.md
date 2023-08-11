\mainpage Main Page
 
---
# Expand 7 click

EXPAND 7 Click is a compact add-on board that contains a multi-port I/O expander with bi-directional input/outputs or PWM outputs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand7_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/expand-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Expand7 Click driver.

#### Standard key functions :

- `expand7_cfg_setup` Config Object Initialization function.
```c
void expand7_cfg_setup ( expand7_cfg_t *cfg ); 
```

- `expand7_init` Initialization function.
```c
err_t expand7_init ( expand7_t *ctx, expand7_cfg_t *cfg );
```

#### Example key functions :

- `expand7_reset` Reset function
```c
void expand7_reset ( expand7_t *ctx );
```

- `expand7_write_all` Set all OUTPUT pins' logic levels function
```c
void expand7_write_all ( expand7_t *ctx, uint8_t value );
```

- `expand7_write_pin` Set a single OUTPUT pin's logic level function
```c
void expand7_write_pin ( expand7_t *ctx, uint8_t pin, uint8_t pin_val );
```

## Examples Description

> This example demonstrates the use of the EXPAND 7 click.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand7_cfg_t cfg;

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
    expand7_cfg_setup( &cfg );
    EXPAND7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand7_init( &expand7, &cfg );
    Delay_ms( 100 );
    
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   EXPAND 7 click   \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}
  
```

### Application Task

> This example shows the capabilities of the EXPAND 7 click by toggling each of the 40 available pins.

```c

void application_task ( void )
{
    expand7_write_all ( &expand7, 0xFF );
    log_printf( &logger, "All pins set to HIGH logic level!\r\n" );
    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms( 2000 );
    
    for ( uint8_t pin_num = 0; pin_num < 40; pin_num++ )
    {
        expand7_write_pin( &expand7, pin_num, EXPAND7_LOW );
        log_printf( &logger, "Pin %u is set to LOW logic level!\r\n", ( uint16_t ) pin_num );
        Delay_ms( 300 );
    }
    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand7

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
