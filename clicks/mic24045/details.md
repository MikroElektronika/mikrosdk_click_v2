
---
# MIC24045 click

MIC24045 click carries MIC24045 I2C-programmable, high-efficiency, wide input range, 5A synchronous step-down regulator from Microchip.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mic24045_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mic24045-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Mic24045 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mic24045 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mic24045_cfg_setup ( mic24045_cfg_t *cfg ); 
 
- Initialization function.
> MIC24045_RETVAL mic24045_init ( mic24045_t *ctx, mic24045_cfg_t *cfg );

- Enable voltage output.
> void mic24045_enable( mic24045_t *ctx );


#### Example key functions :

- Get voltage.
> float mic24045_get_vout ( mic24045_t *ctx );
 
- Set voltage decimal.
> void mic24045_set_vout_decimal ( mic24045_t *ctx, uint8_t dec );

- Get status function.
> uint8_t mic24045_get_status ( mic24045_t *ctx );

## Examples Description

> This example demonstrates the use of MIC24045 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and enables the voltage output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic24045_cfg_t cfg;

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

    mic24045_cfg_setup( &cfg );
    MIC24045_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic24045_init( &mic24045, &cfg );
    
    mic24045_enable( &mic24045 );
    log_printf( &logger, " Output enabled!\r\n" );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Changes the voltage output every 2 seconds and displays the current set value on the USB UART.

```c

void application_task ( void )
{
    for ( uint16_t cnt = MIC24045_MIN_VOUT_DEC; cnt <= MIC24045_MAX_VOUT_DEC; cnt += 15 )
    {
        mic24045_set_vout_decimal( &mic24045, cnt );
        Delay_ms ( 500 );
        current_voltage = mic24045_get_vout( &mic24045 );
    
        log_printf( &logger, " VOUT:    ~%.3f V\r\n", current_voltage );
        log_printf( &logger, "------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 500 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic24045

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
