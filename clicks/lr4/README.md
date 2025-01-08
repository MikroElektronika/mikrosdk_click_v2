
---
# LR 4 Click

> [LR 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4617) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4617&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from LR 4 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LR4

### Example Key Functions

- `lr4_cfg_setup` Config Object Initialization function. 
```c
void lr4_cfg_setup ( lr4_cfg_t *cfg );
``` 
 
- `lr4_init` Initialization function. 
```c
err_t lr4_init ( lr4_t *ctx, lr4_cfg_t *cfg );
```

- `lr4_factory_reset` Function performs the recovery of EEPROM default values. 
```c
err_t lr4_factory_reset ( lr4_t *ctx );
```
 
- `lr4_write_eeprom` Function writes data to EEPROM. 
```c
err_t lr4_write_eeprom ( lr4_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_in );
```

- `lr4_tx_message` Function performs the transmission of radio frames. 
```c
err_t lr4_tx_message ( lr4_t *ctx, lr4_tx_msg_t *tx_msg );
```

### Application Init

> Initializes the driver, and resets the Click board to factory default configuration.
> Then performs a group of commands for getting the FW version, the serial number, and the DevEUI.
> After that executes the join activation by personalization command.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lr4_cfg_t cfg;

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

    lr4_cfg_setup( &cfg );
    LR4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lr4_init( &lr4, &cfg );

    Delay_ms ( 100 );
    lr4_set_ind_handler( &lr4, response_handler );
    log_printf( &logger, "Hard reset!\r\n" );
    lr4_hard_reset( &lr4 );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "Factory reset!\r\n" );
    lr4_factory_reset( &lr4 );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    uint32_t tmp_data = 0;
    log_printf( &logger, "Get FW version!\r\n" );
    lr4_get_fw_version( &lr4, &tmp_data );
    log_printf( &logger, "FW vesion is: 0x%.8LX\r\n", tmp_data );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "Get Serial Number!\r\n" );
    lr4_get_serial_no( &lr4, &tmp_data );
    log_printf( &logger, "Serial Number is: 0x%.8LX\r\n", tmp_data );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    uint8_t tmp_buf[ 8 ] = { 0 };
    log_printf( &logger, "Get Dev EUI!\r\n" );
    lr4_get_dev_eui( &lr4, tmp_buf );
    log_printf( &logger, "Dev EUI is: 0x%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X\r\n", ( uint16_t ) tmp_buf[ 7 ],
                                                                               ( uint16_t ) tmp_buf[ 6 ],
                                                                               ( uint16_t ) tmp_buf[ 5 ],
                                                                               ( uint16_t ) tmp_buf[ 4 ],
                                                                               ( uint16_t ) tmp_buf[ 3 ],
                                                                               ( uint16_t ) tmp_buf[ 2 ],
                                                                               ( uint16_t ) tmp_buf[ 1 ],
                                                                               ( uint16_t ) tmp_buf[ 0 ] );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "Join Network!\r\n" );
    lr4_join_network( &lr4, LR4_JOIN_ACTIVATION_BY_PERSONALIZATION_MODE );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> Checks the activation and session status and displays the results on the USB UART.

```c
void application_task ( void )
{
    log_printf( &logger, "Get Activation Status!\r\n" );
    uint8_t status = lr4_get_status( &lr4, LR4_GET_ACTIVATION_MODE );
    log_printf( &logger, "Status: " );
    switch ( status )
    {
        case LR4_STATUS_NOT_ACTIVATED :
        {
            log_printf( &logger, "Not activated.\r\n" );
            break;
        }
        case LR4_STATUS_JOINING :
        {
            log_printf( &logger, "Joining...\r\n" );
            break;
        }
        case LR4_STATUS_JOINED :
        {
            log_printf( &logger, "Joined.\r\n" );
            break;
        }
        case LR4_STATUS_MAC_ERROR :
        {
            log_printf( &logger, "MAC ERROR.\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "Get Session Status!\r\n" );
    status = lr4_get_status( &lr4, LR4_GET_SESSION_STATUS_MODE );
    log_printf( &logger, "Status: " );
    switch ( status )
    {
        case LR4_STATUS_IDLE :
        {
            log_printf( &logger, "Idle.\r\n" );
            break;
        }
        case LR4_STATUS_BUSY :
        {
            log_printf( &logger, "Busy (LR session running).\r\n" );
            break;
        }
        case LR4_STATUS_DEV_NOT_ACTIVATED :
        {
            log_printf( &logger, "Device not activated.\r\n" );
            break;
        }
        case LR4_STATUS_DELAYED :
        {
            log_printf( &logger, "Delayed (LR session paused due to Duty-cycle).\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
    log_printf( &logger, "------------------------\r\n" );
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
