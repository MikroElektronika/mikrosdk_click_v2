
---
# Vibra Sense 2 Click

> [Vibra Sense 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4355) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4355&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example shows capabilities of Vibra Sense 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VibraSense2

### Example Key Functions

- `vibrasense2_cfg_setup` Config Object Initialization function.
```c
void vibrasense2_cfg_setup ( vibrasense2_cfg_t *cfg );
```

- `vibrasense2_init` Initialization function.
```c
err_t vibrasense2_init ( vibrasense2_t *ctx, vibrasense2_cfg_t *cfg );
```

- `vibrasense2_read_data` Read data function.
```c
uint16_t vibrasense2_read_data ( vibrasense2_t *ctx );
```

- `vibrasense2_read_voltage` Read voltage function.
```c
uint16_t vibrasense2_read_voltage ( vibrasense2_t *ctx, uint16_t v_ref );
```

- `vibrasense2_vibration_level` Get Vibration Level function.
```c
int8_t vibrasense2_vibration_level ( vibrasense2_t *ctx );
```

### Application Init

> Initalizes I2C driver and makes an initial log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vibrasense2_cfg_t vibrasense2_cfg;  /**< Click config object. */

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
    vibrasense2_cfg_setup( &vibrasense2_cfg );
    VIBRASENSE2_MAP_MIKROBUS( vibrasense2_cfg, MIKROBUS_1 );
    err_t init_flag = vibrasense2_init( &vibrasense2, &vibrasense2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    old_val = VIBRASENSE2_ERROR;
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------------------\r\n" );
}
```

### Application Task

> Demonstrates use of Vibra Sense 2 Click board by checking vibration levels and displaying changes via USART terminal.

```c
void application_task ( void ) 
{
    new_val = vibrasense2_vibration_level( &vibrasense2 );
    Delay_ms ( 100 );
    if ( new_val != old_val ) {
        switch ( new_val ) {
            case VIBRASENSE2_VIBRA_LVL_0: {
                log_printf( &logger, "            No Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_1: {
                log_printf( &logger, " Vibration level : Marginal Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_2: {
                log_printf( &logger, " Vibration level : Slight Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_3: {
                log_printf( &logger, " Vibration level : Enhanced Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_4: {
                log_printf( &logger, " Vibration level : Moderate Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_5: {
                log_printf( &logger, " Vibration level : High Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_6: {
                log_printf( &logger, " Vibration level : Severe Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            default: {
                log_printf( &logger, "Error occured!" );
                log_printf( &logger, "-------------------------------------\r\n" );
            }
        }
        old_val = new_val;
    }
}
```

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
