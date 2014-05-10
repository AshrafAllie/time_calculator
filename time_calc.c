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
unsigned char GetLength(unsigned char* argument);
void message(unsigned char message_num);
unsigned char time_form_range_checker(unsigned char* start, unsigned char* end);
void get_time(unsigned char* option, unsigned char* start, unsigned char* end);


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
      if (time_form_range_checker((unsigned char*) argv[1], (unsigned char*) argv[2]))
        get_time((unsigned char*) "default", (unsigned char*) argv[1], (unsigned char*) argv[2]);

      break;
  case 4:
      //Check switch argument
      if (!(argv[1][0] == '-' &&
            (argv[1][1] == 'h' ||
             argv[1][1] == 'm' ||
             argv[1][1] == 's'
            )
           )
         )
      {
       message(9);
       return 0;
      }

      // Check the start and end argument
      if (time_form_range_checker((unsigned char*) argv[2], (unsigned char*) argv[3]))
        get_time((unsigned char*) argv[1], (unsigned char*) argv[2], (unsigned char*) argv[3]);

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


//FUNCTION: GetLength()
unsigned char GetLength(unsigned char* argument)
{
 unsigned char size = 0;

 while (*argument != '\0')
 {
  size++;
  argument++;
 }

 return size;
}


//FUNCTION: message
void message(unsigned char message_num)
{
 unsigned char* error_messages[] =
 {
  //message 0
  (unsigned char*) "time calculator copyleft (c) 2014 Ashraf\n\n"
  "Usage: time_calc [option] <start time> <end time>\n"
  "Options:\n"
  "-h returns time in hours\n"
  "-m returns time in minutes\n"
  "-s returns time in seconds\n"
  "If the option is left out it returns the time in the form dd:dd:dd where d \n"
  "is a digit\n\n"
  "start time and end time must be in the form dd:dd:dd\n",

  //message 1
  (unsigned char*) "Error: argument count cannot be 2 nor exceed 4\n",

  //message 2
  (unsigned char*) "Error: length of start time and end time must be 8 characters and in the form dd:dd:dd\n",

  //message 3
  (unsigned char*) "Error: start or end time's hour's tens column not in range 0 to 2\n"
  "start hour tens column must be <= end hour tens column\n",

  //message 4
  (unsigned char*) "Error: start hour must be less than or equal to end hour and in range 00 to 23\n",

  //message 5
  (unsigned char*) "Error: minutes tens column must be in the range 0 to 5\n"
  "and when hours are the same start minutes <= end minutes\n",

  //message 6
  (unsigned char*) "Error: start minutes must be less than end minutes when hours are the same\n",

  //message 7
  (unsigned char*) "Error: seconds tens column must be in the range 0 to 5\n"
  "and when hours and minutes are the same start seconds <= end seconds\n",

  //message 8
  (unsigned char*) "Error: start seconds must be less than end seconds when hours and minutes are the same\n",

  //message 9
  (unsigned char*) "Error: option switch must be -h or -m or -s\n"
 };

 printf("%s", (unsigned char*) error_messages[message_num]);
}

//FUNCTION: time_form_range_checker
unsigned char time_form_range_checker(unsigned char* start, unsigned char* end)
{
 unsigned char i;

 if ((GetLength(start) != 8) && (GetLength(end) != 8))
 {
  message(2);
  return 0;
 }

 for (i = 0; i < GetLength(start); i++)
 {
  if ((i == 2) || (i == 5))
  {
   if ((start[i] != ':') && (end[i] != ':'))
   {
    message(2);
    return 0;
   }
  }
  else
  {
   if ((!isdigit(start[i])) && (!isdigit(end[i])))
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
            (((start[0] == '2') && !(start[i] <= '3')) ||
             ((end[0]   == '2') && !(end[i]   <= '3'))
            ) ||

            ((start[0] == end[0]) && (!(start[i] <= end[i])))
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
void get_time(unsigned char* option, unsigned char* start, unsigned char* end)
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


 //Print time in default form dd:dd:dd
 if (strcmp((char*) option, "default") == 0)
   printf("%02d:%02d:%02d\n", hour, min, sec);

 //print time in hours
 else if (strcmp((char*) option, "-h") == 0)
        printf("%f hours\n", (float)hour+((float)min/60.0)+((float)sec/3600.0));

 //print time in minutes
 else if (strcmp((char*) option, "-m") == 0)
        printf("%f minutes\n", hour*60 + min + ((float)sec/60.0));

 //print time in seconds
 else if (strcmp((char*) option, "-s") == 0)
        printf("%d seconds\n", hour*3600 + min*60 + sec);
}
