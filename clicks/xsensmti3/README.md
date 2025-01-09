
---
# XSENS MTi-3 Click

> [XSENS MTi-3 Click](https://www.mikroe.com/?pid_product=MIKROE-4192) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4192&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mikroe Team
- **Date**          : Sep 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from XSENS MTi-3 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.XSENSMTi3

### Example Key Functions

- `xsensmti3_cfg_setup` Config Object Initialization function.
```c
void xsensmti3_cfg_setup ( xsensmti3_cfg_t *cfg );
```

- `xsensmti3_init` Initialization function.
```c
err_t xsensmti3_init ( xsensmti3_t *ctx, xsensmti3_cfg_t *cfg );
```

- `xsensmti3_parser` XSENS MTi-3 general parser.
```c
void xsensmti3_parser ( uint8_t *rsp_buf, uint8_t start_cnt, xsensmti3_parse_t *obj );
```

- `xsensmti3_get_data` XSENS MTi-3 get Roll, Pitch and Yaw.
```c
void xsensmti3_get_data( xsensmti3_quat_t *quat_obj, xsensmti3_data_t *data_obj );
```

- `xsensmti3_check_package` XSENS MTi-3 checks package.
```c
err_t xsensmti3_check_package( uint8_t *package_buf, uint8_t *start_package );
```

### Application Init

> Initializes driver and wake-up module.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xsensmti3_cfg_t xsensmti3_cfg;  /**< Click config object. */

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
    xsensmti3_cfg_setup( &xsensmti3_cfg );
    XSENSMTI3_MAP_MIKROBUS( xsensmti3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xsensmti3_init( &xsensmti3, &xsensmti3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data and parses it. Shows Roll, Pitch and Yaw data.

```c
void application_task ( void ) 
{
    uint8_t check_data = 0;
    uint8_t cnt = 0;

    xsensmti3_process( );

    // STARTS COLLECTING DATA
    if ( active_flag == XSENSMTI3_WAIT_FOR_START )
    {
        memset( &current_parser_buf[ 0 ], 0 , PROCESS_PARSER_BUFFER_SIZE );
        parser_buf_cnt = 0;
        active_flag = 0;
        start_rsp = 0;
        rsp_cnt = 0;
        active_flag = XSENSMTI3_START_PROCESS;
    }

    if ( ( parser_buf_cnt > 100 ) && ( active_flag == XSENSMTI3_START_PROCESS ) )
    {
       active_flag = XSENSMTI3_DATA_PROCESSING;
    }

    if ( active_flag == XSENSMTI3_DATA_PROCESSING )
    {
        check_data = xsensmti3_check_package( &current_parser_buf[ 0 ], &start_rsp );
        if ( check_data == XSENSMTI3_OK )
        {
            active_flag = XSENSMTI3_PARSER_DATA;
        }
        else
        {
            active_flag = XSENSMTI3_WAIT_FOR_START;
        }
    }

    if ( active_flag == XSENSMTI3_PARSER_DATA )
    {
       xsensmti3_parser( &current_parser_buf[ 0 ], start_rsp, &parse_data_obj );

       log_printf( &logger, ">> Quaternion data <<\r\n" );

       for ( cnt = 0; cnt < 4; cnt++ )
       {
           log_printf( &logger, ">> Q: %f\r\n", parse_data_obj.quat_obj.quat_data[ cnt ] );
       }

       log_printf( &logger, "--------------\r\n" );

       xsensmti3_get_data( &parse_data_obj.quat_obj, &data_obj );

       log_printf( &logger, ">> ROLL:  %.4f \r\n", data_obj.roll );
       log_printf( &logger, ">> PITCH: %.4f \r\n", data_obj.pitch );
       log_printf( &logger, ">> YAW:   %.4f \r\n", data_obj.yaw );

       active_flag = XSENSMTI3_WAIT_FOR_START;

       log_printf( &logger, "--------------\r\n" );
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
