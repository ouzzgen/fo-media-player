#include "main.h"
#include "ortam_yurutucu.h"

IMPLEMENT_APP(TemelBaslangic)


bool TemelBaslangic::OnInit()
{
    TemelWx *temel = new TemelWx(wxT("Temel"));
    temel->Show(true);
}


