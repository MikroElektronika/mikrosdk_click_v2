\mainpage Main Page
 
---
# PWR Meter click

PWR Meter click is a power measurement Click board™, capable of measuring voltage and current through the load, connected to either AC or DC power source. PWR Meter click uses the MCP39F511A, a very sophisticated monitoring IC from Microchip, with 16-bit processing core.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pwrmeter_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pwr-meter-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the PwrMeter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for PwrMeter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pwrmeter_cfg_setup ( pwrmeter_cfg_t *cfg ); 
 
- Initialization function.
> PWRMETER_RETVAL pwrmeter_init ( pwrmeter_t *ctx, pwrmeter_cfg_t *cfg );


#### Example key functions :

- Function reads 16-bit data from the desired register.
> PWRMETER_RETVAL pwrmeter_read_reg_word ( pwrmeter_t *ctx, uint16_t register_addr, uint16_t *data_out );
 
- Function reads 32-bit data from the desired register.
> PWRMETER_RETVAL pwrmeter_read_reg_dword ( pwrmeter_t *ctx, uint16_t register_addr, uint32_t *data_out );

- Function reads signed 16bit or 32bit data from the desired register.
> PWRMETER_RETVAL pwrmeter_read_reg_signed ( pwrmeter_t *ctx, uint16_t register_addr, uint8_t data_mode, int32_t *data_out );

## Examples Description

> This click is capable of measuring voltage and current through the load, connected to either 
> AC or DC power source. It is used to calculate all the measurement parameters, returning 
> values of multiple power parameters directly, over the UART interface, reducing the processing 
> load on the host MCU. These parameters include active, reactive, and apparent power, current 
> and voltage RMS, line frequency, and power factor.

**The demo application is composed of two sections :**

### Application Init 

> Initializes UART interface, puts output of regulator in active state and
> configures gain channel and uart baud rate.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pwrmeter_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    pwrmeter_cfg_setup( &cfg );
    PWRMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwrmeter_init( &pwrmeter, &cfg );
    Delay_ms ( 500 );
    
    pwrmeter_enable( &pwrmeter, PWRMETER_ENABLE );
    Delay_ms ( 100 );
    
    response_byte = pwrmeter_write_reg_dword ( &pwrmeter, PWRMETER_SYS_CONFIG_REG, PWRMETER_VOLT_GAIN_1 | PWRMETER_CURR_GAIN_8 | PWRMETER_UART_BR_9600 );
    check_response( );
    response_byte = pwrmeter_send_command( &pwrmeter, PWRMETER_SAVE_TO_FLASH_COMM );
    check_response( );

    log_printf( &logger, "PWR Meter is initialized\r\n" );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Reads voltage, current and power measurements from data registers, then converts this values
> to determined units and logs all results on uart terminal each second.

```c

void application_task ( void )
{
    response_byte = pwrmeter_read_reg_word( &pwrmeter, PWRMETER_VOLT_RMS_REG, &voltage_rms );
    check_response( );
    response_byte = pwrmeter_read_reg_dword( &pwrmeter, PWRMETER_CURR_RMS_REG, &current_rms );
    check_response( );
    response_byte = pwrmeter_read_reg_dword( &pwrmeter, PWRMETER_ACTIVE_PWR_REG, &active_power );
    check_response( );
    response_byte = pwrmeter_read_reg_dword( &pwrmeter, PWRMETER_REACTIVE_PWR_REG, &reactive_power );
    check_response( );
    response_byte = pwrmeter_read_reg_dword( &pwrmeter, PWRMETER_APPARENT_PWR_REG, &apparent_power );
    check_response( );
    response_byte = pwrmeter_read_reg_signed( &pwrmeter, PWRMETER_PWR_FACTOR_REG, PWRMETER_16BIT_DATA, &power_factor );
    check_response( );
    
    meas_data[ 0 ] = ( float ) voltage_rms / 100;
    meas_data[ 1 ] = ( float ) current_rms / 1000;
    meas_data[ 2 ] = ( float ) active_power / 100000;
    meas_data[ 3 ] = ( float ) reactive_power / 100000;
    meas_data[ 4 ] = ( float ) apparent_power / 100000;
    meas_data[ 5 ] = ( float ) power_factor / 32767;
    
    response_byte = pwrmeter_get_status( &pwrmeter, &status_byte );
    check_response( );
    
    if ( ( status_byte & PWRMETER_DCMODE_MASK ) != 0 )
    {
        log_printf( &logger, "DC mode\r\n" );
    }
    else
    {
        log_printf( &logger, "AC mode\r\n" );
    }
    

    log_printf( &logger, "RMS voltage:  " );
    if ( ( ( status_byte & PWRMETER_DCMODE_MASK ) != 0) && ( ( status_byte & PWRMETER_DCVOLT_SIGN_MASK ) == 0 ) )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%.2f[ V ]\r\n", meas_data[ 0 ] );
    
    
    log_printf( &logger, "RMS current:  " );
    if ( ( ( status_byte & PWRMETER_DCMODE_MASK ) != 0 ) && ( ( status_byte & PWRMETER_DCCURR_SIGN_MASK ) == 0 ) )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%.2f[ mA ]\r\n", meas_data[ 1 ] );
    
    
    log_printf( &logger, "Active power:  " );
    if ( ( status_byte & PWRMETER_PA_SIGN_MASK ) == 0 )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%.2f[ W ]\r\n", meas_data[ 2 ] );
    
    
    log_printf( &logger, "Reactive power:  " );
    if ( ( status_byte & PWRMETER_PR_SIGN_MASK ) == 0 )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%.2f[ VAr ]\r\n", meas_data[ 3 ] );
    
   
    log_printf( &logger, "Apparent power:  " );
    log_printf( &logger, "%.2f[ VA ]\r\n", meas_data[ 4 ] );

    
    log_printf( &logger, "Power factor:  %.2f\r\n", meas_data[ 5 ] );
    log_printf( &logger, "-----------------------------------\r\n" );
    
    Delay_ms ( 1000 );
}
```

## Note

> Do not apply higher voltage than 60V to this board! This click is designed for lower voltage 
> monitoring and evaluation of the MCP39F511A and its basic functionalities. 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.PwrMeter

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
