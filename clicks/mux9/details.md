
---
# MUX 9 click

> MUX 9 Click is a compact add-on board that contains a precise multiplexing solution. 
> This board features the ADG1438, a CMOS 8-channel analog matrix switch 
> with a high-speed serially controlled 4-wire interface from Analog Devices. 
> Each switch is software-controlled (by a bit of the appropriate register) 
> and conducts equally well in both directions, making it ideal for mux/demux applications. 
> It is specified for a wide supply range ±15V/+12V/±5V where all channels exhibit break-before-make switching action, 
> preventing momentary shorting when switching channels.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mux9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mux-9-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the MUX 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MUX 9 Click driver.

#### Standard key functions :

- `mux9_cfg_setup` Config Object Initialization function.
```c
void mux9_cfg_setup ( mux9_cfg_t *cfg );
```

- `mux9_init` Initialization function.
```c
err_t mux9_init ( mux9_t *ctx, mux9_cfg_t *cfg );
```

#### Example key functions :

- `mux9_active_channel` MUX 9 active channel function.
```c
err_t mux9_active_channel ( mux9_t *ctx, uint8_t sel_ch );
```

- `mux9_reset` MUX 9 reset function.
```c
void mux9_reset ( mux9_t *ctx );
```

- `mux9_disable` MUX 9 disable function.
```c
void mux9_disable ( mux9_t *ctx );
```

## Example Description

> This example demonstrates the use of MUX 9 click board™.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the reset.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;    /**< Logger config object. */
    mux9_cfg_t mux9_cfg;  /**< Click config object. */

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
    mux9_cfg_setup( &mux9_cfg );
    MUX9_MAP_MIKROBUS( mux9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mux9_init( &mux9, &mux9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    mux9_reset( &mux9 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------\r\n" );
}

```

### Application Task

> This is an example that shows the use of a MUX 9 click board™.
> This example shows switching channels (from CH 1 to CH 8) on and off.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    for ( uint8_t ch_pos = MUX9_SELECT_CH_1; ch_pos <= MUX9_SELECT_CH_8; ch_pos++ )
    {
        if ( MUX9_OK == mux9_active_channel( &mux9, ch_pos ) )
        {
            log_printf( &logger, " The Channel %d is activated. \r\n", ( uint16_t ) ch_pos );
            Delay_ms ( 1000 );
        }
    }
    log_printf( &logger, " -----------\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MUX9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
