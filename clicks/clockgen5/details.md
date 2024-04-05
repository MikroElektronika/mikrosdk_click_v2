
---
# Clock Gen 5 click

> Clock Gen 5 Click is a compact add-on board that contains a digital programmable oscillator solution. This board features the LTC6903, a low-power self-contained digital frequency source providing a precision frequency from 1kHz to 68MHz set through a 3-wire SPI digital interface from Analog Devices. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/clockgen5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/clock-gen-5-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the ClockGen5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ClockGen5 Click driver.

#### Standard key functions :

- `clockgen5_cfg_setup` Config Object Initialization function.
```c
void clockgen5_cfg_setup ( clockgen5_cfg_t *cfg );
```

- `clockgen5_init` Initialization function.
```c
err_t clockgen5_init ( clockgen5_t *ctx, clockgen5_cfg_t *cfg );
```

#### Example key functions :

- `clockgen5_out_enable` Enable output function.
```c
void clockgen5_out_enable ( clockgen5_t *ctx, uint8_t en_out );
```

- `clockgen5_set_config` Set configuration function.
```c
void clockgen5_set_config ( clockgen5_t *ctx, uint8_t cfg );
```

- `clockgen5_set_freq` Set frequency function.
```c
void clockgen5_set_freq ( clockgen5_t *ctx, float freq );
```

## Example Description

> This is an example that demonstrates the use of the Clock Gen 5 click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - SPI, set output configuration CLK 180, also write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    clockgen5_cfg_t clockgen5_cfg;  /**< Click config object. */

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

    clockgen5_cfg_setup( &clockgen5_cfg );
    CLOCKGEN5_MAP_MIKROBUS( clockgen5_cfg, MIKROBUS_1 );
    err_t init_flag  = clockgen5_init( &clockgen5, &clockgen5_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... %d", init_flag );

        for ( ; ; );
    }
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    Enabling Output   \r\n" );
    clockgen5_out_enable( &clockgen5, CLOCKGEN5_OUTPUT_ENABLE);
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "   Set configuration   \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    clockgen5_set_config( &clockgen5, CLOCKGEN5_CFG_ON_CLK_180 );
    Delay_ms ( 500 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> In this example, we adjusts different frequencies every 3 sec. Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "        12.0 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 12000.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         8.0 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 8000.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         5.5 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 5500.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         2.7 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 2700.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         0.8 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 800.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         0.2 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 200.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ClockGen5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
