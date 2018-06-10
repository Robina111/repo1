#include <stdio.h>
#include <stdlib.h>
#define SCREEN_ROWS 23 /* assume 24 lines per screen */
#define LINELEN 512
#define SPACEBAR 1
#define RETURN 2
#define QUIT 3
#define INVALID 4

void do_more_of (FILE *fp )
{
      char line[LINELEN] ; // buffer to store line of input
      int num_of_lines = SCREEN_ROWS; // # of lines left on screen
      int getmore = 1 ; // boolean to signal when to stop
      int reply; // input from user
  
      while ( getmore && fgets ( line , LINELEN, fp ) ){
          // fgets ( ) returns pointer to string read or NULL
          if( num_of_lines == 0 ) {
            // reached screen capacity so display prompt
            reply = get_user_input ( ) ;
            switch (reply) {
                case SPACEBAR:
                   // allow full screen
                   num_of_lines = SCREEN_ROWS;
                   break;
                case RETURN:
                   // allow one more line
                   num_of_lines++;
                   break ;
                case QUIT:
                   getmore =0;   
                   break ;
                default : // in case of invalid input
                   break ;
           }
         }
         if (fputs(line,stdout)==EOF)
           exit (1) ;
         num_of_lines--;
      }  
}
int get_user_input ( )
{
     int c ;
  
     printf ( "\033 [7m more?\033[m" ) ; /* reverse on a VT100 */
     while ( ( c = getchar ( ) ) != EOF ) /* wait for response */
         switch (c) {
            case 'q' : /* 'q' pressed */
               return QUIT;
            case ' ' : /* ' ' pressed */
               return SPACEBAR;
            case '\n' : /* Enter key pressed */
               return RETURN;
            default : /* invalid if anything else */
               return INVALID;
        }
}
int main ( int  argc , char * argv [ ] )
{
       FILE * fp ;
       int i = 0 ;
       if ( 1 == argc )
          do_more_of ( stdin ) ; // no args , read from s tandard input
       else
           while ( ++i < argc ) {
               fp = fopen ( argv [ i ] , " r " ) ;
               if ( NULL != fp ) {
                    do_more_of ( fp ) ;
                    fclose ( fp ) ;
               }
               else
                   printf( " Skipping %s \n" , argv [ i ] ) ;
           }       
  return 0 ;
}