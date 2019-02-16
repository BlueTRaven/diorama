#include "variables.h"
#include "strutils.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <assert.h>

using namespace std;

vector<Decl> load_variable_file(const char * source)
{	//check for : and ;. these separate the declaration from the parameters.
	//if :, then first token type, second token subtype, third token name.
	//if ;, assert declaring, first token name, second token parameter
	
	string line;

	ifstream file;

	string directory = "C:/Users/Taylor/Documents/Programming/C++/diorama/diorama/";	
	file.open((directory + source).c_str());

	Decl decl;
	vector<Decl> declarations;
	
	if (!file.is_open())
	{
		printf("File at %s could not be opened.\n", source);
		return declarations;
	}

	bool declaring = false;

	int line_index = 0;
	while (getline(file, line))
	{
		vector<string> tokens;
	
		get_tokens(tokens, line);
		
		if (tokens.size() == 0 || (tokens.size() > 0 && tokens[0].find('#') == 0))
		{
			line_index++;
			continue;
		}

		string end_token = get_end_token(tokens);

		if (end_token == "UNDEFINED")
		{
			printf("%i ERROR: Missing end of line token!\n", line_index);
			return declarations;
		}

		if (end_token == ":")
		{
			if (declaring)
			{
				printf("%i ERROR: began new declaraion before previous was ended. Are you missing a 'declend'?\n", line_index);
				return declarations;
			}

			declaring = true;

			decl = Decl();	//create a new Decl? may not do this actually, C++ is weird

			decl.type = tokens[0];
			decl.subtype = tokens[1];
			decl.name = tokens[2];	
		}
		else if (end_token == ";")
		{	//this is a Decl_Parameter if the last character is ;

			if (tokens[0] == "declend")
			{	//we're finished with the declaration.
				declarations.push_back(decl);
				declaring = false;
			}
			else 
			{
				Decl_Parameter parameter = Decl_Parameter();

				parameter.name = tokens[0];
				parameter.value = tokens[1];

				infer_param_type(parameter);

				decl.parameters.insert(std::pair<string, Decl_Parameter>(parameter.name, parameter));
			}
		}

		line_index++;
	}

	if (declaring)
	{
		printf("%i ERROR: End of file reached, but still declaring. Are you missing a 'declend'?\n", line_index);
		return declarations;
	}

	printf("Finished loading %zu declarations from file %s.\n", declarations.size(), source);

	return declarations;
}

void get_tokens(vector<string> & tokens, string line)
{
	int start = 0;

	bool ended_line_by_colon = false;

	for (int i = 0; i < line.size(); i++)
	{
		char c = line[i];
		if (c == ' ' && !ended_line_by_colon)
		{
			tokens.push_back(line.substr(start, i - start));
			start = i + 1;
		}
		else if (c == ':' || c == ';')
		{
			tokens.push_back(line.substr(start, i - start));
			tokens.push_back(line.substr(i, 1));
			start = i + 1;

			ended_line_by_colon = true;
		}
		else if (c == '#')
		{
			tokens.push_back(line.substr(i, line.size() - start));
			break;	//comments result in everything past becoming a part of the comment token. Therefore, we basically end the line.
		}
	}
}

string get_end_token(vector<string> &tokens)
{
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i] == ":" || tokens[i] == ";")
			return tokens[i];
	}
	//will only reach this line if we don't find the token anywhere.
	return "UNDEFINED";
}

void infer_param_type(Decl_Parameter &param)
{
	string line = param.value;

	vector<int> allquotes =	find_all_str(param.value, '\"');

	if (allquotes.size() == 2 && allquotes[0] == 0 && allquotes[1] == line.size() - 1)
		param.type = "string";
	else if (line.find_first_not_of("0123456789") == string::npos)
		param.type = "int";
	else if (line.find_first_not_of("0123456789.") == string::npos) 
		param.type = "float";
	else 
	{
		string lower = str_to_lower(line);
		if (lower == "true" || lower == "false")
			param.type = "bool";
		else param.type = "string";
	}
}

vector<Decl> get_all_decl_of_type(string type, vector<Decl> declarations)
{
	vector<Decl> output;

	for (int i = 0; i < declarations.size(); i++)
	{
		if (declarations[i].subtype == type)
			output.push_back(declarations[i]);
	}
	
	return output;
}

std::map<std::string, Decl> get_map_of_type(std::string type, std::vector<Decl> declarations)
{
	map<std::string, Decl> output;

	for (int i = 0; i < declarations.size(); i++)
	{
		if (declarations[i].subtype == type)
			output.insert(std::pair<std::string, Decl>(declarations[i].name, declarations[i]));
	}

	return output;
}






