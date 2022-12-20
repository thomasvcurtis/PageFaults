#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <iostream>

#define FIFO 0 //used for indexing
#define LRU 1  //

#define REFNUM 43
int reference[REFNUM] = {1,2,7,4,5,2,7,2,3,2,1,7,6,3,7,6,2,4,3,4,3,4,
			 7,2,1,7,6,7,8,7,8,9,7,8,2,7,8,3,5,5,3,5,7};

#define StartFrame 3 //frame numbers
#define EndFrame 7   //


int pageFaultRecord[2][5]; //2x5 cases
int frames[EndFrame - 1];

void resetFrames(){
	
	for(int a = 0; a < EndFrame;a++)
                frames[a] = 0;
}


void FIFO_Sim(){

	int pageFault = 0;
	int nextVictim = 0;
	bool found = false;

	for(int a = StartFrame; a <= EndFrame; a++){ //go through frames

		resetFrames();
	
		for(int b = 0; b < REFNUM; b++){   //go through reference numbers
		
			for(int c = 0; c < a;c++){ //go through frames

				if(frames[c] == reference[b])
					found = true; 

			}		
	
			if (found == false){ 

				frames[nextVictim] = reference[b]; 
				nextVictim++;                     
				nextVictim = nextVictim % a;      // reset victim 
				pageFault++;                      

			}	

			found = false; 

		}	
		
		pageFaultRecord[FIFO][a] = pageFault;
		pageFault = 0;
	}	
}

void LRU_Sim(){

	int pageFaults = 0;
	int nextVictim = 0;
	int highCount = 0;
	bool found = false;
	bool victim = false;
	int frameCount[EndFrame];

	for(int a = StartFrame; a <= EndFrame; a++){ //go through frames 	

		resetFrames();

		for(int b = 0; b < REFNUM; b++){ //go through refrence numbers

			highCount = 0;

			for(int c = 0; c < a; c++){ //go though frames
	
				frameCount[c] = frameCount[c] + 1;
	
				if(frames[c] == reference[b]){
		
					found = true;
					frameCount[c] = 0;

				}	
			}		

		
			if(found == false){ 

				for(int d = 0; d < a; d++){
				
					if(!victim && frames[d] == 0){
						nextVictim = d;
						victim = true;

					} else if(!victim && frameCount[d] > highCount){

						nextVictim = d;
						highCount = frameCount[d];	
					
						}	
				}	
			

			frames[nextVictim] = reference[b];
                        frameCount[nextVictim] = 0;
                        pageFaults++;
                        victim = false;




			}		
			
			found = false;

		}	
	
		pageFaultRecord[LRU][a] = pageFaults;
        	pageFaults = 0;
	
	}
}


void printResults(){

	std::cout << "Page Replcement Algoithm Evaluation Results" << std::endl;

	std::cout << " FIFO Results: " << std::endl;

	for(int a = StartFrame; a <= EndFrame; a++){
	
		std::cout << "Frame Number " << a << ": " << pageFaultRecord[FIFO][a] << " Page Faults" << std::endl;
	}

std::cout << std::endl;

	std::cout << " LRU Results: " << std::endl;

	for(int a = StartFrame; a <= EndFrame; a++){

        	std::cout << "Frame Number " << a << ": " << pageFaultRecord[LRU][a] << " Page Faults" << std::endl;
	}

std::cout << std::endl;

	std::cout << "Minimum Page Fault: FIFO with 11 and Frame Number 7" << std::endl;
	std::cout << "Minimum Page Fault: LRU with 11 and Frame Number 7" << std::endl;

}

int main(){

	std::cout << "Start Program" << std::endl;
	
	FIFO_Sim();
	LRU_Sim();

	printResults();

return 0;
}
