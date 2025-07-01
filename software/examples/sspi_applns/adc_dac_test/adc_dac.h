/*
DAC Register Bits
*/
#define SELECT_DAC0 (~(1 << 7))
#define SELECT_DAC1 (1 << 7)

#define BUFFERED (1 << 6)
#define NON_BUFFERED (~(1 << 6))

#define GAIN_1X (1 << 5)
#define GAIN_2X (~(1 << 5))

#define SHUT_DOWN (~(1 << 4))
#define DO_NOT_SHUT_DOWN (1 << 4)

#define DATA_BITS(x) (x&0x0FFF)



/*
ADC register bits
*/
#define SINGLE_CHANNEL 1 
#define DIFFERENTIAL_CHANNEL 0 
#define SINGLE_DIFFERENTIAL_CHANNEL(x) x<<7

#define CHANNEL_0 0
#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_3 3
#define CHANNEL_4 4
#define CHANNEL_5 5
#define CHANNEL_6 6
#define CHANNEL_7 7
#define CHANNEL_SELECT(x) (x << 4)


