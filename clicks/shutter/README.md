\mainpage Main Page

---
# Shutter click

> Shutter Click is an adapter Click board™ used to implement an automated capturing feature. This Click board™ features one 3.5mm jack connector suitable for a camera connection with which the frame is captured. By combining two mikroBUS™ pins and the VO617A, a high-reliability phototransistor from Vishay Semiconductors used as a camera activation switch, activating the camera's Auto-Focus and the action of taking pictures is realized. This Click board™ allows you to expressly capture frames in a simple way for various types of photographic and security applications to capture those parts you need.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/shutter_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/shutter-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : GPIO type


# Software Support

We provide a library for the Shutter Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Shutter Click driver.

#### Standard key functions :

- `shutter_cfg_setup` Config Object Initialization function.
```c
void shutter_cfg_setup ( shutter_cfg_t *cfg );
```

- `shutter_init` Initialization function.
```c
err_t shutter_init ( shutter_t *ctx, shutter_cfg_t *cfg );
```

#### Example key functions :

- `shutter_set_auto_focus` This function sets the auto focus ON/OFF by setting the AF pin to desired logic state.
```c
void shutter_set_auto_focus ( shutter_t *ctx, uint8_t state );
```

- `shutter_set_shutter` This function sets the shutter ON/OFF by setting the SHT pin to desired logic state.
```c
void shutter_set_shutter ( shutter_t *ctx, uint8_t state );
```

- `shutter_take_picture` This function sets AF and SHT pins to desired states for taking pictures with or without auto focus function.
```c
void shutter_take_picture ( shutter_t *ctx, uint8_t auto_focus );
```

## Example Description

> This example demonstrates the use of Shutter click board by taking pictures with and without auto focus function.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    shutter_cfg_t shutter_cfg;  /**< Click config object. */

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
    shutter_cfg_setup( &shutter_cfg );
    SHUTTER_MAP_MIKROBUS( shutter_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == shutter_init( &shutter, &shutter_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Swithes ON the auto focus function and triggers the shutter to take the picture, then
swithes OFF the auto focus and triggers the shutter. The shutter is triggered every 13 seconds
approximately. All data is being logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf( &logger, " Take picture with auto focus\r\n\n" );
    shutter_take_picture ( &shutter, SHUTTER_STATE_ON );
    Delay_ms( 10000 );
    log_printf( &logger, " Take picture without auto focus\r\n\n" );
    shutter_take_picture ( &shutter, SHUTTER_STATE_OFF );
    Delay_ms( 10000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Shutter

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
