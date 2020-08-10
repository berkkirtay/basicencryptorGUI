#pragma once

#include "wx/wx.h"
#include "wxMain.h"
#include <wx/icon.h>
//frame_icon ICON "images/icon-win.ico"



class wxAppLaunch : public wxApp
{
private:
	wxMain* frame = nullptr;
public:
	wxAppLaunch();
	~wxAppLaunch();
public:
	virtual bool OnInit();
};

