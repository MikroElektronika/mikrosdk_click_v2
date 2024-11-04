\mainpage Main Page

---
# Cap Touch 4 Click

> Cap Touch 4 Click is a compact add-on board for wake-on-touch and activation applications. This board features the IQS211B, a single-channel capacitive controller from Azoteq, featuring ProxSense® technology for highly sensitive self-capacitance measurements. The board includes a defined circular touch-sensing area, signal conditioning for parasitic capacitance, and a low-power Sleep mode with wake-up functionality, ensuring efficient energy consumption. It communicates via the I2C interface with a fixed address of 0x47, operates at 3.3V logic, and features the new Click Snap for added flexibility.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/captouch4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/cap-touch-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Cap Touch 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Cap Touch 4 Click driver.

#### Standard key functions :

- `captouch4_cfg_setup` Config Object Initialization function.
```c
void captouch4_cfg_setup ( captouch4_cfg_t *cfg );
```

- `captouch4_init` Initialization function.
```c
err_t captouch4_init ( captouch4_t *ctx, captouch4_cfg_t *cfg );
```

- `captouch4_default_cfg` Click Default Configuration function.
```c
err_t captouch4_default_cfg ( captouch4_t *ctx );
```

#### Example key functions :

- `captouch4_read_system_flags` This function reads the system flags register.
```c
err_t captouch4_read_system_flags ( captouch4_t *ctx, uint8_t *sysflags );
```

- `captouch4_read_cap_counts` This function reads the counts number directly proportional to capacitance. The system is calibrated to make the counts as sensitive as possible to changes in capacitance for relative measurements.
```c
err_t captouch4_read_cap_counts ( captouch4_t *ctx, uint16_t *cap_counts );
```

- `captouch4_read_lta` This function reads the long-term averate (LTA) value. The LTA is used as reference to compare with capacitance counts.
```c
err_t captouch4_read_lta ( captouch4_t *ctx, uint16_t *lta );
```

## Example Description

> This example demonstrates the use of Cap Touch 4 Click board by reading the proximity, touch, and movement events.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    captouch4_cfg_t captouch4_cfg;  /**< Click config object. */

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
    captouch4_cfg_setup( &captouch4_cfg );
    CAPTOUCH4_MAP_MIKROBUS( captouch4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == captouch4_init( &captouch4, &captouch4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CAPTOUCH4_ERROR == captouch4_default_cfg ( &captouch4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the proximity, touch, and movement events and approximately displays the results on the USB UART every 200ms. The capacitance counts and the long-term average values are also displayed.

```c
void application_task ( void )
{
    uint8_t sys_flags = 0;
    uint8_t movement = 0;
    uint16_t cap_counts = 0;
    uint16_t lta = 0;
    if ( CAPTOUCH4_OK == captouch4_read_system_flags ( &captouch4, &sys_flags ) )
    {
        if ( sys_flags & CAPTOUCH4_SYSFLAGS0_PROX )
        {
            log_printf( &logger, " Proximity detected\r\n" );
        }
        if ( sys_flags & CAPTOUCH4_SYSFLAGS0_TOUCH )
        {
            log_printf( &logger, " Touch detected\r\n" );
        }
        if ( sys_flags & CAPTOUCH4_SYSFLAGS0_MOVEMENT )
        {
            if ( CAPTOUCH4_OK == captouch4_read_movement ( &captouch4, &movement ) )
            {
                log_printf( &logger, " Movement detected: %u\r\n", ( uint16_t ) movement );
            }
        }
        if ( ( sys_flags & CAPTOUCH4_SYSFLAGS0_MOVEMENT ) || 
             ( sys_flags & CAPTOUCH4_SYSFLAGS0_PROX ) || 
             ( sys_flags & CAPTOUCH4_SYSFLAGS0_TOUCH ) )
        {
            if ( CAPTOUCH4_OK == captouch4_read_cap_counts ( &captouch4, &cap_counts ) )
            {
                log_printf( &logger, " Capacitance counts: %u\r\n", cap_counts );
            }
            if ( CAPTOUCH4_OK == captouch4_read_lta ( &captouch4, &lta ) )
            {
                log_printf( &logger, " Long-term average: %u\r\n\n", lta );
            }
        }
        else
        {
            log_printf( &logger, " No detected events\r\n\n" );
        }
    }
    Delay_ms ( 200 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CapTouch4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
