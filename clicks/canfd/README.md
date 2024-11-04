\mainpage Main Page
 
---
# CAN FD Click

CAN FD Click is a add-on board based on TLE9252V CAN network transceiver, designed for HS CAN networks up to 5 Mbit/s in automotive and industrial applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/canfd_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/can-fd-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the CanFd Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CanFd Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void canfd_cfg_setup ( canfd_cfg_t *cfg ); 
 
- Initialization function.
> CANFD_RETVAL canfd_init ( canfd_t *ctx, canfd_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void canfd_generic_write ( canfd_t *ctx, char *data_buf, uint16_t len );
 
- Generic read function.
> int32_t canfd_generic_read ( canfd_t *ctx, char *data_buf, uint16_t max_len );

- Operation mode.
> void canfd_set_operating_mode ( canfd_t *ctx, uint8_t op_mode );

## Examples Description

> This example reads and processes data from CAN FD clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and enables the Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    canfd_cfg_t cfg;

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

    canfd_cfg_setup( &cfg );
    CANFD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd_init( &canfd, &cfg );

    Delay_ms ( 500 );

#ifdef DEMO_APP_RECEIVER
    canfd_set_operating_mode( &canfd, CANFD_OPERATING_MODE_RECEIVE );
    log_info( &logger, "--- RECEIVER MODE ---" );
#endif
#ifdef DEMO_APP_TRANSMITTER
    canfd_set_operating_mode( &canfd, CANFD_OPERATING_MODE_NORMAL );
    log_info( &logger, "--- TRANSMITTER MODE ---" );
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
    canfd_process( );
#endif
#ifdef DEMO_APP_TRANSMITTER
    canfd_generic_write( &canfd, TEXT_TO_SEND, 8 );
    log_info( &logger, "--- The message is sent ---" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif 
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CanFd

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
