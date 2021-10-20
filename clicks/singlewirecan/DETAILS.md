
---
# Single Wire CAN click

Single Wire CAN Click is a compact add-on board that contains an IC for a single wire data link capable of operating with various protocols such as the Controller Area Network (CAN). This board features the NCV7356D1R2G, Single Wire CAN transceiver from ON Semiconductor, which operates from a supply voltage from 5V to 27V with bus speed up to 40 kbps. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/singlewirecan_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/single-wire-can-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART type


# Software Support

We provide a library for the SingleWireCan Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SingleWireCan Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void singlewirecan_cfg_setup ( singlewirecan_cfg_t *cfg ); 
 
- Initialization function.
> SINGLEWIRECAN_RETVAL singlewirecan_init ( singlewirecan_t *ctx, singlewirecan_cfg_t *cfg );


#### Example key functions :

- The function set desired operating mode of NCV7356 Single Wire CAN Transceiver
> void singlewirecan_set_operating_mode ( singlewirecan_t *ctx, uint8_t op_mode );
 
- This function write specified number of bytes
> void singlewirecan_generic_write ( singlewirecan_t *ctx, char *data_buf, uint16_t len );

- This function reads a desired number of data bytes.
> int32_t singlewirecan_generic_read ( singlewirecan_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example demonstrate the use of Single Wire CAN click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the click for the normal operation mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    singlewirecan_cfg_t cfg;

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

    singlewirecan_cfg_setup( &cfg );
    SINGLEWIRECAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    singlewirecan_init( &singlewirecan, &cfg );
    Delay_ms( 100 );

    singlewirecan_set_operating_mode( &singlewirecan, SINGLEWIRECAN_OPERATING_MODE_NORMAL );
    log_info( &logger, "---- Normal Operation Mode ----" );
    Delay_ms( 100 );
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    singlewirecan_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    singlewirecan_generic_write( &singlewirecan, TEXT_TO_SEND, 8 );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms( 2000 );
#endif    
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.SingleWireCan

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
