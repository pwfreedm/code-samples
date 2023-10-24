/*
  Filename   : reading_input.s
  Author     : Peter Freedman
  Description: Demo on input prompting/collection in ASM
*/

/**********************************************************/       
       
#Define values that need to be recreated with each instance of the program
#in the data section. 
#Also avoids manually building these things.
        .data
prompt:
        .string "n ==> "

formatSpec:
        .string "%d"

/**********************************************************/

#text section is read only, contains code
        .text
#main must be global so that the C STD Library can see it to begin execution
        .globl main

main:
        #Stack frame setup for main
        pushl %ebp
        movl %esp, %ebp

        #prompt user for input
        pushl $prompt
        call printf

        #put address to store input at in eax, so that scanf returns
        #to that address.
        leal -8(%ebp), %eax

        #push what is being searched for (formatSpec) and 
        #address of location to store it to scanf
        pushl %eax
        pushl $formatSpec
        
        #scanf will search for something of type formatSpec and store it
        #at location (%eax)
        call scanf

        #put user input into stackframe
        pushl -8(%ebp)
