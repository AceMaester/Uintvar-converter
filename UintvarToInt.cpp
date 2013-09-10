// uintvar to int converter by Andrew Ettles


#include <iostream>
#include <bitset>
#include <string>
#include <limits>
#include <stdio.h>

#include <stdlib.h>

using namespace std;

void uintvarToInt( unsigned long n );

int main(int argc, char *argv[])
{
	unsigned long number;
   
 
    
   for (int nArg=0; nArg < argc; nArg++){
        
	    number = strtoul(argv[nArg], NULL, 16); //convert argument from hexidecimal to unsigned long number
		if(nArg==0){
		
		}else{
		cout << argv[nArg] << ": " ;
		uintvarToInt(number);
		}
   }

   return 0;
}

void uintvarToInt( unsigned long n )
{
	//cout << n << '\n' ;DEBUG


   enum {
       MAXBITS = numeric_limits< unsigned long>::digits/8*8, //largest unsigned long that can be represented
	   
       MAXGROUPS = MAXBITS/8 //most 8-bit groups that can be represented
   };

	//cout << MAXBITS << '\n' ; DEBUG
	string bitstr = bitset<MAXBITS>(n).to_string() ;
	

	string eightbit_groups[MAXGROUPS] ; //create array of eight bit groups
   for( int i=0 ; i<MAXGROUPS; i++ ){
       eightbit_groups[i] = bitstr.substr( i*8, 8 ) ;
	   //cout << eightbit_groups[i] << '\n' ; DEBUG
	   
   }

   int first_group = -1 ;

   for( int i=0 ; i<MAXGROUPS; i++ ){ //searching for first group with most significant bit equal to 1
       if( eightbit_groups[i].at(0) == '1' ){

           first_group = i;
		   break;
	   }
   }
   
   int first_group_zero = 4;
   for( int i=0 ; i<MAXGROUPS; i++ ){ //searching for first group with most significant bit equal to 0 and is not "0000 0000"
       if( eightbit_groups[i].at(0) == '0' && eightbit_groups[i] != "00000000" ){

           first_group_zero = i;
		   break;
	   }
   }

   if(first_group_zero < first_group){ //check for termination bits preceding firstgroup
	   cout << bitset<8>( eightbit_groups[first_group_zero] ).to_ulong() << '\n' ;
				return;
   }
   
   if(first_group == -1){ //if no leading bits are 1 then output is binary representation of first non-zero group
	   
	   for( int i=0 ; i<MAXGROUPS; i++ ){
			if(eightbit_groups[i] == "00000000" ){
			}else{
				
				cout << bitset<8>( eightbit_groups[i] ).to_ulong() << '\n' ;
				return;
			}
	   }
		cout << "0" << '\n' ;
		return;
	    
   }

   if(eightbit_groups[MAXGROUPS-1].at(0) == '1' ){ //if the MSB of the last group is 1 the input is invlaid so output 0 
	    cout << "0" << '\n' ;
		return;
   }

   string finalNum = ""; // concatenated string of bits

   //cout << first_group << '\n' ; DEBUG
   for( int i= first_group; i<MAXGROUPS; i++ ){ 
	   if( eightbit_groups[i].at(0) == '1' ){
		   finalNum = finalNum + eightbit_groups[i].substr( 1, 7 ) ; //takes last 7 bits and concatenates to final num
		   
	   }else{
		   finalNum = finalNum + eightbit_groups[i].substr( 1, 7 ) ;
		   
		   break; //dont continue if MSB is 0
	   }
   }

   //cout << finalNum << '\n' ; DEBUG
   cout << bitset<MAXBITS>( finalNum ).to_ulong() << '\n' ; //prints binary string in decimal format
}
   

   


   

    

