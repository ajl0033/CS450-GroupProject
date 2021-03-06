#include <string.h>
#include "mpx_supt.h"
#include "print.h"
#include "date.h"
#include <core/io.h>
#include "bcdConversion.h"

/*
day of week - 0x06
day of month - 07
month - 08
year- 09

04/02/2002
01/34/6789
dayOfMonth/Month/year
*/


/*
get date has no arguements
irrelvantly returns 0
prints the date that was accessed through the outb function
calls bcdtoStr on the date to convert from BCD to a char and place it in the date char array
*/
int getdate(){
char date[11] = "00/00/0000";

//year
outb(0x70, 0x09);
BCDtoStr(inb(0x71), &date[8]);

//Month
outb(0x70, 0x08);
BCDtoStr(inb(0x71), &date[0]);

//dayOfMonth
outb(0x70, 0x07);
 BCDtoStr(inb(0x71), &date[3]);

//century
outb(0x70, 0x32);
BCDtoStr(inb(0x71), &date[6]);

print("\n\nCurrent Date (MM/DD/YYYY): ");
println(date);
println("");
return 0;

}


/*
set date has no arguements
irrelvantly return 0
reads in the date entered by the user after printing a prompt
calls checkDate to make sure the date entered was valid
sets the date using the outB and StrtoBCD function to convert the char to a BCD

*/
 int setdate(){
   char cmdBuffer[100];
   int bufferSize;
   memset(cmdBuffer, '\0', 100);
   bufferSize = 99;
   print("\n\nEnter a date in the form MM/DD/YYYY\n");
  sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  char date[11];

    int count = 0;
    while(count < 11) {
    date[count] = cmdBuffer[count];
    count++;
  }
// 04/02/2002
// 01/34/6789


if(checkDate(date)){
  return 1;
}else{
  cli();

  //year
  outb(0x70, 0x09);
  outb(0x71, StrtoBCD(&date[8]));

//month
outb(0x70, 0x08);
outb(0x71, StrtoBCD(&date[0]));

//dayOfMonth
outb(0x70, 0x07);
outb(0x71, StrtoBCD(&date[3]));

//century
outb(0x70, 0x32);
outb(0x71, StrtoBCD(&date[6]));

print("\n\nDate has been set in the form MM/DD/YYYY to: ");
print(date);
println("");
sti();
return 0;

}
}
// 04/02/1999
// 01/34/6789
// Month/dayOfMonth/year

/*
check date recieves the date char array pointer as an arguements
makes sure the date is valid
returns 0 if the date is valid and 1 if the date is invalid
if 0 is returned the setdate function continues if 1 is returned a invalid format message is returned

*/
int checkDate(char* date){
  if (date[0] == '1')
  {
    if (date[1] > 2)
    {
      print("\033[31m");
      println("\n\nDate is invalid format...\n");
      print("\033[37m");
      return 1;
    }
  }

  if (date[3] == '3')
  {
    if (date[4] > 1)
    {
      print("\033[31m");
      println("\n\nDate is invalid format...\n");
      print("\033[37m");
      return 1;
    }
  }

  if ((date[10] >= 97 && date[10] <= 122) || (date[10] >= 44 && date[10] <= 59) || (date[10] >= 65 && date[10] <= 90) || (date[10] == 92))
  {
    print("\033[31m");
    println("\n\nDate is invalid format...\n");
    print("\033[37m");
    return 1;
  }

  if(
        date[2] != '/' || date[5] != '/' ||
        date[0] > '1' || date[0] < '0' ||
        date[1] < '0' || date[1] > '9' ||
        date[3] < '0' || date[3] > '3' ||
        date[4] < '0' || date[4] > '9' ||
        date[6] < '0' || date[6] > '9' ||
        date[7] < '0' || date[7] > '9' ||
        date[8] < '0' || date[8] > '9' ||
        date[9] < '0' || date[9] > '9'
)  {
  print("\033[31m");
  println("\n\nDate is invalid format...\n");
  print("\033[37m");
return 1;
}
else{
  return 0;
}
}
