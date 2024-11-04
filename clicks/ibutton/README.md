\mainpage Main Page

---
# iButton Click

> iButton Click - is an iButton™ probe Click board™. The iButton is a Analog Devices technology based on Analog's 1-Wire® communication protocol, and a chip usually packed in a robust stainless steel casing. The button-shaped iButton device has two contacts - the lid and the base. These contacts carry the necessary connections down to a sensitive silicone chip, embedded inside the metal button. When the iButton touches the reader probe on the Click board™, it establishes the communication with the host MCU, via the 1-Wire® interface. The communication is almost instant, so it is enough to press the iButton lightly to the probe contacts.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ibutton_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ibutton-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : One Wire type


# Software Support

We provide a library for the iButton Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for iButton Click driver.

#### Standard key functions :

- `ibutton_cfg_setup` Config Object Initialization function.
```c
void ibutton_cfg_setup ( ibutton_cfg_t *cfg );
```

- `ibutton_init` Initialization function.
```c
err_t ibutton_init ( ibutton_t *ctx, ibutton_cfg_t *cfg );
```

#### Example key functions :

- `ibutton_add_key` This function reads the ROM address from a DS1990A Serial Number iButton and stores it in the ctx->key_rom buffer.
```c
err_t ibutton_add_key ( ibutton_t *ctx );
```

- `ibutton_remove_keys` This function removes all stored keys by clearing the ctx->key_rom buffer.
```c
void ibutton_remove_keys ( ibutton_t *ctx );
```

- `ibutton_check_key` This function reads the ROM address from a DS1990A Serial Number iButton and checks if it is already stored in the ctx->key_rom buffer.
```c
err_t ibutton_check_key ( ibutton_t *ctx );
```

## Example Description

> This example demonstrates the use of the iButton Click boards by registering a DS1990A Serial Number iButton
key and then waiting until a key is detected on the reader and identifying if the key matches one of those stored in RAM.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and registers a new DS1990A Serial Number iButton key and stores it in RAM.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ibutton_cfg_t ibutton_cfg;  /**< Click config object. */

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
    ibutton_cfg_setup( &ibutton_cfg );
    IBUTTON_MAP_MIKROBUS( ibutton_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == ibutton_init( &ibutton, &ibutton_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ibutton_register_keys ( &ibutton, NUMBER_OF_KEYS );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits until a key is detected on the reader, and checks if there's a key found in the library that matches the one it has just read.
All data is being logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    err_t error_flag = IBUTTON_OK;
    ibutton_led_indication ( &ibutton, IBUTTON_LED_DISABLE );
    log_printf( &logger, " >>> Waiting for a key <<<\r\n" );
    do
    {
        ibutton_led_indication ( &ibutton, IBUTTON_LED_WAIT_KEY );
        error_flag = ibutton_check_key ( &ibutton );
    }
    while ( IBUTTON_ERROR == error_flag );

    ibutton_led_indication ( &ibutton, IBUTTON_LED_DISABLE );
    if ( IBUTTON_OK == error_flag )
    {
        log_printf( &logger, " MATCH, access allowed!\r\n" );
        ibutton_led_indication ( &ibutton, IBUTTON_LED_SUCCESS );
    }
    else if ( IBUTTON_KEY_NO_MATCH == error_flag )
    {
        log_printf( &logger, " NO MATCH, access denied!\r\n" );
        ibutton_led_indication ( &ibutton, IBUTTON_LED_WRONG_KEY );
    }
    ibutton_led_indication ( &ibutton, IBUTTON_LED_DISABLE );
    log_printf( &logger, "--------------------------------\r\n\n" );
    Delay_ms ( 500 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.iButton

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
