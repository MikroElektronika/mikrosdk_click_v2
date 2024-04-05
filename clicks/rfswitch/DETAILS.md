
---
# RF Switch click

> RF Switch Click is a Click board™ equipped with the MASWSS0115, a GaAs PHEMT MMIC single-pole, double-throw (SPDT) switch developed by Macom for switching between small signal components such as filter banks, single-band LNAs, converters, etc. The MASWSS0115 is ideally suited for applications where a very small size and low cost are required.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rfswitch_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rf-switch-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the RFSwitch Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RFSwitch Click driver.

#### Standard key functions :

- `rfswitch_cfg_setup` Config Object Initialization function.
```c
void rfswitch_cfg_setup ( rfswitch_cfg_t *cfg );
```

- `rfswitch_init` Initialization function.
```c
err_t rfswitch_init ( rfswitch_t *ctx, rfswitch_cfg_t *cfg );
```

#### Example key functions :

- `rfswitch_power_on` RF Switch power on function.
```c
void rfswitch_power_on ( rfswitch_t *ctx );
```

- `rfswitch_switch_channel` RF Switch switch channel function.
```c
void rfswitch_switch_channel ( rfswitch_t *ctx );
```

- `rfswitch_select_channel` RF Switch select channel function.
```c
void rfswitch_select_channel ( rfswitch_t *ctx, uint8_t select_channel );
```

## Example Description

> This is an example that demonstrates the use of the RF Switch Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enable's - GPIO, also write log and powers on device.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rfswitch_cfg_t rfswitch_cfg;  /**< Click config object. */

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
    rfswitch_cfg_setup( &rfswitch_cfg );
    RFSWITCH_MAP_MIKROBUS( rfswitch_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == rfswitch_init( &rfswitch, &rfswitch_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "   Powering device on   \r\n" );
    rfswitch_power_on( &rfswitch );
    Delay_ms ( 100 );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "   Select option to     \r\n" );
    log_printf( &logger, "    select channel      \r\n" );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, " 1. Channel 1 selected  \r\n" );
    log_printf( &logger, " 2. Channel 2 selected  \r\n" );
    log_printf( &logger, " 3. Switching channel   \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}

```

### Application Task

> Waiting for valid user input and executes functions based on set of valid commands.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    uint8_t tx_buf;
    if ( log_read( &logger, &tx_buf, 1 ) ) {
        switch ( tx_buf ) {
            case '1' : {
                rfswitch_select_channel( &rfswitch, RFSWITCH_SELECT_CHANNEL_1 );
                log_printf( &logger, " Switching to RF port 1 \r\n" );
                log_printf( &logger, "------------------------\r\n" );
                break;
            }
            case '2' : {
                rfswitch_select_channel( &rfswitch, RFSWITCH_SELECT_CHANNEL_2 );
                log_printf( &logger, " Switching to RF port 2 \r\n" );
                log_printf( &logger, "------------------------\r\n" );
                break;
            }
            case '3' : {
                rfswitch_switch_channel( &rfswitch );
                log_printf( &logger, "   Switching RF port    \r\n" );
                log_printf( &logger, "------------------------\r\n" );
                break;
            }
            default : {
                log_printf( &logger, "   Select option to     \r\n" );
                log_printf( &logger, "    select channel      \r\n" );
                log_printf( &logger, "------------------------\r\n" );
                log_printf( &logger, " 1. Channel 1 selected  \r\n" );
                log_printf( &logger, " 2. Channel 2 selected  \r\n" );
                log_printf( &logger, " 3. Switching channel   \r\n" );
                log_printf( &logger, "------------------------\r\n" );
            }
        }
    }
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RFSwitch

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
