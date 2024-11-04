\mainpage Main Page

---
# LDC Touch Click

> LDC Touch Click is a compact add-on board optimized for inductive touch applications. This board features the LDC3114-Q1, a four-channel inductance-to-digital converter for low-power proximity and touch-button sensing from Texas Instruments. It comes with an adjustable sensitivity per input channel and operational power mode selection and measures frequency shifts caused by micro-deflection in the conductive targets formed by button presses. These presses are reported through a compatible I2C interface beside four LED indicators for its visual indication. This Click board™ enables touch button design for human-machine interface and precise linear position sensing of metal targets for automotive, consumer, and industrial applications by allowing access to the raw data representing the inductance value.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ldctouch_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ldc-touch-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the LDC Touch Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LDC Touch Click driver.

#### Standard key functions :

- `ldctouch_cfg_setup` Config Object Initialization function.
```c
void ldctouch_cfg_setup ( ldctouch_cfg_t *cfg );
```

- `ldctouch_init` Initialization function.
```c
err_t ldctouch_init ( ldctouch_t *ctx, ldctouch_cfg_t *cfg );
```

- `ldctouch_default_cfg` Click Default Configuration function.
```c
err_t ldctouch_default_cfg ( ldctouch_t *ctx );
```

#### Example key functions :

- `ldctouch_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t ldctouch_get_int_pin ( ldctouch_t *ctx );
```

- `ldctouch_get_data` This function reads status, out_state, and all buttons raw data.
```c
err_t ldctouch_get_data ( ldctouch_t *ctx, ldctouch_data_t *button_data );
```

- `ldctouch_set_operation_mode` This function sets the operation mode.
```c
err_t ldctouch_set_operation_mode ( ldctouch_t *ctx, uint8_t mode );
```

## Example Description

> This example demonstrates the use of LDC Touch Click board by configuring
the buttons to trigger on finger press, and reading the buttons state in the loop.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures the buttons to be active on finger press.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ldctouch_cfg_t ldctouch_cfg;  /**< Click config object. */

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
    ldctouch_cfg_setup( &ldctouch_cfg );
    LDCTOUCH_MAP_MIKROBUS( ldctouch_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ldctouch_init( &ldctouch, &ldctouch_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LDCTOUCH_ERROR == ldctouch_default_cfg ( &ldctouch ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the button active event interrupt and then reads and displays the buttons
state and their raw data on the USB UART every 200ms approximately.

```c
void application_task ( void )
{
    static bool button_active = true;
    if ( !ldctouch_get_int_pin ( &ldctouch ) )
    {
        ldctouch_data_t button_data;
        if ( LDCTOUCH_OK == ldctouch_get_data ( &ldctouch, &button_data ) )
        {
            button_active = true;
            log_printf ( &logger, " Active button: -" ); 
            for ( uint8_t cnt = 0; cnt < 4; cnt++ )
            {
                if ( button_data.out_state & ( 1 << cnt ) )
                {
                    log_printf ( &logger, " %u - ", ( uint16_t ) cnt ); 
                }
            }
            log_printf ( &logger, "\r\n Button 0 raw data: %d\r\n", button_data.ch0_raw_button );
            log_printf ( &logger, " Button 1 raw data: %d\r\n", button_data.ch1_raw_button );
            log_printf ( &logger, " Button 2 raw data: %d\r\n", button_data.ch2_raw_button );
            log_printf ( &logger, " Button 3 raw data: %d\r\n\n", button_data.ch3_raw_button );
            Delay_ms ( 200 );
        }
    }
    else
    {
        if ( button_active )
        {
            button_active = false;
            log_printf ( &logger, " Active button: - none -\r\n" ); 
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LDCTouch

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
