
---
# CAN FD4 click

The CAN FD 4 Click is a Click board™ that features the NCV7344D10R2G, a Controller Area Network (CAN) transceiver, from ON Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/canfd4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/can-fd-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the CanFd4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly from compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CanFd4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void canfd4_cfg_setup ( canfd4_cfg_t *cfg ); 
 
- Initialization function.
> CANFD4_RETVAL canfd4_init ( canfd4_t *ctx, canfd4_cfg_t *cfg );


#### Example key functions :

- Generic write function.
> void canfd4_generic_write ( canfd4_t *ctx, char *data_buf, uint16_t len );
 
- Set mode function.
> void canfd4_set_dev_mode ( canfd4_t *ctx, uint8_t mode );

- Generic read function.
> int32_t canfd4_generic_read ( canfd4_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example reads and processes data from CAN FD 4 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    canfd4_cfg_t cfg;

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

    canfd4_cfg_setup( &cfg );
    CANFD4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd4_init( &canfd4, &cfg );

    canfd4_set_dev_mode ( &canfd4, CANFD4_NORMAL_MODE );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    canfd4_process( );
#endif
#ifdef DEMO_APP_TRANSMITTER
    canfd4_generic_write( &canfd4, TEXT_TO_SEND, 8 );
    log_info( &logger, "--- The message is sent ---" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif 
}

```

The full application code, and ready to use projects can be installed directly from compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CanFd4

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
