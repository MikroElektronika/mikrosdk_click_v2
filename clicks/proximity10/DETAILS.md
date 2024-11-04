
---
# Proximity 10 Click

Proximity 10 Click is a versatile proximity detection device on a Click board™. It can detect a foreign object distanced up to 20cm.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity10_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/proximity-10-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity10 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity10 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proximity10_cfg_setup ( proximity10_cfg_t *cfg ); 
 
- Initialization function.
> PROXIMITY10_RETVAL proximity10_init ( proximity10_t *ctx, proximity10_cfg_t *cfg );

- Click Default Configuration function.
> void proximity10_default_cfg ( proximity10_t *ctx );


#### Example key functions :

- This function checks the desired interrupt flags status.
> uint8_t proximity10_check_int_status ( proximity10_t *ctx, uint8_t bit_mask, uint8_t clear_en );
 
- This function allows user to execute a desired command and checks the response.
> uint8_t proximity10_send_command ( proximity10_t *ctx, uint8_t prox_command );

- This function sets the selected parameter to the desired value, and checks the response.
> uint8_t proximity10_param_set ( proximity10_t *ctx, uint8_t param_addr, uint8_t param_value );

## Examples Description

> This application enables proximity sensor to detect objects from distance up to 20cm.

**The demo application is composed of two sections :**

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

## Note

> Additional Functions :
> - checkResponse - Sends an error code message to the uart terminal if error code is detected in the response.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity10

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---