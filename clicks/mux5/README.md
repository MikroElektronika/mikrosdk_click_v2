\mainpage Main Page

---
# MUX 5 Click

> MUX 5 Click is a compact add-on board that contains a precise multiplexing solution. This board features the MAX14661, a serially controlled, dual-channel analog multiplexer from Analog Devices, allowing any of the 16 pins to be connected to either common pin simultaneously in any combination. The MAX14661 features Beyond-the-Rails™ capability that allows ±5.5V signals to be passed with any supply configuration alongside a configurable host interface that supports SPI and I2C serial communications. Both modes provide individual control of each independent switch so that any combination of switches can be applied.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mux5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/mux-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the MUX 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MUX 5 Click driver.

#### Standard key functions :

- `mux5_cfg_setup` Config Object Initialization function.
```c
void mux5_cfg_setup ( mux5_cfg_t *cfg );
```

- `mux5_init` Initialization function.
```c
err_t mux5_init ( mux5_t *ctx, mux5_cfg_t *cfg );
```

- `mux5_default_cfg` Click Default Configuration function.
```c
err_t mux5_default_cfg ( mux5_t *ctx );
```

#### Example key functions :

- `mux5_i2c_write_register` This function writes a desired data to the selected register by using I2C serial interface.
```c
err_t mux5_i2c_write_register ( mux5_t *ctx, uint8_t reg, uint8_t data_in );
```

- `mux5_i2c_read_register` This function reads data from the selected register by using I2C serial interface.
```c
err_t mux5_i2c_read_register ( mux5_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `mux5_set_channels_state` This function sets a desired @b ch_state of the channels selected with @b ch_mask.
```c
err_t mux5_set_channels_state ( mux5_t *ctx, uint16_t ch_mask, uint8_t ch_state );
```

## Example Description

> This example demonstrates the use of MUX 5 Click board by mapping the common connection A and B to different channels every 5 seconds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mux5_cfg_t mux5_cfg;  /**< Click config object. */

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
    mux5_cfg_setup( &mux5_cfg );
    MUX5_MAP_MIKROBUS( mux5_cfg, MIKROBUS_1 );
    if ( MUX5_OK != mux5_init( &mux5, &mux5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MUX5_OK != mux5_default_cfg ( &mux5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Maps the common connection A and B to different channels every 5 seconds, and displays the channels state on the USB UART.

```c
void application_task ( void )
{
    static uint8_t ch_num = 0;
    if ( MUX5_OK == mux5_set_channels_state ( &mux5, MUX5_CHANNEL_ALL, MUX5_CHANNEL_STATE_HIGH_Z ) )
    {
        log_printf ( &logger, " All channels disconnected\r\n" );
    }
    Delay_ms ( 1000 );
    if ( MUX5_OK == mux5_set_channels_state ( &mux5, MUX5_CHANNEL_1 << ch_num, MUX5_CHANNEL_STATE_COM_A ) )
    {
        log_printf ( &logger, " Channel %u connected to COM_A\r\n", ( uint16_t ) ( ch_num + 1 ) );
    }
    if ( MUX5_OK == mux5_set_channels_state ( &mux5, MUX5_CHANNEL_16 >> ch_num, MUX5_CHANNEL_STATE_COM_B ) )
    {
        log_printf ( &logger, " Channel %u connected to COM_B\r\n\n", ( uint16_t ) ( 16 - ch_num ) );
    }
    if ( ++ch_num >= 16 )
    {
        ch_num = 0;
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MUX5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
