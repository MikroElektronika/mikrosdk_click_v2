\mainpage Main Page
 
 
---
# H Bridge 5 click

The H-Bridge 5 Click is designed for control DC motors and inductiv loads. This Click board™ contains the MP6515GF-Z, a H-bridge motor driver from MPS, It features an Full H-Bridge driver with Internal safety features include over-current protection, input over-voltage protection, under voltage lockout (UVLO), and thermal shutdown.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the HBridge5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HBridge5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hbridge5_cfg_setup ( hbridge5_cfg_t *cfg ); 
 
- Initialization function.
> HBRIDGE5_RETVAL hbridge5_init ( hbridge5_t *ctx, hbridge5_cfg_t *cfg );

- Click Default Configuration function.
> void hbridge5_default_cfg ( hbridge5_t *ctx );


#### Example key functions :

- Function sets port.
> void hbridge5_set_port ( hbridge5_t *ctx, uint8_t port, uint8_t value );
 
- Puts motor into reverse motion.
> void hbridge5_reverse ( hbridge5_t *ctx );

- Puts motor into foreward motion.
> void hbridge5_foreward ( hbridge5_t *ctx );

## Examples Description

> This application controls DC motors and inductive loads.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver, configures all ports as output and writes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge5_cfg_t cfg;

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

    hbridge5_cfg_setup( &cfg );
    HBRIDGE5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge5_init( &hbridge5, &cfg );
    hbridge5_default_cfg( &hbridge5 );
}
  
```

### Application Task

> This example demonstrates the use of H-Bridge 5 Click board, by running dc motor forward, then stoping and then running it in reverse and stoping again.

```c

void application_task ( void )
{
    log_printf( &logger, "Mode - FORWARD\r\n" );
    hbridge5_forward( &hbridge5 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Mode - SLEEP\r\n" );
    hbridge5_sleep( &hbridge5, HBRIDGE5_DISABLE_ALL_OUTPUT_PORT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Mode - REVERSE\r\n" );
    hbridge5_reverse( &hbridge5 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Mode - SLEEP\r\n" );
    hbridge5_sleep( &hbridge5, HBRIDGE5_DISABLE_ALL_OUTPUT_PORT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

## Note

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge5

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
