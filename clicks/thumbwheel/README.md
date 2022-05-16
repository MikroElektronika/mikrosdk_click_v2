\mainpage Main Page

---
# Thumbwheel click

> Thumbwheel click is a mikroBUS add-on board with a 10-position rotary sprocket connected to a 1-Wire 8-Channel Addressable Switch.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thumbwheel_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thumbwheel-click)

---


#### Click library

- **Author**        : Aleksandra Cvjeticanin
- **Date**          : Mar 2022.
- **Type**          : One Wire type


# Software Support

We provide a library for the Thumbwheel Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thumbwheel Click driver.

#### Standard key functions :

- `thumbwheel_cfg_setup` Config Object Initialization function.
```c
void thumbwheel_cfg_setup ( thumbwheel_cfg_t *cfg );
```

- `thumbwheel_init` Initialization function.
```c
err_t thumbwheel_init ( thumbwheel_t *ctx, thumbwheel_cfg_t *cfg );
```

#### Example key functions :

- `thumbwheel_get_position` This function gets the position of the rotary sprocket. 
```c
err_t thumbwheel_get_position ( thumbwheel_t *ctx, uint8_t *position ); 
```

## Example Description

> This example demonstrates the use of Thumbwheel click board by displaying the exact position of the rotary sprocket. 

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and checks the communication.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thumbwheel_cfg_t thumbwheel_cfg;  /**< Click config object. */

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
    thumbwheel_cfg_setup( &thumbwheel_cfg );
    THUMBWHEEL_MAP_MIKROBUS( thumbwheel_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == thumbwheel_init( &thumbwheel, &thumbwheel_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THUMBWHEEL_ERROR == thumbwheel_check_communication ( &thumbwheel ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Demonstrates the usage of thumbwheel_get_position function which gives the exact position of the rotary sprocket. The position will be displayed on the UART Terminal.

```c
void application_task ( void ) 
{
    static uint8_t old_position = 0xFF;
    uint8_t position; 
    
    if ( ( THUMBWHEEL_OK == thumbwheel_get_position ( &thumbwheel, &position ) ) && 
         ( old_position != position ) )
    {
        log_printf( &logger, " Position: %u \r\n\n", ( uint16_t ) position );
        old_position = position; 
    }
    Delay_ms( 100 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thumbwheel

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
