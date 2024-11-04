
---
# RS485 Isolator 2 Click

RS485 Isolator 2 Click features ADM2867E a 5.7 kV rms signal and power isolated full duplex RS-485 transceiver.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs485isolator2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rs485-isolator-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Rs485Isolator2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rs485Isolator2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rs485isolator2_cfg_setup ( rs485isolator2_cfg_t *cfg ); 
 
- Initialization function.
> RS485ISOLATOR2_RETVAL rs485isolator2_init ( rs485isolator2_t *ctx, rs485isolator2_cfg_t *cfg );

#### Example key functions :

- Bit by bit write function.
> void rs485isolator2_send_bit_by_bit( rs485isolator2_t *ctx, char *command );
 
- Set RE ( reset ) pin state.
> void rs485isolator2_set_re_pin ( rs485isolator2_t *ctx, uint8_t state );

- Set DE ( cs ) pin state.
> void rs485isolator2_set_de_pin ( rs485isolator2_t *ctx, uint8_t state );

## Examples Description

> This example reads and processes data from RS485 Isolator 2 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and enables the selected mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs485isolator2_cfg_t cfg;

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

    rs485isolator2_cfg_setup( &cfg );
    RS485ISOLATOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs485isolator2_init( &rs485isolator2, &cfg );
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_RECEIVER
    rs485isolator2_set_re_pin( &rs485isolator2, RS485ISOLATOR2_ENABLE_RE );
    rs485isolator2_set_de_pin( &rs485isolator2, RS485ISOLATOR2_DISABLE_DE );
    log_info( &logger, "---- Receiver mode ----" );
#endif    
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator2_set_de_pin( &rs485isolator2, RS485ISOLATOR2_ENABLE_DE );
    rs485isolator2_set_re_pin( &rs485isolator2, RS485ISOLATOR2_DISABLE_RE );
    log_info( &logger, "---- Transmitter mode ----" );
#endif    
    Delay_ms ( 100 );
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs485isolator2_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator2_generic_write( &rs485isolator2, TEXT_TO_SEND, 8 );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif    
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs485Isolator2

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
