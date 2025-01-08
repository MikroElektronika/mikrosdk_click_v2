
---
# SPI Extend Click

> [SPI Extend Click](https://www.mikroe.com/?pid_product=MIKROE-4184) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4184&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> In this example, if the connection is established, we read Accel axis of the connected Accel 14 Click boards to the SPI Extend Click ( Remote Mode ) which is connected by a LAN cable to 
SPI Extend Click ( Local Mode ) placed in the mikroBUS 1. Results are being sent to the Usart Terminal where you can track their changes. All data logs write on USB uart changes for every 1 sec.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIExtend

### Example Key Functions

- `spiextend_cfg_setup` Config Object Initialization function.
```c
void spiextend_cfg_setup ( spiextend_cfg_t *cfg );
```

- `spiextend_init` Initialization function.
```c
err_t spiextend_init ( spiextend_t *ctx, spiextend_cfg_t *cfg );
```

- `spiextend_default_cfg` Click Default Configuration function.
```c
err_t spiextend_default_cfg ( spiextend_t *ctx );
```

- `spiextend_get_config` Function get configuration of the LTC4332 SPI Extender Over Rugged Differential Link on the SPI Extend Click board.
```c
void spiextend_get_config ( spiextend_t *ctx, spiextend_config_data_t *config_data );
```

- `spiextend_set_config` Function set configuration of the LTC4332 SPI Extender Over Rugged Differential Link on the SPI Extend Click board.
```c
void spiextend_set_config ( spiextend_t *ctx, spiextend_config_data_t config_data );
```

- `spiextend_get_status` Function set configuration of the LTC4332 SPI Extender Over Rugged Differential Link on the SPI Extend Click board.
```c
void spiextend_get_status ( spiextend_t *ctx, spiextend_status_data_t *status_data );
```

### Application Init

> Initializes SPI, sets INT pin as input and AN, RST, CS nad PWM pins as outputs and begins to write log. Also, initialization driver enables - SPI, set default configuration of the Accel 14 Click
connected to the SPI Extend Click ( Remote Mode ).

```c
void application_init ( void ) 
{
    
    log_cfg_t log_cfg;                /**< Logger config object. */
    spiextend_cfg_t spiextend_cfg;    /**< Click config object. */

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
    log_info( &logger, " Application Init \r\n" );

    // Click initialization.

    spiextend_cfg_setup( &spiextend_cfg );
    SPIEXTEND_MAP_MIKROBUS( spiextend_cfg, MIKROBUS_1 );
    err_t init_flag  = spiextend_init( &spiextend, &spiextend_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
       
        log_error( &logger, " Application Init Error. \r\n" );
        log_info( &logger, " Please, run program again... \r\n" );

        for ( ; ; );
    }
    spiextend_default_cfg( &spiextend);
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   SPI Extend Click  \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
    
    spiextend_get_status( &spiextend, &spiextend_status );
    log_printf( &logger, " LINK        : " ); 
    
    spiextend_display_status( spiextend_status.nlink );
    log_printf( &logger, " INT         : " );
    
    spiextend_display_status( spiextend_status.nint );
    log_printf( &logger, " Remote INT  : " );
    spiextend_display_status( spiextend_status.rmt_nint );
    
    log_printf( &logger, " Speed Index : %d\r\n", ( uint16_t ) spiextend_status.speed_idx );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
    
    log_printf( &logger, "  >>> Accel 14 <<<   \r\n" );
    log_printf( &logger, " Set default config. \r\n" );
    spiextend_rmt_write ( &spiextend, SPIEXTEND_ACCEL14_REG_CTRL1_XL | SPIEXTEND_ACCEL14_SPI_WRITE, SPIEXTEND_ACCEL14_CTRL1_XL_POWER_UP | SPIEXTEND_ACCEL14_CTRL1_XL_HIGH_RES_FS | SPIEXTEND_ACCEL14_CTRL1_XL_GSEL_4G, SPIEXTEND_SLAVE_SELECT_SS1 );
    Delay_ms ( 100 );
    
    spiextend_rmt_write ( &spiextend, SPIEXTEND_ACCEL14_REG_CTRL3_C | SPIEXTEND_ACCEL14_SPI_WRITE, SPIEXTEND_ACCEL14_CTRL3_C_BOOT_NORMAL | SPIEXTEND_ACCEL14_CTRL3_C_BDU_READ_UPDATE | SPIEXTEND_ACCEL14_CTRL3_C_INT_ACTIVE_HIGH | SPIEXTEND_ACCEL14_CTRL3_C_PP_OD_PUSH_PULL | SPIEXTEND_ACCEL14_CTRL3_C_SIM_SPI_4_WIRE | SPIEXTEND_ACCEL14_CTRL3_C_IF_INC_ENABLE | SPIEXTEND_ACCEL14_CTRL3_C_SW_RESET_DIS, SPIEXTEND_SLAVE_SELECT_SS1 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Acceleration data: \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task \r\n" );
}
```

### Application Task

> If the Click is connected properly then the status becomes active and the X-axis coordinate is printed first on the UART terminal, then Y and finally Z. After 1s the process is repeated. 
In case an error has occurred, printed "LINK is not established" on UART Terminal.

```c
void application_task ( void ) 
{
    
    //  Task implementation.
    
    spiextend_get_status( &spiextend, &spiextend_status );
    
    if ( spiextend_status.nlink == SPIEXTEND_STATUS_ACTIVE ) {
        
        spiextend_accel14_get_axis( SPIEXTEND_ACCEL14_REG_OUTX_L_A );
        Delay_ms ( 10 );
        log_printf( &logger, "  Accel X : %d \r\n", axis );
        
        spiextend_accel14_get_axis( SPIEXTEND_ACCEL14_REG_OUTY_L_A );
        Delay_ms ( 10 );
        log_printf( &logger, "  Accel Y : %d \r\n", axis );

        spiextend_accel14_get_axis( SPIEXTEND_ACCEL14_REG_OUTZ_L_A );
        Delay_ms ( 10 );
        log_printf( &logger, "  Accel Z : %d \r\n", axis );

        log_printf( &logger, "---------------------\r\n" );
        Delay_ms ( 1000 );
    }
    else {
        
        log_printf( &logger, " LINK not established\r\n" );
        log_printf( &logger, "---------------------\r\n" );
        Delay_ms ( 1000 );
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
