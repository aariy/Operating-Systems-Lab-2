/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, Anthea Ariyajeyam (100556294)
 * All rights reserved.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

// Define functions declared in myshell.h here
/* findCommand
      This function returns a String that will be represent the command inputed
      by the user

      parameters
        - *tokenLine the string that contains the line inputed by the user
          (e.g. cd "school")
      return
        a string that contains the command (e.g. cd)
*/
char *findCommand(char *tokenLine)
{
  if(strtok(tokenLine," ") == NULL)
    return tokenLine;
  else
  {
    char *tokenCommand = strtok(tokenLine," ");
    return tokenCommand;
  }
}




int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char *workDir[BUFFER_LEN] = {0};
    char arg[BUFFER_LEN] = { 0 };
    char *tokenLine;
    char *tokenInfo;
    char *arguments; // used in commands that have extra arguments (i.e. cd, dir and echo)
    char *path;

    //Printing the working directory
    printf("PWD: %s:",getenv("PWD"));

    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        //Printing the working directory
        printf("PWD: %s:",getenv("PWD"));

        // Perform string tokenization to get the command and argument
        strcpy(tokenInfo,buffer);
        tokenLine = strtok(buffer, "\n");

        // Check the command and execute the operations for each command
        strcpy(command, findCommand(tokenLine));



        //COMMANDS
        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0)
        {
          //If there are no arguments
          if (strlen(tokenInfo) > 3)
          {
            //Obtaining the arguments from tokenInfo
            strncpy(arguments,&tokenInfo[3],sizeof(tokenLine)-4);
            //Changing their working directory using chdir
            if (chdir(arguments) != 0)
            {
              printf("This directory does not exist\n");
            }
          }

        }
        //clr command
        else if (strcmp(command, "clr") == 0)
        {
            system("clear");
        }

        //dir command
        else if (strcmp(command,"dir") == 0)
        {
          //Obtaining path
          path = strtok(arguments, " ");
          path = strtok(path,"\n");

          //Opening directory
          DIR *directory = opendir(path);
          struct dirent *content;

          //If the directory doesn't exist it will inform the user
          if (directory == NULL)
          {
            printf("Error: The directory does not exist");
          }

          //If the directory exists it will display the content on the terminal
          else
          {
            while ((content = readdir(directory)) != NULL)
            {
              printf("%s\n", content->d_name);
            }
            closedir(directory);
          }
        }

        //Echo command
        else if(strcmp(command,"echo") == 0)
        {
            strncpy(arguments,&tokenInfo[5],sizeof(tokenInfo));
            printf("%s\n",arguments);
        }

        //environ command
        else if(strcmp(command,"environ") == 0)
        {
          printf("arguments: %s\n",getenv("arguments"));
          printf("PWD: %s\n",getenv("PWD"));
          printf("SHELL %s\n",getenv("SHELL"));
        }

        else if (strcmp(command,"pause") == 0)
        {
          printf("Press enter to continue:");
          while (getchar() != '\n');
        }

        //help command
        else if (strcmp(command, "help") == 0)
        {
            printf("supported commands\n");
            printf("quit - exit the shell\n");
            printf("cd <dir> - change directory\n");
            printf("dir <dir> - display contents in directory\n");
            printf("environ - display environmental strings\n");
            printf("echo <comment> - display text\n");
            printf("pause - system waits until user preseses enter\n");
        }
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {

            return EXIT_SUCCESS;
        }

        // Unsupported commands
        else
        {
            fputs("\n\n Unsupported command, use help to display the manual\n", stderr);
        }
    }

    return EXIT_SUCCESS;
}
