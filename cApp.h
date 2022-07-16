#include "wx/wx.h"
#include "cMain.h"

class cApp : public wxApp
{
	public:
		cApp();
		~cApp();

	public:
		cMain* frame1 = nullptr;

	public:
		virtual bool OnInit();
};