
// WeightedRandomAppDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "WeightedRandomApp.h"
#include "WeightedRandomAppDlg.h"
#include "afxdialogex.h"

#include <vector>   // Для хранения данных
#include <random>   // Для случайного выбора
#include <string>   // Для преобразования типов

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CWeightedRandomAppDlg



CWeightedRandomAppDlg::CWeightedRandomAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WEIGHTEDRANDOMAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWeightedRandomAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ITEM_LIST, m_wndListCtrl);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_wndResult);
	DDX_Control(pDX, IDC_ITEM_LIST, m_wndListCtrl);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_wndResult);
}

BEGIN_MESSAGE_MAP(CWeightedRandomAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, &CWeightedRandomAppDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CWeightedRandomAppDlg::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_GET_ITEM, &CWeightedRandomAppDlg::OnBnClickedBtnGetItem)
	ON_NOTIFY(NM_RCLICK, IDC_ITEM_LIST, &CWeightedRandomAppDlg::OnNMRClickItemList)

	//ON_BN_CLICKED(IDC_BTN_ADD, &CWeightedRandomAppDlg::OnBnClickedBtnAdd)
	//ON_BN_CLICKED(IDC_BTN_DELETE, &CWeightedRandomAppDlg::OnBnClickedBtnDelete)
	//ON_BN_CLICKED(IDC_BTN_GET_ITEM, &CWeightedRandomAppDlg::OnBnClickedBtnGetItem)
	//ON_NOTIFY(NM_RCLICK, IDC_ITEM_LIST, &CWeightedRandomAppDlg::OnNMRClickItemList)
	// Новые обработчики
	ON_COMMAND(ID_CONTEXT_ADD, &CWeightedRandomAppDlg::OnContextAdd)
	ON_COMMAND(ID_CONTEXT_DELETE, &CWeightedRandomAppDlg::OnContextDelete)

	// Добавляем новую строку
	ON_EN_KILLFOCUS(IDC_INPLACE_EDIT, &CWeightedRandomAppDlg::OnEnKillFocusInPlaceEdit)

	ON_NOTIFY(NM_CLICK, IDC_ITEM_LIST, &CWeightedRandomAppDlg::OnNMClickItemList)
END_MESSAGE_MAP()

// Обработчики сообщений CWeightedRandomAppDlg

BOOL CWeightedRandomAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	////////////////////////////////////////////////////////////////////////////////////////////////

	// Настройка расширенных стилей для List Control
	// LVS_EX_CHECKBOXES добавит флажки в каждую строку
	// LVS_EX_FULLROWSELECT для выделения всей строки
	// LVS_EX_GRIDLINES для сетки
	m_wndListCtrl.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Добавляем колонки в таблицу
	m_wndListCtrl.InsertColumn(0, _T("#"), LVCFMT_LEFT, 30);
	m_wndListCtrl.InsertColumn(1, _T("Наименование"), LVCFMT_LEFT, 200);
	m_wndListCtrl.InsertColumn(2, _T("Вес"), LVCFMT_LEFT, 80);
	// Четвертая колонка не нужна, т.к. флажок является частью первой колонки.
	// Но мы можем добавить заголовок для ясности, хотя он будет пустым.
	// Для простоты мы просто будем считать, что флажок - это и есть 4-я колонка.

	// Добавим несколько строк для примера
	AddNewItemToList(_T("Меч"), 10.0, true);
	AddNewItemToList(_T("Щит"), 10.0, true);
	AddNewItemToList(_T("Зелье здоровья"), 5.0, true);
	AddNewItemToList(_T("Сломанный кинжал"), 1.0, false);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CWeightedRandomAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CWeightedRandomAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CWeightedRandomAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWeightedRandomAppDlg::AddNewItemToList(const CString& name, double weight, bool isActive)
{
	int nIndex = m_wndListCtrl.GetItemCount();

	// Вставляем новую строку. Номер пока временный.
	m_wndListCtrl.InsertItem(nIndex, _T(""));

	// Устанавливаем значения для подколонок
	m_wndListCtrl.SetItemText(nIndex, 1, name);

	CString strWeight;
	strWeight.Format(_T("%.2f"), weight); // Форматируем вес до 2 знаков после запятой
	m_wndListCtrl.SetItemText(nIndex, 2, strWeight);

	// Устанавливаем состояние флажка (активность)
	m_wndListCtrl.SetCheck(nIndex, isActive ? BST_CHECKED : BST_UNCHECKED);

	// Перенумеровываем все строки
	RenumberItems();
}

void CWeightedRandomAppDlg::RenumberItems()
{
	int count = m_wndListCtrl.GetItemCount();
	for (int i = 0; i < count; ++i)
	{
		CString strNumber;
		strNumber.Format(_T("%d"), i + 1);
		m_wndListCtrl.SetItemText(i, 0, strNumber);
	}
}


void CWeightedRandomAppDlg::OnBnClickedBtnAdd()
{
	// Для простоты примера, добавляем предопределенную строку.
	// В реальном приложении здесь был бы вызов диалога для ввода данных.
	AddNewItemToList(_T("Новый предмет"), 5.0, true);
}

void CWeightedRandomAppDlg::OnBnClickedBtnDelete()
{
	// Получаем индекс выделенной строки
	POSITION pos = m_wndListCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Пожалуйста, выберите строку для удаления."), _T("Ошибка"), MB_OK | MB_ICONWARNING);
		return;
	}

	int nItem = m_wndListCtrl.GetNextSelectedItem(pos);

	// Удаляем строку
	m_wndListCtrl.DeleteItem(nItem);

	// После удаления нужно перенумеровать оставшиеся строки
	RenumberItems();
}

void CWeightedRandomAppDlg::OnBnClickedBtnGetItem()
{
	// Структура для хранения данных активных предметов
	struct ItemData
	{
		CString name;
		double weight;
	};

	std::vector<ItemData> activeItems;
	double totalWeight = 0.0;

	// 1. Собрать все активные предметы и их веса
	int count = m_wndListCtrl.GetItemCount();
	for (int i = 0; i < count; ++i)
	{
		// Проверяем, активна ли строка (установлен ли флажок)
		if (m_wndListCtrl.GetCheck(i) == BST_CHECKED)
		{
			CString name = m_wndListCtrl.GetItemText(i, 1);
			CString strWeight = m_wndListCtrl.GetItemText(i, 2);

			// Преобразуем CString в double
			double weight = _ttof(strWeight);

			if (weight > 0)
			{
				activeItems.push_back({ name, weight });
				totalWeight += weight;
			}
		}
	}

	// 2. Проверить, есть ли из чего выбирать
	if (activeItems.empty() || totalWeight <= 0)
	{
		m_wndResult.SetWindowTextW(_T("Нет активных предметов для выбора."));
		return;
	}

	// 3. Выполнить взвешенный случайный выбор
	// Инициализация генератора случайных чисел
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, totalWeight);

	double randomValue = dis(gen);

	CString selectedName = _T("Ошибка выбора");

	// 4. Найти предмет, на который выпало случайное число
	double currentWeightSum = 0.0;
	for (const auto& item : activeItems)
	{
		currentWeightSum += item.weight;
		if (randomValue <= currentWeightSum)
		{
			selectedName = item.name;
			break;
		}
	}

	// 5. Вывести результат
	m_wndResult.SetWindowTextW(selectedName);
}

void CWeightedRandomAppDlg::OnNMRClickItemList(NMHDR* pNMHDR, LRESULT* pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//// TODO: добавьте свой код обработчика уведомлений
	//*pResult = 0;
	////////////////////////////////////////////////////////////////////////////////////
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	CMenu menu;
	menu.CreatePopupMenu(); // Создаем всплывающее меню

	// Проверяем, есть ли выделенный элемент, чтобы сделать пункт "Удалить" активным/неактивным
	UINT deleteFlag = (m_wndListCtrl.GetFirstSelectedItemPosition() == NULL) ? MF_GRAYED : MF_ENABLED;

	// Добавляем пункты в меню
	menu.AppendMenu(MF_STRING, ID_CONTEXT_ADD, _T("Добавить строку"));
	menu.AppendMenu(MF_STRING | deleteFlag, ID_CONTEXT_DELETE, _T("Удалить выделенную строку"));

	// Получаем позицию курсора и отображаем меню
	CPoint pt;
	GetCursorPos(&pt);
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	*pResult = 0;
}

// в CWeightedRandomAppDlg.cpp
void CWeightedRandomAppDlg::OnContextAdd()
{
	// Просто вызываем тот же код, что и для кнопки
	OnBnClickedBtnAdd();
}

void CWeightedRandomAppDlg::OnContextDelete()
{
	// Просто вызываем тот же код, что и для кнопки
	OnBnClickedBtnDelete();
}

void CWeightedRandomAppDlg::OnEnKillFocusInPlaceEdit()
{
	CString strNewText;
	m_editInPlace.GetWindowText(strNewText);

	// Обновляем текст в таблице
	m_wndListCtrl.SetItemText(m_nEditItem, m_nEditSubItem, strNewText);

	// Прячем поле ввода
	m_editInPlace.ShowWindow(SW_HIDE);
}

void CWeightedRandomAppDlg::OnNMClickItemList(NMHDR* pNMHDR, LRESULT* pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//// TODO: добавьте свой код обработчика уведомлений
	//*pResult = 0;

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// Определяем, по какой строке и колонке был клик
	LVHITTESTINFO hitTestInfo;
	hitTestInfo.pt = pNMItemActivate->ptAction; // Координаты клика
	m_wndListCtrl.SubItemHitTest(&hitTestInfo);

	int nItem = hitTestInfo.iItem;
	int nSubItem = hitTestInfo.iSubItem;

	// Разрешаем редактировать только колонки 1 ("Наименование") и 2 ("Вес")
	if (nItem != -1 && (nSubItem == 1 || nSubItem == 2))
	{
		ShowInPlaceEdit(nItem, nSubItem);
	}

	*pResult = 0;
}

BOOL CWeightedRandomAppDlg::PreTranslateMessage(MSG* pMsg)
{
	// Проверяем, что это сообщение о нажатии клавиши и оно пришло от нашего поля ввода
	if (pMsg->message == WM_KEYDOWN && pMsg->hwnd == m_editInPlace.GetSafeHwnd())
	{
		if (pMsg->wParam == VK_RETURN) // Нажат Enter
		{
			// Вызываем обработчик потери фокуса, который сохранит данные
			OnEnKillFocusInPlaceEdit();
			return TRUE; // Сообщение обработано, дальше не передавать
		}
		else if (pMsg->wParam == VK_ESCAPE) // Нажат Escape
		{
			// Просто прячем поле без сохранения
			m_editInPlace.ShowWindow(SW_HIDE);
			return TRUE; // Сообщение обработано
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CWeightedRandomAppDlg::ShowInPlaceEdit(int nItem, int nSubItem)
{
	// Если поле ввода уже видимо, сначала спрячем его
	if (m_editInPlace.GetSafeHwnd())
	{
		m_editInPlace.ShowWindow(SW_HIDE);
	}

	m_nEditItem = nItem;
	m_nEditSubItem = nSubItem;

	// Получаем геометрию ячейки
	CRect rectSubItem;
	m_wndListCtrl.GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rectSubItem);

	// Получаем текущий текст ячейки
	CString strText = m_wndListCtrl.GetItemText(nItem, nSubItem);

	// Если поле ввода еще не создано, создаем его
	if (!m_editInPlace.GetSafeHwnd())
	{
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL;
		// Для колонки "Вес" можно добавить стиль ES_NUMBER, чтобы разрешить ввод только цифр
		if (nSubItem == 2) {
			dwStyle |= ES_NUMBER;
		}
		m_editInPlace.Create(dwStyle, rectSubItem, &m_wndListCtrl, IDC_INPLACE_EDIT);
		m_editInPlace.SetFont(m_wndListCtrl.GetFont());
	}
	else
	{
		// Если уже создано, просто перемещаем и меняем размер
		m_editInPlace.MoveWindow(&rectSubItem);
	}

	m_editInPlace.SetWindowText(strText);
	m_editInPlace.ShowWindow(SW_SHOW);
	m_editInPlace.SetFocus();
	m_editInPlace.SetSel(0, -1); // Выделить весь текст
}
