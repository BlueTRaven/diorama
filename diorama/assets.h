#pragma once
#include <map>
#include <vector>

static const int ASSET_ERR			  = -1;
static const int ASSET_MATERIAL		   = 0;
static const int ASSET_SOUND		   = 1;
static const int ASSET_FONT			   = 2;
static const int ASSET_SHADER_VERTEX   = 3;
static const int ASSET_SHADER_FRAGMENT = 4;

static const int ASSET_PROPERTY_ERR	  = -1;
static const int ASSET_PROPERTY_STRING = 0;
static const int ASSET_PROPERTY_INT	   = 1;
static const int ASSET_PROPERTY_FLOAT  = 2;
static const int ASSET_PROPERTY_BOOL   = 3;

struct assetproperty
{
	int type;

	std::string name;
	std::string prop;
};

struct Asset
{
	int type;

	std::string name;
	std::map<std::string, assetproperty*> properties;
};

void load_all_assets(const char * source);

bool line_start_defines_comment(std::string line);

bool line_start_defines_asset(std::string line);

void set_asset_values(Asset &asset, std::string line);

void set_asset_properties(Asset &asset, std::string line);

int asset_name_to_type(std::string token);

std::string asset_type_to_name(int type);

int asset_property_to_type(std::string token);