--
-- Haaf's Game Engine 1.7
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeStringTable helper class header
--

bindhgeStrings = {
	classes = {
		{
			name = "hge.NamedString",
			className = "NamedString",
			properties = {
-- 				'char name[MAXSTRNAMELENGTH]',
-- 				'char* string',
				'NamedString *next',
			}
		},
		{
			name = "hge.StringTable",
			className = "hgeStringTable",
			ctors = {
				'(const char *filename)',
			},
			memberFunctions = {
				{ rename = 'getstring', 'const char* GetString(const char* name);' },
			},
		}
	},
	modules = {
	}
}

--[[

#define MAXSTRNAMELENGTH 64

struct NamedString
{
	char name[MAXSTRNAMELENGTH];
	char *string;
	NamedString *next;
};

/*
** HGE String table class
*/
class hgeStringTable
{
public:
	hgeStringTable(const char *filename);

	char *GetString(const char *name);
};

--]]