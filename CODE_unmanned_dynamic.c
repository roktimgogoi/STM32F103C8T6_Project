#include "stm32f10x.h"

volatile uint16_t adc_value;

void UART_SendChar(char c)
{
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = c;
}

void UART_SendString(char *s)
{
    while (*s)
    {
        UART_SendChar(*s++);
    }
}

void UART_SendNumber(uint16_t num)
{
    char buf[6];
    int i = 0;

    if (num == 0)
    {
        UART_SendChar('0');
        return;
    }
    while (num > 0)
    {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    while (i--)
    {
        UART_SendChar(buf[i]);
    }
}

void TIM2_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->PSC = 7199;   // 72MHz / 7200 = 10 kHz
    TIM2->ARR = 99;     // 10 kHz / 100 = 100 Hz

    /* TRGO on update event */
    TIM2->CR2 &= ~TIM_CR2_MMS;
    TIM2->CR2 |=  TIM_CR2_MMS_1;

    TIM2->CR1 |= TIM_CR1_CEN;
}





void DMA1_Channel1_IRQHandler(void)
{
    if (DMA1->ISR & DMA_ISR_TCIF1)
    {
        DMA1->IFCR = DMA_IFCR_CTCIF1;

        UART_SendString("ADC = ");
        UART_SendNumber(adc_value);
        UART_SendString("\r\n");
    }
}


int main(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    
    GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);

    
    GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
    GPIOA->CRH |=  (GPIO_CRH_MODE9_1);      // Output 2 MHz
    GPIOA->CRH |=  (GPIO_CRH_CNF9_1);       // AF push-pull
	
	
	   RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    USART1->BRR = 0x1D4C;   // 9600 baud @ 72 MHz
    USART1->CR1 = USART_CR1_TE | USART_CR1_UE;

       RCC->AHBENR |= (1 << 0);   

    DMA1_Channel1->CPAR  = (uint32_t)&ADC1->DR;
    DMA1_Channel1->CMAR  = (uint32_t)&adc_value;
    DMA1_Channel1->CNDTR = 1;

    DMA1_Channel1->CCR = 0;
    
    DMA1_Channel1->CCR |= (1 << 8);
    DMA1_Channel1->CCR |= (1 << 10);
    DMA1_Channel1->CCR |= (1 << 1);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    DMA1_Channel1->CCR |= (1 << 0);
		
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    /* ADC external trigger TIM2 TRGO */
	  ADC1->CR2 |= ADC_CR2_RSTCAL;
    while (ADC1->CR2 & ADC_CR2_RSTCAL);

    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);

    ADC1->CR2 |= ADC_CR2_EXTTRIG;
    ADC1->CR2 |= ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_2;

    ADC1->CR2 |= ADC_CR2_DMA;

    ADC1->SQR1 = 0;          
    ADC1->SQR3 = 0;         

    ADC1->CR2 |= ADC_CR2_ADON;
		
     RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->PSC = 7199;   // 72MHz / 7200 = 10 kHz
    TIM2->ARR = 99;     // 10 kHz / 100 = 100 Hz

    /* TRGO on update event */
    TIM2->CR2 &= ~TIM_CR2_MMS;
    TIM2->CR2 |=  TIM_CR2_MMS_1;

    TIM2->CR1 |= TIM_CR1_CEN;

    UART_SendString("System Started\r\n");

    while (1)
    {
        
    }
}