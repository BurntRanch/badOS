#include "print.h"
#include "graphics.h"
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

size_t capslock = 0;

char kbd_US [128] =
{
  0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', -1,   
  '\t', /* <-- Tab */
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
  0, /* <-- control key */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
  '*',
  0,  /* Alt */
  ' ',  /* Space bar */
  -3,  /* Caps lock */
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
  char c = 0;
  size_t length = 0;
  char haha [5] = {
    '.', '.', '.', '.', '.'
  };
  do
  {
    if (inb(0x60) != c) //PORT FROM WHICH WE READ
    {
      c = inb(0x60);
      if (c > 0)
      {
        if (kbd_US[c] != -1 & kbd_US[c] != -2 & kbd_US[c] != -3) {    // the user did not press end/backspace so print the character
          if (kbd_US[c] >= 97 & kbd_US[c] <= 122 & capslock == 1) {
            print_char(kbd_US[c] - 32, 0, 0);
          } else {
            print_char(kbd_US[c], 0, 0);
          }
          haha[length] = kbd_US[c];
        } else if (kbd_US[c] == -1) {   //the user pressed backspace, so clear the screen.
          print_clear();
        } else if (kbd_US[c] == -3) {
          if (capslock == 1) {
            capslock = 0;
          } else {
            capslock = 1;
          }
        }
      }
    }
  }while(kbd_US[c] != -2); // 1= ESCAPE
  for (size_t len = 0; len < 5; len++) {
    print_char(haha[len], 0, 0);
  }
}