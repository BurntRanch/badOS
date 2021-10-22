#include "print.h"
#define INT_DISABLE 0
#define INT_ENABLE  0x200
#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01

void outb( unsigned short port, unsigned char val )
{
   asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) );
}

static __inline unsigned char inb (unsigned short int port)
{
  unsigned char _v;

  __asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (port));
  return _v;
}

void init_pics(int pic1, int pic2)
{
   /* send ICW1 */
   outb(PIC1, ICW1);
   outb(PIC2, ICW1);

   /* send ICW2 */
   outb(PIC1 + 1, pic1);   
   outb(PIC2 + 1, pic2);   

   /* send ICW3 */
   outb(PIC1 + 1, 4);   
   outb(PIC2 + 1, 2);

   /* send ICW4 */
   outb(PIC1 + 1, ICW4);
   outb(PIC2 + 1, ICW4);

   /* disable all IRQs */
   outb(PIC1 + 1, 0xFF);
}

char kbd_US [128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', -1,   
  '\t', /* <-- Tab */
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    0, /* <-- control key */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    -2,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

void kernel_main() {
    print_str("", 0, 0);
    char c = 0;
    do
    {
        if (inb(0x60) != c) //PORT FROM WHICH WE READ
        {
            c = inb(0x60);
            if (c > 0)
            {
                if (kbd_US[c] != -1 & kbd_US[c] != -2) {
                    print_char(kbd_US[c], 1, 1);
                } else if (kbd_US[c] == -1) {
                    print_clear();
                } else {
                    break;
                }
            }
        }
    }while(c!=1); // 1= ESCAPE
}