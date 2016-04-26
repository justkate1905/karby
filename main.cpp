#include <fstream>
#include <iostream>
#include <vector>
#define size_opcode int
using namespace std;
int main(int argc, char **argv)
{
		FILE *file;
		char* name = " ";
		vector<double> opcodes;
		int buff[1];
		int size, addr_reg1, addr_reg2;
		short int s;
		char f;
		double op1, op2;
		vector<double> math_stack;
		if(argc==1){
			cout<<"There's no filename"<<endl;
			}
		else{
		name = argv[1];
		}
		int p;
		file = fopen(name, "rb");
		if((file = fopen(name, "rb"))==NULL){
			cout<< "This file is not exist!"<<endl;
			}
		else{
			fread(buff, sizeof(int), 1, file);
			size = buff[0];
			opcodes.push_back(buff[0]);
			for(int i =0; i < size/4-1;i++){
				fread(buff, sizeof(int), 1, file);	
				opcodes.push_back(buff[0]);				
			}
		}
		fclose(file);
		for(int i =0; i<opcodes.size(); i++){
			cout<<hex<<opcodes.at(i)<<endl;
			}
		for(int i =0; i<opcodes.size(); i++){
			p=(int)(opcodes.at(i));
			switch(p){
				case 0x00A1:
					break;
				case 0x00A6:
					break;
				case 0x00A7:
					break;
				case 0x00A9:
					break;
				case 0x00AA:
					break;
				case 0x00AB:
					break;
				case 0x00AC:
					break;
				case 0x00AF:
					break;
				case 0x00B0:
					break;
				case 0x00C9:
					cout<<opcodes.at(i+1)<<endl;
					break;
				case 0x00CA:
					//f = ((int)(opcodes.at(i+1))|0)&&0xFFFF;
					//s = ((int)(opcodes.at(i+1))); 
					//s = 0x00000062;// && 0xFFFF;
					//cout<< s <<' ' << 16<<endl;
					break;
				case 0x00C8:
					cout<<opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2)<<endl;
					break;
				//Операция сложения	
				case 0x1000:
					op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
					op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
					math_stack.push_back(op1+op2);
					i+=2;
					break;
				case 0x1001:
					op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
					op2 = opcodes.at(i+2);
					switch((int)(op2)){
						case 0x00A9:
							
							break;
						case 0x00AA:
							op2 = math_stack.back();
							math_stack.pop_back();
							break;
					} 
					math_stack.push_back(op1+op2);
					i+=2;
					break;
				case 0x1002:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
					switch((int)(op1)){
						case 0x00A9:
							
							break;
						case 0x00AA:
							op1 = math_stack.back();
							math_stack.pop_back();
							break;
					} 
					math_stack.push_back(op1+op2);
					i+=2;
					break;
				case 0x1003:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					switch((int)(op1)){
						case 0x00A9:
							op2 = math_stack.back();
							math_stack.pop_back();
							op1 = math_stack.back();
							math_stack.pop_back();
							break;
						case 0x00AA:
							op1 = math_stack.back();
							math_stack.pop_back();
							break;
					} 
					math_stack.push_back(op1+op2);
					i+=2;
					break;
				//Операция вычитания 
				case 0x1004:
					op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
					op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
					math_stack.push_back(op1-op2);
					i+=2;
					break;
				case 0x1005:
					op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
					op2 = opcodes.at(i+2);
					switch((int)(op2)){
						case 0x00A9:
							
							break;
						case 0x00AA:
							op2 = math_stack.back();
							math_stack.pop_back();
							break;
					} 
					math_stack.push_back(op1-op2);
					i+=2;
					break;
				case 0x1006:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
					switch((int)(op1)){
						case 0x00A9:
							
							break;
						case 0x00AA:
							op1 = math_stack.back();
							math_stack.pop_back();
							break;
					} 
					math_stack.push_back(op1-op2);
					i+=2;
					break;
				case 0x1007:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					switch((int)(op1)){
						case 0x00A9:
							op2 = math_stack.back();
							math_stack.pop_back();
							op1 = math_stack.back();
							math_stack.pop_back();
							break;
						case 0x00AA:
							op1 = math_stack.back();
							math_stack.pop_back();
							break;
					} 
					math_stack.push_back(op1-op2);
					i+=2;
					break;
				//операция умножения	
				case 0x1008:
					op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
					op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
					math_stack.push_back(op1*op2);
					i+=2;
					break;
				case 0x1009:
					op1 = opcodes.at(opcodes.at(i+1)/sizeof(int)+2);
					op2 = opcodes.at(i+2);
					switch((int)(op2)){
						case 0x00A9:
							
							break;
						case 0x00AA:
							op2 = math_stack.back();
							math_stack.pop_back();
							break;
					} 
					math_stack.push_back(op1*op2);
					i+=2;
					break;
				case 0x100A:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(opcodes.at(i+2)/sizeof(int)+2);
					switch((int)(op1)){
						case 0x00A9:
							
							break;
						case 0x00AA:
							op1 = math_stack.back();
							math_stack.pop_back();
							break;
					} 
					math_stack.push_back(op1*op2);
					i+=2;
					break;
				case 0x100B:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					switch((int)(op1)){
						case 0x00A9:
							op2 = math_stack.back();
							math_stack.pop_back();
							op1 = math_stack.back();
							math_stack.pop_back();
							break;
						case 0x00AA:
							op1 = math_stack.back();
							math_stack.pop_back();
							break;
					} 
					math_stack.push_back(op1*op2);
					i+=2;
					break;
				//Операция деления
				case 0x100C:
					op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
					op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
					math_stack.push_back((double)(op1)/(double)(op2));
					i+=2;
					break;
				case 0x100D:
					op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
					op2 = opcodes.at(i+2);
					switch((int)(op2)){
						case 0x00A9:
							
							break;
						case 0x00AA:
							op2 = math_stack.back();
							math_stack.pop_back();
							break;
					} 
					math_stack.push_back((double)(op1)/(double)(op2));
					i+=2;
					break;
					break;
				case 0x100E:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
					switch((int)(op1)){
						case 0x00A9:
							
							break;
						case 0x00AA:
							op1 = math_stack.back();
							math_stack.pop_back();
							break;
					} 
					math_stack.push_back((double)(op1)/(double)(op2));
					i+=2;
					break;
				case 0x100F:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					switch((int)(op1)){
						case 0x00A9:
							op2 = math_stack.back();
							math_stack.pop_back();
							op1 = math_stack.back();
							math_stack.pop_back();
							break;
						case 0x00AA:
							op1 = math_stack.back();
							math_stack.pop_back();
							break;
					} 
					math_stack.push_back((double)(op1)/(double)(op2));
					i+=2;
					break;
				case 0x3000:
					opcodes.at(opcodes.at(i+1)/sizeof(int)+2) = opcodes.at(opcodes.at(i+2)/sizeof(int)+2);
					break;
				case 0x3001:
					//cout<<dec<<"~~~~"<<math_stack.back()<<"~~~~~"<<endl;
					op1 =  opcodes.at(i+2);
					switch((int)(op1)){
						case 0x00AA:
							op1 = math_stack.back();
							math_stack.pop_back();
						break;
					}
					opcodes.at(opcodes.at(i+1)/sizeof(int)+2) = op1;
					break;
			}
		}
	return 0;
}