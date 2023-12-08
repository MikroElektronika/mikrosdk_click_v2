
---
# Thunder EMU click

> Thunder EMU Click is a compact add-on board that can be used to emulate lightning. This board features circuits that generate an RF signal that mimics lightning strikes. It is a thunder emulator board that allows you to mimic lightning signals that can represent different distances, thus enabling you to debug your lightning detector application for all kinds of scenarios. The RF signal has an effective range of about 5 – 15cm from the emulator antenna of this Click board™ to the sensor antenna.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thunderemu_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thunder-emu-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Thunder EMU Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thunder EMU Click driver.

#### Standard key functions :

- `thunderemu_cfg_setup` Config Object Initialization function.
```c
void thunderemu_cfg_setup ( thunderemu_cfg_t *cfg );
```

- `thunderemu_init` Initialization function.
```c
err_t thunderemu_init ( thunderemu_t *ctx, thunderemu_cfg_t *cfg );
```

- `thunderemu_default_cfg` Click Default Configuration function.
```c
err_t thunderemu_default_cfg ( thunderemu_t *ctx );
```

#### Example key functions :

- `thunderemu_generate_thunder` This function generates close, mid or far range thunder signal by setting the predefined DAC output profile at the specific timing.
```c
err_t thunderemu_generate_thunder ( thunderemu_t *ctx, uint8_t mode );
```

- `thunderemu_get_close_pin` This function returns the CLOSE pin logic state.
```c
uint8_t thunderemu_get_close_pin ( thunderemu_t *ctx );
```

- `thunderemu_get_mid_pin` This function returns the MID pin logic state.
```c
uint8_t thunderemu_get_mid_pin ( thunderemu_t *ctx );
```

## Example Description

> This example demonstrates the use of Thunder EMU click board by generating
CLOSE, MID, or FAR range thunder signal depending on the click push-buttons state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thunderemu_cfg_t thunderemu_cfg;  /**< Click config object. */

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
    thunderemu_cfg_setup( &thunderemu_cfg );
    THUNDEREMU_MAP_MIKROBUS( thunderemu_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thunderemu_init( &thunderemu, &thunderemu_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THUNDEREMU_ERROR == thunderemu_default_cfg ( &thunderemu ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Checks if any of the click board buttons are pressed and then generates a thunder
signal related to the pressed button and displays an appropriate message on the USB UART.

```c
void application_task ( void )
{
    if ( !thunderemu_get_close_pin ( &thunderemu ) )
    {
        if ( THUNDEREMU_OK == thunderemu_generate_thunder ( &thunderemu, THUNDEREMU_MODE_CLOSE ) )
        {
            log_printf( &logger, " Close range thunder signal generated!\r\n\n" );
            Delay_ms ( 500 );
        }
    }
    else if ( !thunderemu_get_mid_pin ( &thunderemu ) )
    {
        if ( THUNDEREMU_OK == thunderemu_generate_thunder ( &thunderemu, THUNDEREMU_MODE_MID ) )
        {
            log_printf( &logger, " Mid range thunder signal generated!\r\n\n" );
            Delay_ms ( 500 );
        }
    }
    else if ( !thunderemu_get_far_pin ( &thunderemu ) )
    {
        if ( THUNDEREMU_OK == thunderemu_generate_thunder ( &thunderemu, THUNDEREMU_MODE_FAR ) )
        {
            log_printf( &logger, " Far range thunder signal generated!\r\n\n" );
            Delay_ms ( 500 );
        }
    }
}
```

## Note

> Thunder EMU click should be used in combination with a Thunder click which detects
a lightning presence. The emulator is calibrated for ranges of up to 15cm from the sensor board.
It's recommended to distant both click boards from their development boards using a Shuttle click
to reduce the board noise that can affect the sensor and emulator performance.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ThunderEMU

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
