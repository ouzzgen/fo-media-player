#ifndef ORTAM_YURUTUCU_H 
#define ORTAM_YURUTUCU_H 

#include <wx/wx.h>
#include <wx/protocol/ftp.h>
#include <wx/wxprec.h>
#include <wx/window.h>
#include <wx/notebook.h>
#include <wx/menu.h>
#include <wx/html/htmlwin.h>
#include <wx/webview.h>
#include <wx/event.h>
#include <wx/url.h>
#include <wx/mediactrl.h>
#include <stdio.h>
#include <iostream>

class TemelWx : public wxFrame
{
    public:
        TemelWx(const wxString &title);
        wxWindow *mainWin;
        wxWindow *window;
        wxNotebook *notebook;
        wxMenuBar *menubar;
        wxMenu *fileMenu;
        wxMenu *editMenu;
        wxMenu *historyMenu;
        wxMenu *lastTabs;
        wxMenu *toolsMenu;
        wxMenu *helpMenu;
        wxMenu *karalama;
        wxMenuItem *kar;
        wxMenuItem *openFile;
        wxPanel *panel, *pnl;
        wxBoxSizer *vbox, *toolbarhbox, *mediaControlsHBox;
        
        
        wxTextCtrl *tctrl, *newTextCtrl;
        wxButton *goButton, *newGoButton;
        wxButton *playButton, *pauseButton, *stopButton;
        
        wxMediaCtrl *mediaCtrl;
        


        wxMenuItem *newTab, *loadUrlVal, *editPageItem, *cutItem, *copyItem, *pasteItem;
        wxMenuItem *quit;
        


        void TabbedPages(wxCommandEvent &event);
        void SetTabWidgets();
        void RunOnTabs(wxCommandEvent &event);
        void OnQuit(wxCommandEvent &event);

        void LoadMediaFile(wxCommandEvent &event);
        void MediaPlay(wxCommandEvent &event);
        void MediaPause(wxCommandEvent &event);
        void MediaStop(wxCommandEvent &event);


        const int ID_TOOLS_MENU = 10;
        const int ID_GO_BUTTON = 3;
        const int ID_NEWTAB = 4;
        const int id_openFile = 11;
        const int ID_LAST_TABS = 5;
        const int ID_NEW_GO_BUTTON = 6;
        const int id_playButton = 7;
        const int id_pauseButton = 8;
        const int id_stopButton = 9;
        const int id_textCtrl = 1;
        const int id_newTextCtrl = 2;
        const int id_editPageItem = 20;
        const int id_editCheckItem = 21; 
        const int id_context_menu = 30;

        const int id_mediaCtrl = 33;

    private : 
        DECLARE_EVENT_TABLE();    
};

#endif // ORTAM_YURUTUCU_H

