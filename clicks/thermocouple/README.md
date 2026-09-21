
---
# Thermocouple Click

> [Thermocouple Click](https://www.mikroe.com/?pid_product=MIKROE-6984) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6984&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Thermocouple Click board for
temperature measurement using thermocouple sensors. The application
alternates between two channels, reading temperature values from
different thermocouple types, and also retrieves ambient and delta
temperatures.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermocouple

### Example Key Functions

- `thermocouple_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void thermocouple_cfg_setup ( thermocouple_cfg_t *cfg );
```

- `thermocouple_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t thermocouple_init ( thermocouple_t *ctx, thermocouple_cfg_t *cfg );
```

- `thermocouple_default_cfg` This function executes a default configuration of Thermocouple Click board.
```c
err_t thermocouple_default_cfg ( thermocouple_t *ctx );
```

- `thermocouple_get_hot_junction` This function reads the hot junction (thermocouple) temperature register.
```c
err_t thermocouple_get_hot_junction ( thermocouple_t *ctx, float *temp );
```

- `thermocouple_get_cold_junction` This function reads the cold junction (ambient) temperature register.
```c
err_t thermocouple_get_cold_junction ( thermocouple_t *ctx, float *temp );
```

- `thermocouple_get_delta_temp` This function reads the junction delta temperature register.
```c
err_t thermocouple_get_delta_temp ( thermocouple_t *ctx, float *temp );
```

### Application Init

> Initializes the logger and Thermocouple Click driver, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermocouple_cfg_t thermocouple_cfg;  /**< Click config object. */

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
    thermocouple_cfg_setup( &thermocouple_cfg );
    THERMOCOUPLE_MAP_MIKROBUS( thermocouple_cfg, MIKROBUS_POSITION_THERMOCOUPLE );
    if ( THERMOCOUPLE_ERROR == thermocouple_init( &thermocouple, &thermocouple_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMOCOUPLE_ERROR == thermocouple_default_cfg ( &thermocouple ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Configures the active thermocouple channel, waits for measurement
completion, reads hot junction temperature, ambient temperature,
and delta temperature, and logs the results while alternating between channels.

```c
void application_task ( void )
{
    static uint8_t active_channel = THERMOCOUPLE_CHANNEL_1;
    err_t error_flag = THERMOCOUPLE_OK;
    float tc_temp = 0;
    float amb_temp = 0;
    float delta_temp = 0;
    uint32_t timeout = 0;
    uint8_t status = 0;

    if ( THERMOCOUPLE_CHANNEL_1 == active_channel )
    {
        error_flag = thermocouple_set_sensor_cfg( &thermocouple,
                                                  active_channel,
                                                  THERMOCOUPLE_TYPE_K,
                                                  THERMOCOUPLE_FILTER_OFF );
    }
    else
    {
        error_flag = thermocouple_set_sensor_cfg( &thermocouple,
                                                  active_channel,
                                                  THERMOCOUPLE_TYPE_J,
                                                  THERMOCOUPLE_FILTER_OFF );
    }
    Delay_ms ( 10 );

    if ( THERMOCOUPLE_OK == error_flag )
    {
        while ( ( THERMOCOUPLE_STATUS_TH_UPDATE != ( status & THERMOCOUPLE_STATUS_TH_UPDATE ) ) && 
                ( ++timeout < THERMOCOUPLE_STATUS_TIMEOUT ) )
        {
            thermocouple_get_status ( &thermocouple, &status );
            Delay_ms ( 1 );
        }
        error_flag = thermocouple_get_hot_junction( &thermocouple, &tc_temp );
        error_flag |= thermocouple_clear_status( &thermocouple );
    }

    if ( THERMOCOUPLE_OK == error_flag )
    {
        if ( THERMOCOUPLE_CHANNEL_1 == active_channel )
        {
            log_printf( &logger, " CH1 Type K: %.2f C\r\n", tc_temp );
            active_channel = THERMOCOUPLE_CHANNEL_2;
        }
        else
        {
            log_printf( &logger, " CH2 Type J: %.2f C\r\n", tc_temp );
            active_channel = THERMOCOUPLE_CHANNEL_1;
        }
        error_flag |= thermocouple_get_cold_junction( &thermocouple, &amb_temp );
        log_printf( &logger, " Ambient Temp: %.2f C\r\n", amb_temp );
        error_flag |= thermocouple_get_delta_temp( &thermocouple, &delta_temp );
        log_printf( &logger, " Delta Temp: %.2f C\r\n\n", delta_temp );
    }

    Delay_ms ( 1000 );
}
```

### Note

> Thermocouple connections:
> - Connect the Type K thermocouple to channel CH1 input terminals on the Click board.
> - Connect the Type J thermocouple to channel CH2 input terminals on the Click board.
>
> Ensure correct polarity when connecting thermocouples (positive and negative leads).

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
