#include "cMain.h"
#include <iostream>
#include <fstream> 
#include "testcases.h"

int global_problem = 1;
bool valid_sign_in = false;
int global_index_user = -1;

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(101, cMain::WhenSubmitButton)
	EVT_BUTTON(102, cMain::WhenSolutionButton)
	EVT_BUTTON(103, cMain::WhenNextProblemButton)
	EVT_BUTTON(104, cMain::WhenSaveButton)

	EVT_BUTTON(201, cMain::on_create_account)
	EVT_BUTTON(202, cMain::on_new_account)
	EVT_BUTTON(203, cMain::on_sign_in)

wxEND_EVENT_TABLE()



cMain::cMain() : wxFrame(nullptr, wxID_ANY, "James Collyer's C++ Coding Challenge", wxPoint(10, 10), wxSize(1000, 750))
{	
	SetBackgroundColour(*wxBLACK);
	// parent sizer
	sizer1 = new wxBoxSizer(wxVERTICAL);
	// childern
	sizer2 = new wxBoxSizer(wxHORIZONTAL);
	sizer3 = new wxBoxSizer(wxHORIZONTAL);
	sizer4 = new wxBoxSizer(wxHORIZONTAL);

	// Sign in display:
	sign = new wxTextCtrl(this, wxID_ANY, "Username:", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTRE);
	sizer3->Add(sign, 0);

	type_username = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
	sizer3->Add(type_username, 0);

	pass = new wxTextCtrl(this, wxID_ANY, "Password:", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTRE);
	sizer3->Add(pass, 0);

	type_password = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
	sizer3->Add(type_password, 0);

	output = new wxTextCtrl(this, wxID_ANY, "To create a new account please select New Account and then enter your desired details.", wxDefaultPosition, wxDefaultSize, wxTE_READONLY |wxTE_CENTRE);
	sizer3->Add(output, 3, wxEXPAND);

	sizer1->Add(sizer3, 0, wxCENTER | wxEXPAND);

	// Buttons:
	sizer1->Add(sizer2, 0, wxCENTER);

	sign_in_btn = new wxButton(this, 203, "Sing In", wxDefaultPosition, wxSize(280, 60));
	sizer2->Add(sign_in_btn, 0);

	new_account = new wxButton(this, 202, "New Account", wxDefaultPosition, wxSize(280, 60));
	sizer2->Add(new_account, 0);

	create_account = new wxButton(this, 201, "Create Account", wxDefaultPosition, wxSize(280, 60));
	sizer2->Add(create_account, 0);
	create_account->Enable(false);


	// Main application functionality:
	// Info at top center: 
	info1 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE | wxTE_CENTRE);
	wxFont font_info1(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL);
	info1->SetDefaultStyle(wxTextAttr(wxNullColour, wxNullColour, font_info1));
	info1->AppendText(  "C++ Coding Challenge: Complete the function as described below.\n"
						"Problem 1/2:\n"
						"Given 2 positive integer inputs, int num and int target,\n"
						"determine and return the least amount of steps necessary to go from num to target given the following rules:\n\n"
						"'current number' starts as num, but changes as you apply steps.\n"
						"1. You can add to current number by num\n"
						"2. You can multiply curent number by num\n");
	sizer1->Add(info1, 3, wxEXPAND);
	
	// Text box for user to write code:
	codespace = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_TAB);
	wxFont font_txt1(wxFontInfo(12));
	codespace->SetDefaultStyle(wxTextAttr(wxNullColour, wxNullColour, font_txt1));
	codespace->AppendText(	"#include <iostream>\n"
						"using namespace std;\n\n"
						"int usr_func(int num, int target){\n"
						"}\n"
						"Please log in before writing any code.");
	sizer1->Add(codespace, 5, wxEXPAND);

	// Submit button:
	SubmitButton = new wxButton(this, 101, "Submit Your Code", wxDefaultPosition, wxSize(200, 40));
	SubmitButton->Enable(false);
	sizer1->Add(SubmitButton, 0, wxCENTER);

	// List of results:
	results = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE | wxTE_CENTRE);
	sizer1->Add(results, 0, wxCENTER | wxEXPAND);

	// Show solution button:
	SolutionButton = new wxButton(this, 102, "Show Solution", wxDefaultPosition, wxDefaultSize);
	SolutionButton->Enable(false);
	sizer4->Add(SolutionButton, 0, wxCENTER);

	// Next question button, this will be disablet on init, and changed to enabled if all test cases are passed
	NextProblemButton = new wxButton(this, 103, "Next Problem", wxDefaultPosition, wxDefaultSize);
	NextProblemButton->Enable(false);
	sizer4->Add(NextProblemButton, 0, wxCENTER);

	SaveButton = new wxButton(this, 104, "Save Code", wxDefaultPosition, wxDefaultSize);
	SaveButton->Enable(false);
	sizer4->Add(SaveButton, 0, wxCENTER);

	sizer1->Add(sizer4, 0, wxCENTER);

	SetSizer(sizer1);

}




cMain::~cMain()
{

}




void cMain::WhenSubmitButton(wxCommandEvent &evt)
{	
// Testing of problem 1:
	if (global_problem == 1)
	{	
		int usr_output;

	  	// Test 1: compiling and command line interface component abstracted to function compile_return()
	  	// Overwriting file each time with user code and new variation of main (to ged rid of previous main), then call compile_run
	  	bool passed_all = true;
	  	test get_output_1;
	    test test1;
	    int expected_1 = test1.test_case_p1(2, 40);

	    std::ofstream MyFile1("user_program.cpp");
		MyFile1 << codespace->GetValue() + "\nint main(){\n 	int x = usr_func(2, 40);\n 	cout << x << endl;\n 	return 0;\n}//" << std::endl;
	    usr_output = get_output_1.compile_return();
	    //Error checking
	    if (usr_output > 100000 || usr_output < -100000)
	    	{
	    		results->Replace(0, 1000, "Error! Your code failed to compile.");
	    		SetBackgroundColour(*wxRED);
	    	}
	    	else
	    	{


			    // Replacing on test case 1, appending on others
			    if (expected_1 == usr_output)
			    	results->Replace(0, 1000, "Test Case 1: Passed!\n");
			    else
			    	{
			    		results->Replace(0, 1000,	"Test Case 1: Failed!\n");
			    		passed_all = false;
			    	}

			    // Test 2:
			    test get_output_2;
			    test test2;
			    int expected_2 = test2.test_case_p1(5, 5);
			   
			    std::ofstream MyFile2("user_program.cpp");
			    MyFile2 << codespace->GetValue() + "\nint main(){\n 	int x = usr_func(5, 5);\n 	cout << x << endl;\n 	return 0;\n}//" << std::endl;
			    usr_output = get_output_2.compile_return();

			    if (expected_2 == usr_output)
			    	results->AppendText("Test Case 2: Passed!\n");
			    else
			    	{
			    		results->AppendText("Test Case 2: Failed!\n");
			    		passed_all = false;
			    	}

			    // Test 3:
			    test get_output_3;
			    test test3;
			    int expected_3 = test3.test_case_p1(7, 56);
			   
			    std::ofstream MyFile3("user_program.cpp");
			    MyFile3 << codespace->GetValue() + "\nint main(){\n 	int x = usr_func(7, 56);\n 	cout << x << endl;\n 	return 0;\n}//" << std::endl;
			    usr_output = get_output_3.compile_return();

			    if (expected_3 == usr_output)
			    	results->AppendText("Test Case 3: Passed!\n");
			    else
			    	{
			    		results->AppendText("Test Case 3: Failed!\n");
			    		passed_all = false;
			    	}

			    if (passed_all)
			    {
			    	NextProblemButton->Enable(true);
			    	results->AppendText("All Test Cases Passed! Move On To Next Problem.");
			    	SetBackgroundColour(*wxGREEN);
			    }
			    else
			    {
					NextProblemButton->Enable(false);
					SetBackgroundColour(*wxYELLOW);
				}
			    
			}

	}

// Testing of problem 2:
	if  (global_problem == 2)
	{	
		int usr_output;
		test get_output_1;
	    test test1;
	  	bool passed_all = true;
	  	int arr1[6][4] = 	{{0,1,1,1},
							 {0,1,1,0},
						 	 {0,1,0,1},
						 	 {0,1,0,0},
							 {1,1,1,1},
							 {1,1,1,0}};

	    int expected_1 = test1.test_case_p2(arr1, 6);

	    std::ofstream MyFile1("user_program.cpp");
		MyFile1 << codespace->GetValue() + "\nint main(){\n\tint arr1[6][4] = {{0,1,1,1},{0,1,1,0},{0,1,0,1},{0,1,0,0},{1,1,1,1},{1,1,1,0}};\n\tint x = usr_func(arr1, 6);\n\tcout << x << endl;\n\treturn 0;\n}//" << std::endl;
	    usr_output = get_output_1.compile_return();
	    //Error checking
	    if (usr_output > 100000 || usr_output < -100000)
	    	{
	    		results->Replace(0, 1000, "Error! Your code failed to compile.");
	    		SetBackgroundColour(*wxRED);
	    	}
	    	else
	    	{


			    // Replacing on test case 1, appending on others
			    if (expected_1 == usr_output)
			    	results->Replace(0, 1000, "Test Case 1: Passed!\n");
			    else
			    	{
			    		results->Replace(0, 1000,	"Test Case 1: Failed!\n");
			    		passed_all = false;
			    	}
			    
			    // Test 2:
			    test get_output_2;
			    test test2;

			    int arr2[4][4] =   {{1,1,0,0},
							 		{0,1,1,0},
						 	 		{0,1,1,0},
						 	 		{0,1,1,0}};

			    int expected_2 = test2.test_case_p2(arr2, 4);
			
			    std::ofstream MyFile2("user_program.cpp");
			    MyFile1 << codespace->GetValue() + "\nint main(){\n\tint arr1[4][4] = {{1,1,0,0},{0,1,1,0},{0,1,1,0},{0,1,1,0}};\n\tint x = usr_func(arr1, 6);\n\tcout << x << endl;\n\treturn 0;\n}//" << std::endl;
			    usr_output = get_output_2.compile_return();

			    if (expected_2 == usr_output)
			    	results->AppendText("Test Case 2: Passed!\n");
			    else
			    	{
			    		results->AppendText("Test Case 2: Failed!\n");
			    		passed_all = false;
			    	}

			    // Test 3:
			    test get_output_3;
			    test test3;

			    int arr3[7][4] =   {{0,1,1,1},
							 		{0,1,0,0},
						 	 		{0,1,0,1},
						 	 		{1,0,0,1},
							 		{1,0,1,1},
							 		{1,0,1,0},
							 		{1,0,1,1}};

			    int expected_3 = test3.test_case_p2(arr3, 7);
			   
			    std::ofstream MyFile3("user_program.cpp");
			    MyFile1 << codespace->GetValue() + "\nint main(){\n\tint arr1[7][4] = {{0,1,1,1},{0,1,0,0},{0,1,0,1},{1,0,0,1},{1,0,1,1},{1,0,1,0},{1,0,1,1}};\n\tint x = usr_func(arr1, 6);\n\tcout << x << endl;\n\treturn 0;\n}//" << std::endl;
			    usr_output = get_output_3.compile_return();

			    if (expected_3 == usr_output)
			    	results->AppendText("Test Case 3: Passed!\n");
			    else
			    	{
			    		results->AppendText("Test Case 3: Failed!\n");
			    		passed_all = false;
			    	} 

			    if (passed_all)
			    {
			    	NextProblemButton->Enable(true);
			    	results->AppendText("All Test Cases Passed! Move On To Next Problem.");
			    	SetBackgroundColour(*wxGREEN);
			    }
			    else
			    {
					NextProblemButton->Enable(false);
					SetBackgroundColour(*wxYELLOW);
				}
			    
			}

	}
	

	// Remove data files
	std::system("rm user_exe result.txt user_program.cpp");

	evt.Skip();
}

void cMain::on_sign_in(wxCommandEvent &evt)
{
	std::string attempted_username(type_username->GetValue());
	std::string attempted_password(type_password->GetValue());
	std::string str;

	// 2d array -> number of users -> user name then password then code for respective problem
	std::ofstream MyFile11;
	MyFile11.open("collyerApp_user_sign.cpp");
	MyFile11 << "#include <iostream>\n"
				"#include <fstream>\n"
				"using namespace std;\n\n"
				"int main(){\n"
				"\tstring index_current_user = \"none\";\n"
				"\tstring user_info[100][10] = {" << std::endl;
	MyFile11.close();

	// import user details
	std::ifstream MyFile15("collyerApp_user_info.txt");
	if(MyFile15)
	{	
		MyFile11.open("collyerApp_user_sign.cpp", std::ios_base::app);
		while (getline(MyFile15, str))
		{
			MyFile11 << str << std::endl;
		}
		MyFile11.close();
	}

	MyFile11.open("collyerApp_user_sign.cpp", std::ios_base::app);
	MyFile11 << "};\n"
				"\tint idx = 0;\n"
				"\tstring usr = \"" + attempted_username + "\";"
				"\tstring pass = \"" + attempted_password + "\";\n"
				"\tbool valid = false;\n"
				"\tfor(int i = 0; i < 100; i++)\n"
				"\t{\n"
				"\t\tif((user_info[i][0] == usr) && (user_info[i][1] == pass) && (usr != \"\"))\n"
				"\t\t{\n"
				"\t\t\tvalid = true;\n"
				"\t\t\tindex_current_user = std::to_string(i);\n"
				"\t\t\tidx = i;\n"
				"\t\t}\n"
				"\t}\n"
				"\tif(valid)\n"
				"\t{\n"
				"\t\tcout << \"0\" << index_current_user << endl;\n"
				"\t\tstd::ofstream MyFile;\n"
				"\t\tMyFile.open(\"get_codespace.txt\");\n"
				"\t\tMyFile << user_info[idx][2] << endl;\n"
				"\t}\n"
				"\telse\n"
				"\t{\n"
				"\t\tcout << 1 << endl;\n"
				"\t}\n"
				"\treturn 0;\n"
				"}" << std::endl;

	std::system("g++ collyerApp_user_sign.cpp -o collyerApp_user_sign");
	std::system("./collyerApp_user_sign > result_sign.txt");

	int usr_output_log;
	std::string str_usr_output_log;
	std::string str_usr_output_log_0;
	std::ifstream result_sign("result_sign.txt");
	if (std::getline(result_sign, str_usr_output_log))
		{
			// for validating log in we consider first element
			str_usr_output_log_0 = str_usr_output_log[0];
			usr_output_log = std::stoi(str_usr_output_log_0);

		}
	if (usr_output_log == 0)
	{
		//log inn
		valid_sign_in = true;

		sign_in_btn->Enable(false);
		new_account->Enable(false);

		SolutionButton->Enable(true);
		SubmitButton->Enable(true);
		SaveButton->Enable(true);

		// after that the remaining int is an index for current user
		str_usr_output_log.erase(0,1);
		global_index_user = std::stoi(str_usr_output_log);

		output->Replace(0, 1000, "Welcome!");

		// display saved code
		std::string strstr;
		std::string to_codespace;
		std::ifstream MyFile909;
		MyFile909.open("get_codespace.txt");
		while (getline(MyFile909, strstr))
		{
			to_codespace = to_codespace + strstr;
		}
		if (to_codespace != "")
		{
			codespace->Replace(0, 1000, to_codespace);
		}

	}
	else if (usr_output_log == 1)
	{
		//wrong details
		output->Replace(0, 1000, "Wrong Details");
	}
	else
	{
		//error
		output->Replace(0, 1000, "error");
	}

	std::system("rm get_codespace.txt");
	std::system("rm result_sign.txt");
	std::system("rm collyerApp_user_sign.cpp collyerApp_user_sign");

	evt.Skip();
}

void cMain::on_new_account(wxCommandEvent &evt)
{
	sign_in_btn->Enable(false);
	new_account->Enable(false);
	create_account->Enable(true);
	output->Replace(0, 1000, "Please enter your desired details and then press Create Account");

	evt.Skip();
}

void cMain::on_create_account(wxCommandEvent &evt)
{
	sign_in_btn->Enable(true);
	new_account->Enable(true);
	create_account->Enable(false);

	std::string new_username(type_username->GetValue());
	std::string new_password(type_password->GetValue());

	// contains all user details in practical and importable fashion
	std::ofstream MyFile12;
	MyFile12.open("collyerApp_user_info.txt", std::ios_base::app);
	MyFile12 << "{\"" + new_username + "\", \"" + new_password + "\", \"\", \"\", \"\"}, " << std::endl;

	evt.Skip();
}

void cMain::WhenSaveButton(wxCommandEvent &evt)
{	
	std::string str;
	if (global_problem == 1)
	{
		std::ofstream MyFile11;
		MyFile11.open("collyerApp_user_save.cpp");
		MyFile11 << "#include <iostream>\n"
					"#include <fstream>\n"
					"using namespace std;\n\n"
					"int main(){\n"
					"string user_info[100][10] = {" << std::endl;
		MyFile11.close();

		// import user details
		std::ifstream MyFile15("collyerApp_user_info.txt");
		if(MyFile15)
		{	
			MyFile11.open("collyerApp_user_save.cpp", std::ios_base::app);
			while (getline(MyFile15, str))
			{
				MyFile11 << str << std::endl;
			}
			MyFile11.close();
		}

		// transfer codespace to file
		std::ofstream MyFile99;
		MyFile99.open("collyer_transfer.txt");
		MyFile99 << codespace->GetValue() << std::endl;
		MyFile99.close();

		// create script to read from file and save code
		std::string index = std::to_string(global_index_user);
		MyFile11.open("collyerApp_user_save.cpp", std::ios_base::app);
		MyFile11 << "};\n"
					"int index = " + index + ";\n"
					"std::string str;\n"
					"std::string to_save;\n" 
					"std::ifstream MyFile101(\"collyer_transfer.txt\");\n"
					"while (getline(MyFile101, str))\n"
					"{\n"
					"\tto_save = to_save + str;\n"
					"}\n"
					"user_info[index][2] = to_save;\n"
					"int arrSize = sizeof(user_info)/sizeof(user_info[0]);\n"
					"std::ofstream MyFile;\n"
					"MyFile.open(\"collyerApp_user_info.txt\");\n"
					"for(int i = 0; i < arrSize; i++)\n"
					"{\n"
					"\tif (user_info[i][0] == \"\")\n"
					"\t{\n"
					"\t\tbreak;\n"
					"\t}\n"
					"\tMyFile << \"{\\\"\" + user_info[i][0] + \"\\\", \" + \"\\\"\" + user_info[i][1] + \"\\\", \" + \"\\\"\" + user_info[i][2] + \"\\\", \" + \"\\\"\" + user_info[i][3] + \"\\\"\" + \"}, \" << std::endl;\n"
					"}\n"
					"}"
					<< std::endl;

	}
	else if (global_problem == 2)
	{

	}

	std::system("g++ collyerApp_user_save.cpp -o collyerApp_user_save");
	std::system("./collyerApp_user_save");
	std::system("rm collyerApp_user_save.cpp");
	std::system("rm collyerApp_user_save");
	std::system("rm collyer_transfer.txt");

}

void cMain::WhenSolutionButton(wxCommandEvent &evt)
{	
	if (global_problem == 1)
	{
		codespace->AppendText(	"\n\n\nExample Solution (Remove This Code Before Submitting Again):\n\n"
								"int usr_func(int num, int target){\n"
								"\tint count = 0;\n"
								"\tint current = num;\n"
								"\t// First we determine if its possible or not\n"
								"\tbool is_possible = false;\n"
								"\tif (target \% num == 0)\n"
								"\t\tis_possible = true;\n"
								"\tif (is_possible == false)\n"
								"\t\treturn -1;\n"
								"\t// Now we multiply as many times as possible\n"
								"\twhile (current * num < target)\n"
								"\t{\n"
								"\t\tcurrent *= num;\n"
								"\t\tcount += 1;\n"
								"\t}\n"
								"\t// Finally we add until we reach the target\n"
								"\twhile (current != target)\n"
								"\t{\n"
								"\t\tcurrent += num;\n"
								"\t\tcount += 1;\n"
								"\t}\n"
								"\treturn count;\n"
							"}");
	}
	else if (global_problem ==2)
	{
		codespace->AppendText(	"\n\n\nExample Solution (Remove This Code Before Submitting Again):\n\n"
								"int connected(int arr[][4], int height){\n"
								"\tint coordinates[height * 4][2];\n"
								"\tint count = 0;\n\n"
								"\t// check if a number is a 1 -> store its coordinates\n"
								"\tfor(int y = 0; y < height; y++)\n"
								"\t{\n"
								"\t\tfor(int x = 0; x < 4; x++)\n"
								"\t\t{\n"
								"\t\t\tif(arr[y][x] == 1)\n"
								"\t\t\t{\n"
								"\t\t\t\tcoordinates[count][0] = x;\n"
								"\t\t\t\tcoordinates[count][1] = y;\n"
								"\t\t\t\tcount ++;\n"
								"\t\t\t}\n"
								"\t\t}\n"
								"\t}\n\n"
								"\t// for each coordinate, compare agianst all coordinates in the array\n"
								"\tint nbrs;\n"
								"\tint current_x;\n"
								"\tint current_y;\n"
								"\tint current_length;\n"
								"\tint current_cor = 0;\n"
								"\tint comp_coords;\n\n"
								"\twhile(current_cor < count)\n"
								"\t{\n"
								"\t\tnbrs = 0;\n"
								"\t\tfor(comp_coords = 0; comp_coords < count; comp_coords++)\n"
								"\t\t{\n"
								"\t\t\tcurrent_x = coordinates[current_cor][0] - coordinates[comp_coords][0];\n"
								"\t\t\tcurrent_y = coordinates[current_cor][1] - coordinates[comp_coords][1];\n"
								"\t\t\tcurrent_length = (current_x * current_x) + (current_y * current_y);\n\n"
								"\t\t\tif(current_length == 1)\n"
								"\t\t\t{\n"
								"\t\t\t\tnbrs ++;\n"
								"\t\t\t}\n"
								"\t\t}\n"
								"\t\t// removing all 1s that are not strongly connected\n"
								"\t\tif(nbrs == 0 || nbrs == 1)\n"
								"\t\t{\n"
								"\t\t\tfor(int start = current_cor; start < count; start++)\n"
								"\t\t\t{\n"
								"\t\t\t\tcoordinates[start][0] = coordinates[start + 1][0];\n"
								"\t\t\t\tcoordinates[start][1] = coordinates[start + 1][1];\n"
								"\t\t\t}\n"
								"\t\t\tcount --;\n"
								"\t\t\tcurrent_cor = 0;\n"
								"\t\t\tcomp_coords = 0;\n"
								"\t\t}\n"
								"\t\telse\n"
								"\t\t\tcurrent_cor ++;\n"
								"\t}\n\n"							
								"\treturn count;\n"
								"\t// now we have an array of coordinates only containing the strongly connected componens\n"
								"\t// count is now a variable for the length of that array\n"
								"}");
		
	}

	evt.Skip();
}



void cMain::WhenNextProblemButton(wxCommandEvent &evt)
{
	NextProblemButton->Enable(false);
	SetBackgroundColour(*wxBLACK);
	global_problem += 1;

	if(global_problem == 2)
	{
		info1->Replace(0, 10000, 	"Problem 2/2:\n"
									"Given a matrix (2d array) of width 4 containing 1s and 0s:\n"
									"Return the number of 1s that are part of a strongly connected system.\n"
									"This can be imagined as 'Dead ends' not counting.\n\n"
									"Example:\n"
									"0,0,0,1\n" 
									"1,1,1,1\n"
									"1,1,0,0\n"
									"Returns 4 (ignores the 3 1s that form a dead end path)\n\n"
									"0,0,0,0\n"
									"1,1,1,1\n"
									"0,0,0,0\n"
									"1,1,1,1\n"
									"Returns 0 (all are dead end paths)");

		codespace->Replace(0, 10000,	"#include <iostream>\n"
										"using namespace std;\n\n"
										"int usr_func(int arr[][4], int height){\n"
										"}");
	}

	if(global_problem == 3)
	{
		info1->Replace(0, 10000, "No more problems for now.");
	}

	results->Replace(0, 1000, "");

	evt.Skip();
}

