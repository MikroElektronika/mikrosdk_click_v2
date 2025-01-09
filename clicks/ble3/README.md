
---
# BLE 3 Click

> [BLE 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2471) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2471&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type

# Software Support

## Example Description

> This example reads and processes data from BLE 3 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ble3

### Example Key Functions

- `ble3_cfg_setup` Config Object Initialization function. 
```c
void ble3_cfg_setup ( ble3_cfg_t *cfg );
``` 
 
- `ble3_init` Initialization function. 
```c
err_t ble3_init ( ble3_t *ctx, ble3_cfg_t *cfg );
```

- `ble3_generic_read` Generic read function. 
```c
int32_t ble3_generic_read ( ble3_t *ctx, char *data_buf, uint16_t max_len );
```

- `ble3_generic_write` Generic write function. 
```c
void ble3_generic_write ( ble3_t *ctx, char *data_buf, uint16_t len );
``` 

### Application Init

> Initializes driver and wake-up module.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ble3_cfg_t cfg;
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

    ble3_cfg_setup( &cfg );
    BLE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble3_init( &ble3, &cfg );
    
    log_printf( &logger, "Configuring the module...\n" );
    Delay_1sec( );
    
    do {
        ble3_generic_write( &ble3, AT, (uint16_t) strlen( AT ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, ATE1, (uint16_t) strlen( ATE1 ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, AT_UBTLN, (uint16_t) strlen( AT_UBTLN ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, AT_UBTDM, (uint16_t) strlen( AT_UBTDM ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, AT_UBTCM, (uint16_t) strlen( AT_UBTCM ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, AT_UBTPM, (uint16_t) strlen( AT_UBTPM ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, ATO1, (uint16_t) strlen( ATO1 ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    data_mode = 1;
    log_printf( &logger, "The module has been configured.\n" );
}
```

### Application Task

> Reads the received data.

```c
void application_task ( void )
{
    ble3_process(  );
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
