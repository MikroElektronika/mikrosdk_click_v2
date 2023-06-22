/*!
 * @file main.c
 * @brief SWI EEPROM Click Example.
 *
 * # Description
 * This example demonstrates the use of SWI EEPROM click board by writing specified data to
 * the memory and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and checks the communication.
 *
 * ## Application Task
 * Writes the specified text message to the memory and reads it back. After that, erases
 * the whole memory and tries to read the same message verifying that the memory is erased.
 * All data is being displayed on the USB UART where you can track the program flow.
 *
 * @note
 * This application is written for the following MCUs and specifically for MIKROBUS 1:
 * STM32F407ZG, MK64FN1M0VDC12, TM4C129XNCZAD, GD32VF103VBT6, PIC32MX795F512L
 * In order to use it on another MCUs the pin_x functions must be defined in a way
 * it matches the required timing specifications for the Single Wire interface.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "swieeprom.h"

#define DEMO_TEXT_MESSAGE       "MIKROE"
#define STARTING_ADDRESS        0x00

static swieeprom_t swieeprom;   /**< SWI EEPROM Click driver object. */
static log_t logger;    /**< Logger object. */

/**
 * @brief Pin init function.
 * @details This function initializes the SIO pin.
 * @return None.
 * @note By default it initializes the SIO pin to the PWM pin from MIKROBUS 1.
 * The implementation differs from MCU to MCU.
 */
static void pin_init( void );

/**
 * @brief Pin low function.
 * @details This function sets the SIO pin to LOW logic level.
 * @return None.
 * @note The pin it uses should match the one that is initialized using the pin_init function.
 * The implementation differs from MCU to MCU.
 */
static void pin_low( void );

/**
 * @brief Pin release function.
 * @details This function releases the SIO pin by setting it to digital input.
 * @return None.
 * @note The pin it uses should match the one that is initialized using the pin_init function.
 * The implementation differs from MCU to MCU.
 */
static void pin_release( void );

/**
 * @brief Pin get function.
 * @details This function returns the SIO pin logic state.
 * @return Pin logic state.
 * @note The pin it uses should match the one that is initialized using the pin_init function.
 * The implementation differs from MCU to MCU.
 */
static uint8_t pin_get( void );

/**
 * @brief SWI EEPROM reset function.
 * @details This function initializes the SIO pin and performs the SWI reset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t swieeprom_reset ( void );

/**
 * @brief SWI EEPROM start stop function.
 * @details This function sends the SWI start/stop signal.
 * @return None.
 * @note None.
 */
static void swieeprom_start_stop ( void );

/**
 * @brief SWI EEPROM logic write 0 function.
 * @details This function sends the SWI logic zero signal.
 * @return None.
 * @note None.
 */
static void swieeprom_logic_write_0 ( void );

/**
 * @brief SWI EEPROM logic write 1 function.
 * @details This function sends the SWI logic one signal.
 * @return None.
 * @note None.
 */
static void swieeprom_logic_write_1 ( void );

/**
 * @brief SWI EEPROM logic read function.
 * @details This function reads the SWI logic state.
 * @return None.
 * @note None.
 */
static uint8_t swieeprom_logic_read ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */

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
    swieeprom.swi_reset = &swieeprom_reset;
    swieeprom.swi_start_stop = &swieeprom_start_stop;
    swieeprom.swi_logic_0 = &swieeprom_logic_write_0;
    swieeprom.swi_logic_1 = &swieeprom_logic_write_1;
    swieeprom.swi_logic_read = &swieeprom_logic_read;
    if ( SWIEEPROM_ERROR == swieeprom_init ( &swieeprom ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SWIEEPROM_ERROR == swieeprom_check_communication ( &swieeprom ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t data_buf[ 8 ] = { 0 };
    // Write data to the specified address
    log_printf ( &logger, " Memory address: 0x%.2X\r\n", ( uint16_t ) STARTING_ADDRESS );
    memcpy ( data_buf, DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) );
    if ( SWIEEPROM_OK == swieeprom_mem_write_page ( &swieeprom, STARTING_ADDRESS, 
                                                    data_buf, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    // Read data from the specified address to verify the previous memory write
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( SWIEEPROM_OK == swieeprom_mem_read ( &swieeprom, STARTING_ADDRESS, 
                                              data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n", data_buf );
        Delay_ms ( 2000 );
    }
    // Clear whole memory
    if ( SWIEEPROM_OK == swieeprom_mem_clear ( &swieeprom ) )
    {
        log_printf ( &logger, " Memory clear\r\n" );
        Delay_ms ( 100 );
    }
    // Read data from the specified address to verify the previous memory clear
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( SWIEEPROM_OK == swieeprom_mem_read ( &swieeprom, STARTING_ADDRESS, 
                                              data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 2000 );
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

#ifdef STM32F407ZG
void pin_init( void ) 
{ 
    digital_in_t sio_in;
    digital_in_init ( &sio_in, PD12 );
}

void pin_low( void ) 
{ 
    if ( !GPIOD_MODER.B24 ) 
    { 
        GPIOD_MODER.B24 = 1; 
    }
    GPIOD_ODR.B12 = 0;
}

void pin_release( void )
{ 
    if ( GPIOD_MODER.B24 ) 
    { 
        GPIOD_MODER.B24 = 0; 
    }
}

uint8_t pin_get( void )
{
    if ( GPIOD_MODER.B24 ) 
    { 
        GPIOD_MODER.B24 = 0; 
    }
    return GPIOD_IDR.B12;
}
#elif MK64FN1M0VDC12
void pin_init( void ) 
{ 
    digital_in_t sio_in;
    digital_in_init ( &sio_in, PE6 );
}

void pin_low( void ) 
{ 
    if ( !GPIOE_PDDR.B6 ) 
    { 
        GPIOE_PDDR.B6 = 1; 
    }
    GPIOE_PDOR.B6 = 0;
}

void pin_release( void )
{ 
    if ( GPIOE_PDDR.B6 ) 
    { 
        GPIOE_PDDR.B6 = 0; 
    }
}

uint8_t pin_get( void )
{
    if ( GPIOE_PDDR.B6 ) 
    { 
        GPIOE_PDDR.B6 = 0; 
    }
    return GPIOE_PDIR.B6;
}
#elif TM4C129XNCZAD
void pin_init( void ) 
{ 
    digital_in_t sio_in;
    digital_in_init ( &sio_in, PD0 );
}

void pin_low( void ) 
{ 
    if ( !GPIO_PORTD_AHB_DIR.B0 ) 
    { 
        GPIO_PORTD_AHB_DIR.B0 = 1; 
    }
    GPIO_PORTD_AHB_DATA.B0 = 0;
}

void pin_release( void )
{ 
    if ( GPIO_PORTD_AHB_DIR.B0 ) 
    { 
        GPIO_PORTD_AHB_DIR.B0 = 0; 
    }
}

uint8_t pin_get( void )
{
    if ( GPIO_PORTD_AHB_DIR.B0 ) 
    { 
        GPIO_PORTD_AHB_DIR.B0 = 0; 
    }
    return GPIO_PORTD_AHB_DATA.B0;
}
#elif GD32VF103VBT6
#define GPIOC9_CTL1_MASK    ( ( uint32_t ) 0x000000F0 )
#define GPIOC9_IO_MASK      ( ( uint32_t ) 0x00000200 )
#define GPIOC_CTL1          ( *( uint32_t * ) 0x40011004 )
#define GPIOC_ISTAT         ( *( uint32_t * ) 0x40011008 )
#define GPIOC_OCTL          ( *( uint32_t * ) 0x4001100C )

void pin_init( void ) 
{
    static digital_in_t sio_in;
    digital_in_init ( &sio_in, PC9 );
}

void pin_low( void ) 
{ 
    if ( ( GPIO_CFG_DIGITAL_INPUT << 4 ) == ( GPIOC_CTL1 & GPIOC9_CTL1_MASK ) ) 
    { 
        GPIOC_CTL1 = ( GPIOC_CTL1 & ~( GPIOC9_CTL1_MASK ) ) | ( GPIO_CFG_DIGITAL_OUTPUT << 4 );
    }
    GPIOC_OCTL &= ~GPIOC9_IO_MASK;
}

void pin_release( void )
{ 
    if ( ( GPIO_CFG_DIGITAL_OUTPUT << 4 ) == ( GPIOC_CTL1 & GPIOC9_CTL1_MASK ) ) 
    { 
        GPIOC_CTL1 = ( GPIOC_CTL1 & ~( GPIOC9_CTL1_MASK ) ) | ( GPIO_CFG_DIGITAL_INPUT << 4 );
    }
}

uint8_t pin_get( void )
{
    if ( ( GPIO_CFG_DIGITAL_OUTPUT << 4 ) == ( GPIOC_CTL1 & GPIOC9_CTL1_MASK ) ) 
    { 
        GPIOC_CTL1 = ( GPIOC_CTL1 & ~( GPIOC9_CTL1_MASK ) ) | ( GPIO_CFG_DIGITAL_INPUT << 4 );
    }
    return ( GPIOC9_IO_MASK == ( GPIOC_ISTAT & GPIOC9_IO_MASK ) );
}
#elif PIC32MX795F512L
void pin_init( void ) 
{ 
    digital_in_t sio_in;
    digital_in_init ( &sio_in, PD1 );
}

void pin_low( void ) 
{ 
    if ( TRISD1_bit ) 
    { 
        TRISD1_bit = 0; 
    }
    LATD1_bit = 0;
}

void pin_release( void )
{ 
    if ( !TRISD1_bit ) 
    { 
        TRISD1_bit = 1; 
    }
}

uint8_t pin_get( void )
{
    if ( !TRISD1_bit ) 
    { 
        TRISD1_bit = 1; 
    }
    return RD1_bit;
}
#else
    #error "Pin functions are not defined for the selected system"
#endif

static err_t swieeprom_reset ( void )
{
    // Pin initialization
    pin_init ( );
    
    // Reset
    pin_low ( );
    // tDSCHG delay: 150+us
    Delay_80us( );
    Delay_80us( );
    pin_release ( );
    // tRRT delay: 8+us
    Delay_10us( );
    
    // Discovery
    pin_low ( );
    // tDRR delay: 1-2us
    Delay_1us( );
    pin_release ( );
    // tDACK delay: 8-24us
    Delay_10us( );
    
    if ( pin_get ( ) )
    {
        return SWIEEPROM_ERROR;
    }
    return SWIEEPROM_OK;
}

static void swieeprom_start_stop ( void )
{
    pin_release ( );
    // tHTSS delay: 150+us
    Delay_80us( );
    Delay_80us( );
}

static void swieeprom_logic_write_0 ( void )
{
    pin_low ( );
    // tLOW0 delay: 6-16us
    Delay_10us( );
    pin_release ( );
    // tBIT - tLOW0 delay: 8-24us - 6-16us
    Delay_6us( );
}

static void swieeprom_logic_write_1 ( void )
{
    pin_low ( );
    // tLOW1 delay: 1-2us
    Delay_1us( );
    pin_release ( );
    // tBIT - tLOW1 delay: 8-24us - 1-2us
    Delay_10us( );
    Delay_5us( );
}

static uint8_t swieeprom_logic_read ( void )
{
    pin_low ( );
    // tRD delay: 1-2us
    Delay_1us( );
    pin_release ( );
    // tMRS delay: 1-2us
    Delay_1us( );
    uint8_t pin_state = pin_get ( );
    // tBIT - tRD - tMRS delay: 8-24us - 1-2us - 1-2us
    Delay_9us( );
    Delay_5us( );
    return pin_state;
}

// ------------------------------------------------------------------------ END
