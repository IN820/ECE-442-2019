#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include "i2c-dev.h"
#include "ADXL345.h" #define I2C_FILE_NAME "/dev/i2c-1" //include header files
void INThandler ( int sig ) ;
int main ( int argc , char ** argv ){ int i2c_fd = open ( I2C_FILE_NAME , O_RDWR ) ; // open I2C connection
if ( i2c_fd < 0 ){
printf ( "unable to open i2c control file err=%d \n " , i2c_fd ) ;
exit ( 1 ) ; }
printf ( "Opened i2c control file, id = %d \n " , i2c_fd ) ;
ADXL345 myAcc ( i2c_fd ) ; int ret = myAcc. init () ; // initialize ADXL345
if ( ret ){
printf ( "failed init ADXL345, ret=%d \n " , ret ) ;
exit ( 1 ) ; }
usleep ( 100 * 1000 ) ;
signal ( SIGINT , INThandler ) ;
short ax , ay , az ;
FILE * fp ; fp = fopen ( "./output.txt" , "w+" ) ; //create an output file
char TimeString [ 128 ] ;
timeval curTime ;
while ( 1 ){
gettimeofday ( & curTime , NULL ) ;
strftime ( TimeString , 80 , "%Y-%m-%d %H:%M:%S" , localtime ( & curTime. tv_sec )) ; // put current time in a string printf ( TimeString ) ; //Writing time
printf ( ": " ) ;
myAcc. readXYZ ( ax , ay , az ) ; // read data from gyroscope printf ( "Ax: %hi \t Ay : %hi \t Az : %hi \n " , ax , ay , az ) ; // print sensor data
printf ( "---------- \n " ) ;
fprintf ( fp , TimeString ) ; // write timestamp to file
fprintf ( fp , ": " ) ; fprintf ( fp , "Ax: %hi \t Ay : %hi \t Az : %hi \n " , ax , ay , az ) ; // write data to output file
fprintf ( fp , "----------------- \n " ) ; if (getchar()==’q’)break; // if ‘q’ is detected, the program will stop
}
fclose(fp);
return 0;
}
void INThandler ( int sig ) { signal ( sig , SIG_IGN ) ; // Interruption handler
exit ( 0 ) ;
}
