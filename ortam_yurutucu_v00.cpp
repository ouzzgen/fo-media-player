#include "ortam_yurutucu.h"
using namespace std;


BEGIN_EVENT_TABLE(TemelWx, wxFrame)
END_EVENT_TABLE()


TemelWx::TemelWx(const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 500))
{
	wxColour col1, col2;
	col1.Set(wxT("Red"));
	col2.Set(wxT("Blue"));
	menubar = new wxMenuBar;
	fileMenu = new wxMenu;
	editMenu = new wxMenu;
	historyMenu = new wxMenu;
	lastTabs = new wxMenu;
	toolsMenu = new wxMenu;
	helpMenu = new wxMenu;

	newTab = new wxMenuItem(fileMenu, ID_NEWTAB, wxT("New Tab\tCtrl+T"));
	openFile = new wxMenuItem(fileMenu, id_openFile, wxT("Open media file"));
	quit = new wxMenuItem(fileMenu, wxID_EXIT, wxT("&Quit"));

	fileMenu->Append(newTab);
	fileMenu->Append(quit);
	fileMenu->Append(openFile);
	editMenu->AppendCheckItem(id_editCheckItem, wxT("editCheckItem"), wxEmptyString);
	historyMenu->AppendSubMenu(lastTabs, wxT("Son Se&kmeler"));
	menubar->Append(fileMenu, wxT("&File"));
	menubar->Append(editMenu, wxT("&Edit"));
	menubar->Append(historyMenu, wxT("&Past"));
	menubar->Append(toolsMenu, wxT("Tools"));
	menubar->Append(helpMenu, wxT("&Help"));
	SetMenuBar(menubar);

	notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxNotebookNameStr);
	panel = new wxPanel(notebook);

	notebook->AddPage(panel, wxT("Page"), true, -1);

	//panel->SetBackgroundColour(col2);
	vbox = new wxBoxSizer(wxVERTICAL);
	toolbarhbox = new wxBoxSizer(wxHORIZONTAL);
	mediaControlsHBox = new wxBoxSizer(wxHORIZONTAL);

	tctrl = new wxTextCtrl(panel, id_textCtrl, wxT(""), wxPoint(-1, -1), wxSize(-1, -1));
	goButton = new wxButton(panel, ID_GO_BUTTON, wxT("Go"), wxPoint(-1, -1), wxSize(-1, -1));
	mediaCtrl = new wxMediaCtrl(panel, id_mediaCtrl, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxMEDIABACKEND_GSTREAMER, wxDefaultValidator, "mediaCtrl");
	playButton = new wxButton(panel, id_playButton, wxT("play"),
				  wxPoint(-1, -1), wxSize(-1, -1));
	pauseButton = new wxButton(panel, id_pauseButton, wxT("pause"),
				   wxPoint(-1, -1), wxSize(-1, -1));
	stopButton = new wxButton(panel, id_stopButton, wxT("stop"),
				  wxPoint(-1, -1), wxSize(-1, -1));
	//wxFileName fn("./hello-wx.html");
	//htmlWin->LoadFile(fn);
	//htmlWin->SetBackgroundColour(col1);
	//htmlWin->LoadPage("https://www.google.com");

	toolbarhbox->Add(tctrl, 1, wxEXPAND | wxALL, 20);
	toolbarhbox->Add(goButton, 1, wxEXPAND | wxALL, 20);

	mediaControlsHBox->Add(playButton, 1, wxEXPAND | wxALL, 20);
	mediaControlsHBox->Add(pauseButton, 1, wxEXPAND | wxALL, 20);
	mediaControlsHBox->Add(stopButton, 1, wxEXPAND | wxALL, 20);

	vbox->Add(toolbarhbox, 0, wxEXPAND | wxALL, 20);
	vbox->Add(mediaCtrl, 1, wxEXPAND | wxALL, 20);
	vbox->Add(mediaControlsHBox, 1, wxEXPAND | wxALL, 20);

	panel->SetSizer(vbox);

	Connect(ID_NEWTAB, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(TemelWx::TabbedPages));

	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(TemelWx::OnQuit));

	Connect(id_openFile, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(TemelWx::LoadMediaFile));

	this->Connect(id_openFile, wxEVT_MEDIA_LOADED, (wxObjectEventFunction)
		      (wxEventFunction)(wxMediaEventFunction) &TemelWx::LoadMediaFile);

	// this->Connect(id_playButton, wxEVT_MEDIA_LOADED, (wxObjectEventFunction)
	// 	      (wxEventFunction)(wxMediaEventFunction) &TemelWx::MediaPlay);

	this->Connect(id_playButton, wxEVT_MEDIA_PLAY, (wxObjectEventFunction)
		      (wxEventFunction)(wxMediaEventFunction) &TemelWx::MediaPlay);

	Connect(id_playButton, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(TemelWx::MediaPlay));

	Connect(id_pauseButton, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(TemelWx::MediaPause));

	Connect(id_stopButton, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(TemelWx::MediaStop));


	Center();
}


void TemelWx::TabbedPages(wxCommandEvent &WXUNUSED(event))
{
	// wxNotebook *parent;
	pnl = new wxPanel(notebook);
	wxBoxSizer *vbs = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbs = new wxBoxSizer(wxHORIZONTAL);
	newTextCtrl = new wxTextCtrl(pnl, id_newTextCtrl, wxT(""), wxPoint(-1, -1), wxSize(-1, -1));
	newGoButton = new wxButton(pnl, ID_NEW_GO_BUTTON, wxT("new button"), wxPoint(-1, -1), wxSize(-1, -1));
	hbs->Add(newTextCtrl, 1, wxEXPAND | wxALL, 20);
	hbs->Add(newGoButton, 1, wxEXPAND | wxALL, 20);
	vbs->Add(hbs, 0, wxEXPAND | wxALL, 20);

	pnl->SetSizer(vbs);

	notebook->AddPage(pnl, wxT("Page"), true, -1);
}


void TemelWx::SetTabWidgets()
{
	if (notebook->GetSelection() > 0) {
		panel = pnl;
		tctrl = newTextCtrl;
		goButton = newGoButton;
	}
	else
	{
		panel = panel;
		tctrl = tctrl;
		goButton = goButton;
	}
}


void TemelWx::RunOnTabs(wxCommandEvent &WXUNUSED(event))
{
	int n = notebook->GetSelection();
	cout << n << endl;
}


void TemelWx::OnQuit(wxCommandEvent &WXUNUSED(event))
{
	Close(true);
}


void TemelWx::LoadMediaFile(wxCommandEvent &WXUNUSED(event))
{
	wxFileDialog *fd = new wxFileDialog(this);
	wxString fileName;
	if (fd->ShowModal() == wxID_OK) {
		fileName = fd->GetPath();
		if (mediaCtrl->Load(fileName) == true) {
			std::cout << "Yüklendi" << std::endl;
		}
	}

	delete fd;
}


void TemelWx::MediaPlay(wxCommandEvent &WXUNUSED(event))
{
	panel->GetHandle();
	mediaCtrl->Play();
}


void TemelWx::MediaPause(wxCommandEvent &WXUNUSED(event))
{
	mediaCtrl->Pause();
}


void TemelWx::MediaStop(wxCommandEvent &WXUNUSED(event))
{
	mediaCtrl->Stop();
}

