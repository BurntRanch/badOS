#include "print.h"
#include "proccessCommand.h"
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
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', -4,
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

char capital_kbd_US [128] =
{
  0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', -1,   
  '\t', /* <-- Tab */
  'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
  0, /* <-- control key */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',  0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', -5,
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
  unsigned char c = 0;
  unsigned short port = 0x60;
  int shift = 0;
  int length = 0;
  int doType = 0;
  char* haha = "";
  do
  {
    if (inb(port) != c) //PORT FROM WHICH WE READ
    {
      c = inb(port);
      if (kbd_US[c] != -1 & kbd_US[c] != -2 & kbd_US[c] != -3 & doType & kbd_US[c] != '\n') {    // the user did not press end/backspace/capslock so print the character
        if (kbd_US[c] >= 97 & kbd_US[c] <= 122 & capslock == 1 & shift != 1) {
          print_char(capital_kbd_US[c], 0, 0);
          haha[length] = capital_kbd_US[c];
          haha[length + 1] = '\0';
          length++;
        } else if (shift == 1)  {
          print_char(capital_kbd_US[c], 0, 0);
          haha[length] = capital_kbd_US[c];
          haha[length + 1] = '\0';
          length++;
        } else {
          print_char(kbd_US[c], 0, 0);
          haha[length] = kbd_US[c];
          haha[length + 1] = '\0';
          length++;
        }
      } else if (kbd_US[c] == -1) {   //the user pressed backspace, so clear the screen.
        print_clear();
      } else if (kbd_US[c] == -3) {
        if (capslock == 1) {
          capslock = 0;
        } else {
          capslock = 1;
        }
      } else if (kbd_US[c] == '\n') {
        print_char(kbd_US[c], 0, 0);
        if (process(haha) == 'c') {
          print_clear();
        }
        length = 0;
        haha = "";
      }

      doType = !doType;
    } else {
      if (kbd_US[c] == -4) {
        shift = 1;
      } else if (kbd_US[c] == -5) {
        shift = 0;
      }
    }
  }while(kbd_US[c] != -2); // 1= ESCAPE
}