/*******************************
 * stm32 minimal example main.c
 *******************************/
  
/* memory and peripheral start addresses */
#define FLASH_BASE      0x08000000
#define SRAM_BASE       0x20000000
#define PERIPH_BASE     0x40000000
 
/* work out end of RAM address as initial stack pointer */
#define SRAM_SIZE       20*1024     // STM32F103RB has 20 Kbye of RAM
#define SRAM_END        (SRAM_BASE + SRAM_SIZE)
 
/* LED connected to PIN 8 of GPIOA */
#define LED_PIN         7
#define OUTPUT_MODE     (0x10|0x03) // output mode: push-pull + 50MHz
 
/* RCC peripheral addresses applicable to GPIOA */
#define RCC_BASE        (PERIPH_BASE + 0x21000)
#define RCC_APB2ENR     (*(volatile unsigned long*)(RCC_BASE + 0x18))
 
/* GPIOA peripheral addresses */
#define GPIOA_BASE      (PERIPH_BASE + 0x10800)
#define GPIOA_CRL       (*(volatile unsigned long*)(GPIOA_BASE + 0x00))
#define GPIOA_CRH       (*(volatile unsigned long*)(GPIOA_BASE + 0x04))
#define GPIOA_BSRR      (*(volatile unsigned long*)(GPIOA_BASE + 0x10))
#define GPIOA_BRR       (*(volatile unsigned long*)(GPIOA_BASE + 0x14))
 
/* user functions */
int main(void);
void delay(unsigned long count);
 
/* vector table */
unsigned long *vector_table[] __attribute__((section(".vector_table"))) =
{
    (unsigned long *)SRAM_END,   // initial stack pointer 
    (unsigned long *)main        // main as Reset_Handler
};
 
int main()
{
    /* enable clock on GPIOA peripheral */
    RCC_APB2ENR = 0x04;
     
    /* set LED pin output mode */
    GPIOA_CRL |= OUTPUT_MODE << ((LED_PIN) << 2); // if pins 0 to 7
    //GPIOA_CRH |= OUTPUT_MODE << ((LED_PIN-8) << 2); // if pins 8 to 15
 
    while(1)
    {
        GPIOA_BSRR = 1<<LED_PIN;  // set LED pin high
        delay(200000);
        GPIOA_BRR  = 1<<LED_PIN;  // set LED pin low
        delay(200000);
    }
}
 
void delay(unsigned long count)
{
    while(count--);
}
