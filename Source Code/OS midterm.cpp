#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int Check_Safety(int resources,int processes, int Available[], int **Need, int **Allocation, string Safe[])
{
	// Work matrix;
	int* Work = new int[resources];
	for (int i = 0; i < resources; i++)
	{
		Work[i] = Available[i];
	}
	// Finish matrix
	string* Finish = new string[processes];
	for (int i = 0; i < processes; i++)
	{
		Finish[i] = "False";
	}
	
	
	
	string cs;
	int c = 0;
	for (int k = 0; k < processes; k++)
	{
		
		for (int i = 0; i < processes; i++)
		{
			if (Finish[i] == "False")
			{
				for (int j = 0; j < resources; j++)
				{
					if( Need[i][j] <= Work[j])
					{
						if (j == resources - 1)
						{
							for (int m = 0; m < resources; m++)
							{
								Work[m] = Work[m] + Allocation[i][m];
							}
							Finish[i] = "True";
							std ::stringstream ss;
							ss << i;
							ss >> cs;
							Safe[c] = "P" + cs;
							c++;
						}
					}
					else break;
				}
				
			}
			
		}
	}
	int count = 1;
	for (int i = 0; i < processes; i++)
	{
		if (Finish[i] == "False")
			count = 0;
	}
	delete[]Work;
	delete[]Finish;
	return count;
}
int main()
{
	cout << "Enter number of processes" << endl;
	int processes; cin >> processes;
	cout << "Enter number of resources" << endl;
	int resources; cin >> resources;
	// Allocation matrix
	int** Allocation = new int* [processes];
	for (int i = 0; i < processes; i++)
		Allocation[i] = new int[resources];
	// Max matrix
	int** Max = new int* [processes];
	for (int i = 0; i < processes; i++)
		Max[i] = new int[resources];
	// Available matrix
	int* Available = new int[resources];
	// Need matrix
	int** Need = new int* [processes];
	for (int i = 0; i < processes; i++)
		Need[i] = new int[resources];

	cout << "Enter Allocation Matrix" << endl;
	for (int i = 0; i < processes; i++)
	{
		cout << "P" << i << " ";
		for (int j = 0; j < resources; j++)
		{
			cin >> Allocation[i][j];
		}
	}
	cout << "Enter Max Matrix" << endl;
	for (int i = 0; i < processes; i++)
	{
		cout << "P" << i << " ";
		for (int j = 0; j < resources; j++)
		{
			cin >> Max[i][j];
		}
	}
	cout << "Enter Available Matrix" << endl;
	for (int i = 0; i < resources; i++)
	{
		cin >> Available[i];
	}
	// Calculating Need matrix
	for (int i = 0; i < processes; i++)
	{
		for (int j = 0; j < resources; j++)
		{
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
	}
	cout << "Need Matrix :" << endl;
	for (int i = 0; i < processes; i++)
	{
		cout << "P" << i << " ";
		for (int j = 0; j < resources; j++)
		{
			cout << Need[i][j] << " ";
		}
		cout << endl;
	}
	//Safe state
	string* Safe = new string[processes];
	while (true)
	{
		cout << "To check if system is safe press 1" << endl << "To make a request press 2" << endl;
		cout << "To exit press 3" << endl;
		int choice; cin >> choice;

		if (choice == 1)
		{
			int check = Check_Safety(resources, processes, Available, Need, Allocation, Safe);
			if (check == 1)
			{
				cout << "Yes, Safe state <";
				for (int i = 0; i < processes; i++)
				{
					if (i == processes - 1)
						cout << Safe[i];
					else
						cout << Safe[i] << ",";
				}
				cout << ">" << endl;
			}
			else if (check == 0)
				cout << "No"<<endl;


		}

		else if (choice == 2)
		{
			int* request = new int[resources];
			cout << "Enter number of process you want the request for" << endl;
			int number; cin >> number;
			cout << "Enter Request matrix" << endl;
			int error1 = 0; int error2 = 0;
			for (int i = 0; i < resources; i++)
			{
				cin >> request[i];
				if (request[i] > Need[number][i])
					error1 = 1;
				else if (request[i] > Available[i])
					error2 = 1;
			}
			if (error1 == 1)
				cout << "ERROR. P" << number << " has exceeded its claim." << endl;
			else if (error2 == 1)
				cout << "ERROR. P" << number << " must wait because resources are not available." << endl;
			else if (error1 == 0 && error2 == 0)
			{
				for (int i = 0; i < resources; i++)
				{
					Available[i] -= request[i];
					Allocation[number][i] += request[i];
					Need[number][i] -= request[i];
				}
				int check = Check_Safety(resources, processes, Available, Need, Allocation, Safe);
				if (check == 1)
				{
					cout << "Yes, request can be granted with safe state. Safe state <P"<<number<<"req,";
					for (int i = 0; i < processes; i++)
					{
						if (i == processes - 1)
							cout << Safe[i];
						else
							cout << Safe[i] << ",";
					}
					cout << ">"<<endl;
				}
				else if (check == 0)
					cout << "No"<<endl;

			}
		}
		else if (choice == 3)
			break;
	}
	delete[]Allocation;
	delete[]Max;
	delete[]Available;
	delete[]Need;
	delete[]Safe;
	return 0;
}

