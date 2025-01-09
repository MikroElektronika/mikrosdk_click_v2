
---
# STSPIN233 Click

> [STSPIN233 Click](https://www.mikroe.com/?pid_product=MIKROE-3546) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3546&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This application is motor driver.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stspin233

### Example Key Functions

- `stspin233_cfg_setup` Config Object Initialization function. 
```c
void stspin233_cfg_setup ( stspin233_cfg_t *cfg );
``` 
 
- `stspin233_init` Initialization function. 
```c
err_t stspin233_init ( stspin233_t *ctx, stspin233_cfg_t *cfg );
```

- `stspin233_send_single_cmd` Send single command. 
```c
void stspin233_send_single_cmd ( stspin233_t *ctx, uint8_t *tx_buf );
```
 
- `stspin233_send_double_cmd` Send double command. 
```c
void stspin233_send_double_cmd ( stspin233_t *ctx, uint8_t *cmd_buf, uint8_t *arg_buf );
```

- `stspin233_get_int_state` Get INT pin state. 
```c
uint8_t stspin233_get_int_state ( stspin233_t *ctx );
```

### Application Init

> Initializes driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    stspin233_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    stspin233_cfg_setup( &cfg );
    STSPIN233_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stspin233_init( &stspin233, &cfg );

    stspin233_default_cfg( &stspin233 );
}
```

### Application Task

> This example demonstrates the use of STSPIN233 Click board, by running the motor clockwise and counter clockwise.
> All results will be displayed on USB UART.

```c
void application_task ( void )
{
    log_printf( &logger, ">>> START MOTOR\r\n" );
    stspin233_send_single_cmd( &stspin233, STSPIN233_CMD_START_MOTOR );
    stspin233_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">>> Set clockwise direction\r\n" );
    stspin233_send_double_cmd( &stspin233, STSPIN233_CMD_DIR_MOTOR, STSPIN233_CW_DIR );
    stspin233_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">>> Set counter clockwise direction\r\n" );
    stspin233_send_double_cmd( &stspin233, STSPIN233_CMD_DIR_MOTOR, STSPIN233_CCW_DIR );
    stspin233_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">>> STOP MOTOR\r\n" );
    stspin233_send_single_cmd( &stspin233, STSPIN233_CMD_STOP_MOTOR );
    stspin233_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    stspin233_send_single_cmd( &stspin233, STSPIN233_CMD_STATUS );
    stspin233_process( );
    log_printf( &logger, ">>> STATUS: %.5s\r\n", &current_parser_buf[ 9 ] );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "------------------------------\r\n" );
}
```

### Note

> For all other commands that you can use to control your engine, 
> see the firmware documentation. We used an 8 pole motor for the test.

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
