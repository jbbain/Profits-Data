/*********************************************************************/
/*Jared Bain                                            Homework 1   */
/*CISC3110                                                           */
/*********************************************************************/


#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class products {
public:
	string item;
	int sales[4];
	double total;
	double avg;
};
void printData (products);
void HighestProfits (products [], int);
void ProfitLoss (products [], int);
string ProfitMovement (products);


int main()
{

	int size=0;
	int abctotal=0;
    ifstream myfile;
    myfile.open("file.txt"); // Open input file

    // Check for error when opening input file
    if (!myfile.is_open())
    {
    	cout << "File could not be opened" << endl;
    	cout << "Program End";
    	return 0;
    }


    string line;
    line.clear();
	  getline(myfile,line);
	while (myfile)
	{
		size++;
		getline(myfile,line);
	}
    if(myfile.eof())
    {
       myfile.clear();
       myfile.seekg(0,ios::beg); // Go back to the start of the file
    }


	products records[size];
	for (int i=0; i<size; i++){
		myfile >> records[i].item;
		myfile >> records[i].sales[0];
		myfile >> records[i].sales[1];
		myfile >> records[i].sales[2];
		myfile >> records[i].sales[3];

		//Calculate product's total annual profit:
		records[i].total =
				records[i].sales[0] + records[i].sales[1] + records[i].sales[2] + records[i].sales[3];

		//Calculate product's average quarterly profit:
		records[i].avg = records[i].total/4;
	}

	// This prints the table headers:
	cout << setw(10) << "ITEM"
		<< setw(6) << "Q1" << setw(6) << "Q2" << setw(6) << "Q3" << setw(6) << "Q4"
		<< setw(7) << "GROSS" << setw(7) << "AVG" << endl
		<< "__________________________________________________" << endl;
	for (int i=0; i<size; i++)
		printData (records[i]); // Print records
	for (int i=0; i<size; i++)
		abctotal = abctotal + records[i].total; // Total annual profits
		cout << endl;
		cout << "ABC Corp. total annual profits: " << abctotal << endl;
		cout << endl;
		cout << endl;
		cout << "GREATEST QUARTERLY PROFITS:" << endl;
		cout << "___________________________" << endl;

		HighestProfits (records, size); // Prints largest profit and the product for each quarter
		cout << endl;
		cout << endl;

		ProfitLoss (records, size); // Prints table of how many items profited and lost profit for each quarter
		cout << endl;
		cout << endl;
		cout << "PROFIT MOVEMENT:" << endl;
		cout << "________________________________" << endl;

        for (int i=0; i<size; i++)
            {
                cout << records[i].item << "\t";
                cout << ProfitMovement(records[i]);
                cout << endl;
                } // Determines and prints profit movement for the products

    myfile.close(); // Close input file


	return 0;
}



void printData (products detail)
{
	cout << left
	<< setw(14) << detail.item
	<< setw(6) << detail.sales[0]
	<< setw(6) << detail.sales[1]
	<< setw(6) << detail.sales[2]
	<< setw(6) << detail.sales[3]
	<< setw(7) << setprecision(0) << fixed << detail.total
	<< setw(7) << setprecision(1) << fixed << detail.avg
	<< endl;
	return;
}



void HighestProfits (products a[], int n)
{
	string highestprod[4];
	int ProfitForProd[4];
	for (int q=0; q<4; q++)
	{
		// Gives the values for quarter:
		highestprod[q] = a[0].item;
		ProfitForProd[q] = a[0].sales[q];

		for (int r=0; r<n; r++)
			if (a[r].sales[q] > ProfitForProd[q])
			{
				ProfitForProd[q] = a[r].sales[q];
				highestprod[q] = a[r].item;
			}
		// Prints
		cout << " " << "Q" << q+1 << "\t"
				<< highestprod[q] << "\t" << ProfitForProd[q] << endl;
	}
	return;
}



void ProfitLoss (products a[], int n)
{
	int profits[4]; int losses[4]; // Declare arrays to store profit/loss item counts for each quarter
	cout << setw(8) << "" << "QUARTERLY" << endl;
	cout << setw(5) << "" << setw(9) << "Profits" << setw(7) << "Losses" << endl;
	cout << "     _______________" << endl;
	for (int q=0; q<4; q++) // loop through quarters
	{
		profits[q]=0; losses[q]=0;
		for (int r=0; r<n; r++)
		{
			if (a[r].sales[q] > 0)
				profits[q]++;
			else if (a[r].sales[q] < 0)
				losses[q]++;
		}
		// Print
		cout << "Q" << q+1 << ":\t"
				<< profits[q] << "\t" << losses[q] << endl;
	}
	return;
}



string ProfitMovement (products detail)
{
	// Check for an increasing movement
	for (int q=0; q<4; q++)
	{
		if (detail.sales[q] > detail.sales[q+1])
			break;
		else if (q == 2)
			return "STEADILY INCREASED";
	}
	// Check for a decreasing movement
	for (int q=0; q<3; q++)
	{
		if (detail.sales[q] < detail.sales[q+1])
			break;
		else if (q == 2)
			return "STEADILY DECREASED";
	}
	//Otherwise
	return "UP and DOWN";
}
