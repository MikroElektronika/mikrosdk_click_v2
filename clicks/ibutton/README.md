
---
# iButton Click

> [iButton Click](https://www.mikroe.com/?pid_product=MIKROE-3045) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3045&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : One Wire type

# Software Support

## Example Description

> This example demonstrates the use of the iButton Click boards by registering a DS1990A Serial Number iButton
key and then waiting until a key is detected on the reader and identifying if the key matches one of those stored in RAM.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.iButton

### Example Key Functions

- `ibutton_cfg_setup` Config Object Initialization function.
```c
void ibutton_cfg_setup ( ibutton_cfg_t *cfg );
```

- `ibutton_init` Initialization function.
```c
err_t ibutton_init ( ibutton_t *ctx, ibutton_cfg_t *cfg );
```

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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
