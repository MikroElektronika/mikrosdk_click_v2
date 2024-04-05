
---
# UART 1-Wire click

UART 1-Wire click is used to convert standard UART or RS232 signals into 1-Wire® signals. Apart from other features such as the slew rate control for larger 1-Wire® busses, selectable data rate, an accurate self-calibrating time base, ESD protection and more, the main feature of the UART 1-Wire® click, is that it manages all the sensitive signal timings involved in 1-Wire® communication, allowing rapid development of UART to 1-Wire® applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uart1wire_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uart-1-wire-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the UART1Wire Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for UART1Wire Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void uart1wire_cfg_setup ( uart1wire_cfg_t *cfg ); 
 
- Initialization function.
> UART1WIRE_RETVAL uart1wire_init ( uart1wire_t *ctx, uart1wire_cfg_t *cfg );

#### Example key functions :

- This function sends an 8-bit command to the click module.
> void uart1wire_write_command ( uart1wire_t *ctx, uint8_t cmd );
 
- This function reads the temperature from DALLAS one wire temperature sensors.
> int8_t uart1wire_read_temperature ( uart1wire_t *ctx, float *temperature, uint8_t resolution );

- This function sends a reset pulse signal.
> void uart1wire_reset ( uart1wire_t *ctx );

## Examples Description

> This example reads and processes data from UART 1-Wire clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uart1wire_cfg_t cfg;

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

    uart1wire_cfg_setup( &cfg );
    UART1WIRE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uart1wire_init( &uart1wire, &cfg );
    
    Delay_ms ( 100 );
}
  
```

### Application Task

> Reads the temperature data from DALLAS temperature sensors and logs the results on the USB UART every second.

```c

void application_task ( void )
{
    float temp_f;
    uint8_t res_flag;
    
    res_flag = uart1wire_read_temperature ( &uart1wire, &temp_f, UART1WIRE_TEMP_SENSOR_RESOLUTION_9BIT );
    if ( res_flag == UART1WIRE_OK )
    {
        log_printf( &logger, " * Temperature:     %.2f C\r\n", temp_f );
        log_printf( &logger, "------------------------------\r\n" );
        Delay_ms ( 1000 );
    }
} 

```

## Note

> Connect only DQ and GND pins to the UART 1-Wire click connector.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.UART1Wire

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
