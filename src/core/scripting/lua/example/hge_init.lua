-- Just the basic hge initialization
HGE = hge.HGE
lhge = HGE.create(0x181) -- hard coded for now, it should be based off the define HGE_VERSION

if lhge then
	-- Setup log file and window title
	lhge:system_set_string_state(HGE.HGE_LOGFILE, 'lua_scripting_example.log')
	lhge:system_set_string_state(HGE.HGE_TITLE, 'HGE Scripting Example (like tutorial 2)');

	-- Setup video mode
	lhge:system_set_bool_state(HGE.HGE_WINDOWED, true);
	lhge:system_set_bool_state(HGE.HGE_USESOUND, true);
	lhge:system_set_int_state(HGE.HGE_SCREENWIDTH, 800);
	lhge:system_set_int_state(HGE.HGE_SCREENHEIGHT, 600);
	lhge:system_set_int_state(HGE.HGE_SCREENBPP, 32);
else
	print("Unable to initialize HGE")
end
