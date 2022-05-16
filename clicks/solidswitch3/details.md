
---
# SolidSwitch 3 click

> SolidSwitch 3 Click is a compact add-on board that contains a load switching device. This board features the BD8LB600FS-C, an automotive eight-channel low-side switch from Rohm Semiconductor. Every switch is controlled via an SPI interface and includes an N-channel MOSFET that supports a maximum current of 1A. The BD8LB600FS-C also has built-in protection circuits, namely the overcurrent, the thermal shutdown, the open-load detection, and the voltage lock-out circuits. Moreover, this device also possesses a diagnostic output function during abnormal detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/solidswitch3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/solidswitch-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the SolidSwitch 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SolidSwitch 3 Click driver.

#### Standard key functions :

- `solidswitch3_cfg_setup` Config Object Initialization function.
```c
void solidswitch3_cfg_setup ( solidswitch3_cfg_t *cfg );
```

- `solidswitch3_init` Initialization function.
```c
err_t solidswitch3_init ( solidswitch3_t *ctx, solidswitch3_cfg_t *cfg );
```

- `solidswitch3_default_cfg` Click Default Configuration function.
```c
err_t solidswitch3_default_cfg ( solidswitch3_t *ctx );
```

#### Example key functions :

- `solidswitch3_enable_output` This function enables the specified output channel.
```c
err_t solidswitch3_enable_output ( solidswitch3_t *ctx, uint8_t channel );
```

- `solidswitch3_disable_output` This function disables the specified output channel.
```c
err_t solidswitch3_disable_output ( solidswitch3_t *ctx, uint8_t channel );
```

- `solidswitch3_reset` This function resets the device by toggling the reset pin.
```c
void solidswitch3_reset ( solidswitch3_t *ctx );
```

## Example Description

> This example demonstrates the use of SolidSwitch 3 click board by controlling the output state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch3_cfg_t solidswitch3_cfg;  /**< Click config object. */

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
    solidswitch3_cfg_setup( &solidswitch3_cfg );
    SOLIDSWITCH3_MAP_MIKROBUS( solidswitch3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == solidswitch3_init( &solidswitch3, &solidswitch3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    SET_SPI_DATA_SAMPLE_EDGE;
    
    if ( SOLIDSWITCH3_ERROR == solidswitch3_default_cfg ( &solidswitch3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Enables all outputs one by one in the span of 8 seconds, and after that disables
all outputs for 3 seconds. Accordingly, the outputs status will be displayed on the USB UART.

```c
void application_task ( void )
{
    for ( uint16_t cnt = SOLIDSWITCH3_CH_OUT1; cnt <= SOLIDSWITCH3_CH_OUT8; cnt <<= 1 )
    {
        if ( SOLIDSWITCH3_OK == solidswitch3_enable_output ( &solidswitch3, cnt ) )
        {
            solidswitch3_display_enabled_channels( &solidswitch3 );
            Delay_ms ( 1000 );
        }
    }
    
    if ( SOLIDSWITCH3_OK == solidswitch3_disable_output ( &solidswitch3, SOLIDSWITCH3_ALL_CHANNELS ) )
    {
        solidswitch3_display_enabled_channels( &solidswitch3 );
        Delay_ms ( 3000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SolidSwitch3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
