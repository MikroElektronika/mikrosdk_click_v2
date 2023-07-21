
---
# IR Gesture 3 click

> IR Gesture 3 Click is a compact add-on board that provides contactless gesture recognition. This board features the ADPD1080, a photometric front-end from Analog Devices. The IR Gesture 3 Click allows gesture recognition in two dimensions, with a built-in optical filter and a sharp visible light cutoff. It eliminates the need for external lenses and preserves the dynamic range of the sensor when placed under sunlight or indoor lighting. It does not require a precise alignment because its sensor maintains a linear response within the ±35° angular field of view.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irgesture3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ir-gesture-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the IR Gesture 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IR Gesture 3 Click driver.

#### Standard key functions :

- `irgesture3_cfg_setup` Config Object Initialization function.
```c
void irgesture3_cfg_setup ( irgesture3_cfg_t *cfg );
```

- `irgesture3_init` Initialization function.
```c
err_t irgesture3_init ( irgesture3_t *ctx, irgesture3_cfg_t *cfg );
```

- `irgesture3_default_cfg` Click Default Configuration function.
```c
err_t irgesture3_default_cfg ( irgesture3_t *ctx );
```

#### Example key functions :

- `irgesture3_set_mode` This function sets the device operating mode.
```c
err_t irgesture3_set_mode ( irgesture3_t *ctx, uint8_t mode );
```

- `irgesture3_set_adc_fsample` This function sets the sample frequency of the device.
```c
err_t irgesture3_set_adc_fsample ( irgesture3_t *ctx, uint16_t freq_hz );
```

- `irgesture3_get_gesture` This function waits up to IRGESTURE3_MAX_NUM_SAMPLES for an object to be detected and then calculates its gesture.
```c
err_t irgesture3_get_gesture ( irgesture3_t *ctx, uint8_t *gesture );
```

## Example Description

> This example demonstrates the use of IR Gesture 3 click board by processing the incoming gestures and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgesture3_cfg_t irgesture3_cfg;  /**< Click config object. */

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
    irgesture3_cfg_setup( &irgesture3_cfg );
    IRGESTURE3_MAP_MIKROBUS( irgesture3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irgesture3_init( &irgesture3, &irgesture3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRGESTURE3_ERROR == irgesture3_default_cfg ( &irgesture3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and processes all the incoming gestures and displays them on the USB UART.

```c
void application_task ( void )
{
    uint8_t gesture = 0;
    if ( IRGESTURE3_OK == irgesture3_get_gesture ( &irgesture3, &gesture ) )
    {
        log_printf( &logger, "\r\n Gesture: " );
        switch ( gesture )
        {
            case IRGESTURE3_GESTURE_CLICK:
            {
                log_printf( &logger, "CLICK\r\n" );
                break;
            }
            case IRGESTURE3_GESTURE_SWIPE_UP:
            {
                log_printf( &logger, "SWIPE UP\r\n" );
                break;
            }
            case IRGESTURE3_GESTURE_SWIPE_DOWN:
            {
                log_printf( &logger, "SWIPE DOWN\r\n" );
                break;
            }
            case IRGESTURE3_GESTURE_SWIPE_LEFT:
            {
                log_printf( &logger, "SWIPE LEFT\r\n" );
                break;
            }
            case IRGESTURE3_GESTURE_SWIPE_RIGHT:
            {
                log_printf( &logger, "SWIPE RIGHT\r\n" );
                break;
            }
            default:
            {
                log_printf( &logger, "UNKNOWN\r\n" );
                break;
            }
        }
    }
    else
    {
        log_printf( &logger, "\r\n No gesture detected!\r\n" );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IRGesture3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
