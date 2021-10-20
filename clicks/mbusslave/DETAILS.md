
---
# M-Bus Slave click

M-Bus Slave Click is a Click board™ equipped with the TSS721A, a single chip transceiver developed by Texas Instruments for Meter-Bus applications according to EN1434-3 standard. The connection to the bus is polarity independent and serves as a slave node in the system. M-Bus Slave Click has full galvanic isolation with optocouplers to improve the reliability of the whole circuit.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mbusslave_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/m-bus-slave-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the MBusSlave Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MBusSlave Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mbusslave_cfg_setup ( mbusslave_cfg_t *cfg ); 
 
- Initialization function.
> MBUSSLAVE_RETVAL mbusslave_init ( mbusslave_t *ctx, mbusslave_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void mbusslave_generic_write ( mbusslave_t *ctx, char *data_buf, uint16_t len );
 
- Generic read function.
> int32_t mbusslave_generic_read ( mbusslave_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example reads and processes data from M-Bus Slave clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mbusslave_cfg_t cfg;

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
    Delay_ms( 100 );

    //  Click initialization.

    mbusslave_cfg_setup( &cfg );
    MBUSSLAVE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mbusslave_init( &mbusslave, &cfg );
    Delay_ms( 100 );
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    mbusslave_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    mbusslave_generic_write( &mbusslave, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms( 2000 );
#endif  
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.MBusSlave

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
