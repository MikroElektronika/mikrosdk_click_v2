
---
# CAN FD 2 click

CAN FD 2 Click is a HS CAN transceiver add on board, suitable for evaluation of TLE9255W CAN network transceiver from Infineon.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/canfd2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/can-fd-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the CanFd2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CanFd2 Click driver.

#### Standard key functions :

- `canfd2_cfg_setup` Config Object Initialization function.
```c
void canfd2_cfg_setup ( canfd2_cfg_t *cfg );
```
 
- `canfd2_init` Initialization function.
```c
err_t canfd2_init ( canfd2_t *ctx, canfd2_cfg_t *cfg );
```

#### Example key functions :

- `canfd2_generic_read` Generic read function.
```c
int32_t canfd2_generic_read ( canfd2_t *ctx, uint8_t *data_buf, uint16_t max_len );
```
 
- `canfd2_write_data` Generic write the byte of data function
```c
void canfd2_write_data ( canfd2_t *ctx, uint8_t reg_addr, uint8_t write_data );
```

- `canfd2_get_mode` Get operating mode function
```c
uint8_t canfd2_get_mode ( canfd2_t *ctx );
```

## Examples Description

> This example reads and processes data from CAN FD 2 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the click board for the selected mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    canfd2_cfg_t cfg;

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

    canfd2_cfg_setup( &cfg );
    CANFD2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd2_init( &canfd2, &cfg );
    
    CANFD2_SET_DATA_SAMPLE_EDGE;
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_TRANSMITTER
    canfd2_set_mode( &canfd2, CANFD2_OP_MODE_NORMAL );
    if ( CANFD2_OP_MODE_NORMAL == canfd2_get_mode ( &canfd2 ) )
    {
        log_info( &logger, "--- TRANSMITTER MODE ---" );
    }
    else
    {
        log_info( &logger, "--- ERROR ---" );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }
#else
    canfd2_set_mode( &canfd2, CANFD2_OP_MODE_RECEIVE_ONLY );
    if ( CANFD2_OP_MODE_RECEIVE_ONLY == canfd2_get_mode ( &canfd2 ) )
    {
        log_info( &logger, "--- RECEIVER MODE ---" );
    }
    else
    {
        log_info( &logger, "--- ERROR ---" );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }
#endif
    Delay_ms ( 100 );
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    canfd2_generic_write( &canfd2, DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) );
    log_info( &logger, "--- The message is sent ---" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    canfd2_process( &canfd2 );
    if ( app_buf_len > 0 ) 
    {
        Delay_ms ( 100 );
        canfd2_process ( &canfd2 );
        log_printf( &logger, "Received data: %s", app_buf );
        canfd2_clear_app_buf( );
    }
#endif
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CanFd2

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
