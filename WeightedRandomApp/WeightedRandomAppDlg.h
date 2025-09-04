
// WeightedRandomAppDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CWeightedRandomAppDlg
class CWeightedRandomAppDlg : public CDialogEx
{
// Создание
public:
	CWeightedRandomAppDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEIGHTEDRANDOMAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnContextAdd();
	afx_msg void OnContextDelete();

	afx_msg void OnEnKillFocusInPlaceEdit();

	//menu
	afx_msg void OnFileReset();
	afx_msg void OnFileExit();
	afx_msg void OnHelpAbout();

	DECLARE_MESSAGE_MAP()

private:
	void AddNewItemToList(const CString& name, double weight, bool isActive);
	void RenumberItems(); // Функция для перенумерации строк

	CEdit m_editInPlace;   // Наше поле для редактирования
	int m_nEditItem;       // Индекс строки, которую редактируем
	int m_nEditSubItem;    // Индекс колонки, которую редактируем

	// Вспомогательная функция для показа поля редактирования
	void ShowInPlaceEdit(int nItem, int nSubItem);

	void ResetList();

public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnGetItem();
	afx_msg void OnNMRClickItemList(NMHDR* pNMHDR, LRESULT* pResult);

	CListCtrl m_wndListCtrl;
	CStatic m_wndResult;
	afx_msg void OnNMClickItemList(NMHDR* pNMHDR, LRESULT* pResult);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
