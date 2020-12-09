#include<iostream>
#include<iomanip> // std::setprecision
#include<fstream>
#include<string>
//#include<algorithm>    // std::swap
#include<time.h> // clock_t, clock, CLOCKS_PER_SEC
using namespace std;

template <typename T>
void swap(T* a, T* b) 
{ 
    T t = *a; 
    *a = *b; 
    *b = t; 
}

struct entry {
	string country;
	string item_type;
	string order_id;
	int units_sold;
	double total_profit;
};

int partition(entry arr[], int l, int r) {
	int i = l;

	int pivot = r;

	for (int j = l; j < r; j++) {
		if ((arr[j].country).compare(arr[pivot].country) < 0 || ((arr[j].country).compare(arr[pivot].country) == 0 && arr[j].total_profit > arr[pivot].total_profit)) {
			swap(&arr[i], &arr[j]);
			i++;
		}
	}
	swap(&arr[i], &arr[pivot]);
	return i;
}

void quicksort(entry arr[], int l, int r) {
	if(l < r){ 
		int pivot = partition(arr, l, r);
		quicksort(arr, l, pivot - 1);  
        quicksort(arr, pivot + 1, r);
	}
}

void print(entry arr[], int N, string header) {

	ofstream outfile;

	outfile.open("sorted.txt");

	if (!outfile) {
		cerr << "Write file cannot be opened!";
		exit(1);
	}

	outfile << header << endl;

	//outfile << setprecision(15);
	for(int i = 0; i < N; i++) {
		outfile << arr[i].country << '\t' << arr[i].item_type << '\t' << arr[i].order_id << '\t' << arr[i].units_sold << '\t' << arr[i].total_profit << '\n';
	}

	//outfile << endl;
	outfile.close();
}

int main(int argc, char** argv){

	int N;

	if (argc > 1) {
		N = atoi(argv[1]);
	} else {
		N = 100;
		cout << "N was not specified as an argument" << endl;
		cout << "Automatically setting N as 100" << endl;
	}
	
	clock_t time_elapsed;
	clock_t algo_time;
	time_elapsed = clock();

	ifstream file;
	file.open("sales.txt");
	
	if (!file){
		cerr << "File cannot be opened!";
		exit(1);
	}

	string line;
	
	getline(file, line); //this is the header line

	string header = line;

	entry * arr = new entry[N];

	for(int i = 0; i<N; i++){
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
	//print(country, item_type, order_id, units_sold, total_profit, N);
	algo_time = clock();
	quicksort(arr, 0, N-1);
	cout << "Quicksort algo call took " << algo_time << " clocks or " << ( (float (clock() - algo_time) / CLOCKS_PER_SEC)) << " seconds." << endl;
	print(arr, N, header);

	delete [] arr;

	time_elapsed = clock() - time_elapsed;

	cout << "The program took " << time_elapsed << " clocks or " << ( (float) time_elapsed ) / CLOCKS_PER_SEC << " seconds." << endl;

	return 0;
}
