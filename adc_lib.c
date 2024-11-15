


 
#byte ADCON0 =  0x1F
#byte ADCON1 =  0x9F   
#byte ADRESL =  0x9E                 
#byte ADRESH =  0x1E 
#byte PIR1   =  0x0C 
// ADC MOD BELÝRLEME         ADC_INIT(INT32 MOD)
#define ADC_KAPALI          0          
#define ADC_CLOCK_DAHILI    0x00C0                        
#define ADC_CLOCK_2         0x10000     
#define ADC_CLOCK_4         0x4000                        
#define ADC_CLOCK_8         0x0040     
#define ADC_CLOCK_16        0x4040                              
#define ADC_CLOCK_32        0x0080     
#define ADC_CLOCK_64        0x4080     
// ADC KANALLARI             ADC_PORTLAR(int8 mod) 
#define ANALOG_KAPALI                        7
#define TUM_ANALOG                           0
#define AN0_AN1_AN2_AN4_AN5_AN6_AN7_VSS_VREF 1    // A0 A1 A2 A5 E0 E1 E2 VRefh=A3     
#define AN0_AN1_AN2_AN3_AN4                  2    // A0 A1 A2 A3 A5          
#define AN0_AN1_AN2_AN4_VSS_VREF             3    // A0 A1 A2 A4 VRefh=A3              
#define AN0_AN1_AN3                          4    // A0 A1 A3
#define AN0_AN1_VSS_VREF                     5    // A0 A1 VRefh=A3
#define AN0_AN1_AN4_AN5_AN6_AN7_VREF_VREF 0x08    // A0 A1 A5 E0 E1 E2 VRefh=A3 VRefl=A2     
#define AN0_AN1_AN2_AN3_AN4_AN5           0x09    // A0 A1 A2 A3 A5 E0        
#define AN0_AN1_AN2_AN4_AN5_VSS_VREF      0x0A    // A0 A1 A2 A5 E0 VRefh=A3           
#define AN0_AN1_AN4_AN5_VREF_VREF         0x0B    // A0 A1 A5 E0 VRefh=A3 VRefl=A2           
#define AN0_AN1_AN4_VREF_VREF             0x0C    // A0 A1 A4 VRefh=A3 VRefl=A2              
#define AN0_AN1_VREF_VREF                 0x0D    // A0 A1 VRefh=A3 VRefl=A2
#define AN0                               0x0E    // A0
#define AN0_VREF_VREF                     0x0F    // A0 VRefh=A3 VRefl=A2  

// ADC_INIT() BAÞLANGIÇ AYARLARI  
// SEÇÝLEN MODA GÖRE CLOCK AYARI YAPILIR
                         
                               
void adc_init_baslat(int32 mod){        
     ADCON0 |= mod & 0x000FF;    
     ADCON1 |= (mod>>24) & 0x000FF;      
     ADCON1 |= (1<<7);   
     //ADCON0 =  0x00;               
     //ADCON1 =  0x80;
     
}                                               
                                             
void adc_portlar(int8 port){                      
     ADCON1 |= port;           
}                            
// SEÇÝLEN ADC KANALINDAN ANALOG DATASI OKUNUR VE REGÝSTERA KAYIT EDÝLÝR
void set_adc_kanali(int8 kanal){
     ADCON0 |=  (kanal<<3);  //                           
     ADCON0 |=  0x01;        // ADC TURN ON
     delay_us(21);  
     ADCON0 |= 0x04;               
     //while((ADCON0 & (1<<2)) || (PIR1 & (1<<6)));    
     PIR1 &= ~(1<<6);                    
}
                                                                       
int16 adc_oku(void){            
   int16  lsb   = ADRESL;
   int16  msb   = ADRESH;   
   return  (msb<<8) | lsb;                                              
}                               
                                 
                                                            
