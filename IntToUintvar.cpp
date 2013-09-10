// integer to uintvar converter by Andrew Ettles
//



#include <iostream>
#include <bitset>
#include <string>
#include <limits>
#include <stdio.h>

#include <stdlib.h>

using namespace std;

void intToUintvar( unsigned long n );

int main(int argc, char *argv[])
{
	unsigned long number;
   
 
    
   for (int nArg=0; nArg < argc; nArg++){
        
	    number = atol(argv[nArg]);
		if(nArg==0){
		
		}else{
		cout<<argv[nArg] << ": ";
		intToUintvar(number);
		}
   }

   return 0;
}

void intToUintvar( unsigned long n )
{
   
	
	
	cout << hex << ""; //change string stream to hexidecimal

   
   if( n == 0 ) { //zero case
	   cout << ' ' << 0 << '\n' ; 
	   return ; 
   }

   enum {
       MAXBITS = numeric_limits< unsigned long>::digits/ 7 * 7, //largest unsigned long that can be represented
	   
       MAXGROUPS = MAXBITS/7 //most 7-bit groups that can be represented
   };

   
   
   string bitstr = bitset<MAXBITS>(n).to_string() ; //converts to binary string

   
   string sevenbit_groups[MAXGROUPS] ; //create array of seven bit groups
   for( int i=0 ; i<MAXGROUPS; i++ ){
       sevenbit_groups[i] = bitstr.substr( i*7, 7 ) ;
   }

   
   int first_group = 0 ;
   for( int i=0 ; i<MAXGROUPS; i++ ){ //searching for group with most significant bit
       if( sevenbit_groups[i] != "0000000" ){
           first_group = i ;
           break ;
       }
   }

   
   for( int i = first_group ; i < (MAXGROUPS-1) ; i++ ){ //add 1 as the most significant bit to each group except the last
       sevenbit_groups[i] = '1' + sevenbit_groups[i] ;
   }
   
   sevenbit_groups[ (MAXGROUPS-1) ] = '0' + sevenbit_groups[ (MAXGROUPS-1) ] ;//add 0 as the most significant bit to the last group

   
   for( int i = first_group ; i < MAXGROUPS ; i++ ){
        cout << ' ' << bitset<8>( sevenbit_groups[i] ).to_ulong() ; //print each group of 8-bits out in hexidecimal

   }
   
   cout << '\n' ;
   
}