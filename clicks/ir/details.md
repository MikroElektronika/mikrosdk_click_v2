
---
# IR Click

> IR Click is an add-on board in mikroBUS form factor. It’s a compact and easy solution for adding infrared (IR) remote control module to your design.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ir_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ir-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : UART type


# Software Support

We provide a library for the IR Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IR Click driver.

#### Standard key functions :

- `ir_cfg_setup` Config Object Initialization function.
```c
void ir_cfg_setup ( ir_cfg_t *cfg );
```

- `ir_init` Initialization function.
```c
err_t ir_init ( ir_t *ctx, ir_cfg_t *cfg );
```

#### Example key functions :

- `ir_get_an_state` IR get AN pin state function.
```c
uint8_t ir_get_an_state ( ir_t *ctx );
```

- `ir_nec_send_command` IR NEC send data function.
```c
void ir_nec_send_command ( ir_t *ctx, uint8_t address, uint8_t command );
```

- `ir_nec_read_command` IR NEC data reading function.
```c
err_t ir_nec_read_command ( ir_t *ctx, uint8_t *address, uint8_t *command );
```

## Example Description

> This is an example that demonstrates the use of the IR Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - GPIO and Log.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ir_cfg_t ir_cfg;    /**< Click config object. */

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
    ir_cfg_setup( &ir_cfg );
    IR_MAP_MIKROBUS( ir_cfg, MIKROBUS_1 );
    err_t error_flag = ir_init( &ir, &ir_cfg );
    if ( ( UART_ERROR == error_flag ) || ( PWM_ERROR == error_flag ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    
    #ifdef IR_TRANSMITTER_MODE
        log_printf( &logger, "-  Transmitter mode   - \r\n" );
    #else
        log_printf( &logger, "-    Receiver mode    - \r\n" );
    #endif
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
}

```

### Application Task

> This example contains two parts :
> - Transmitter mode - Sends data using NEC protocol.
> - Receiver mode - Reads data that is been sent using NEC protocol and 
>                   displaying it on the UART terminal.

```c

void application_task ( void ) 
{
    #ifdef IR_TRANSMITTER_MODE
        log_printf( &logger, " Sending message." );
        
        for ( uint8_t cnt = 0; cnt < 8; cnt++ )
        {
            ir_nec_send_command( &ir, 0x00, tx_data[ cnt ] );
            log_printf( &logger, "." );
            Delay_ms ( 50 );
        }
        
        log_printf( &logger, "\r\n Message sent! \r\n" );
        log_printf( &logger, "- - - - - - - - - - - - \r\n" );
        Delay_ms ( 500 );
    #else
        uint8_t arr;
        char rx_data;
        
        err_t err_flag = ir_nec_read_command ( &ir, &arr, &rx_data );
        
        if ( IR_OK == err_flag )
        {
            log_printf( &logger, "%c", rx_data );
        }
        else
        {
            log_printf( &logger, "Read ERROR! \r\n" );
        }
        Delay_ms ( 50 );
    #endif
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IR

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
