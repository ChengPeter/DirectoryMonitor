// FileVersion.h: interface for the CFileVersion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEVERSION_H__0100D74C_87A6_4EA1_8568_CBE1D7689208__INCLUDED_)
#define AFX_FILEVERSION_H__0100D74C_87A6_4EA1_8568_CBE1D7689208__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileVersion  
{
// Construction  
public:   
    CFileVersion();  
	// Operations     
public:   
    BOOL    Open(LPCTSTR lpszModuleName);  
    void    Close();  
    CString QueryValue(LPCTSTR lpszValueName, DWORD dwLangCharset = 0);  
    CString GetFileDescription()  {return QueryValue(_T("FileDescription")); };  
    CString GetFileVersion()      {return QueryValue(_T("FileVersion"));     };  
    CString GetInternalName()     {return QueryValue(_T("InternalName"));    };  
    CString GetCompanyName()      {return QueryValue(_T("CompanyName"));     };   
    CString GetLegalCopyright()   {return QueryValue(_T("LegalCopyright"));  };  
    CString GetOriginalFilename() {return QueryValue(_T("OriginalFilename"));};  
    CString GetProductName()      {return QueryValue(_T("ProductName"));     };  
    CString GetProductVersion()   {return QueryValue(_T("ProductVersion"));  };  
	CString GetComments()         {return QueryValue(_T("Comments"));  };  
    BOOL    GetFixedInfo(VS_FIXEDFILEINFO& vsffi);  
    CString GetFixedFileVersion();  
    CString GetFixedProductVersion();  
	// Attributes  
protected:  
    LPBYTE  m_lpVersionData;   
    DWORD   m_dwLangCharset;   
	// Implementation  
public:  
    ~CFileVersion(); 

};

#endif // !defined(AFX_FILEVERSION_H__0100D74C_87A6_4EA1_8568_CBE1D7689208__INCLUDED_)
