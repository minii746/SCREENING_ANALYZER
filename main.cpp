#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <stdio.h>
#include <process.h>
#include <bits/stdc++.h>
using namespace std;

//function which will find the required mesh number
string find_mesh_number(string csv_name);

//function which will find the effectiveness
double find_effectiveness(string csv_name, string mesh, int choice);

int main()
{
    char name_of_csv[100];
    string product;

    cout << setw(70)<< "SCREENING ANALYZER!" << endl << endl ;
    cout << "This program will help you to perform Screen Analysis faster with high accuracy ."
         << "This Exploratory project was done under the guidance of Mrs. Bhavna Verma" << endl << endl ;

    cout << "Press any key to continue ..." << endl << endl ;
    getch();

    cout << "Enter the name of Csv file from which the values will be imported : ";
    gets(name_of_csv);

    string mesh_number = find_mesh_number( name_of_csv );

    //Error handling for incorrect file name
    if(mesh_number == "\0"){
        cout << endl << name_of_csv << ".csv not found!";
        exit(1);
    }

    int choice;

    //Enforcing to enter the between 1 & 2
    do{
        cout << endl << "The desired product is Oversize(enter 1) or Undersize(enter 2) ? : ";
        cin >> choice;

        switch(choice){
            case 1: product = "Oversize";
                break;
            case 2: product = "Undersize";
                break;
            default: cout << endl << "Try to choose between 1 or 2" << endl;
        }
    }while(choice!=1 && choice !=2);

    double effectiveness = find_effectiveness( name_of_csv, mesh_number, choice );

    cout << endl <<"The Effectiveness of the Mesh number "<< mesh_number << " for the "
         << product << " product is : " << effectiveness << "%" << endl << endl ;

    cout << "This project was made by -" << endl << endl;
    cout << "19045023 Arjun Gupta" << endl;
    cout << "19045146 Aaryam Sthapak" << endl;
    cout << "19045015 Amit Singh Rawat" << endl;
    cout << "19045017 Anjali Meena" << endl;

    return 0;
}

string find_mesh_number(string csv_name){
    int length = 0;

    //Opening the file
    fstream fin;
    fin.open(csv_name+".csv", ios::in);

    if(fin){
        vector<string> row, mesh_values;
        string line, mesh;

        cout << endl <<"The Mesh numbers available in " << csv_name << ".csv file are :" << endl << endl;

        //Storing the mesh numbers available
        while (fin>>mesh) {
        length++;
        getline(fin, line);
        cout << "index " << length << "-> " << mesh <<endl;
        mesh_values.push_back(mesh);
        }

        int index = 0;

        //Enforcing to enter a valid mesh index
        do{
        cout << endl << "Enter the index of the Mesh number for which the computation must be performed : ";
        cin >> index;
        if(!(index<=length && index>0)){
            cout << endl << "Try to choose between 1 and " << length << endl;
        }
        }while(!(index<=length && index>0));

        //Returning the mesh number
        return mesh_values[index-1];
    }
    else {
        //Returning null if file was not found
        return "\0";
    }
}

double find_effectiveness(string csv_name, string mesh_number, int choice){
    double result, Xf=0, Xd=0, Xb=0;

    //Opening file (as file was opened previously so no need for considering "file not found" error)
    fstream fin;
    fin.open(csv_name+".csv", ios::in);

    vector<string> row;
	string line, word, mesh;

	//Storing the cumulative values of feed , product and reject
    while (fin >> mesh) {
		row.clear();
        getline(fin, line);
		stringstream s(line);
		while (getline(s, word, ',')) {
			row.push_back(word);
		}
		Xf = Xf + stod(row[0]);
		Xd = Xd + stod(row[1]);
		Xb = Xb + stod(row[2]);
        if(mesh_number == mesh){
            break;
        }
    }

    cout << endl << "The cumulative values are - " <<endl ;
    cout <<"Xf: " << Xf << endl;
    cout <<"Xd: " << Xd << endl;
    cout <<"Xb: " << Xb << endl;

    if(choice == 1){
        //If the desired product is oversize
        result = ((Xd*(Xf-Xb))/(Xf*(Xd-Xb)))*(1-(((Xf-Xb)*(1-Xd))/((Xd-Xb)*(1-Xf))));
        return result*100;
    }
    else if(choice == 2){
        //If the desired product is undersize
        Xf = 1-Xf;
        Xd = 1-Xd;
        Xb = 1-Xb;
        result = ((Xd*(Xf-Xb))/(Xf*(Xd-Xb)))*(1-(((Xf-Xb)*(1-Xd))/((Xd-Xb)*(1-Xf))));
        return result*100;
    }
    else{
        //If wrong choice was given return 0
        return 0;
    }
}
