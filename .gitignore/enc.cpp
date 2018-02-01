
#include "fourway.h"
#include "hnode.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <ctime>
#include <stack>
#include <string>
#include <queue>

void freqmapping(
	std::ifstream &infile,
	std::unordered_map<int,unsigned int> &freq_map){

	int n;
	while(infile >> n){
		auto it_f=freq_map.find(n);
		if(it_f!=freq_map.end()){
			it_f->second++;
		} else {
			freq_map[n]=1;
		}
	}
}

void hnodecreate(
	std::unordered_map<int,unsigned int> const &freq_map,
	std::vector<hnode const*> &hnode_vec){

	for(auto it:freq_map){
		hnode* huff_node=new hnode(it.first,it.second,NULL,NULL);
		hnode_vec.push_back(huff_node);
	}
}

hnode const* treecreatefourway(
		std::unordered_map<int,unsigned int> const &freq_map){

	std::vector<hnode const*> hnode_vec;
	hnodecreate(freq_map,hnode_vec);

	fourway fourway_obj(hnode_vec);

	unsigned int freq;
	while (fourway_obj.size() > 4)
	{
		hnode const *left =fourway_obj.getmin();
		fourway_obj.delmin();
		hnode const *right = fourway_obj.getmin();
		fourway_obj.delmin();
		freq=left->freq + right->freq;
		hnode const* parent = new hnode(-1,freq, left, right );
		fourway_obj.instamodeheap(parent);
	}
	return fourway_obj.getmin();
}

/*hnode const* treecreatebinary(
		std::unordered_map<int,unsigned int> const &freq_map){

	std::vector<hnode const*> hnode_vec;
	hnodecreate(freq_map,hnode_vec);

	binary binary_obj(hnode_vec);

	binary_obj.displayheap();
	unsigned int freq;

	int count=0;
	while ((binary_obj.size() > 1))
	{	count++;
		hnode const *left =binary_obj.get_min();
		binary_obj.delete_min();
		hnode const *right = binary_obj.get_min();
		binary_obj.delete_min();

		freq=left->freq + right->freq;
		hnode const* parent = new hnode(-1,freq, left, right );
		binary_obj.ins(parent);
	}
	return binary_obj.get_min();
}*/


/*hnode const* treecreatepairing(
		std::unordered_map<int,unsigned int> const &freq_map){

	std::vector<hnode const*> hnode_vec;
	hnodecreate(freq_map,hnode_vec);

	pairing pairing_obj(hnode_vec);

	pairing_obj.displayheap();
	unsigned int freq;

	while ((pairing_obj.size() > 1))
	{
		hnode const *left =pairing_obj.find_Min();
		pairing_obj.delete_Min();
		hnode const *right = pairing_obj.find_Min();
		pairing_obj.delete_Min();

		freq=left->freq + right->freq;
		hnode const* parent = new hnode(-1,freq, left, right );
		pairing_obj.Ins(parent);
	}
	return pairing_obj.find_Min();
} */

void pr(hnode const *root,std::string str,std::unordered_map<int,std::string> &code_table_map)
{

    if (!root)
        return;

    if (root->data != -1){
    	code_table_map[root->data]=str;
    }

    pr(root->left, str + "0",code_table_map);
    pr(root->right, str + "1",code_table_map);
}


char set(char num, int i){
	return num|(1<<i);
}

void compress(std::string &value,std::vector<char> &result){

	char res=0;
	char str;
	for(long i=0;i<value.size();){
		res=0;
		for(int j=7;j>=0;j--){
			if(value[i]=='1')
				res=set(res,j);
			i++;
		}
		result.push_back(res);
	}
}

void bin(
		std::unordered_map<int,std::string> &code_table_map,
		char *filename,
		char const *out
		){

	std::ifstream infile (filename);
	std::ofstream onfile (out,std::ios::out | std::ios::binary);

	int n;
	std::string value;
	while(infile >> n){
		auto it_f=code_table_map.find(n);
		if(it_f!=code_table_map.end()){
			value+=it_f->second;

		} else {
			std::cout<<"Condition not possible : "<<(it_f->first)<<std::endl;
		}
	}
	std::cout<<"Limit"<<std::endl;
	std::vector<char> result;
	compress(value,result);
	std::cout<<"Size:"<<result.size()<<", String:"<<value.size()<<std::endl;
	char *res=&result[0];
	onfile.write(res,result.size());
	onfile.close();
	infile.close();

}
struct comp
{
    bool operator()(hnode* l, hnode* r)
    {
        return (l->freq > r->freq);
    }
};


int main(int argc, char *argv[]){

	if ( argc != 2 ){
		std::cout<<"Usage:./"<<argv[0]<<" <input_file_name>\n";
		return 0;
	}

	std::ifstream infile (argv[1]);
	if ( !infile.is_open() ){
	  std::cout<<"File cannot be opened\n";
	  return 0;
	}
	std::unordered_map<int,unsigned int> freq_map;


	freqmapping(infile,freq_map);

	infile.close();
	clock_t start_time;
	std::string of;
	std::cout<<"Fourway:"<<std::endl;
	start_time=clock();
	hnode const* rootf=treecreatefourway(freq_map);
	std::unordered_map<int,std::string> code_table_map2;
	pr(rootf,"",code_table_map2);
	of="encoded.bin";
	char const *o2=of.c_str();
	bin(code_table_map2,argv[1],o2);
	std::cout << "Fourway time:  " << (clock() - start_time)/10 << std::endl;

	std::cout<<"Table is being encoded"<<std::endl;
	std::string code_table_file_name="code_table.txt";
	std::ofstream onfile (code_table_file_name,std::ios::out);
	for(auto it:code_table_map2){
		onfile<<it.first<<" "<<it.second<<"\n";
	}

	onfile.close();
	return 0;
}


