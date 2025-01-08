
---
# NFC 2 Click

> [NFC 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4309) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4309&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example which demonstrates the usage of NFC 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NFC2

### Example Key Functions

- `nfc2_cfg_setup` Config Object Initialization function.
```c
void nfc2_cfg_setup ( nfc2_cfg_t *cfg );
```

- `nfc2_init` Initialization function.
```c
err_t nfc2_init ( nfc2_t *ctx, nfc2_cfg_t *cfg );
```

- `nfc2_default_cfg` Click Default Configuration function.
```c
err_t nfc2_default_cfg ( nfc2_t *ctx );
```

- `nfc2_hw_reset` HW reset function.
```c
void nfc2_hw_reset( nfc2_t *ctx );
```

- `nfc2_core_set_protocol_config` Set protocol configuration function.
```c
void nfc2_core_set_protocol_config ( nfc2_t *ctx );
```

- `nfc2_cmd_card_disconnected` Card disconnected command function.
```c
void nfc2_cmd_card_disconnected ( nfc2_t *ctx );
```

### Application Init

> Initialization driver enables - I2C, hw reset, reseteting and initialize core, disabling standby mode,  starting test procedure, set configuration and start discovery, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc2_cfg_t nfc2_cfg;  /**< Click config object. */

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
    nfc2_cfg_setup( &nfc2_cfg );
    NFC2_MAP_MIKROBUS( nfc2_cfg, MIKROBUS_1 );
    err_t init_flag = nfc2_init( &nfc2, &nfc2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, "        HW Reset       \r\n" );
    nfc2_hw_reset( &nfc2 );
    Delay_ms ( 100 );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, " Reset and Init. Core  \r\n" );
    nfc2_cmd_core_reset( &nfc2 );
    Delay_ms ( 100 );

    nfc2_read_ctrl_packet_data( &nfc2, &ctrl_pck_data );
    Delay_ms ( 100 );

    nfc2_cmd_core_init( &nfc2 );
    Delay_ms ( 100 );

    nfc2_read_ctrl_packet_data( &nfc2, &ctrl_pck_data );
    Delay_ms ( 100 );
    display_packet( &ctrl_pck_data );

    while ( nfc2_check_irq( &nfc2 ) == NFC2_IRQ_STATE_HIGH );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, " Disabling Standby Mode \r\n" );
    nfc2_cmd_disable_standby_mode( &nfc2 );
    Delay_ms ( 100 );

    nfc2_read_ctrl_packet_data( &nfc2, &ctrl_pck_data );
    Delay_ms ( 100 );
    display_packet( &ctrl_pck_data );

    nfc2_test_antenna( &nfc2, &ctrl_pck_data );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "Starting Test Procedure\r\n" );
    nfc2_cmd_test_procedure( &nfc2 );
    Delay_ms ( 100 );

    nfc2_read_ctrl_packet_data( &nfc2, &ctrl_pck_data );
    Delay_ms ( 100 );
    display_packet( &ctrl_pck_data );

    nfc2_hw_reset( &nfc2 );
    Delay_ms ( 100 );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "       NFC Config.     \r\n" );
    nfc2_default_cfg ( &nfc2, &ctrl_pck_data );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "     Discovery Start   \r\n" );
    nfc2_cmd_start_discovery( &nfc2 );
    Delay_ms ( 100 );

    nfc2_read_ctrl_packet_data( &nfc2, &ctrl_pck_data );
    Delay_ms ( 100 );
    display_packet( &ctrl_pck_data );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "-------- START --------\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 500 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> NFC 2 Click board can be used for detection of RFiD tag and displays it's value via USART terminal. All data logs write on USB uart changes for every 1 sec.

```c
void application_task ( void ) 
{
    while ( nfc2_check_irq( &nfc2 ) == NFC2_IRQ_STATE_HIGH ) {
        nfc2_read_nfc_data ( &nfc2, &ctrl_pck_data );
    }

    while ( nfc2_check_irq( &nfc2 ) == NFC2_IRQ_STATE_LOW );

    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
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
