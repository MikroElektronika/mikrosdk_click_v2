
---
# Haptic 6 Click

> [Haptic 6 Click](https://www.mikroe.com/?pid_product=MIKROE-7047) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7047&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example initializes Haptic 6 Click and the IQS397 haptic controller.
The application waits for a button press, drives the LRA motor while the
button remains pressed and stops the vibration when the finger is lifted.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Haptic6

### Example Key Functions

- `haptic6_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void haptic6_cfg_setup ( haptic6_cfg_t *cfg );
```

- `haptic6_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t haptic6_init ( haptic6_t *ctx, haptic6_cfg_t *cfg );
```

- `haptic6_default_cfg` This function executes a default configuration of Haptic 6 Click board.
```c
err_t haptic6_default_cfg ( haptic6_t *ctx );
```

- `haptic6_read_reg` This function reads a single byte of data from the selected register.
```c
err_t haptic6_read_reg ( haptic6_t *ctx, uint16_t reg, uint8_t *data_out );
```

- `haptic6_trigger` This function triggers one haptic waveform using the IQS397 System Commands register.
```c
err_t haptic6_trigger ( haptic6_t *ctx );
```

- `haptic6_cancel` This function cancels the active haptic waveform.
```c
err_t haptic6_cancel ( haptic6_t *ctx );
```

### Application Init

> Initializes the logger, click driver and default IQS397 haptic settings.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    haptic6_cfg_t haptic6_cfg;  /**< Click config object. */

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
    haptic6_cfg_setup( &haptic6_cfg );
    HAPTIC6_MAP_MIKROBUS( haptic6_cfg, MIKROBUS_POSITION_HAPTIC6 );
    if ( I2C_MASTER_ERROR == haptic6_init( &haptic6, &haptic6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HAPTIC6_ERROR == haptic6_default_cfg ( &haptic6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a button event, repeatedly triggers haptic feedback while the
button event remains active and cancels the active haptic output after the
release debounce expires.

```c
void application_task ( void )
{
    static uint8_t button_state = 0;
    static uint8_t haptic_state = 0;
    
    log_printf( &logger, "\r\n Waiting for button press...\r\n" );

    for ( ; ; )
    {
        if ( HAPTIC6_OK == haptic6_get_button_state( &button_state ) )
        {
            if ( button_state )
            {
                if ( 0 == haptic_state )
                {
                    log_printf( &logger, " Button pressed - Haptic active\r\n" );
                    haptic_state = 1;
                }
                haptic6_trigger( &haptic6 );
            }
            else if ( haptic_state )
            {
                haptic6_cancel( &haptic6 );
                haptic_state = 0;
                log_printf( &logger, " Button released - Haptic idle\r\n" );
                break;
            }
        }
        else
        {
            log_error( &logger, " Button state read." );
        }
    }
}
```

### Note

> Connect an LRA motor to the M+ and M- terminal block before running the example. 
A Vibration LRA Motor 240Hz - LRA0825BC-0167F [MIKROE-6809] is recommended.

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
