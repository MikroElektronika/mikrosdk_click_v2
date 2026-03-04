
---
# Ultrasonic 4 Click

> [Ultrasonic 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6601) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6601&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates ranging with Ultrasonic 4 Click (Chirp/TDK time-of-flight).
The example periodically triggers a measurement and prints the measured
distance to the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ultrasonic4

### Example Key Functions

- `ultrasonic4_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void ultrasonic4_cfg_setup ( ultrasonic4_cfg_t *cfg );
```

- `ultrasonic4_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t ultrasonic4_init ( ultrasonic4_t *ctx, ultrasonic4_cfg_t *cfg );
```

- `ultrasonic4_default_cfg` This function executes a default configuration of Ultrasonic 4 Click board.
```c
err_t ultrasonic4_default_cfg ( ultrasonic4_t *ctx );
```

- `ultrasonic4_get_measurements` This function triggers and reads the measurements and logs data.
```c
void ultrasonic4_get_measurements ( void );
```

### Application Init

> Initialize the USB UART logger and the Ultrasonic 4 driver, then apply
the default configuration to start the sensor and prepare it for
continuous single-shot ranging.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ultrasonic4_cfg_t ultrasonic4_cfg;  /**< Click config object. */

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
    ultrasonic4_cfg_setup( &ultrasonic4_cfg );
    ULTRASONIC4_MAP_MIKROBUS( ultrasonic4_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ultrasonic4_init( &ultrasonic4, &ultrasonic4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ULTRASONIC4_ERROR == ultrasonic4_default_cfg ( &ultrasonic4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Triggers a measurement and logs results (distance, sample number, and amplitude) every 100ms.

```c
void application_task ( void )
{
    ultrasonic4_get_measurements ( );
    Delay_ms ( 100 );
}
```

### Note

> Make sure to configure falling-edge external interrupt on INT pin in bsp.c for your selected setup.
Currently, only 3 interrupts are pre-configured for the following setups:
> - MCU Card for STM32 STM32F407ZG (MIKROBUS1)
> - MCU Card for Tiva TM4C129XNCZAD (MIKROBUS1)
> - MCU Card for PIC32 PIC32MX795F512L (MIKROBUS1)

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
