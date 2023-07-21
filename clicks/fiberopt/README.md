\mainpage Main Page
 
---
# Fiber Opt click

> Fiber Opt click is a compact and easy solution for adding fiber-optic communication to your design. It features IF-D91 fiber-optic photodiode, IF-E97 fiber-optic LED diode as well as two operational amplifiers.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fiberopt_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/fiber-opt-33v-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : UART type


# Software Support

We provide a library for the FiberOpt Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for FiberOpt Click driver.

#### Standard key functions :

- `fiberopt_cfg_setup` Config Object Initialization function.
```c
void fiberopt_cfg_setup ( fiberopt_cfg_t *cfg ); 
```

- `fiberopt_init` Initialization function.
```c
err_t fiberopt_init ( fiberopt_t *ctx, fiberopt_cfg_t *cfg );
```

#### Example key functions :

- `fiberopt_generic_write` Generic single write function.
```c
err_t fiberopt_generic_write ( fiberopt_t *ctx, uint8_t *data_buf, uint16_t len );
```

- `fiberopt_generic_read` Generic single read function.
```c
err_t fiberopt_generic_read ( fiberopt_t *ctx, uint8_t *data_buf, uint16_t len );
```

## Examples Description

> This example demonstrates the use of an Fiber Opt click board by showing the communication between the two click boards.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes device and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    fiberopt_cfg_t cfg;

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
    fiberopt_cfg_setup( &cfg );
    FIBEROPT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fiberopt_init( &fiberopt, &cfg );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Depending on the selected application mode, it reads all the received data or 
sends the desired text message with the message counter once per second.

```c

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    fiberopt_generic_write( &fiberopt, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms( 1000 ); 
#else
    uint8_t rx_byte = 0;
    if ( 1 == fiberopt_generic_read( &fiberopt, &rx_byte, 1 ) )
    {
       log_printf( &logger, "%c", rx_byte );
    }
#endif
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.FiberOpt

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
