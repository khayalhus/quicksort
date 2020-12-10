#include<iostream>
#include<fstream>
#include<string>
#include<time.h> // clock_t, clock, CLOCKS_PER_SEC
using namespace std;

// This function swaps contents of two addresses
template <typename T>
void swap(T* a, T* b) 
{ 
    T t = *a; 
    *a = *b; 
    *b = t; 
}

// this is the struct that holds each sales entry
struct entry {
	string country;
	string item_type;
	string order_id;
	int units_sold;
	double total_profit; // total profit is stored with double because float was losing some of the data
};

int partition(entry arr[], int left, int right) {
	int orange = left; // this is for the orange bar and j is the blue bar in the lecture slides

	int pivot = right; // pivot is chosen as right-most element of partition

	for (int blue = left; blue < right; blue++) { // compare each element (excluding pivot) with pivot
		if ((arr[blue].country).compare(arr[pivot].country) < 0 || ((arr[blue].country).compare(arr[pivot].country) == 0 && arr[blue].total_profit > arr[pivot].total_profit)) {
			// element is smaller than pivot if country is alphabetically smaller or total profit is bigger than pivot
			swap(&arr[orange], &arr[blue]); // swap the things ahead of the bars
			orange++; // move bar to the right
		}
	}
	swap(&arr[orange], &arr[pivot]); // swap pivot back into its place
	return orange; // return pivot
}

void quicksort(entry arr[], int left, int right) {
	if(left < right){ 
		int pivot = partition(arr, left, right); // get pivot and sort according to it
		quicksort(arr, left, pivot - 1); // send left of pivot
        quicksort(arr, pivot + 1, right); // send right of pivot
	}
}

void print(entry arr[], int N, string header) {

	ofstream outfile;

	outfile.open("sorted.txt"); // open file for writing

	if (!outfile) {
		cerr << "Write file cannot be opened!";
		exit(1);
	}

	outfile << header << endl; // write the category names (the header line)

	for(int i = 0; i < N; i++) {
		// write each sorted sales entry to the "sorted.txt" file
		outfile << arr[i].country << '\t' << arr[i].item_type << '\t' << arr[i].order_id << '\t' << arr[i].units_sold << '\t' << arr[i].total_profit << '\n';
	}

	outfile.close(); // close "sorted.txt"
}

int main(int argc, char** argv){

	clock_t time_elapsed; // used for storing program execution time
	clock_t algo_time; // used for quicksort call execution time
	time_elapsed = clock();

	int N; // number of sales entries

	if (argc > 1) {
		N = atoi(argv[1]); // get number N from console argument (./a.out N)
	} else {
		N = 100; // default value for N
		cout << "N was not specified as an argument" << endl;
		cout << "Automatically setting N as 100" << endl;
	}
	
	ifstream file;
	file.open("sales.txt");
	
	if (!file){
		cerr << "File cannot be opened!";
		exit(1);
	}

	string line;
	
	getline(file, line); //this is the header line

	string header = line;

	entry * arr = new entry[N]; // create N struct objects and hold their pointers in an array of size N

	for(int i = 0; i<N; i++){
		//store data in struct objects
		getline(file, line, '\t'); //country (string)
		arr[i].country = line;
		getline(file, line, '\t'); //item type (string)
		arr[i].item_type = line;
		getline(file, line, '\t'); //order id (string)
		arr[i].order_id = line;
		file >> line; //units sold (integer)
		arr[i].units_sold = stoi(line);
		file >> line; //total profit (float)
		arr[i].total_profit = stod(line);
	    getline(file, line, '\n'); //this is for reading the \n character into dummy variable.
	}
	
	algo_time = clock(); // get time passed until QuickSort call
	quicksort(arr, 0, N-1);
	cout << "Quicksort algo call took " << clock() - algo_time << " clocks or " << ( (float (clock() - algo_time) / CLOCKS_PER_SEC)) << " seconds." << endl;
	print(arr, N, header); // write the sorted list to the "sorted.txt" file

	delete [] arr; // delete sales entries

	time_elapsed = clock() - time_elapsed; // calculate program execution time

	cout << "The program took " << time_elapsed << " clocks or " << ( (float) time_elapsed ) / CLOCKS_PER_SEC << " seconds." << endl;

	return 0;
}
