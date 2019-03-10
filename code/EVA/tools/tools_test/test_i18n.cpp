#include "test_misc.h"
#include <string>
#include <iostream>

// contains all i18n features
#include <server_share/i18n_def.h>

// contains the path features
#include "nel/misc/path.h"

using namespace std;
using namespace NLMISC;

void test_i18n()
{
    cout<<"---------------  test_i18n ----------------"<<endl;
    CPath::addSearchPath("./i18n");

    CI18N::load("cn");

    InfoLog->displayRawNL( I18N::GetStr("LanguageName") );
    InfoLog->displayRawNL( I18N::Format(I18N::GetStr("PresentI18N"), "Nevrax").c_str() );
    InfoLog->displayRawNL( I18N::GetStr("ExitStr") );

}

