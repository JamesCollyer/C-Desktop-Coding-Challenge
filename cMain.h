#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	// main application components:
	wxButton *SubmitButton = nullptr;
	wxButton *SolutionButton = nullptr;
	wxButton *NextProblemButton = nullptr;
	wxButton *SaveButton = nullptr;

	wxTextCtrl *codespace = nullptr;
	wxTextCtrl *info1 = nullptr;
	wxTextCtrl *results = nullptr;

	wxBoxSizer *sizer1 = nullptr;
	wxBoxSizer *sizer2 = nullptr;
	wxBoxSizer *sizer3 = nullptr;
	wxBoxSizer *sizer4 = nullptr;
	
	void WhenNextProblemButton(wxCommandEvent &evt);
	void WhenSubmitButton(wxCommandEvent &evt);
	void WhenSolutionButton(wxCommandEvent &evt);
	void WhenSaveButton(wxCommandEvent &evt);

	// log in components:
	wxButton *new_account = nullptr;
	wxButton *sign_in_btn = nullptr;
	wxButton *create_account = nullptr;

	wxTextCtrl *sign = nullptr;
	wxTextCtrl *type_username = nullptr;
	wxTextCtrl *pass = nullptr;
	wxTextCtrl *type_password = nullptr;
	wxTextCtrl *output = nullptr;

	void on_sign_in(wxCommandEvent &evt);
	void on_new_account(wxCommandEvent &evt);
	void on_create_account(wxCommandEvent &evt);


    

	wxDECLARE_EVENT_TABLE();

};