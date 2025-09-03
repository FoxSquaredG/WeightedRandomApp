
// WeightedRandomApp.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CWeightedRandomAppApp:
// Сведения о реализации этого класса: WeightedRandomApp.cpp
//

class CWeightedRandomAppApp : public CWinApp
{
public:
	CWeightedRandomAppApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CWeightedRandomAppApp theApp;
