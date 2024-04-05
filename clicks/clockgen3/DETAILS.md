
---
# Clock Gen 3 click

Clock Gen 3 Click features a low power self-contained digital frequency source providing a precision frequency from 1kHz to 68MHz, set through a serial port.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/clockgen3_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/clock-gen-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the ClockGen3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https:///shop.mikroe.com/development-boards).

Package can be downloaded/installed directly from compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ClockGen3 Click driver.

#### Standard key functions :

- `clockgen3_cfg_setup` Config Object Initialization function.
```c
void clockgen3_cfg_setup ( clockgen3_cfg_t *cfg );
```
 
- `clockgen3_init` Initialization function.
```c
err_t clockgen3_init ( clockgen3_t *ctx, clockgen3_cfg_t *cfg );
```

#### Example key functions :

- `clockgen3_set_cs_pin` Sets CS pin state
```c
void clockgen3_set_cs_pin ( clockgen3_t *ctx, uint8_t state );
```
 
- `clockgen3_generic_write` Generic write function.
```c
void clockgen3_generic_write ( clockgen3_t *ctx, uint8_t *data_buf, uint8_t len );
```

- `clockgen3_set_freq` Sets Frequency
```c
void clockgen3_set_freq ( clockgen3_t *ctx, float freq );
```

## Examples Description

> This example demonstrates the use of Clock Gen 3 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    clockgen3_cfg_t cfg;

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

    // Click initialization.
    clockgen3_cfg_setup( &cfg );
    CLOCKGEN3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    clockgen3_init( &clockgen3, &cfg );

    clockgen3_config( &clockgen3, CLOCKGEN3_CFG_ON_CLK_180 );
    Delay_ms ( 500 );
}
  
```

### Application Task

> Sets different frequencies every 3 seconds and displays the set frequency on the USB UART.

```c

void application_task ( void )
{
    log_printf( &logger, ">> Set Freq = 12.000 MHz \r\n" );
    clockgen3_set_freq( &clockgen3, 12000.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, ">> Set Freq = 8.000 MHz \r\n" );
    clockgen3_set_freq( &clockgen3, 8000.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, ">> Set Freq = 5.500 MHz \r\n" );
    clockgen3_set_freq( &clockgen3, 5500.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, ">> Set Freq = 2.700 MHz \r\n" );
    clockgen3_set_freq( &clockgen3, 2700.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, ">> Set Freq = 800 KHz \r\n" );
    clockgen3_set_freq( &clockgen3, 800.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, ">> Set Freq = 200 KHz \r\n" );
    clockgen3_set_freq( &clockgen3, 200.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "---------------------------- \r\n" );
} 

```


The full application code, and ready to use projects can be installed directly from compilers IDE(recommended) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ClockGen3

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https:///shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https:///shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https:///shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https:///shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
