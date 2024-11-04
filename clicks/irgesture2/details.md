
---
# IR Gesture 2 Click

> IR Gesture 2 Click is a compact add-on board that provides contactless gesture recognition. This board features the MAX25405, a data-acquisition system for the gesture and proximity sensing from Analog Devices. Detection distance is improved by integrating a complete optical system with a lens, aperture, visible light filter, and a 6x10 photodetector array. The proximity, hand detection, and gesture recognition functions of the MAX25405 operate by detecting the light reflected from the controlled IR-LED light sources driven directly from the MAX25405. It can also detect these gestures even when exposed to bright ambient light and process data from the sensor through an SPI interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irgesture2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ir-gesture-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the IR Gesture 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IR Gesture 2 Click driver.

#### Standard key functions :

- `irgesture2_cfg_setup` Config Object Initialization function.
```c
void irgesture2_cfg_setup ( irgesture2_cfg_t *cfg );
```

- `irgesture2_init` Initialization function.
```c
err_t irgesture2_init ( irgesture2_t *ctx, irgesture2_cfg_t *cfg );
```

- `irgesture2_default_cfg` Click Default Configuration function.
```c
err_t irgesture2_default_cfg ( irgesture2_t *ctx );
```

#### Example key functions :

- `irgesture2_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t irgesture2_get_int_pin ( irgesture2_t *ctx );
```

- `irgesture2_read_pixels` This function reads the raw ADC values of entire 60-pixel IR photodiode array.
```c
err_t irgesture2_read_pixels ( irgesture2_t *ctx, int16_t *pixels, bool flip_pixels );
```

- `irgesture2_write_register` This function writes a data byte to the selected register by using SPI serial interface.
```c
err_t irgesture2_write_register ( irgesture2_t *ctx, uint8_t reg, uint8_t data_in );
```

## Example Description

> This example demonstrates the use of IR Gesture 2 Click board by reading and displaying the raw ADC values of entire 60-pixel IR photodiode array.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgesture2_cfg_t irgesture2_cfg;  /**< Click config object. */

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
    irgesture2_cfg_setup( &irgesture2_cfg );
    IRGESTURE2_MAP_MIKROBUS( irgesture2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == irgesture2_init( &irgesture2, &irgesture2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRGESTURE2_ERROR == irgesture2_default_cfg ( &irgesture2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for an end of conversion interrupt and then reads the raw ADC values of entire
60-pixel IR photodiode array and displays the results on the USB UART as a 10x6 matrix every 100ms approximately.

```c
void application_task ( void )
{
    // Wait for an end of conversion interrupt
    while ( irgesture2_get_int_pin ( &irgesture2 ) );
    
    int16_t pixels[ IRGESTURE2_NUM_SENSOR_PIXELS ];
    if ( IRGESTURE2_OK == irgesture2_read_pixels ( &irgesture2, pixels, false ) )
    {
        for ( uint8_t cnt = 0; cnt < IRGESTURE2_NUM_SENSOR_PIXELS; cnt++ )
        {
            if ( 0 == ( cnt % IRGESTURE2_SENSOR_X_SIZE ) )
            {
                log_printf( &logger, "\r\n" );
            }
            log_printf( &logger, "%d\t", pixels[ cnt ] );
        }
        log_printf( &logger, "\r\n" );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IRGesture2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
