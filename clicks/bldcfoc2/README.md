
---
# BLDC FOC 2 Click

> [BLDC FOC 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6681) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6681&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2025.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the control of a 3-phase brushless DC motor using 
the BLDC FOC 2 Click board. The motor speed is gradually increased and 
decreased while changing direction on each cycle. The example also includes 
an optional EEPROM programming step if enabled via macro.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BLDCFOC2

### Example Key Functions

- `bldcfoc2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void bldcfoc2_cfg_setup ( bldcfoc2_cfg_t *cfg );
```

- `bldcfoc2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t bldcfoc2_init ( bldcfoc2_t *ctx, bldcfoc2_cfg_t *cfg );
```

- `bldcfoc2_default_cfg` This function executes a default configuration of BLDC FOC 2 Click board.
```c
err_t bldcfoc2_default_cfg ( bldcfoc2_t *ctx );
```

- `bldcfoc2_eeprom_set_config` This function sets the default EEPROM configuration for the motor F80 PRO KV1900, optimized for 11.2V 10A power supply and PWM input range 10-50% at 20kHz.
```c
err_t bldcfoc2_eeprom_set_config ( bldcfoc2_t *ctx );
```

- `bldcfoc2_set_duty_cycle` This function sets the PWM duty cycle used to control the motor speed.
```c
err_t bldcfoc2_set_duty_cycle ( bldcfoc2_t *ctx, float duty_cycle );
```

- `bldcfoc2_switch_direction` This function toggles the motor rotation direction by inverting the DIR pin state.
```c
void bldcfoc2_switch_direction ( bldcfoc2_t *ctx );
```

### Application Init

> Initializes the logger and the Click board driver, applies the default configuration, and optionally programs the EEPROM if enabled.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bldcfoc2_cfg_t bldcfoc2_cfg;  /**< Click config object. */

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
    bldcfoc2_cfg_setup( &bldcfoc2_cfg );
    BLDCFOC2_MAP_MIKROBUS( bldcfoc2_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == bldcfoc2_init( &bldcfoc2, &bldcfoc2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( BLDCFOC2_ERROR == bldcfoc2_default_cfg ( &bldcfoc2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

#if ( 1 == BLDCFOC2_PROGRAM_EEPROM )
    bldcfoc2_pull_brake ( &bldcfoc2 );
    log_printf( &logger, " Configuring EEPROM in 5 seconds...\r\n" );
    log_printf( &logger, " Set PROG SEL on-board switches to SCL/SDA positions.\r\n" );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( BLDCFOC2_ERROR == bldcfoc2_eeprom_set_config ( &bldcfoc2 ) )
    {
        log_error( &logger, " EEPROM configuration." );
        for ( ; ; );
    }
    log_printf( &logger, " EEPROM configured successfully\r\n\n" );
    log_printf( &logger, " Driving motor in 5 seconds...\r\n" );
    log_printf( &logger, " Set PROG SEL on-board switches to SPD/FGO positions.\r\n" );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    bldcfoc2_release_brake ( &bldcfoc2 );
#endif
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Gradually ramps the motor speed up and down, applies brake and switches direction on each full speed cycle. Speed is controlled via PWM duty cycle.

```c
void application_task ( void )
{
    static int8_t speed = BLDCFOC2_SPEED_START;
    static int8_t speed_step = 1;
    
    bldcfoc2_set_duty_cycle ( &bldcfoc2, ( float ) speed / BLDCFOC2_SPEED_TO_DUTY );
    log_printf( &logger, " Speed: %u%%\r\n\n", ( uint16_t ) speed );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( BLDCFOC2_SPEED_MAX == speed ) 
    {
        speed_step = -speed_step;
    }
    else if ( BLDCFOC2_SPEED_MIN == speed ) 
    {
        speed_step = -speed_step;
        log_printf( &logger, " Pull brake\r\n\n" );
        bldcfoc2_pull_brake ( &bldcfoc2 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Switch direction\r\n\n" );
        bldcfoc2_switch_direction ( &bldcfoc2 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Release brake\r\n\n" );
        bldcfoc2_release_brake ( &bldcfoc2 );
        Delay_ms ( 1000 );
        speed = BLDCFOC2_SPEED_START - 1;
    }
    speed += speed_step;
}
```

### Note

> To program the EEPROM, set the @c BLDCFOC2_PROGRAM_EEPROM macro to 1 
and ensure that the on-board PROG SEL switch is set to SCL/SDA during 
EEPROM programming, then returned to SPD/FGO before motor drive.
The default EEPROM configuration is optimized for the motor F80 PRO KV1900,
11.2V 10A power supply and PWM input range 10-50% at 20kHz.

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
