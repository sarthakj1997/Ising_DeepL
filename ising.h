#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <vector>

using namespace std;

int dim,CN;
vector<int> latticeSize;
int mcSweep, saveFrequency, thermalization;
float tempStart, tempEnd, tempStep, criticalTemp;
int totLatticeSites;
vector<int> lattice;
vector<int> neighbors;
vector<float> energy, magnet; 

void create_lattice() {
	for(int l=0; l<totLatticeSites; l++) {
		double random = float(rand())/RAND_MAX;
		lattice[l]= (random<0.5)?1:-1;
	}
}

void find_neighbors(int l) {
	neighbors.resize(CN);
	for (int cn=0; cn<neighbors.size(); cn++) {
		int sumTerm=1,prodTerm=1;
		for(int i=0; i<cn/2; i++) sumTerm*=latticeSize[i];
		for(int i=0; i<cn/2+1; i++) prodTerm*=latticeSize[i];
		if(cn%2==0) {
			neighbors[cn]=l+sumTerm;
			if(neighbors[cn]/prodTerm != l/prodTerm || neighbors[cn]<0) neighbors[cn]=neighbors[cn]-prodTerm;
		}
		else {
			neighbors[cn]=l-sumTerm;
			if(neighbors[cn]/prodTerm != l/prodTerm || neighbors[cn]<0) neighbors[cn]=neighbors[cn]+prodTerm;
		}
	}
}

void calculate_energy() {
	double sum=0;
	for(int l=0; l<totLatticeSites; l++) {
		find_neighbors(l);
		sum=0;
		for(int cn=0;cn<2*dim;cn++) sum=sum+lattice[neighbors[cn]];
		energy[l]=(-1.0)*(lattice[l])*sum;
	}
}

double calculate_energy(int l) {
	double sum=0;
	find_neighbors(l);
	for(int cn=0; cn<2*dim; cn++) sum=sum+lattice[neighbors[cn]];
	double energy=(-1.0)*(lattice[l])*sum;
	return energy;
}

void flip(double temp){
	for(int l=0; l<totLatticeSites; l++) {
		double erg=calculate_energy(l);
		lattice[l]=lattice[l]*(-1);
		double ergAfterFlip=calculate_energy(l);
		lattice[l]=lattice[l]*(-1);
		if(ergAfterFlip<erg) { 
			lattice[l]=lattice[l]*(-1);
			energy[l]=ergAfterFlip;
		}
		else { 
			double thermal=-(ergAfterFlip-erg)/temp;
			if(exp(thermal)>float(rand())/(RAND_MAX)) { 
				lattice[l]=lattice[l]*(-1); 
				energy[l]=ergAfterFlip;
			}
		}
	}
}

