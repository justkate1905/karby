#include <fstream>
#include <iostream>
#include <vector>
#include <boost/locale/encoding_utf.hpp>
#define size_opcode int
using boost::locale::conv::utf_to_utf;
using namespace std;
std::wstring utf8_to_wstring(const std::string& str)
	{
		return utf_to_utf<wchar_t>(str.c_str(), str.c_str() + str.size());
	}

std::string wstring_to_utf8(const std::wstring& str)
	{
	return utf_to_utf<char>(str.c_str(), str.c_str() + str.size());
	}
int main(int argc, char **argv)
{
		setlocale(0,"");
		FILE *file;
		char* name = " ";
		vector<double> opcodes, math_stack, func_params; 
		int buff[1];
		int size, addr_reg1, addr_reg2, symb_number, max, type, param_num, start_size, given_param, index;
		vector<int> call_stack;
		double op1, op2, vals;
		string utf;
		wstring wide_str;
		wchar_t ch;
		wstring::iterator beg, end;
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
			//cout<<hex<<opcodes.at(i)<<endl;
			}
		
		for(int i = opcodes.at(1)/sizeof(int); i<opcodes.size(); i++){
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
				case 0x00C8:
					type =  (int)(opcodes.at((int)(opcodes.at(i+1))/sizeof(int)));
					symb_number = (int)(opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+1));
					if(type==0x00AB){
						if(symb_number==1){
						cout<<opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2)<<endl;
						}
						else{
							for(int j =0; j<symb_number;j++){
							cout<<opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2+j)<<" ";	
							}
						}
					}
					else{
						max = symb_number/2 + symb_number%2;
						for(int j = 0; j<max; j++){
							ch = (short int)((int)(opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2+j))>>16);
							wide_str+=ch;
							//wcout<<hex<<(short int)(ch)<<endl;
							ch = (short int)((int)(opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2+j))&0xFFFF);
							//wcout<<hex<<(short int)(ch)<<endl;
							if(ch!=0x0000){
								wide_str+=ch;
								}
							}
						
						beg = wide_str.begin();
						end = wide_str.end();
						//while(beg!=end){
						wcout<<wide_str<<endl;
							//beg++;
						//}
						utf = wstring_to_utf8(wide_str);
						wide_str = L"";
						//cout<<utf<<endl;
					}
					i++;
					break;
				case 0x00C9:
					cout<<opcodes.at(i+1)<<endl;
					i++;
					break;
				case 0x00CA:
					symb_number = (int)(opcodes.at(i+1));
					max = symb_number/2 + symb_number%2;
					i+=2;
					for(int j = 0; j<max; j++){
						ch = (short int)((int)(opcodes.at(i+j))>>16);
						wide_str+=ch;
						ch = (short int)((int)(opcodes.at(i+j))&0xFFFF);
						if(!(max-j==1)){
							wide_str+=ch;						
							}
						}
					
					beg = wide_str.begin();
					end = wide_str.end();
					//while(beg!=end){
					wcout<<wide_str<<endl;
						//beg++;
					//}
					utf = wstring_to_utf8(wide_str);
					wide_str = L"";
					//cout<<utf<<endl;
					i+=max-1;
					//if(symb_number%2==1){
						//i++;
						//}
					
					break;
				case 0x01B0:
					i = call_stack.back() - 1;
					call_stack.pop_back();
					//cout<<"Hello "<<i<<endl;
					break;
				case 0x01B3:
					func_params.push_back(opcodes.at(i+1));
					i++;
					//cout<<"return value "<<func_params.back()<<endl;
					break;
				case 0x01B4:
					func_params.push_back(math_stack.back());
					i++;
					break;
				case 0x01B5:
					vals = (opcodes.at(i+1));
					if((((int)(vals))&0xFFFF0) == 0x188A0){
						//cout << "return "<<vals<<endl;
						given_param = vals - 0x188A0;
						index = param_num-given_param+1;
						//cout<<"return_params: "<<index<<endl;
						vals = func_params.at(func_params.size()-index);
					}
					else{
						vals = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
					}
					func_params.push_back(vals);
					i++;
					//cout<<"return value "<<func_params.back()<<endl;
					break;
				case 0x01B6:
					param_num = (int)(opcodes.at(i+1));
					//cout << "Hello "<<param_num <<endl;
					i+=2;
					for(int j =0; j<param_num*2; j+=2){
						switch((int)(opcodes.at(i+j))){
							case 0x01B1:
								func_params.push_back(opcodes.at(i+j+1));
								//cout<<"number param : "<<func_params.back()<<endl;
								break;
							case 0x01B2:
								vals = opcodes.at((int)(opcodes.at(i+j+1))/sizeof(int)+2);
								func_params.push_back(vals);
								//cout<<"var param : "<<func_params.back()<<endl;
								break;
						}
					}
					i+=param_num*2;
					//cout<< "function address "<< opcodes.at(i)<<endl;
					//cout<<"First command "<<std::hex<<(int)(opcodes.at(((int)(opcodes.at(i)))/sizeof(int)))<<endl;
					call_stack.push_back(i+1);
					//cout<<"Next command "<<std::hex<<(int)(opcodes.at(call_stack.back()))<<endl;
					start_size = func_params.size();
					i = ((int)(opcodes.at(i)))/sizeof(int) -1;
					break;
				//Операция сложения	
				case 0x1000:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					//cout<<"addr: "<<(((int)(op1))&0xFFFF0)<<" "<< (((int)(op2)) & 0xFFFF0 ) <<endl;
					if((((int)(op1))&0xFFFF0) == 0x188A0){
						given_param = ((int)(op1))-0x188A0;
						index = param_num-given_param+1;
						//cout<<"given_params: "<<index<<endl;
						op1 = func_params.at(func_params.size()-index);
						//cout<<"~ "<<op1<<endl;
						if((((int)(op2)) & 0xFFFF0) == 0x188A0){
							//cout<<"hello "<<op2<<endl;
							given_param = ((int)(op2)) - 0x188A0;
							index = param_num-given_param+1;
							//cout<<"index: "<<index<<endl;
							op2 = func_params.at(func_params.size()-index);
						}
						else{
							op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
							//cout<<"hello "<<op2<<endl;
						}
					}
					else{
						op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
						if(((int)(op2)) & 0xFFFF0 == 0x188A0){
							given_param = ((int)(op2))-0x188A0;
							index = param_num-given_param+1;
							op2 = func_params.at(func_params.size()-index);
						}
						else{
							op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
						}
						
					}
					
					math_stack.push_back(op1+op2);
					i+=2;
					break;
				case 0x1001:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					if((((int)(op1))&0xFFFF0) == 0x188A0){
						given_param = ((int)(op1))-0x188A0;
						index = param_num-given_param+1;
						//cout<<"given_params: "<<index<<endl;
						op1 = func_params.at(func_params.size()-index);
					}
					else{
						op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
					}
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
					op2 = opcodes.at(i+2);
					if((((int)(op2)) & 0xFFFF0) == 0x188A0){
							//cout<<"hello "<<op2<<endl;
							given_param = ((int)(op2)) - 0x188A0;
							index = param_num-given_param+1;
							//cout<<"index: "<<index<<endl;
							op2 = func_params.at(func_params.size()-index);
					}
					else{
						op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
					}
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
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					//cout<<"addr: "<<(((int)(op1))&0xFFFF0)<<" "<< (((int)(op2)) & 0xFFFF0 ) <<endl;
					if((((int)(op1))&0xFFFF0) == 0x188A0){
						given_param = ((int)(op1))-0x188A0;
						index = param_num-given_param+1;
						//cout<<"given_params: "<<index<<endl;
						op1 = func_params.at(func_params.size()-index);
						//cout<<"~ "<<op1<<endl;
						if((((int)(op2)) & 0xFFFF0) == 0x188A0){
							//cout<<"hello "<<op2<<endl;
							given_param = ((int)(op2)) - 0x188A0;
							index = param_num-given_param+1;
							//cout<<"index: "<<index<<endl;
							op2 = func_params.at(func_params.size()-index);
						}
						else{
							op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
							//cout<<"hello "<<op2<<endl;
						}
					}
					else{
						op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
						if(((int)(op2)) & 0xFFFF0 == 0x188A0){
							given_param = ((int)(op2))-0x188A0;
							index = param_num-given_param+1;
							op2 = func_params.at(func_params.size()-index);
						}
						else{
							op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
						}
						
					}
					math_stack.push_back(op1-op2);
					i+=2;
					break;
				case 0x1005:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					if((((int)(op1))&0xFFFF0) == 0x188A0){
						given_param = ((int)(op1))-0x188A0;
						index = param_num-given_param+1;
						//cout<<"given_params: "<<index<<endl;
						op1 = func_params.at(func_params.size()-index);
					}
					else{
						op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
					}
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
					op2 = opcodes.at(i+2);
					if((((int)(op2)) & 0xFFFF0) == 0x188A0){
							//cout<<"hello "<<op2<<endl;
							given_param = ((int)(op2)) - 0x188A0;
							index = param_num-given_param+1;
							//cout<<"index: "<<index<<endl;
							op2 = func_params.at(func_params.size()-index);
					}
					else{
						op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
					}
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
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					//cout<<"addr: "<<(((int)(op1))&0xFFFF0)<<" "<< (((int)(op2)) & 0xFFFF0 ) <<endl;
					if((((int)(op1))&0xFFFF0) == 0x188A0){
						given_param = ((int)(op1))-0x188A0;
						index = param_num-given_param+1;
						//cout<<"given_params: "<<index<<endl;
						op1 = func_params.at(func_params.size()-index);
						//cout<<"~ "<<op1<<endl;
						if((((int)(op2)) & 0xFFFF0) == 0x188A0){
							//cout<<"hello "<<op2<<endl;
							given_param = ((int)(op2)) - 0x188A0;
							index = param_num-given_param+1;
							//cout<<"index: "<<index<<endl;
							op2 = func_params.at(func_params.size()-index);
							//cout<<"hello "<<op2<<endl;
						}
						else{
							op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
							//cout<<"hello "<<op2<<endl;
						}
					}
					else{
						op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
						if(((int)(op2)) & 0xFFFF0 == 0x188A0){
							given_param = ((int)(op2))-0x188A0;
							index = param_num-given_param+1;
							op2 = func_params.at(func_params.size()-index);
						}
						else{
							op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
						}
						
					}
					math_stack.push_back(op1*op2);
					i+=2;
					break;
				case 0x1009:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					if((((int)(op1))&0xFFFF0) == 0x188A0){
						given_param = ((int)(op1))-0x188A0;
						//cout<<"given_params: "<<given_param<<endl;
						index = param_num-given_param+1;
						op1 = func_params.at(func_params.size()-index);
					}
					else{
						op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
					}
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
					op2 = opcodes.at(i+2);
					if((((int)(op2)) & 0xFFFF0) == 0x188A0){
							//cout<<"hello "<<op2<<endl;
							given_param = ((int)(op2)) - 0x188A0;
							index = param_num-given_param+1;
							//cout<<"index: "<<index<<endl;
							op2 = func_params.at(func_params.size()-index);
					}
					else{
						op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
					}
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
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					//cout<<"addr: "<<(((int)(op1))&0xFFFF0)<<" "<< (((int)(op2)) & 0xFFFF0 ) <<endl;
					if((((int)(op1))&0xFFFF0) == 0x188A0){
						given_param = ((int)(op1))-0x188A0;
						index = param_num-given_param+1;
						//cout<<"given_params: "<<index<<endl;
						op1 = func_params.at(func_params.size()-index);
						//cout<<"~ "<<op1<<endl;
						if((((int)(op2)) & 0xFFFF0) == 0x188A0){
							//cout<<"hello "<<op2<<endl;
							given_param = ((int)(op2)) - 0x188A0;
							index = param_num-given_param+1;
							//cout<<"index: "<<index<<endl;
							op2 = func_params.at(func_params.size()-index);
						}
						else{
							op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
							//cout<<"hello "<<op2<<endl;
						}
					}
					else{
						op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
						if(((int)(op2)) & 0xFFFF0 == 0x188A0){
							given_param = ((int)(op2))-0x188A0;
							index = param_num-given_param+1;
							op2 = func_params.at(func_params.size()-index);
						}
						else{
							op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
						}
						
					}
					math_stack.push_back((double)(op1)/(double)(op2));
					i+=2;
					break;
				case 0x100D:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					if((((int)(op1))&0xFFFF0) == 0x188A0){
						given_param = ((int)(op1))-0x188A0;
						index = param_num-given_param+1;
						//cout<<"given_params: "<<index<<endl;
						op1 = func_params.at(func_params.size()-index);
					}
					else{
						op1 = opcodes.at((int)(opcodes.at(i+1))/sizeof(int)+2);
					}
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
				case 0x100E:
					op1 = opcodes.at(i+1);
					op2 = opcodes.at(i+2);
					if((((int)(op2)) & 0xFFFF0) == 0x188A0){
							//cout<<"hello "<<op2<<endl;
							given_param = ((int)(op2)) - 0x188A0;
							index = param_num-given_param+1;
							//cout<<"index: "<<index<<endl;
							op2 = func_params.at(func_params.size()-index);
					}
					else{
						op2 = opcodes.at((int)(opcodes.at(i+2))/sizeof(int)+2);
					}
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
					op1 = opcodes.at(opcodes.at(i+2)/sizeof(int)+2);
					//cout<<"assoc  var "<<op1<<endl;
					opcodes.at(opcodes.at(i+1)/sizeof(int)+2) = opcodes.at(opcodes.at(i+2)/sizeof(int)+2);
					i+=2;
					break;
				case 0x3001:
					op1 =  opcodes.at(i+2);
					switch((int)(op1)){
						case 0x00AA:
							op1 = math_stack.back();
							//cout<<"assoc stack "<<op1<<endl;
							math_stack.pop_back();
						break;
						case 0x01B7:
							if(func_params.size()==start_size){
								cout<<"ERROR: this function doesn't have the return value."<<endl;
							}
							else{
								op1 = func_params.back();
								//scout<<"assoc "<<op1<<endl;
								func_params.pop_back();
							}
						break;
					}
					opcodes.at(opcodes.at(i+1)/sizeof(int)+2) = op1;
					i+=2;
					break;
				default:
					continue;
			}
		}
	return 0;
}