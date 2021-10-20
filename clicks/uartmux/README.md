\mainpage Main Page
 
---
# UART Mux click

The UART Mux click is a Click board™ that switches the UART pins (RX and TX) from the mikroBUS™ to one of the four available outputs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uartmux_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uart-mux-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the UartMux Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for UartMux Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void uartmux_cfg_setup ( uartmux_cfg_t *cfg ); 
 
- Initialization function.
> UARTMUX_RETVAL uartmux_init ( uartmux_t *ctx, uartmux_cfg_t *cfg );

#### Example key functions :

- Send command.
> void uartmux_send_command ( uartmux_t *ctx, char *command, uartmux_channel_t *channel );
 
- Set INT pin
> void uartmux_set_inhibit_communication ( uartmux_t *ctx, uint8_t state );

- Choose channel
> void uartmux_choose_channel ( uartmux_t *ctx, uartmux_channel_t *channel );

## Examples Description

> This example reads and processes data from UART Mux clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uartmux_cfg_t cfg;

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

    uartmux_cfg_setup( &cfg );
    UARTMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uartmux_init( &uartmux, &cfg );

    uartmux_set_inhibit_communication( &uartmux, UARTMUX_PIN_STATE_LOW );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    uartmux_process( );
#endif

#ifdef DEMO_APP_TRANSMITER
    uartmux_process( );

    channel.state_a = UARTMUX_STATE_A_CHANNEL_1;
    channel.state_b = UARTMUX_STATE_B_CHANNEL_1;

    if ( send_data_cnt == 2 )
    {
        uartmux_send_command( &uartmux, TEXT_TO_SEND, &channel );
        uartmux_process( );
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
    }
#endif
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.UartMux

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
