
---
# Opto 7 Click

> Opto 7 Click is a compact add-on board that provides uncomplicated safety isolation from high voltage. This board features two ISOM8710, high-speed single-channel opto-emulators from Texas Instruments. The ISOM8710 opto-emulator has a diode-emulator input and digital output

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/opto7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/opto-7-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : UART/GPIO type


# Software Support

We provide a library for the Opto 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Opto 7 Click driver.

#### Standard key functions :

- `opto7_cfg_setup` Config Object Initialization function.
```c
void opto7_cfg_setup ( opto7_cfg_t *cfg );
```

- `opto7_init` Initialization function.
```c
err_t opto7_init ( opto7_t *ctx, opto7_cfg_t *cfg );
```

#### Example key functions :

- `opto7_generic_write` Opto 7 data writing function.
```c
err_t opto7_generic_write ( opto7_t *ctx, uint8_t *data_in, uint16_t len );
```

- `opto7_set_gp1_pin` Opto 7 set GP1 pin function.
```c
void opto7_set_gp1_pin( opto7_t *ctx, uint8_t pin_state );
```

- `opto7_get_gp2_pin` Opto 7 get GP2 pin function.
```c
uint8_t opto7_get_gp2_pin( opto7_t *ctx );
```

## Example Description

> This example demonstrates the use of Opto 7 Click board by processing
  the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initialization of UART LOG and GPIO pin, and UART drivers.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    opto7_cfg_t opto7_cfg;  /**< Click config object. */

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
    opto7_cfg_setup( &opto7_cfg );
    OPTO7_MAP_MIKROBUS( opto7_cfg, MIKROBUS_1 );
    
#if ( DEMO_EXAMPLE == EXAMPLE_GPIO )
    opto7_drv_interface_selection( &opto7_cfg, OPTO7_DRV_SEL_GPIO );
#else
    opto7_drv_interface_selection( &opto7_cfg, OPTO7_DRV_SEL_UART );
#endif
    
    if ( UART_ERROR == opto7_init( &opto7, &opto7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example is made of two parts:
> GPIO Example - The output pin is toggled every 5 seconds and input pin state is being tracked.
> UART Example - Device assigned as transmitter is sending message and receiver is reading it and displaying it on USB UART.

```c
void application_task ( void ) 
{
#if ( DEMO_EXAMPLE == EXAMPLE_GPIO )
    log_printf( &logger, " GP1 pin state HIGH \r\n" );
    opto7_set_gp1_pin( &opto7, OPTO7_PIN_STATE_HIGH );
     if ( OPTO7_PIN_STATE_HIGH == opto7_get_gp2_pin( &opto7 ) )
    {
        log_printf( &logger, " GP2 pin state HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " GP2 pin state LOW \r\n" );
    }
    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " GP1 pin state LOW \r\n" );
    opto7_set_gp1_pin( &opto7, OPTO7_PIN_STATE_LOW );
    if ( OPTO7_PIN_STATE_HIGH == opto7_get_gp2_pin( &opto7 ) )
    {
        log_printf( &logger, " GP2 pin state HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " GP2 pin state LOW \r\n" );
    }
    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
#if defined TRANSMITTER
    log_printf( &logger, " Message sent! \r\n" );
    opto7_generic_write( &opto7, TX_MESSAGE, strlen( TX_MESSAGE ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    if ( OPTO7_OK == opto7_process( &opto7 ) ) 
    {
        opto7_log_app_buf( );
        opto7_clear_app_buf( );
    }
#endif

#endif
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Opto7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
