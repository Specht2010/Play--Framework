#include "win32/ListView.h"

using namespace Framework::Win32;

CListView::CListView(HWND hWnd)
{
	m_hWnd = hWnd;
}

CListView::CListView(HWND hParent, RECT* pR, unsigned long nStyle, unsigned long nExStyle)
{
	InitCommonControls();
	Create(nExStyle, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | nStyle, pR, hParent, NULL);
}

CListView::~CListView()
{

}

int CListView::GetItemCount()
{
	return ListView_GetItemCount(m_hWnd);
}

int CListView::FindItemData(unsigned long nData)
{
	LVFINDINFO info;
	memset(&info, 0, sizeof(LVFINDINFO));

	info.flags	= LVFI_PARAM;
	info.lParam = nData;

	return ListView_FindItem(m_hWnd, -1, &info);
}

void CListView::DeleteItem(unsigned int itemIdx)
{
	ListView_DeleteItem(m_hWnd, itemIdx);
}

void CListView::DeleteAllItems()
{
	ListView_DeleteAllItems(m_hWnd);
}

int CListView::InsertItem(LVITEM* pI)
{
	return ListView_InsertItem(m_hWnd, pI);
}

int CListView::InsertItem(const LVITEM& Item)
{
	return InsertItem(const_cast<LVITEM*>(&Item));
}

void CListView::SetColumnWidth(unsigned int nCol, unsigned int nCX)
{
	ListView_SetColumnWidth(m_hWnd, nCol, nCX);
}

void CListView::InsertColumn(unsigned int nCol, LVCOLUMN* pC)
{
	ListView_InsertColumn(m_hWnd, nCol, pC);
}

void CListView::GetItemText(unsigned int nItem, unsigned int nSubItem, TCHAR* sText, unsigned int nCount)
{
	ListView_GetItemText(m_hWnd, nItem, nSubItem, sText, nCount);
}

unsigned long CListView::GetItemData(unsigned int nItem)
{
	LVITEM it;
	memset(&it, 0, sizeof(LVITEM));
	it.iItem	= nItem;
	it.mask		= LVIF_PARAM;

	ListView_GetItem(m_hWnd, &it);

	return (unsigned long)it.lParam;
}

void CListView::SetItemText(unsigned int nItem, unsigned int nSubItem, const TCHAR* sText)
{
	ListView_SetItemText(m_hWnd, nItem, nSubItem, const_cast<TCHAR*>(sText));
}

void CListView::SetItemState(unsigned int itemIdx, unsigned int state, unsigned int mask)
{
	ListView_SetItemState(m_hWnd, itemIdx, state, mask);
}

int CListView::GetSelection()
{
	return ListView_GetSelectionMark(m_hWnd);
}

void CListView::SetSelection(int nIndex)
{
	ListView_SetSelectionMark(m_hWnd, nIndex);
}

void CListView::EnableGroupView(bool enabled)
{
	ListView_EnableGroupView(m_hWnd, enabled);
}

int CListView::InsertGroup(const TCHAR* name, unsigned int id, unsigned int index)
{
	LVGROUP group;
	memset(&group, 0, sizeof(group));
	group.cbSize		= sizeof(LVGROUP);
	group.mask			= LVGF_HEADER | LVGF_GROUPID;
	group.pszHeader		= const_cast<TCHAR*>(name);
	group.iGroupId		= id;
	return ListView_InsertGroup(m_hWnd, index, &group);
}

void CListView::RemoveAllGroups()
{
	ListView_RemoveAllGroups(m_hWnd);
}

void CListView::SetExtendedListViewStyle(unsigned long nStyle)
{
	ListView_SetExtendedListViewStyle(m_hWnd, nStyle);
}

unsigned long CListView::GetExtendedListViewStyle()
{
	return ListView_GetExtendedListViewStyle(m_hWnd);
}

void CListView::SetItemCount(int nCount)
{
	ListView_SetItemCount(m_hWnd, nCount);
}

void CListView::EnsureItemVisible(unsigned int nItem, bool nPartialOk)
{
	ListView_EnsureVisible(m_hWnd, nItem, nPartialOk);
}

void CListView::ProcessGetDisplayInfo(NMHDR* pHdr, const GetDispInfoCallbackType& Callback)
{
	if(pHdr->code != LVN_GETDISPINFO) return;
	if(pHdr->hwndFrom != m_hWnd) return;

	LV_DISPINFO* pDispInfo = reinterpret_cast<LV_DISPINFO*>(pHdr);
	Callback(&pDispInfo->item);
}

HWND CListView::GetHeader()
{
	return ListView_GetHeader(m_hWnd);
}

//////////////////////////////////////
//CItem implementation
//////////////////////////////////////

CListView::CItem::CItem(const TCHAR* sText)
{
	memset(&m_Item, 0, sizeof(LVITEM));
	SetText(sText);
}

CListView::CItem::~CItem()
{

}

void CListView::CItem::SetText(const TCHAR* sText)
{
	m_Item.mask |= LVIF_TEXT;
	m_Item.pszText = const_cast<TCHAR*>(sText);
}

void CListView::CItem::SetParam(LPARAM lParam)
{
	m_Item.mask |= LVIF_PARAM;
	m_Item.lParam = lParam;
}

CListView::CItem::operator const LVITEMW&() const
{
	return m_Item;
}
