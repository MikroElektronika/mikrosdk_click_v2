
---
# Fingerprint 5 Click

> [Fingerprint 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6787) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6787&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates how to use the Fingerprint 5 Click board to enroll and identify fingerprints.
The application cycles through several states: checking firmware readiness, reading version info, 
deleting existing templates, enrolling new fingerprints, and continuously identifying them.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Fingerprint5

### Example Key Functions

- `fingerprint5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void fingerprint5_cfg_setup ( fingerprint5_cfg_t *cfg );
```

- `fingerprint5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t fingerprint5_init ( fingerprint5_t *ctx, fingerprint5_cfg_t *cfg );
```

- `fingerprint5_enroll_finger` This function sends the enroll command for fingerprint registration.
```c
err_t fingerprint5_enroll_finger ( fingerprint5_t *ctx );
```

- `fingerprint5_identify_finger` This function sends the identify command to compare the input fingerprint with existing templates.
```c
err_t fingerprint5_identify_finger ( fingerprint5_t *ctx );
```

- `fingerprint5_read_cmd` This function reads a response or event frame from the device.
```c
err_t fingerprint5_read_cmd ( fingerprint5_t *ctx );
```

### Application Init

> Initializes the logger and the Click board, resets the device and sets up the application state machine.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    fingerprint5_cfg_t fingerprint5_cfg;  /**< Click config object. */

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
    fingerprint5_cfg_setup( &fingerprint5_cfg );
    FINGERPRINT5_MAP_MIKROBUS( fingerprint5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == fingerprint5_init( &fingerprint5, &fingerprint5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    fingerprint5_reset_device ( &fingerprint5 );

    log_info( &logger, " Application Task " );
    
    app_state = FINGERPRINT5_APP_STATE_WAIT_READY;
    log_printf ( &logger, "\r\nAPP STATE: WAIT READY\r\n" );
}
```

### Application Task

> Handles command processing and application state transitions, enabling fingerprint enrollment and identification.

```c
void application_task ( void )
{
    if ( FINGERPRINT5_OK == fingerprint5_read_cmd ( &fingerprint5 ) )
    {
        fingerprint5_parse_cmd ( &fingerprint5 );
        fingerprint5_process ( &fingerprint5 );
    }
}
```

### Note

> Make sure to place your finger on the sensor when prompted during enrollment and identification.
The example registers 2 fingerprints by default.

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
