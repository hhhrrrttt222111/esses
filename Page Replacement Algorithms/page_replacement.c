/*
	Harishankar S Kumar
	TVE19CS034
	Program to implement following Page Replacement Algorithms:
		FIFO
		LRU
		LFU
*/

#include <stdio.h>
#include <stdlib.h>

/*
	Sample test case: 
		3
		20
		7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
		// 7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1
*/

/*
	Struct Page is the page table history
	So the last row of frame is the current page status
	Members: 
		frame : 2D matrix, contents of the page in each row, 
			if value of frame[i][j] is -1, then it is free
		number_of_faults: number of rows in frame, denoting the number of times the page table had to be changed
		change_history: 1D array storing each index of reference string at which the table had to be changed
		reference_time: 1D array, element counts the number of times frame[last][i] was referenced
			can also be used to store last used
*/
typedef struct Page
{
	int number_of_faults;
	int number_of_frames;
	int **frame;
	int *change_history;
	int *reference_time;
}Page;

void free_page(Page *page)
{
	/*
		Deallocate Page instance
	*/

	for(int i=page->number_of_faults-1; i>-1; i--)
		free(page->frame[i]);
	free(page->frame);
	free(page);
}

Page* new_page(int number_of_frames)
{
	// page->number_of_faults = 1;
	/*
		Initializes page instance to contain: 
			0 rows but 1 row pointer in frame
			0 values in change but 1 pointer_history
	*/
	Page *page = (Page *)malloc(sizeof(Page));
	if(page == NULL)
	{
		printf("!> Page Variable Creation failed!\n");
		// free_page(page);
		return(NULL);
	}

	page->number_of_faults = 0; // because it is empty
	page->number_of_frames = number_of_frames;
	page->frame = (int **)malloc(sizeof(int *));
	page->change_history = (int *)malloc(sizeof(int));
	// page->reference_time = (int *)calloc(number_of_frames, sizeof(int));
	page->reference_time = NULL;
	if(page->frame == NULL || page->change_history == NULL)
	{
		printf("!> Resize of Page history failed!\n");
		free_page(page);
		return(NULL);
	}
	page->change_history[0] = 0;
	// page->frame[page->number_of_faults - 1] = (int *)calloc(number_of_frames, sizeof(int));
	// for(int i=0; i<number_of_frames; i++)
	// 	page->reference_time[i] = -1;
	return(page);
}

Page* add_new_snapshot(Page *page, int time)
{
	/*
		Adds a new row to frame
		And initialises it with -1
		number_of_faults must be updated before call
	*/
	int **new_frame = (int **)realloc(page->frame, (page->number_of_faults)*sizeof(int *));
	int *new_history = (int *)realloc(page->change_history, (page->number_of_faults)*sizeof(int));
	if(new_frame == NULL || new_history == NULL)
	{
		printf("!> Resize of Page history failed!\n");
		free_page(page);
		return(NULL);
	}
	page->frame = new_frame;
	page->change_history = new_history;
	page->change_history[page->number_of_faults - 1] = time;
	page->frame[page->number_of_faults - 1] = (int *)calloc(page->number_of_frames, sizeof(int));
	if(new_frame == NULL || new_history == NULL)
	{
		printf("!> Resize of Page history failed!\n");
		free_page(page);
		return(NULL);
	}
	for(int i=0; i<page->number_of_frames; i++)
		page->frame[page->number_of_faults - 1][i] = -1;
	// page->reference_time = page->reference_time;
	return(page);
}

Page* initialize_reference_time(Page *page)
{
	page->reference_time = (int *)calloc(page->number_of_frames, sizeof(int));
	if(page->reference_time == NULL)
	{
		printf("!> Resize of Page history failed!\n");
		free_page(page);
		return(NULL);
	}
	for(int i = 0; i < page->number_of_frames; i++)
		page->reference_time[i] = -1;
	return(page);
}

void print_element(int val)
{
	if(val > -1)
		printf("|%2d", val);
	else
		printf("|  ");
}

void print_History(Page *page, int number_of_references, int *reference_string)
{
	int i, j, history_index=0, history_time=0;
	
	printf("\n\n    Reference String: \n               ");
	for(i=0; i<number_of_references; i++)
		printf(" %2d", reference_string[i]);
	
	history_index = 0;
	printf("\n    Page Frames: \n      ");
	for(i = 0; i < page->number_of_frames; i++)
	{
		printf("         ");
		for(j =0; j < number_of_references; j++)
			printf("---");
		printf("-\n      Frame %d  ", (i+1));
		history_time = 0;
		history_index = 0;
		for(j = 0; j < number_of_references; j++)
		{
			if(j == page->change_history[history_index])
			{
				print_element(page->frame[history_index][i]);
				history_index++;
			}
			else
				print_element(page->frame[history_index-1][i]);
		}

		// Old faulty method to print the thing
		// for(history_index = 0; history_index < page->number_of_faults; history_index++)
		// {
		// 	while( history_time <= page->change_history[history_index])
		// 	{	
		// 		if(page->frame[history_index][i] > -1)
		// 			printf("|%d", page->frame[history_index][i]);
		// 		else
		// 			printf("| ");
		// 		history_time++;
		// 	}
		// 	// printf("|\n ");
		// }
		printf("|\n      ");
	}
	printf("         ");
	for(j =0; j < number_of_references; j++)
		printf("---");
	printf("-");
	// To print search hits

	history_index = 0;
	printf("\n      Hits:    ");
	for(i=0; i<number_of_references; i++)
	{
		if(i == page->change_history[history_index])
		{
			printf("|  ");
			history_index++;
		}
		else
			printf("| H");
	}
	printf("|\n");

	printf("     Number of page faults = %d\n", page->number_of_faults);
}

int search_in_page(Page *page, int value)
{
	int index = page->number_of_faults -1;
	if(index < 0)
		return(-1);
	for(int i=0; i<page->number_of_frames; i++)
	{
		if(page->frame[index][i] == value)
		{
			return(1);
		}
	}
	return(-1);
}

typedef struct SearchResult
{
	int query_index;
	int time_index;
}SearchResult;

SearchResult* search_in_page_2(Page *page, SearchResult *result, int value, int mode)
{
	/*
		Parameters: 
			Page : variable, is required to have the reference_time member initialized
			result : variable to which values will be stored and returned
			value : the value to be searched
			mode: 1 for min time, 0 for max time
		returns SearchResult
	*/
	result->time_index = -1;
	result->query_index = -1;
	int index = page->number_of_faults -1;
	if(index >= 0)
	{
		result->time_index = 0;
		for(int i=0; i<page->number_of_frames; i++)
		{
			if(page->frame[index][i] == value && result->query_index == -1)
			{
				result->query_index = i;
			}
			if(mode)
			{
				if(page->reference_time[i] < page->reference_time[result->time_index])
					result->time_index = i;
			}
			else
			{
				if(page->reference_time[i] > page->reference_time[result->time_index])
					result->time_index = i;
			}
			/*
			It is The First time since 11th, since I created a Dangling else problem 
			if(mode)
				if(page->reference_time[i] < page->reference_time[result->time_index])
					result->time_index = i;
			else
				if(page->reference_time[i] > page->reference_time[result->time_index])
					result->time_index = i;
			*/
		}
	}
	return(result);
}


int fifo_algorithm(Page *page, int number_of_references, int *reference_string)
{
	/*
		First In First Out Algorithm for page replacement
		if the memory to be accessed is not in page, 
			then the the memory address which was placed first in the page is replaced by new memory address
			This increases the number of faults
	*/
	int i, j, res;

	// Keeps track of the queue head, the position of the oldest memory placement
	int queue_head = 0;
	for(i = 0; i < number_of_references; i++)
	{
		res = search_in_page(page, reference_string[i]);
		// printf("%d, ", res);
		if(res == -1)
		{
			page->number_of_faults++;
			page = add_new_snapshot(page, i);
			if(page == NULL)
			{
				printf("!> Iteration %d in fifo_algorithm\n", i);
				free_page(page);
				return(-1);
			}

			// Copy previous Values except at queue_head,
			//  where new value will be placed
			int index = page->number_of_faults - 1;
			if(index < 1)
				page->frame[index][queue_head] = reference_string[i];
			else
			{
				for(j = 0; j < page->number_of_frames; j++)
				{
					page->frame[index][j] = page->frame[index-1][j] ;
				}
				page->frame[index][queue_head] = reference_string[i];
			}
			queue_head = (queue_head + 1)%page->number_of_frames;
		}
		// To check values on each addition to history
		// printf("(%d,%d,%d)|", page->frame[page->number_of_faults-1][1], reference_string[i], i);
	}

	printf("\n -------------------\n Using FIFO Method :");
	print_History(page, number_of_references, reference_string);
	return(0);
}

int lru_algorithm(Page *page, int number_of_references, int *reference_string)
{
	/* 
		Least Recently Used Algorithm
		if memory to be accessed is not in page, then
			each frame has a counter, it will be assigned to the last time it was accessed
			we replace the address of the one with minimum last access time
	*/
	int i, j;

	SearchResult *res = (SearchResult *)malloc(sizeof(SearchResult));
	page = initialize_reference_time(page);
	if(res == NULL || page == NULL)
	{
		printf("!> Failed to Create initialize LRU\n");
		free_page(page);
		return(-1);
	}
	res->query_index = -1;
	res->time_index = -1;

	for(i =0; i < number_of_references; i++)
	{
		res = search_in_page_2(page, res, reference_string[i], 1);
		if(res->query_index == -1)
		{
			page->number_of_faults++;
			page = add_new_snapshot(page, i);
			if(page == NULL)
			{
				printf("!> Iteration %d in lru_algorithm\n", i);
				free_page(page);
				return(-1);
			}

			// Copy all previous values
			// new value will be placed at res->time_index
			int index = page->number_of_faults -1;
			if(index < 1)
			{
				// Initially when the page was empty
				page->frame[index][index] = reference_string[i];
				page->reference_time[index] = i;
			}
			else
			{
				for(j = 0; j<page->number_of_frames; j++)
				{
					page->frame[index][j] = page->frame[index -1][j];
				}
				if(index < page->number_of_frames)
				{
					// To avoid the present values getting overwritten
					// when the page frames are not completely
					// filled
					page->reference_time[index] = i;
					page->frame[index][index] = reference_string[i];
				}
				else
				{
					// Page frames are filled
					// selecting least referred memory 
					// to be overwritten
					page->reference_time[res->time_index] = i;
					page->frame[index][res->time_index] = reference_string[i];
				}
			}
		}
		else
		{
			// Update reference time of value which was looked up
			if(res->time_index != -1)
			{
				page->reference_time[res->query_index] = i;
			}
			else
			{
				printf("!> time_index search fault @ iteration %d of LRU!\n", i);
			}
		}
	}
	free(res);
	free(page->reference_time);
	printf("\n -------------------\n Using LRU Method :");
	print_History(page, number_of_references, reference_string);
	return(0);
}

int lfu_algorithm(Page *page, int number_of_references, int *reference_string)
{
	/* 
		Least Frequently Used Algorithm
		if memory to be accessed is not in page, then
			each frame has a counter, it will be assigned 0 initially and incremented each time it is accessed
			we replace the address of the one with minimum total accessess
	*/
	int i, j;

	SearchResult *res = (SearchResult *)malloc(sizeof(SearchResult));
	page = initialize_reference_time(page);
	if(res == NULL || page == NULL)
	{
		printf("!> Failed to Create initialize LFU\n");
		free_page(page);
		return(-1);
	}
	res->query_index = -1;
	res->time_index = -1;

	for(i =0; i < number_of_references; i++)
	{
		res = search_in_page_2(page, res, reference_string[i], 1);
		if(res->query_index == -1)
		{
			page->number_of_faults++;
			page = add_new_snapshot(page, i);
			if(page == NULL)
			{
				printf("!> Iteration %d in lfu_algorithm\n", i);
				free_page(page);
				return(-1);
			}

			// Copy all previous values
			// new value will be placed at res->time_index
			int index = page->number_of_faults -1;
			if(index < 1)
			{
				page->frame[index][index] = reference_string[i];
				page->reference_time[index] = 0;
			}
			else
			{
				for(j = 0; j<page->number_of_frames; j++)
				{
					page->frame[index][j] = page->frame[index -1][j];
				}
				if(index < page->number_of_frames)
				{
					// To avoid the present values getting overwritten
					// when the page frames are not completely
					// filled

					page->reference_time[index] = 0;
					page->frame[index][index] = reference_string[i];
				}
				else
				{
					// Page frames are filled
					// selecting least referred memory 
					// to be overwritten

					page->reference_time[res->time_index] = 0;
					page->frame[index][res->time_index] = reference_string[i];
				}
			}
		}
		else
		{
			if(res->time_index != -1)
			{
				// Increment the reference whose value was looked up
				page->reference_time[res->query_index]++;
			}
			else
			{
				printf("!> time_index search fault @ iteration %d of LFU!\n", i);
			}
		}
	}
	free(res);
	free(page->reference_time);
	printf("\n -------------------\n Using LFU Method :");
	print_History(page, number_of_references, reference_string);
	return(0);
}



int main()
{
	int number_of_frames, number_of_references, i, status = 0;
	int *reference_string;
	
	printf(" Enter the number of page frames: ");
	scanf("%d", &number_of_frames);
	printf(" Enter the number of references in reference string: ");
	scanf("%d", &number_of_references);

	if(number_of_references < 1 || number_of_frames < 1)
		return(0);

	Page *page = new_page(number_of_frames);
	reference_string = (int *)calloc(number_of_references, sizeof(int));

	if(page == NULL || reference_string == NULL)
	{
		printf("!> Unable to allocate variables!\n> Exiting!");
		free_page(page);
		free(reference_string);
		return(1);
	}

	printf("\n Enter the reference string (space separated integers)!\n");
	printf(">> ");
	for(i=0; i<number_of_references; i++)
		scanf("%d", &reference_string[i]);

	status = fifo_algorithm(page, number_of_references, reference_string);
	if(status != 0)
	{
		printf("!> Error %d\n, !> Exiting!\n", status);
		free_page(page);
		free(reference_string);
		return(1);
	}

	// Reset page for LRU 
	free_page(page);
	page = new_page(number_of_frames);
	if(page == NULL)
	{
		printf("!> Unable to allocate variables!\n> Exiting!");
		free_page(page);
		free(reference_string);
		return(1);
	}

	status = lru_algorithm(page, number_of_references, reference_string);
	if(status != 0)
	{
		printf("!> Error %d\n, !> Exiting!\n", status);
		free_page(page);
		free(reference_string);
		return(1);
	}

	// Reset page for LFU algorithm
	free_page(page);
	page = new_page(number_of_frames);
	if(page == NULL)
	{
		printf("!> Unable to allocate variables!\n> Exiting!");
		free_page(page);
		free(reference_string);
		return(1);
	}

	status = lfu_algorithm(page, number_of_references, reference_string);
	if(status != 0)
	{
		printf("!> Error %d\n, !> Exiting!\n", status);
		free_page(page);
		free(reference_string);
		return(1);
	}
	printf("\n");
	free_page(page);
	free(reference_string);
	return(0);
}