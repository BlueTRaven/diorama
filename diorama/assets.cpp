#include "assets.h"
#include "strutils.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>

#include <assert.h>

using namespace std;

vector<Asset> assets;

void load_all_assets(const char * source)
{
	string line;
	ifstream file;

	int currentasset = -1;
	bool is_defining_asset = false;

	file.open(source);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line_start_defines_asset(line))
			{	//this line begins defining an asset.
				if (is_defining_asset)
				{
					printf("Can not begin defining an asset while already defining an asset. Are you missing a newline in between asset declarations?");
					continue;
				}
				
				is_defining_asset = true;

				currentasset++;
				Asset* asset = new Asset();
				set_asset_values(*asset, line);

				assets.push_back(*asset);
				
			}
			else if (line.empty())
			{
				if (is_defining_asset)
				{
					is_defining_asset = false;

					printf("Finished loading %s asset %s.\n", asset_type_to_name(assets[currentasset].type).c_str(), assets[currentasset].name.c_str());
				}
			}
			else 
			{	//continue asset declaration
				if (is_defining_asset)
					set_asset_properties(assets[currentasset], line);
			}
		}

		if (is_defining_asset)
		{
			is_defining_asset = false;

			printf("Finished loading %s asset %s.\n", asset_type_to_name(assets[currentasset].type).c_str(), assets[currentasset].name.c_str());
		}

		printf("Finished loading %zu assets.\n", assets.size());
	}
}

void set_asset_values(Asset &asset, string line)
{	//set the asset values (name, path)
	int token_index = 0;

	size_t pos = 0;
	string token;

	pos = line.find(" ");

	//we use this, because if we didn't, if there were extra lines past the :, say, for instance, there's a comment,
	//it would continue parsing. just a small optimization.
	bool is_last = false;

	while (true)
	{
		if (line.length() == 0 || pos == string::npos) break;

		if (token_index > 0)
		{	//skip the first token; it's always going to be the "asset" declaration
			token = line.substr(0, pos);

			if (token.find("#") != string::npos)
				break;	//the next tokens are going to be comments as well. we can skip them.

			if (token_index == 1)		//type
				asset.type = asset_name_to_type(token);
			else if (token_index == 2)	//name
				asset.name = token;	//len -1 to get rid of the :
		}

		if (is_last)
			break;

		line.erase(0, pos + string(" ").length());

		token_index++;

		pos = line.find(" ");

		if (pos == 0 || pos == string::npos)
		{
			pos = line.find(":");	//find end-of-line colon
			is_last = true;
		}
	}
}

void set_asset_properties(Asset& asset, string line)
{
	int token_index = 0;

	size_t pos = 0;
	string token;

	string key;

	pos = line.find(" ");

	//we use this, because if we didn't, if there were extra lines past the :, say, for instance, there's a comment,
	//it would continue parsing. just a small optimization.
	bool is_last = false;	

	while (true)
	{
		if (line.length() == 0 || pos == string::npos) break;

		token = line.substr(0, pos);

		if (token.find("#") != string::npos)
			break;	//the next tokens are going to be comments as well. we can skip them.

		if (token_index == 0)
		{
			asset.properties.insert(std::pair<string, assetproperty*>(token, new assetproperty()));
			key = token;
			asset.properties[key]->name = token;
		}
		else if (token_index == 1)
		{
			asset.properties[key]->prop = token;
			asset.properties[key]->type = asset_property_to_type(token);
		}

		if (is_last)
			break;

		line.erase(0, pos + string(" ").length());

		token_index++;

		pos = line.find(" ");

		if (pos == 0 || pos == string::npos)
		{
			pos = line.find(";");	//find end-of-line semi colon
			is_last = true;
		}
	}
}

bool line_start_defines_comment(string line)
{
	return line.rfind("#", 0);
}

bool line_start_defines_asset(string line)
{
	return line.rfind("asset", 0) == 0;
}

int asset_name_to_type(string token)
{
	if (token == "material")
		return ASSET_MATERIAL;
	else if (token == "sound")
		return ASSET_SOUND;
	else if (token == "bitfont")
		return ASSET_FONT;
	else if (token == "vertex_shader")
		return ASSET_SHADER_VERTEX;
	else if (token == "fragment_shader")
		return ASSET_SHADER_FRAGMENT;
	else return ASSET_ERR;
}

string asset_type_to_name(int type)
{
	if (type == ASSET_SOUND)
		return "sound";
	else if (type == ASSET_MATERIAL)
		return "material";
	else if (type == ASSET_FONT)
		return "font";
	else if (type == ASSET_SHADER_VERTEX)
		return "vertex shader";
	else if (type == ASSET_SHADER_FRAGMENT)
		return "fragment shader";
	else return "UNDEFINED";
}

int asset_property_to_type(string token)
{
	if (token.find_first_not_of("0123456789") == string::npos)
		return ASSET_PROPERTY_INT;
	else if (token.find_first_not_of("0123456789.") == string::npos)
		return ASSET_PROPERTY_FLOAT;
	else 
	{
		string lower = str_to_lower(token);
		if (lower == "true" || lower == "false")
			return ASSET_PROPERTY_BOOL;
		else return ASSET_PROPERTY_STRING;
	}
	return 0;
}
