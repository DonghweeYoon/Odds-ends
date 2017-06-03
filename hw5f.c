/*
What is the maximum number of page table entries?
64, 6 bits are allocated for number of page in logical address
With 6 bits, we can make 2^6 different addresses

What is the size of a page (in bytes)?
1024, 10 bits are allocated for offset of page in logical address
With 10 bits, we can make 2^10 different addresses
(Offset 단위 byte)

How many pages are necessary to store a process whose size is 24800 bytes?
25, Process Size + Offset Size - 1 / Offset Size;
전체 prcess 크기를 offset 크기로 나누어준 뒤 올림하면 페이지의 개수가 됩니다.
*/

#include <stdio.h>
#include <stdlib.h>

//Declare the followings globally.
#define BitsForPageNo 6
#define BitsForPageOffset 10

#define ProcessSize 24800

void init_page_table(int table[], int no_page);
char* to_binary(unsigned short addr);

unsigned short logical2physical(unsigned short logical_addr, int page_table[]);

int main(){
	int no_page = 0;
	int *page_table = NULL;

	//logical addresses to test case logical2physical() - can be changed
	unsigned short logical_addr[] = { 0x21dd, 0x0829, 0x08f0, 0x0ad1, 0x071e, 0x0431, 0x0fb8, 0x0b18, 0x38ab, 0x07a0 };

	int i = 0;

	//print maximum # of pages and page size
	no_page = (ProcessSize + (1 << BitsForPageOffset) - 1) / (1 << BitsForPageOffset);//compute # size of pages to store ProcessSize (=24800) bytes
	page_table = (int*)malloc(no_page * sizeof(int));
	if(page_table == NULL){
		printf("Failed to allocate memory!\n");
		exit(-1);
	}
	
	init_page_table(page_table, no_page);

	for(i = 0; i < 10; i++){
		unsigned short physical_addr = logical2physical(logical_addr[i], page_table);
		printf("0x%04x (%s) ", logical_addr[i], to_binary(logical_addr[i]));
		printf("--> 0x%04x (%s)\n", physical_addr, to_binary(physical_addr));
	}
	free(page_table);

	return 0;
}

//Initialize page table entries
void init_page_table(int table[], int no_page){
	int i = 0;
	
	//For simple experiment, set table[i] by (i * 2 +3) for all i.
	for(i = 0; i < no_page; i++)
		table[i] = i * 2 + 3;
}

//return a string containing binary representation of addr.
//Provided
char* to_binary(unsigned short addr){
	static char bits[17];
	int i = 0;
	for(i = 0; i < 16; i++){
		bits[15 - i] = '0' + (addr & 1);
		addr >>= 1;
	}
	bits[16] = 0;

	return bits;
}

//Given a page table, translates a logical address into the corresponding physical address.
unsigned short logical2physical(unsigned short logical_addr, int page_table[]){
	unsigned short pageNum;
	unsigned short Offset;
	unsigned short frameNum;
	unsigned short physical_addr;
	
	//Retrieve page number from logical_addr
	pageNum = logical_addr >> BitsForPageOffset;
	//Retrieve page offset from logical_addr
	Offset = logical_addr & ((1 << BitsForPageOffset) - 1);
	
	//Convert page number into frame number using page_table
	frameNum = page_table[pageNum];
	//Combine frame number and page offset to make physical address
	physical_addr = (frameNum << BitsForPageOffset) | Offset;
	
	//Retrun physical address
	return physical_addr;
}
