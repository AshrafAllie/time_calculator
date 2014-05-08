//Date:   28Apr2014Mon10:45
//File:   time_calc.c
//Author: Ashraf
//Email:  ashraf.allie01@gmail.com
/*Desc:   Calculates the time between 2 time intervals in a day.
          Usage example:

          ./time_calc 09:40:12 10:25:39
          00:45:27

          ./time_calc -h 09:40:12 10:25:39
          0.7575 hours

          ./time_calc -m 09:40:12 10:25:39
          45.45 minutes

          ./time_calc -s 09:40:12 10:25:39
          2727 seconds


          This program is free software: you can redistribute it and/or modify
          it under the terms of the GNU General Public License as published by
          the Free Software Foundation, either version 3 of the License, or (at
          your option) any later version.

          This program is distributed in the hope that it will be useful, but 
          WITHOUT ANY WARRANTY; without even the implied warranty of 
          MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
          General Public License for more details.

          You should have received a copy of the GNU General Public License 
          along with this program. If not, see <http://www.gnu.org/licenses/>
*/


//----------------
//Macro Defintions
//----------------
#include<stdio.h>
#include<string.h>
#include<ctype.h>


//---------------------
//Function Declarations (prototypes)
//---------------------
void message(unsigned char message_num);
unsigned char time_form_range_checker(unsigned char* start, unsigned char* end);
unsigned char* get_time(unsigned char* start, unsigned char* end);


//------------
//Main Program
//------------
int main(int argc, char* argv[])
{
 switch(argc)
 {
  case 1:
      message(0);
      break;
  case 3:
      if (time_form_range_checker(argv[1], argv[2]))
        get_time(argv[1], argv[2]);

      break;
  case 4:
      break;
  default:
      message(1);
      break;
 }


 return 0;
}


//--------------------
//Function Definitions (Implementation)
//--------------------


//FUNCTION: message
void message(unsigned char message_num)
{
 unsigned char* error_messages[] =
 {
  //message 0
  "time calculator copyleft (c) 2014 Ashraf\n\n"
  "Usage: time_calc [option] <start time> <end time>\n"
  "Options:\n"
  "-h returns time in hours\n"
  "-m returns time in minutes\n"
  "-s returns time in seconds\n"
  "If the option is left out it returns the time in the form dd:dd:dd where d \n"
  "is a digit\n\n"
  "start time and end time must be in the form dd:dd:dd\n",

  //message 1
  "Error: argument count cannot be 2 nor exceed 4\n",

  //message 2
  "Error: length of start time and end time must be 8 characters and in the form dd:dd:dd\n",

  //message 3
  "Error: start or end time's hour's tens column not in range 0 to 2\n"
  "start hour tens column must be <= end hour tens column\n",

  //message 4
  "Error: start hour must be less than or equal to end hour and in range 00 to 23\n",

  //message 5
  "Error: minutes tens column must be in the range 0 to 5\n"
  "and when hours are the same start minutes <= end minutes\n",

  //message 6
  "Error: start minutes must be less than end minutes when hours are the same\n",

  //message 7
  "Error: seconds tens column must be in the range 0 to 5\n"
  "and when hours and minutes are the same start seconds <= end seconds\n",

  //message 8
  "Error: start seconds must be less than end seconds when hours and minutes are the same\n"
 };

 printf("%s", error_messages[message_num]);
}

//FUNCTION: time_form_range_checker
unsigned char time_form_range_checker(unsigned char* start, unsigned char* end)
{
 unsigned char i;

 if (strlen(start) != 8 && strlen(end) != 8)
 {
  message(2);
  return 0;
 }
 
 for (i = 0; i < strlen(start); i++)
 {
  if (i == 2 || i == 5)
  {
   if (start[i] != ':' && end[i] != ':')
   {
    message(2);
    return 0;
   }
  }
  else
  {
   if (!isdigit(start[i]) && !isdigit(end[i]))
   {
    message(2);
    return 0;
   }

   switch (i)
   {
    case 0:
        //hours tens column
        if (!((start[i] >= '0') && (start[i] <= '2') &&
              (end[i]   >= '0') && (end[i]   <= '2') &&
              (start[i] <= end[i])
             )
           )
        {
         message(3);
         return 0;
        }

        break;


    case 1:
        //hours unit column
        if (
            ((start[0] == '2') && !(start[i] <= '3') ||
             (end[0]   == '2') && !(end[i]   <= '3')
            ) ||

            ((start[0] == end[0]) && !(start[i] <= end[i]))

           )
        {
         message(4);
         return 0;
        }

        break;


    case 3:
        //minutes tens column
        if (
            !((start[i] >= '0' && start[i] <= '5') &&
              (end[i]   >= '0' && end[i]   <= '5')
             ) ||

            ((start[0] == end[0]) && (start[1] == end[1]) &&
             !(start[i] <= end[i])
            )
           )
        {
         message(5);
         return 0;
        }

        break;


    case 4:
        //minutes unit column
        if (
            ((start[0] == end[0]) && (start[1] == end[1]) &&
             (start[3] == end[3]) &&
             !(start[i] <= end[i])
            )
           )
        {
         message(6);
         return 0;
        }

        break;


    case 6:
        //seconds tens column
        if (
            !((start[i] >= '0' && start[i] <= '5') &&
              (end[i]   >= '0' && end[i]   <= '5')
             ) ||

            (
             (start[0] == end[0]) && (start[1] == end[1]) &&
             (start[3] == end[3]) && (start[4] == end[4]) &&
             !(start[6] <= end[i])
            )
           )
        {
         message(7);
         return 0;
        }

        break;


    case 7:
        //seconds unit column
        if (
            ((start[0] == end[0]) && (start[1] == end[1]) &&
             (start[3] == end[3]) && (start[4] == end[4]) &&
             !(start[i] <= end[i])
            )
           )
        {
         message(8);
         return 0;
        }


        break;
   }
  }
 }

 return 1;
}


//FUNCTION: get_time()
unsigned char* get_time(unsigned char* start, unsigned char* end)
{
 unsigned char start_sec, start_min, start_hour,
               end_sec,   end_min,   end_hour,
               sec,       min,       hour;

 end_sec  = end[7] - '0' + ((end[6] - '0') * 10);
 end_min  = end[4] - '0' + ((end[3] - '0') * 10);
 end_hour = end[1] - '0' + ((end[0] - '0') * 10);

 start_sec  = start[7] - '0' + ((start[6] - '0') * 10);
 start_min  = start[4] - '0' + ((start[3] - '0') * 10);
 start_hour = start[1] - '0' + ((start[0] - '0') * 10);

/*
 printf("get_time:\n"
        "start_sec:  %2d\n"
        "start_min:  %2d\n"
        "start_hour: %2d\n\n"
        "end_sec:  %2d\n"
        "end_min:  %2d\n"
        "end_hour: %2d\n",
        start_sec, start_min, start_hour,
        end_sec, end_min, end_hour);
*/

 if (end_sec < start_sec)
 {
  if (end_min > 0)
  {
   end_min--;
   sec = 60 + end_sec - start_sec;
  }
  else printf("to be done borow from end_hour\n");
 }
 else
     sec = end_sec - start_sec;



 if (end_min < start_min)
 {
  if (end_hour > 0)
  {
   end_hour--;
   min = 60 + end_min -start_min;
  }
 }
 else
     min = end_min - start_min;


 hour = end_hour - start_hour;


 printf("%02d:%02d:%02d\n", hour, min, sec);
}
