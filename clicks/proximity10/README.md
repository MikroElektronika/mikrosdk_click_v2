
---
# Proximity 10 Click

> [Proximity 10 Click](https://www.mikroe.com/?pid_product=MIKROE-3455) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3455&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application enables proximity sensor to detect objects from distance up to 20cm.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity10

### Example Key Functions

- `proximity10_cfg_setup` Config Object Initialization function. 
```c
void proximity10_cfg_setup ( proximity10_cfg_t *cfg );
``` 
 
- `proximity10_init` Initialization function. 
```c
err_t proximity10_init ( proximity10_t *ctx, proximity10_cfg_t *cfg );
```

- `proximity10_default_cfg` Click Default Configuration function. 
```c
void proximity10_default_cfg ( proximity10_t *ctx );
```

- `proximity10_check_int_status` This function checks the desired interrupt flags status. 
```c
uint8_t proximity10_check_int_status ( proximity10_t *ctx, uint8_t bit_mask, uint8_t clear_en );
```
 
- `proximity10_send_command` This function allows user to execute a desired command and checks the response. 
```c
uint8_t proximity10_send_command ( proximity10_t *ctx, uint8_t prox_command );
```

- `proximity10_param_set` This function sets the selected parameter to the desired value, and checks the response. 
```c
uint8_t proximity10_param_set ( proximity10_t *ctx, uint8_t param_addr, uint8_t param_value );
```

### Application Init

> Initializes I2C serial interface and performs a device wake up, reset and 
> all necessary configurations.
> The device will wake up and performs measurements every 10 milliseconds.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity10_cfg_t cfg;

    uint8_t w_temp;
    uint8_t cmd_resp;

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

    proximity10_cfg_setup( &cfg );
    PROXIMITY10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity10_init( &proximity10, &cfg );

    Delay_ms ( 500 );

    w_temp = PROXIMITY10_HW_KEY;
    proximity10_generic_write( &proximity10, PROXIMITY10_HW_KEY_REG, &w_temp, 1 );
    
    cmd_resp = proximity10_send_command( &proximity10, PROXIMITY10_NOP_CMD );
    check_response( cmd_resp );
    cmd_resp = proximity10_send_command( &proximity10, PROXIMITY10_RESET_CMD );
    check_response( cmd_resp );
    Delay_ms ( 200 );
    
    cmd_resp = proximity10_param_set( &proximity10, PROXIMITY10_CHLIST_PARAM, PROXIMITY10_EN_AUX | PROXIMITY10_EN_ALS_IR | PROXIMITY10_EN_ALS_VIS | PROXIMITY10_EN_PS1 );
    check_response( cmd_resp );
    cmd_resp = proximity10_param_set( &proximity10, PROXIMITY10_PSLED12_SEL_PARAM, PROXIMITY10_LED1_DRIVE_EN );
    check_response( cmd_resp );
    cmd_resp = proximity10_param_set( &proximity10, PROXIMITY10_PS_ADC_MISC_PARAM, PROXIMITY10_NORMAL_SIGNAL_RANGE | PROXIMITY10_NORMAL_PROX_MEAS_MODE );
    check_response( cmd_resp );
    cmd_resp = proximity10_param_set( &proximity10, PROXIMITY10_PS_ADC_GAIN_PARAM, PROXIMITY10_ADC_CLOCK_DIV_4 );
    check_response( cmd_resp );

    proximity10_default_cfg ( &proximity10 );

    cmd_resp = proximity10_send_command( &proximity10, PROXIMITY10_PS_AUTO_CMD );
    check_response( cmd_resp );
    
    //Sound_Init( &GPIOE_ODR, 14 ); //??
    
    log_printf( &logger, "** Proximity 10 is initialized **\r\n" );
    log_printf( &logger, "**************************************\r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

> Reads the proximity PS1 data value and sends result to the uart terminal.
> If measured proximity value is greater than selected proximity threshold value, the interrupt will be generated and
> the message will be showed on the uart terminal.
> When interrupt is generated the Sound function will make an alarm sound with determined duration depending on the    > detected proximity value,
> how much is object away or close from the sensor.


```c
void application_task ( void )
{
    //  Task implementation.

    uint32_t proximity;
    uint8_t temp_read[ 2 ];
    uint8_t int_status;
    uint16_t alarm_dur;

    proximity10_generic_read( &proximity10, PROXIMITY10_PS1_DATA_REG, &temp_read, 2 );
    proximity = temp_read[ 1 ];
    proximity <<= 8;
    proximity |= temp_read[ 0 ];
    
    log_printf( &logger, "** Proximity PS1 : %u \r\n", proximity );
    
    int_status = proximity10_check_int_status( &proximity10, PROXIMITY10_PS1_INT_FLAG, PROXIMITY10_INT_CLEAR_DIS );
    
    if ( int_status == PROXIMITY10_PS1_INT_FLAG )
    {
        log_printf( &logger, "** Object is detected **\r\n" );
        
        alarm_dur = proximity / 100;
        alarm_dur = alarm_dur + 35;
        alarm_dur = ( float )( alarm_dur * 0.30928 );
        alarm_dur = 180 - alarm_dur;
        
       // Sound_Play( 1400, alarm_dur );  //??
        Delay_ms ( 100 );
    }
    else
    {
        Delay_ms ( 200 );
    }
    log_printf( &logger, "**************************************\r\n" );
}
```

### Note

> Additional Functions :
> - checkResponse - Sends an error code message to the uart terminal if error code is detected in the response.

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
