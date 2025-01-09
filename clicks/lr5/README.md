
---
# LR 5 Click

> [LR 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4618) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4618&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type

# Software Support

## Example Description

> This example reads and processes data from LR 5 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LR5

### Example Key Functions

- `lr5_cfg_setup` Config Object Initialization function. 
```c
void lr5_cfg_setup ( lr5_cfg_t *cfg );
``` 
 
- `lr5_init` Initialization function. 
```c
err_t lr5_init ( lr5_t *ctx, lr5_cfg_t *cfg );
```

- `lr5_get_fw_version_cmd` This command allows user to get the 32bit firmware version. 
```c
void lr5_get_fw_version_cmd ( lr5_t *ctx );
```
 
- `lr5_get_serial_no_cmd` This command allows user to get the 32bit Mipot serial number. 
```c
void lr5_get_serial_no_cmd ( lr5_t *ctx );
```

- `lr5_get_session_status_cmd` This command allows user to get the module current status. 
```c
void lr5_get_session_status_cmd ( lr5_t *ctx );
```

### Application Init

> Initializes UART interface and UART interrupt, and performs a module reset commands.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lr5_cfg_t cfg;

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

    lr5_cfg_setup( &cfg );
    LR5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lr5_init( &lr5, &cfg );

    lr5_response_handler_set( &lr5, &make_response );
    Delay_ms ( 1000 );

    lr5_reset_cmd( &lr5 );
    wait_response( );
    Delay_ms ( 1000 );
    lr5_factory_reset_cmd( &lr5 );
    wait_response( );
    
    log_printf( &logger, "** LR 5 (MIPOT 32001409) reset is done **\r\n" );
    log_printf( &logger, "\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> Performs a group of commands to get FW version, the serial number provided by Mipot,
> DevEUI, the session status, the activation status and the parameters for the selected channel.
> Also sets the next transmission data rate to the desired value.
> The responses from the Mipot module to the host will be sent to the uart terminal.

```c
void application_task ( void )
{
    lr5_process(  );

    log_printf( &logger, "** FW version reading...\r\n" );
    lr5_get_fw_version_cmd( &lr5 );
    wait_response( );
    
    log_printf( &logger, "** Serial number reading...\r\n" );
    lr5_get_serial_no_cmd( &lr5 );
    wait_response( );
    
    log_printf( &logger, "** DevEUI reading...\r\n" );
    lr5_get_dev_eui_cmd( &lr5 );
    wait_response( );
    
    log_printf( &logger, "** Session status reading...\r\n" );
    lr5_get_session_status_cmd( &lr5 );
    wait_response( );
    switch ( response.cmd_data[ 0 ] )
    {
        case 0x00 :
        {
            log_printf( &logger, "Idle.\r\n" );
        break;
        }
        case 0x01 :
        {
            log_printf( &logger, "Busy (LR session running).\r\n" );
        break;
        }
        case 0x02 :
        {
            log_printf( &logger, "Device not activated.\r\n" );
        break;
        }
        case 0x03 :
        {
            log_printf( &logger, "Delayed.\r\n" );
        break;
        }
        default :
        {
        break;
        }
    }
    log_printf( &logger, "***********************************************\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "** Activation status reading...\r\n" );
    lr5_get_activation_status_cmd( &lr5 );
    wait_response( );
    switch ( response.cmd_data[ 0 ] )
    {
        case 0x00 :
        {
            log_printf( &logger, "Not activated.\r\n" );
        break;
        }
        case 0x01 :
        {
            log_printf( &logger, "Joining...\r\n" );
        break;
        }
        case 0x02 :
        {
            log_printf( &logger, "Joined.\r\n" );
        break;
        }
        case 0x03 :
        {
            log_printf( &logger, "MAC ERROR.\r\n" );
        break;
        }
        default :
        {
        break;
        }
    }
    log_printf( &logger, "***********************************************\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "** Next TX Data Rate setting...\r\n" );
    lr5_set_next_dr_cmd( &lr5, LR5_SF10_125KHZ );
    wait_response( );
    if ( response.cmd_data[ 0 ] == 0x00 )
    {
        log_printf( &logger, "Success!\r\n" );
    }
    else
    {
        log_printf( &logger, "Error!\r\n" );
    }
    log_printf( &logger, "***********************************************\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "** Channel parameters reading...\r\n" );
    lr5_get_ch_param_cmd( &lr5, LR5_CH_IDX_15 );
    wait_response( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
