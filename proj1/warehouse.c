#include "slots.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv) {
	int maxInt = 2147483647;
	int slotOn=0;//used at the start to fill up empty slots at the start
	int leastUsed[2];//0 = slot index, 1 = times used. Used to find which bin has been used the least
	int tracker[100];//keeps track of how many times each bin is used
	int currSlots[4];//used to keep track of whats in each slot
	int i;
	//initialies all values in tracker to 0
	for(i = 0; i < 100; i++){
		tracker[i] = 0;
	}
	int bin;

	initSlots();
	while(1==scanf("%d",&bin)) {
		//if the bin is not in a slot
		if (-1==findSlot(bin)) {
			//fills up slots before replacing any bins
			if(slotOn < 4){
				getBin(bin,slotOn);
				currSlots[slotOn] = bin;
				slotOn++;
			}
			//if all slots are in use, replaces bin in the slot with least used bin
			else{
				leastUsed[1] = maxInt;
				for(i=0; i< 4; i++){
					if(tracker[currSlots[i]] < leastUsed[1]){
						leastUsed[0] = i;
						leastUsed[1] = tracker[currSlots[i]];
					}
				}
				currSlots[leastUsed[0]] = bin;
				getBin(bin,leastUsed[0]);
			}
		}
		getWidget(bin);
		tracker[bin]++;
	}
	printEarnings();
	/*****Test case generating code given to me by prof Bartenstein*****
	int order[100];
	int n = 100;
	for(i=0;i<n;i++) {
		int ind = rand()%(i+1);
		if (ind==i) order[i]=rand()%100;
		else order[i]=order[ind];
		printf("%d ",order[i]);
	}
	*/
	return 0;
}

