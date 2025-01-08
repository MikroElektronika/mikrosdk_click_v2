
---
# H Bridge 3 Click

> [H-Bridge 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3613) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3613&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> H-bridge in general, allows the current to flow in one or another direction.
> This Click is used for drive a H-Bridge motor by changing output states. 
> The outputs can be pulse width modulated at frequencies up to 20kHz by means of PWM/DIR control. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge3

### Example Key Functions

- `hbridge3_cfg_setup` Config Object Initialization function. 
```c
void hbridge3_cfg_setup ( hbridge3_cfg_t *cfg );
``` 
 
- `hbridge3_init` Initialization function. 
```c
err_t hbridge3_init ( hbridge3_t *ctx, hbridge3_cfg_t *cfg );
```

- `hbridge3_default_cfg` Click Default Configuration function. 
```c
void hbridge3_default_cfg ( hbridge3_t *ctx );
```

- `hbridge3_set_duty_cycle` This function sets the PWM duty cycle. 
```c
void hbridge3_set_duty_cycle ( hbridge3_t *ctx, pwm_data_t duty_cycle );
```
 
- `hbridge3_spi` This function sends SPI command and receives response to command sent. 
```c
uint8_t hbridge3_spi ( hbridge3_t *ctx, uint8_t spi_command );
```

- `hbridge3_generic_transfer` Generic SPI transfer, for sending and receiving packages. 
```c
void hbridge3_generic_transfer ( hbridge3_t *ctx, spi_master_transfer_data_t *block );
```

### Application Init

> Initializes SPI and LOG modules, AN, RST, CS and PWM pins

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge3_cfg_t cfg;

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

    hbridge3_cfg_setup( &cfg );
    HBRIDGE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge3_init( &hbridge3, &cfg );
    Delay_ms ( 500 );
    
    hbridge3_pwm_start( &hbridge3 );
    log_info( &logger, "---- Application Task ----" );
    log_printf( &logger, "> CLOCKWISE <\r\n" );
}
```

### Application Task

>  This example demonstrates the use of H-Bridge 3 Click board, 
>  by running dc motor in both directions - increasing and decreasing PWM duty cycle.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;


    hbridge3_set_duty_cycle ( &hbridge3, duty );
    log_printf( &logger, " Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        
        if ( motor_direction == 1 )
        {
            log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
            motor_direction = 0;
             hbridge3_dir_set ( &hbridge3 , 0 );
        }
        else if ( motor_direction == 0 )
        {
            log_printf( &logger, "> CLOCKWISE <\r\n" );
            motor_direction = 1;
            hbridge3_dir_set ( &hbridge3 , 1 );
        }
    }
    duty_cnt += duty_inc;
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
