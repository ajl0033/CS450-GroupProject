/*
  ----- serial.c -----

  Description..: Contains methods and variables used for
    serial input and output.
*/

#include <stdint.h>
#include <string.h>

#include <core/io.h>
#include <core/serial.h>

#include "modules/print.h"

#define NO_ERROR 0

// Active devices used for serial I/O
int serial_port_out = 0;
int serial_port_in = 0;

/*
  Procedure..: init_serial
  Description..: Initializes devices for user interaction, logging, ...
*/
int init_serial(int device)
{
  outb(device + 1, 0x00); //disable interrupts
  outb(device + 3, 0x80); //set line control register
  outb(device + 0, 115200/9600); //set bsd least sig bit
  outb(device + 1, 0x00); //brd most significant bit
  outb(device + 3, 0x03); //lock divisor; 8bits, no parity, one stop
  outb(device + 2, 0xC7); //enable fifo, clear, 14byte threshold
  outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
  (void)inb(device);      //read bit to reset port
  return NO_ERROR;
}

/*
  Procedure..: serial_println
  Description..: Writes a message to the active serial output device.
    Appends a newline character.
*/
int serial_println(const char *msg)
{
  int i;
  for(i=0; *(i+msg)!='\0'; i++){
    outb(serial_port_out,*(i+msg));
  }
  outb(serial_port_out,'\r');
  outb(serial_port_out,'\n');
  return NO_ERROR;
}

/*
  Procedure..: serial_print
  Description..: Writes a message to the active serial output device.
*/
int serial_print(const char *msg)
{
  int i;
  for(i=0; *(i+msg)!='\0'; i++){
    outb(serial_port_out,*(i+msg));
  }
  if (*msg == '\r') outb(serial_port_out,'\n');
  return NO_ERROR;
}

/*int (*student_read)(char *buffer, int *count);
  Procedure..: set_serial_out
  Description..: Sets serial_port_out to the given device address.
    All serial output, such as that from serial_println, will be
    directed to this device.
*/
int set_serial_out(int device)
{
  serial_port_out = device;
  return NO_ERROR;
}

/*
  Procedure..: set_serial_in
  Description..: Sets serial_port_in to the given device address.
    All serial input, such as console input via a virtual machine,
    QEMU/Bochs/etc, will be directed to this device.
*/
int set_serial_in(int device)
{
  serial_port_in = device;
  return NO_ERROR;
}

int *polling(char *buffer, int *count){
// insert your code to gather keyboard input via the technique of polling.
// You must validat each key and handle special keys such as delete, back space, and
// arrow keys
int counter = 0;
int index = 0;
print(">> ");
while(1)
{

  if (inb(COM1+5) & 1)
  {
    // Assign character input to letter
    char letter = inb(COM1);
    println("\n\n");
    print("\'");
    print(&letter);
    print("\'");
    println("\n\n");
    // Check if enter is pressed
    // If enter is pressed, return count
    if (letter == '\n' || letter == '\r')
    {
      return count;
    } // Check if backspace is pressed
    // else if (letter == '\b')
    // {
    //   print("AAAHHHHHHH");
    //   if (index == 0)
    //   {
    //     continue;
    //   }
    //   else
    //   {
    //     int i;
    //     for (i = 0; i < counter; i++)
    //     {
    //       if (i >= index-1)
    //       {
    //         buffer[index] = buffer[index+1];
    //       }
    //     }
    //   }
    // } // Check for left arrow key
    else if (letter == '9')
    {

    } // Check for right arrow key
    else if (letter == '8')
    {

    }



    // Place the character (letter) in the proper index of the buffer
    // Increment the counter
    buffer[counter] = letter;
    counter++;

    // Increment index
    index++;

    // Print the character that was pressed
    print("\33[2K\r>> ");
    print(buffer);
  }
}

// remove the following line after implementing your module, this is present
// just to allow the program to compile before R1 is complete
//strlen(buffer);

return count;
}
