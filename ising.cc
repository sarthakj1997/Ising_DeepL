#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <string>
#include <vector>
#include "ising.h"

using namespace std;

int main(int argc, char **argv) {
	
	dim=atoi(argv[1]);
	CN=2*dim;
	if(argc==dim+9) {
		latticeSize.resize(dim);
		for (int d=0; d<dim; d++) latticeSize[d]=atoi(argv[d+2]);	
		mcSweep=atoi(argv[dim+2]);
		saveFrequency=atoi(argv[dim+3]);
		tempStart=atof(argv[dim+4]);
		tempEnd=atof(argv[dim+5]);
		tempStep=atof(argv[dim+6]);
		criticalTemp=atof(argv[dim+7]);
		thermalization=atoi(argv[dim+8]);
	}
	else {
		cout<<"Usage: <Lattice Dimension> <size of every lattice dimension> <No. of MC sweeps> <Save Frequency> <tempStart> <tempEnd> <Step size of temp> <critical temp> <thermalization>"<<endl; 
		return 0;
	}
	totLatticeSites=1;
	for(int d=0; d<dim; d++) totLatticeSites*=latticeSize[d];
	lattice.resize(totLatticeSites);
	create_lattice();
	energy.resize(totLatticeSites);
	calculate_energy();
	for(float temp=tempStart; temp<=tempEnd; temp+=tempStep) {
		string label;
		if(temp<criticalTemp) label="ferro";
		else label="para";
		string fileName=label+"_"+to_string(dim)+"_"+to_string(latticeSize[0])+"_"+to_string(temp).substr(0,4)+".csv";
		ofstream outputFile(fileName);
		if(outputFile.is_open()) {
			for(int sweep=0; sweep<=mcSweep; sweep++) {
				flip(temp);
				if(sweep>thermalization && sweep%saveFrequency==0) {
					for(int l=0; l<totLatticeSites; l++) {
						outputFile<<lattice[l];
						if(l<totLatticeSites-1) outputFile<<",";
					}
					outputFile<<endl;
				}
			}
			outputFile.close();
		}
		
		//for printing as 2-D array slices
		/*for(int i=0; i<totLatticeSites; i++) {
			cout<<i<<" ";
			if((i+1)%latticeSize[0]==0) cout<<endl;
			if((i+1)%(latticeSize[0]*latticeSize[1])==0) cout<<"!!!!!!"<<endl;
		}*/
		
	}
}
