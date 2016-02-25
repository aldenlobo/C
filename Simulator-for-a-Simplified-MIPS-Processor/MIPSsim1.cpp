/*
“I have neither given nor received any unauthorized aid on this assignment”.

Name: Alden Lobo
UFID: 85771004 

*/



#include <iostream>
#include <string>
#include <fstream>		//Used while working with files.
#include <sstream>

using namespace std;

	struct instructions
	{
		string opcode;
		string destination;
		string operand_1;
		string operand_2;
		
		void printme()
		{
			cout << "Opcode " << opcode << '\t';
			cout << "Destination " << destination << '\t';
			cout << "Operand_1 " << operand_1 << '\t';
			cout << "Operand_2 " << operand_2 << endl;
		}
	} names[18];
	
	struct registers
	{
		string reg_name;
		int reg_value;
		
		void printme()
		{
			cout << "reg_name " << reg_name << '\t';
			cout << "reg_value " << reg_value << endl;
			
		}
	} reg_names[20];
	
	struct data
	{
		string data_add;
		int data_value;
		
		void printme()
		{
			cout << "data_add " << data_add << '\t';
			cout << "data_value " << data_value << endl;
			
		}
	} data_names[20];
	
	
	struct inst_buffer
	{
		string opcode;
		string destination;
		int operand_1;
		int operand_2;
		
		void printme()
		{
			cout << "Printing the values from inst_buffer" << endl;
			cout << "Opcode " << opcode << '\t';
			cout << "Destination " << destination << '\t';
			cout << "Operand_1 " << operand_1 << '\t';
			cout << "Operand_2 " << operand_2 << endl;
		}
	} inst_buffer[20];
	
	
	struct AIB
	{
		string opcode;
		string destination;
		int operand_1;
		int operand_2;
		
		void printme()
		{
			cout << "Printing the values from inst_buffer" << endl;
			cout << "Opcode " << opcode << '\t';
			cout << "Destination " << destination << '\t';
			cout << "Operand_1 " << operand_1 << '\t';
			cout << "Operand_2 " << operand_2 << endl;
		}
	} AIB[20];
	
	struct SIB
	{
		string opcode;
		string destination;
		int operand_1;
		int operand_2;
		
		void printme()
		{
			cout << "Printing the values from inst_buffer" << endl;
			cout << "Opcode " << opcode << '\t';
			cout << "Destination " << destination << '\t';
			cout << "Operand_1 " << operand_1 << '\t';
			cout << "Operand_2 " << operand_2 << endl;
		}
	} SIB[20];
	
	struct REB
	{
		string reg_name;
		int reg_value;
		
		void printme()
		{
			cout << "reg_name " << reg_name << '\t';
			cout << "reg_value " << reg_value << endl;
		}
	} REB[20];
	
	struct PRB
	{
		string opcode;
		string destination;
		int operand_1;
		int operand_2;
		
		void printme()
		{
			cout << "Printing the values from inst_buffer" << endl;
			cout << "Opcode " << opcode << '\t';
			cout << "Destination " << destination << '\t';
			cout << "Operand_1 " << operand_1 << '\t';
			cout << "Operand_2 " << operand_2 << endl;
		}
	} PRB[20];
	
	struct ADB
	{
		string reg_name;
		int address;
		
		void printme()
		{
			cout << "reg_name " << reg_name << '\t';
			cout << "address " << address << endl;
		}
	} ADB[20];
	
	
	/*-----------------------------------------------------------------------------------
	-------------------------------------------------------------------------------------
	Prototyping all the functions!!.*/
	
	int decode();
	
	int issue_1();
	
	int ASU();
	
	int MUL_1();
	
	int MUL_2();
	
	int write();
	
	int issue_2();
	
	int ADDR();
	
	int store();
	
	int display();
	
	static int step = 0;
	
	int no_REB_values = 0;
	
	int no_of_instructions = 0;
	
	int no_of_registers = 0;
	
	ofstream output;
	
	int no_of_data = 0;
	
	int no_of_inst_to_del = 0;
	
	
int main()
{
	ifstream instructions ("instructions.txt");		//ifstream reads data from a file.
	
	string opcode;
	string delimiter = ",";
	string del = "<";
	string token; 
	size_t pos = 0;
	size_t pos1 = 0;
	
	int a = 0;

	while(getline(instructions, opcode))
	
	{
		int i = 0;	
		while ((pos = opcode.find(delimiter)) != string::npos) 
			{
			    token = opcode.substr(0, pos);
			    if(pos1 = token.find(del) != string::npos)
			    {
			    	token.erase(token.begin());
				}

				if (i == 0)
			    {
			    	names[a].opcode = token;
				}
				else if (i == 1)
				{
					names[a].destination = token;
				}
				else if (i == 2)
				{
					names[a].operand_1 = token;
				}
			    opcode.erase(0, pos + delimiter.length());
			    i += 1;
			}

		opcode = opcode.substr(0, opcode.size()-1);
		names[a].operand_2 = opcode;
		a += 1;
		no_of_instructions += 1;		//Gives the total number of instructions in the input file. 
	}
	
	/*--------------------------------------------------
	------------------------------------------------------
	-----------------------------------------------------
	The inputting of registers starts here. */
	
	
	ifstream registers ("registers.txt");		//ifstream reads data from a file.
	
	string reg;
	string reg_token;
	a = 0;
	
	while(getline(registers, reg))
	{
	// Loop to get the individual parametes of the 1st instruction.
		
		int i = 0;		
		while ((pos = reg.find(delimiter)) != string::npos) 
			{
			    reg_token = reg.substr(0, pos);
			    if(pos1 = reg_token.find(del) != string::npos)
			    {
			    	reg_token.erase(reg_token.begin());
				}
			    {
			    	reg_names[a].reg_name = reg_token;
				}
			    reg.erase(0, pos + delimiter.length());
				reg = reg.substr(0, reg.size()-1);
				{
					istringstream (reg) >> reg_names[a].reg_value; 	//Changed the string to an int as the reg_value is an int.
				}
			}
		a += 1;
		no_of_registers += 1;
	}

	/*--------------------------------------------------
	------------------------------------------------------
	-----------------------------------------------------
	Setting up the Data Memory. */
	
	ifstream data_memory ("datamemory.txt");		//ifstream reads data from a file.
	
	string mem_add;
	string data_token;
	a = 0;
	no_of_data = 0;
	
	while(getline(data_memory, mem_add))
	{
	// Loop to get the individual parametes of the 1st instruction.
		int i = 0;		
		while ((pos = mem_add.find(delimiter)) != string::npos) 
			{
			    data_token = mem_add.substr(0, pos);
			    if(pos1 = data_token.find(del) != string::npos)
			    {
			    	data_token.erase(data_token.begin());
				}
			    {
			    	data_names[a].data_add = data_token;
				}
			    mem_add.erase(0, pos + delimiter.length());
				mem_add = mem_add.substr(0, mem_add.size()-1);
				{
					istringstream (mem_add) >> data_names[a].data_value; 	//Changed the string to an int as the reg_value is an int.
				}
			}
		a += 1;
		no_of_data += 1;
	}
		
	/*--------------------------------------------------
	------------------------------------------------------
	-----------------------------------------------------
	The list of all the functions in proper order. */
	
	
	output.open ("simulation.txt");
	
	while (names[0].opcode != "" || inst_buffer[0].opcode != "" || AIB[0].opcode != "" || SIB[0].opcode != "" || REB[0].reg_name != "" || PRB[0].opcode != "" || ADB[0].reg_name != "")
	{
		display();
		
		write();
		
		store();
		
		ADDR();
		
		MUL_2();
		
		MUL_1();
		
		issue_2();
		
		ASU();
		
		issue_1();
		
		decode();
		
		step += 1;	
	}
	
	display();
		
	output.close();
	instructions.close();
	registers.close();
	data_memory.close();
	return 0;
}


		int decode () 		 
		{
			if(no_of_instructions == 0)
				return 0;

			for (int j = 0; j < no_of_registers; j++)
			{
				if(names[0].operand_1 == reg_names[j].reg_name)
				{
					inst_buffer[0].operand_1 = reg_names[j].reg_value;
				}
				if (names[0].operand_2 == reg_names[j].reg_name)
				{
					inst_buffer[0].operand_2 = reg_names[j].reg_value;
				}
			}
			
			if (names[0].opcode == "ST")
			{
				istringstream(names[0].operand_2) >> inst_buffer[0].operand_2;
			}
			inst_buffer[0].opcode = names[0].opcode;
			inst_buffer[0].destination = names[0].destination;

			for(int i = 0 ; i < no_of_instructions ; i++)
			{
				names[i] = names[i+1];
			}
				
			no_of_instructions--;		
		}
		
		int issue_1 ()
		{
			if (inst_buffer[0].opcode != "ST")
			{
				AIB[0].opcode = inst_buffer[0].opcode;
				AIB[0].destination = inst_buffer[0].destination;
				AIB[0].operand_1 = inst_buffer[0].operand_1;
				AIB[0].operand_2 = inst_buffer[0].operand_2;
				
				inst_buffer[0].opcode = "";
				inst_buffer[0].destination = "";
				inst_buffer[0].operand_1 = 0;
				inst_buffer[0].operand_2 = 0;
			}
		}
		
		int ASU ()
		{
			if (AIB[0].opcode == "ADD" || AIB[0].opcode == "SUB")
			{
				REB[no_REB_values].reg_name = AIB[0].destination;
				if (AIB[0].opcode == "ADD")
				{	
					REB[no_REB_values].reg_value = (AIB[0].operand_1 + AIB[0].operand_2);
				}
				else 
					REB[no_REB_values].reg_value = (AIB[0].operand_1 - AIB[0].operand_2);
				
				AIB[0].opcode = "";
				AIB[0].destination = "";
				AIB[0].operand_1 = 0;
				AIB[0].operand_2 = 0;
				
				no_REB_values += 1;
			}
		}
		
		int MUL_1 ()
		{
			if (AIB[0].opcode == "MUL")
			{
				PRB[0].opcode  = AIB[0].opcode;
				PRB[0].destination = AIB[0].destination;
				PRB[0].operand_1 = AIB[0].operand_1;
				PRB[0].operand_2 = AIB[0].operand_2;
				
				AIB[0].opcode = "";
				AIB[0].destination = "";
				AIB[0].operand_1 = 0;
				AIB[0].operand_2 = 0;
			}
		}
		
		int MUL_2 ()
		{
			if (PRB[0].opcode == "MUL")
			{
				REB[no_REB_values].reg_name = PRB[0].destination;
				REB[no_REB_values].reg_value = (PRB[0].operand_1 * PRB[0].operand_2);
				
				PRB[0].opcode = "";
				PRB[0].destination = "";
				PRB[0].operand_1 = 0;
				PRB[0].operand_2 = 0;
				
				no_REB_values += 1;
			}
		}
		
		int write ()
		{
			if (REB[0].reg_name == "")
				return 0;
				
			int found = 0;
			
			for (int i = 0; i < no_of_registers; i++)
			{
				if(REB[0].reg_name == reg_names[i].reg_name)
				{
					reg_names[i].reg_value = REB[0].reg_value;
					found = 1;
					break;
				}
			}	
			
			string temp;
			int temp2;
			string temp3;
			int temp4;
			int inserted = 0;
			if (found == 0)
			{	
				temp = REB[0].reg_name.substr(1, REB[0].reg_name.size());
				istringstream (temp) >> temp2;
				
				for (int i = 0; i < no_of_registers; i++)
				{
					temp3 = reg_names[i].reg_name.substr(1, reg_names[i].reg_name.size());
					istringstream (temp3) >> temp4;
					
					if(temp4 > temp2)
					{
						for (int j = no_of_registers; j > i; j--)
						{
							reg_names[j] = reg_names[j-1];
						}
						reg_names[i].reg_name = REB[0].reg_name;
						reg_names[i].reg_value = REB[0].reg_value;
						inserted = 1;
						break;
					} 
		
				}
				if (inserted == 0)
				{
					reg_names[no_of_registers].reg_name = REB[0].reg_name;
					reg_names[no_of_registers].reg_value = REB[0].reg_value;
				}
				no_of_registers += 1; 
			}
			
			REB[no_REB_values].reg_name = "";
			REB[no_REB_values].reg_value = 0;
			
			for (int i = 0; i < no_REB_values; i++)
			{
				REB[i] = REB[i+1];
			}
			no_REB_values -= 1;	
		}
		
		int issue_2 ()
		{
			if (inst_buffer[0].opcode == "ST")
			{
				SIB[0].opcode = inst_buffer[0].opcode;
				SIB[0].destination = inst_buffer[0].destination;
				SIB[0].operand_1 = inst_buffer[0].operand_1;
				SIB[0].operand_2 = inst_buffer[0].operand_2;
				
				inst_buffer[0].opcode = "";
				inst_buffer[0].destination = "";
				inst_buffer[0].operand_1 = 0;
				inst_buffer[0].operand_2 = 0;
			}
		}	
		
		int ADDR ()
		{
			ADB[0].reg_name = SIB[0].destination;
			ADB[0].address = (SIB[0].operand_1 + SIB[0].operand_2);
			
			SIB[0].opcode = "";
			SIB[0].destination = "";
			SIB[0].operand_1 = 0;
			SIB[0].operand_2 = 0;
		}
		
		int store ()
		{
			int reg_temp = 0;
			if (ADB[0].reg_name != "")
			{
				for(int i = 0; i < no_of_registers; i++)
				{
					if (ADB[0].reg_name == reg_names[i].reg_name)
					{
						reg_temp = reg_names[i].reg_value;
					}
				}

				string temp_s2;
				ostringstream convert_1;   // stream used for the conversion
				convert_1 << ADB[0].address;
				temp_s2 = convert_1.str();
	
				int found = 0;
				for(int i = 0; i < no_of_data; i++)
				{
					if (temp_s2 == data_names[i].data_add)
					{
						data_names[i].data_value = reg_temp;
						found = 1;
					}
				}
				
				string temp;
				int temp2;
				string temp3;
				int temp4;
				int inserted = 0;
				if (found == 0)
				{
					for (int i = 0; i < no_of_data; i++)
					{
						istringstream (data_names[i].data_add) >> temp4;
						
						if(ADB[0].address < temp4)
						{
							for (int j = no_of_data; j > i; j--)
							{
								data_names[j] = data_names[j-1];
							}
							data_names[i].data_add = temp_s2;
							data_names[i].data_value = reg_temp;
							inserted = 1;
							break;
						} 
					}
					if (inserted == 0)
					{
						data_names[no_of_data].data_add = temp_s2;
						data_names[no_of_data].data_value = reg_temp;
					}
					no_of_data += 1; 
				}
			
				ADB[0].reg_name = "";
				ADB[0].address = 0;
			}
		}
		
		int display()
		{
			int c = 0;
					  	
		    output << "STEP " << step << ": " << endl;
		    output << "INM:";
		    if (names[0].opcode != "")
			{
				for (;c < (no_of_instructions-1); c++)
				{
				output << "<" << names[c].opcode << "," << names[c].destination << "," << names[c].operand_1 << "," << names[c].operand_2 << ">,";
				}
				output << "<" << names[c].opcode << "," << names[c].destination << "," << names[c].operand_1 << "," << names[c].operand_2 << ">" << endl;
			}
			else
				output << endl;
			output << "INB:" ;
			if (inst_buffer[0].opcode != "")
			{
				output << "<" << inst_buffer[0].opcode << "," << inst_buffer[0].destination << "," << inst_buffer[0].operand_1 << "," << inst_buffer[0].operand_2 << ">" << endl;
			}
			else
				output << endl;
			output << "AIB:";
			if (AIB[0].opcode != "")
			{
				output << "<" << AIB[0].opcode << "," << AIB[0].destination << "," << AIB[0].operand_1 << "," << AIB[0].operand_2 << ">" << endl;
			}
			else
				output << endl;
			output << "SIB:"; 
			if (SIB[0].opcode != "")
			{
				output << "<" << SIB[0].opcode << "," << SIB[0].destination << "," << SIB[0].operand_1 << "," << SIB[0].operand_2 << ">" << endl;
			}
			else
				output << endl;
			output << "PRB:";
			if (PRB[0].opcode != "")
			{
				output << "<" << PRB[0].opcode << "," << PRB[0].destination << "," << PRB[0].operand_1 << "," << PRB[0].operand_2 << ">" << endl;
			}
			else
				output << endl;
			output << "ADB:";	
			if (ADB[0].reg_name != "")
			{
				output << "<" << ADB[0].reg_name << "," << ADB[0].address << ">" << endl;
			}
			else
				output << endl;
			output << "REB:";	
			c = 0;
			if (REB[0].reg_name != "")
			{
				for (;c < (no_REB_values-1); c++)
				{
					output << "<" << REB[c].reg_name << "," << REB[c].reg_value << ">,"; 
				}
				output << "<" << REB[c].reg_name << "," << REB[c].reg_value << ">" << endl;
			}
			else
				output << endl;
			output << "RGF:";	
			c = 0;
			if (reg_names[c].reg_name != "")
			{
				for (;c < (no_of_registers-1); c++)
				{
				output << "<" << reg_names[c].reg_name << "," << reg_names[c].reg_value << ">,";
				}
				output << "<" << reg_names[c].reg_name << "," << reg_names[c].reg_value << ">" << endl;
			}
			else
				output << endl;
			output << "DAM:";
			c = 0;
			if (data_names[c].data_add != "")
			{
				for (;c < (no_of_data-1); c++)
				{
				output << "<" << data_names[c].data_add << "," << data_names[c].data_value << ">,";
				}
				output << "<" << data_names[c].data_add << "," << data_names[c].data_value << ">" << endl;
			}
			else
				output << endl;
			
			output << endl;
		}
		
		
